#!/usr/bin/env python3
"""生成済みリファレンスから Jekyll のソースツリーを組み立てる。

ページの中身は `tools/reference_docs.py build` が作る `docs/generated/` に
あり、ここでやるのは「サイトとしての体裁」だけである。

* カテゴリ → ヘッダ → 型/関数 のナビゲーション
* 依存関係・検証結果・実装全文（ヘッダページの下部）
* 検証プログラムのページ
* トップページと検索インデックス

verify_files.json / result.json が無い環境（ローカル）でも見た目を確認できる
よう、`--offline` で `#include` を辿った簡易版を合成する。
"""

from __future__ import annotations

import argparse
import datetime as dt
import json
import os
import re
import shutil
import subprocess
import sys
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_DOCS_DIR = ROOT / ".verify-helper" / "docs"
DEFAULT_GENERATED_DIR = ROOT / "docs" / "generated"
FRONT_MATTER_RE = re.compile(r"\A---\s*\n(.*?)\n---\s*\n", re.DOTALL)
MARKDOWN_LINK_RE = re.compile(r"\]\(([^)\s]+?)\.md(#[^)]*)?\)")
INCLUDE_RE = re.compile(r'^\s*#include\s+"([^"]+)"', re.MULTILINE)
PROBLEM_RE = re.compile(r"competitive-verifier:\s*PROBLEM\s+(\S+)")

LIBRARY_ALL_AC = "LIBRARY_ALL_AC"
LIBRARY_PARTIAL_AC = "LIBRARY_PARTIAL_AC"
LIBRARY_SOME_WA = "LIBRARY_SOME_WA"
LIBRARY_ALL_WA = "LIBRARY_ALL_WA"
LIBRARY_NO_TESTS = "LIBRARY_NO_TESTS"
TEST_ACCEPTED = "TEST_ACCEPTED"
TEST_WRONG_ANSWER = "TEST_WRONG_ANSWER"
TEST_WAITING_JUDGE = "TEST_WAITING_JUDGE"


@dataclass(frozen=True)
class ReferencePage:
    """`docs/generated/` の 1 ページ。"""

    relative_path: str
    front_matter: dict[str, str]
    content: str

    @property
    def url(self) -> str:
        return "reference/" + self.relative_path.removesuffix(".md") + ".html"

    @property
    def kind(self) -> str:
        return self.front_matter.get("reference_kind", "")

    @property
    def source(self) -> str:
        return self.front_matter.get("reference_source", "")

    @property
    def title(self) -> str:
        return self.front_matter.get("title", self.relative_path)


def fail(message: str) -> None:
    raise ValueError(message)


def load_json_object(path: Path, *, label: str) -> dict[str, Any]:
    try:
        value = json.loads(path.read_text(encoding="utf-8"))
    except FileNotFoundError:
        fail(f"{label} が見つかりません: {path}")
    except json.JSONDecodeError as error:
        fail(f"{label} が正しいJSONではありません: {path}: {error}")
    if not isinstance(value, dict):
        fail(f"{label} のルートはオブジェクトである必要があります: {path}")
    files = value.get("files")
    if not isinstance(files, dict):
        fail(f"{label} に files オブジェクトがありません: {path}")
    return value


def parse_front_matter(text: str) -> tuple[dict[str, str], str]:
    match = FRONT_MATTER_RE.match(text)
    if match is None:
        return {}, text
    values: dict[str, str] = {}
    for line in match.group(1).splitlines():
        if ":" not in line or line[:1].isspace():
            continue
        key, value = line.split(":", 1)
        value = value.strip()
        if value.startswith(('"', "'")):
            try:
                value = json.loads(value)
            except json.JSONDecodeError:
                value = value.strip("\"'")
        values[key.strip()] = value
    return values, text[match.end() :]


def load_reference_pages(generated: Path) -> list[ReferencePage]:
    if not generated.is_dir():
        fail(
            f"生成済みリファレンスがありません: {generated}"
            "（先に python3 tools/reference_docs.py build を実行してください）"
        )
    pages: list[ReferencePage] = []
    for path in sorted(generated.glob("**/*.md")):
        relative = path.relative_to(generated).as_posix()
        if relative == "index.md":
            continue
        front_matter, content = parse_front_matter(path.read_text(encoding="utf-8"))
        pages.append(ReferencePage(relative, front_matter, content))
    if not pages:
        fail(f"生成済みリファレンスが空です: {generated}")
    return pages


def rewrite_links(content: str) -> str:
    """生成物の `.md` リンクを公開時の `.html` へ差し替える。"""
    return MARKDOWN_LINK_RE.sub(lambda m: f"]({m.group(1)}.html{m.group(2) or ''})", content)


def is_verification_file(path: str, file_input: dict[str, Any]) -> bool:
    verification = file_input.get("verification", [])
    return path.startswith("test/") or (
        isinstance(verification, list) and bool(verification)
    )


def result_flags(result_file: Any) -> frozenset[str]:
    if not isinstance(result_file, dict):
        return frozenset()
    verifications = result_file.get("verifications", [])
    if not isinstance(verifications, list):
        return frozenset()
    return frozenset(
        item.get("status")
        for item in verifications
        if isinstance(item, dict) and isinstance(item.get("status"), str)
    )


def test_icon(flags: frozenset[str]) -> str:
    if "failure" in flags:
        return TEST_WRONG_ANSWER
    if "skipped" in flags or "success" not in flags:
        return TEST_WAITING_JUDGE
    return TEST_ACCEPTED


def library_icon(flags: frozenset[str]) -> str:
    if "failure" in flags:
        return LIBRARY_SOME_WA if "success" in flags else LIBRARY_ALL_WA
    if "success" in flags:
        return LIBRARY_PARTIAL_AC if "skipped" in flags else LIBRARY_ALL_AC
    return LIBRARY_NO_TESTS


def get_git_timestamps(root: Path) -> tuple[dict[str, dt.datetime], dt.datetime]:
    command = [
        "git",
        "log",
        "--format=__REFERENCE_COMMIT__%aI",
        "--name-only",
        "--no-renames",
        "--",
    ]
    result = subprocess.run(
        command, cwd=root, text=True, capture_output=True, check=False
    )
    if result.returncode != 0:
        return {}, dt.datetime.now(tz=dt.UTC)

    timestamps: dict[str, dt.datetime] = {}
    current: dt.datetime | None = None
    newest: dt.datetime | None = None
    for line in result.stdout.splitlines():
        if line.startswith("__REFERENCE_COMMIT__"):
            raw = line.removeprefix("__REFERENCE_COMMIT__")
            current = dt.datetime.fromisoformat(raw)
            newest = max(newest, current) if newest else current
        elif line and current is not None:
            timestamps.setdefault(line, current)

    fallback = newest or dt.datetime.now(tz=dt.UTC)
    return timestamps, fallback


def latest_timestamp(
    path: str,
    dependencies: set[str],
    timestamps: dict[str, dt.datetime],
    fallback: dt.datetime,
) -> str:
    values = [timestamps[item] for item in dependencies | {path} if item in timestamps]
    return max(values, default=fallback).isoformat()


def dump_front_matter(values: dict[str, Any]) -> str:
    lines = ["---"]
    for key, value in values.items():
        if value is None:
            continue
        if isinstance(value, str):
            lines.append(f"{key}: {json.dumps(value, ensure_ascii=False)}")
        else:
            lines.append(
                f"{key}: "
                + json.dumps(value, ensure_ascii=False, separators=(",", ":"), sort_keys=True)
            )
    lines.extend(["---", ""])
    return "\n".join(lines)


def page_attributes(file_input: dict[str, Any]) -> dict[str, Any]:
    raw = file_input.get("document_attributes", {})
    attributes = dict(raw) if isinstance(raw, dict) else {}
    links = attributes.get("links")
    if not isinstance(links, list):
        attributes["links"] = []
    verification = file_input.get("verification", [])
    if isinstance(verification, list):
        for item in verification:
            if not isinstance(item, dict):
                continue
            problem = item.get("problem")
            if isinstance(problem, str) and problem:
                attributes.setdefault("PROBLEM", problem)
                break
    return attributes


def embedded_code(root: Path, path: str, file_input: dict[str, Any]) -> list[dict[str, str]]:
    embedded: list[dict[str, str]] = [
        {"name": "default", "code": (root / path).read_text(encoding="utf-8")}
    ]
    additional = file_input.get("additonal_sources", [])
    if not isinstance(additional, list):
        return embedded
    for item in additional:
        if not isinstance(item, dict):
            continue
        source = item.get("path")
        if not isinstance(source, str):
            continue
        name = str(item.get("name") or source)
        # competitive-verifier の bundler はリポジトリ直下からしか探さず、
        # コンパイラの include パスを見ない。lib/ 起点の include を使う都合上、
        # bundle error はリファレンスとして意味がないので落とす。
        if name == "bundle error":
            continue
        source_path = root / source
        if not source_path.is_file():
            continue
        embedded.append({"name": name, "code": source_path.read_text(encoding="utf-8")})
    return embedded


def synthesize_verify_input(root: Path) -> tuple[dict[str, Any], dict[str, Any]]:
    """検証結果なしで見た目を確認するための簡易 verify_files。"""
    files: dict[str, Any] = {}
    sources = [
        *sorted((root / "lib").glob("**/*.hpp")),
        *sorted((root / "test").glob("**/*.test.cpp")),
    ]
    for path in sources:
        relative = path.relative_to(root).as_posix()
        content = path.read_text(encoding="utf-8")
        dependencies = []
        for include in INCLUDE_RE.findall(content):
            candidate = (root / "lib" / include).as_posix()
            if Path(candidate).is_file():
                dependencies.append(Path(candidate).relative_to(root).as_posix())
        attributes: dict[str, Any] = {"links": []}
        problem = PROBLEM_RE.search(content)
        entry: dict[str, Any] = {
            "dependencies": dependencies,
            "document_attributes": attributes,
        }
        if problem is not None:
            attributes["PROBLEM"] = problem.group(1)
            entry["verification"] = [{"type": "problem", "problem": problem.group(1)}]
        files[relative] = entry
    return {"files": files}, {"files": {}}


def write_config(docs_dir: Path, destination: Path) -> None:
    source = docs_dir / "_config.yml"
    content = source.read_text(encoding="utf-8") if source.is_file() else ""
    generated = """
# Generated by tools/render_reference_site.py.
icons:
  LIBRARY_ALL_AC: "✅"
  LIBRARY_PARTIAL_AC: "☑️"
  LIBRARY_SOME_WA: "⚠️"
  LIBRARY_ALL_WA: "❌"
  LIBRARY_NO_TESTS: "➖"
  TEST_ACCEPTED: "✅"
  TEST_WRONG_ANSWER: "❌"
  TEST_WAITING_JUDGE: "⏳"
icon_labels:
  LIBRARY_ALL_AC: "検証済み"
  LIBRARY_PARTIAL_AC: "一部検証"
  LIBRARY_SOME_WA: "一部失敗"
  LIBRARY_ALL_WA: "失敗"
  LIBRARY_NO_TESTS: "未検証"
  TEST_ACCEPTED: "AC"
  TEST_WRONG_ANSWER: "WA"
  TEST_WAITING_JUDGE: "判定待ち"
"""
    (destination / "_config.yml").write_text(
        content.rstrip() + "\n" + generated, encoding="utf-8"
    )


def copy_plain_markdown(root: Path, destination: Path) -> None:
    """`docs/` 直下の手書きページ（執筆ガイドなど）をそのまま載せる。"""
    for source in sorted((root / "docs").glob("**/*.md")):
        relative = source.relative_to(root)
        if relative.parts[1] == "generated":
            continue
        front_matter, content = parse_front_matter(source.read_text(encoding="utf-8"))
        target = destination / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(
            dump_front_matter(
                {"layout": "page", "title": front_matter.get("title", source.stem)}
            )
            + content,
            encoding="utf-8",
        )


def build_site(
    *,
    root: Path,
    docs_dir: Path,
    generated_dir: Path,
    destination: Path,
    verify_files_path: Path | None,
    verify_result_path: Path | None,
) -> tuple[int, int]:
    if verify_files_path is None or verify_result_path is None:
        verify_input, verify_result = synthesize_verify_input(root)
    else:
        verify_input = load_json_object(verify_files_path, label="verify_files")
        verify_result = load_json_object(verify_result_path, label="verify_result")
    raw_files = verify_input["files"]
    raw_results = verify_result["files"]

    files: dict[str, dict[str, Any]] = {}
    for path, value in raw_files.items():
        if not isinstance(path, str) or not isinstance(value, dict):
            fail("verify_files.files はパスからオブジェクトへの対応である必要があります")
        if (root / path).is_file():
            files[path] = value

    reference_pages = load_reference_pages(generated_dir)
    reference_index = json.loads(
        (generated_dir / "reference.json").read_text(encoding="utf-8")
    )
    header_pages = {
        page.source: page for page in reference_pages if page.kind == "header"
    }
    missing = sorted(set(header_pages) - set(files))
    if missing:
        fail(
            "リファレンスの対象が verify_files にありません:\n  - " + "\n  - ".join(missing)
        )

    test_files = {
        path for path, file_input in files.items() if is_verification_file(path, file_input)
    }
    library_files = set(files) - test_files
    dependencies: dict[str, set[str]] = {}
    required_by: dict[str, set[str]] = defaultdict(set)
    verified_with: dict[str, set[str]] = defaultdict(set)
    for path, file_input in files.items():
        raw_dependencies = file_input.get("dependencies", [])
        if not isinstance(raw_dependencies, list):
            fail(f"{path}: dependencies は配列である必要があります")
        deps = {
            item
            for item in raw_dependencies
            if isinstance(item, str) and item in files and item != path
        }
        dependencies[path] = deps
        for dependency in deps:
            if path in test_files:
                verified_with[dependency].add(path)
            else:
                required_by[dependency].add(path)

    flags = {path: result_flags(raw_results.get(path)) for path in test_files}
    icons: dict[str, str] = {path: test_icon(flags[path]) for path in test_files}
    for path in library_files:
        aggregate: set[str] = set()
        for test in verified_with[path]:
            aggregate.update(flags[test])
        icons[path] = library_icon(frozenset(aggregate))

    def url_for(path: str) -> str:
        page = header_pages.get(path)
        if page is not None:
            return page.url
        return f"{path}.html"

    def title_for(path: str) -> str:
        page = header_pages.get(path)
        if page is not None:
            return page.title
        attributes = files.get(path, {}).get("document_attributes", {})
        if isinstance(attributes, dict):
            title = attributes.get("document_title")
            if isinstance(title, str) and title:
                return title
        return path

    def links(paths: set[str]) -> list[dict[str, str]]:
        return [
            {
                "path": item,
                "url": url_for(item),
                "icon": icons.get(item, LIBRARY_NO_TESTS),
                "title": title_for(item),
            }
            for item in sorted(paths, key=str.casefold)
        ]

    if destination.exists():
        shutil.rmtree(destination)
    destination.mkdir(parents=True)
    write_config(docs_dir, destination)
    static_dir = docs_dir / "static"
    if static_dir.is_dir():
        shutil.copytree(static_dir, destination, dirs_exist_ok=True)

    timestamps, fallback_timestamp = get_git_timestamps(root)

    for category in reference_index["categories"]:
        for header in category["headers"]:
            source = f"lib/{header['include']}"
            header["icon"] = icons.get(source, LIBRARY_NO_TESTS)
    data_dir = destination / "_data"
    data_dir.mkdir(parents=True, exist_ok=True)
    (data_dir / "reference.json").write_text(
        json.dumps(
            {"categories": reference_index["categories"]},
            ensure_ascii=False,
            separators=(",", ":"),
        ),
        encoding="utf-8",
    )
    assets_dir = destination / "assets"
    assets_dir.mkdir(parents=True, exist_ok=True)
    (assets_dir / "reference-index.json").write_text(
        json.dumps(reference_index["entries"], ensure_ascii=False, separators=(",", ":")),
        encoding="utf-8",
    )

    for page in reference_pages:
        source = page.source
        slug = page.front_matter.get("reference_slug", "")
        data: dict[str, Any] = {
            "kind": page.kind,
            "category": page.front_matter.get("reference_category", ""),
            "slug": slug,
            "stem": slug.rpartition("/")[2],
            "pageUrl": page.relative_path.removesuffix(".md") + ".html",
            "include": page.front_matter.get("reference_include", ""),
            "entity": page.front_matter.get("reference_entity", ""),
            "source": source,
        }
        if page.kind == "header" and source in files:
            data.update(
                {
                    "icon": icons.get(source, LIBRARY_NO_TESTS),
                    "timestamp": latest_timestamp(
                        source, dependencies[source], timestamps, fallback_timestamp
                    ),
                    "embedded": embedded_code(root, source, files[source]),
                    "relations": [
                        {"type": "依存するヘッダ", "files": links(dependencies[source])},
                        {"type": "このヘッダを使うライブラリ", "files": links(required_by[source])},
                        {"type": "検証プログラム", "files": links(verified_with[source])},
                    ],
                }
            )
        target = destination / "reference" / page.relative_path
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(
            dump_front_matter({"layout": "reference", "title": page.title, "data": data})
            + rewrite_links(page.content),
            encoding="utf-8",
        )

    for path in sorted(test_files):
        file_input = files[path]
        data = {
            "path": path,
            "pathExtension": Path(path).suffix.lstrip("."),
            "icon": icons.get(path, TEST_WAITING_JUDGE),
            "attributes": page_attributes(file_input),
            "embedded": embedded_code(root, path, file_input),
            "timestamp": latest_timestamp(
                path, dependencies[path], timestamps, fallback_timestamp
            ),
            "relations": [
                {"type": "依存するヘッダ", "files": links(dependencies[path])},
            ],
        }
        target = destination / f"{path}.md"
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(
            dump_front_matter({"layout": "verification", "title": path, "data": data}),
            encoding="utf-8",
        )

    copy_plain_markdown(root, destination)

    verification_categories: dict[str, list[dict[str, str]]] = defaultdict(list)
    for path in sorted(test_files):
        verification_categories[Path(path).parent.as_posix()].append(
            {
                "path": path,
                "url": f"{path}.html",
                "icon": icons.get(path, TEST_WAITING_JUDGE),
                "title": title_for(path),
            }
        )
    index_content_path = docs_dir / "index.md"
    index_content = (
        index_content_path.read_text(encoding="utf-8")
        if index_content_path.is_file()
        else ""
    )
    (destination / "index.md").write_text(
        dump_front_matter(
            {
                "layout": "toppage",
                "data": {
                    "headerCount": len(header_pages),
                    "entityCount": len(reference_pages) - len(header_pages),
                    "verificationCount": len(test_files),
                    "verifications": [
                        {"name": name, "pages": verification_categories[name]}
                        for name in sorted(verification_categories, key=str.casefold)
                    ],
                },
            }
        )
        + index_content,
        encoding="utf-8",
    )

    summary_path = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary_path:
        with Path(summary_path).open("a", encoding="utf-8") as summary:
            summary.write(
                "### Reference documentation\n\n"
                f"- Header pages: {len(header_pages)}\n"
                f"- Entity pages: {len(reference_pages) - len(header_pages)}\n"
                f"- Verification pages: {len(test_files)}\n"
                f"- Destination: `{destination}`\n"
            )
    return len(reference_pages), len(test_files)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--verify-files", type=Path)
    parser.add_argument("--verify-result", type=Path)
    parser.add_argument("--destination", type=Path, default=Path("_jekyll"))
    parser.add_argument("--docs-dir", type=Path, default=DEFAULT_DOCS_DIR)
    parser.add_argument("--generated-dir", type=Path, default=DEFAULT_GENERATED_DIR)
    parser.add_argument(
        "--offline",
        action="store_true",
        help="verify の結果なしで、#include を辿った簡易版を組み立てる",
    )
    args = parser.parse_args()

    if not args.offline and (args.verify_files is None or args.verify_result is None):
        parser.error("--verify-files と --verify-result、または --offline が必要です")

    try:
        reference_count, verification_count = build_site(
            root=ROOT,
            docs_dir=args.docs_dir.resolve(),
            generated_dir=args.generated_dir.resolve(),
            destination=args.destination.resolve(),
            verify_files_path=None if args.offline else args.verify_files.resolve(),
            verify_result_path=None if args.offline else args.verify_result.resolve(),
        )
    except ValueError as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    print(
        f"reference site: {reference_count} reference pages / "
        f"{verification_count} verification pages"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
