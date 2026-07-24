#!/usr/bin/env python3
"""Render the reference Jekyll source without competitive-verifier's docs command.

The renderer intentionally depends only on the two JSON artifacts produced by
the verification pipeline.  Keeping the rendering model in this repository
prevents upstream template/model changes from breaking the Pages build.
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
FRONT_MATTER_RE = re.compile(r"\A---\s*\n(.*?)\n---\s*\n", re.DOTALL)

LIBRARY_ALL_AC = "LIBRARY_ALL_AC"
LIBRARY_PARTIAL_AC = "LIBRARY_PARTIAL_AC"
LIBRARY_SOME_WA = "LIBRARY_SOME_WA"
LIBRARY_ALL_WA = "LIBRARY_ALL_WA"
LIBRARY_NO_TESTS = "LIBRARY_NO_TESTS"
TEST_ACCEPTED = "TEST_ACCEPTED"
TEST_WRONG_ANSWER = "TEST_WRONG_ANSWER"
TEST_WAITING_JUDGE = "TEST_WAITING_JUDGE"


@dataclass(frozen=True)
class MarkdownDocument:
    path: Path
    target: str | None
    title: str | None
    content: str
    display: str


@dataclass(frozen=True)
class Page:
    path: str
    title: str
    is_verification: bool
    display: str
    icon: str


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


def parse_front_matter(path: Path) -> tuple[dict[str, str], str]:
    text = path.read_text(encoding="utf-8")
    match = FRONT_MATTER_RE.match(text)
    if match is None:
        return {}, text

    values: dict[str, str] = {}
    for line in match.group(1).splitlines():
        if ":" not in line or line[:1].isspace():
            continue
        key, value = line.split(":", 1)
        values[key.strip()] = value.strip().strip("\"'")
    return values, text[match.end() :]


def discover_markdown(root: Path) -> tuple[dict[str, MarkdownDocument], list[Path]]:
    documents: dict[str, MarkdownDocument] = {}
    plain: list[Path] = []
    candidates = sorted([*root.glob("*.md"), *(root / "docs").glob("**/*.md")])
    for path in candidates:
        front_matter, content = parse_front_matter(path)
        target = front_matter.get("documentation_of")
        if target is None:
            plain.append(path)
            continue
        if not target.startswith("//"):
            fail(f"{path.relative_to(root)}: documentation_of は // から始めてください")
        source_path = target.removeprefix("//")
        if source_path in documents:
            fail(
                f"{path.relative_to(root)}: documentation_of が重複しています: "
                f"{source_path}"
            )
        documents[source_path] = MarkdownDocument(
            path=path,
            target=source_path,
            title=front_matter.get("title"),
            content=content,
            display=front_matter.get("display", "visible"),
        )
    return documents, plain


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
        command,
        cwd=root,
        text=True,
        capture_output=True,
        check=False,
    )
    if result.returncode != 0:
        return {}, dt.datetime.now(tz=dt.UTC)

    timestamps: dict[str, dt.datetime] = {}
    current: dt.datetime | None = None
    newest: dt.datetime | None = None
    for line in result.stdout.splitlines():
        if line.startswith("__REFERENCE_COMMIT__"):
            raw = line.removeprefix("__REFERENCE_COMMIT__")
            current = dt.datetime.fromisoformat(raw.replace("Z", "+00:00"))
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


def title_for(
    path: str,
    file_input: dict[str, Any],
    documents: dict[str, MarkdownDocument],
) -> str:
    document = documents.get(path)
    if document and document.title:
        return document.title
    attributes = file_input.get("document_attributes", {})
    if isinstance(attributes, dict):
        title = attributes.get("document_title")
        if isinstance(title, str) and title:
            return title
    return path


def render_link(page: Page) -> dict[str, str]:
    return {
        "path": page.path,
        "url": f"{page.path}.html",
        "filename": Path(page.path).name,
        "icon": page.icon,
        "title": "" if page.title == page.path else page.title,
    }


def dump_front_matter(*, layout: str, title: str | None, data: Any) -> str:
    lines = ["---", f"layout: {layout}"]
    if title is not None:
        lines.append(f"title: {json.dumps(title, ensure_ascii=False)}")
    lines.append(
        "data: "
        + json.dumps(data, ensure_ascii=False, separators=(",", ":"), sort_keys=True)
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
        source_path = root / source
        if not source_path.is_file():
            continue
        embedded.append(
            {
                "name": str(item.get("name") or source),
                "code": source_path.read_text(encoding="utf-8"),
            }
        )
    return embedded


def write_config(docs_dir: Path, destination: Path) -> None:
    source = docs_dir / "_config.yml"
    content = source.read_text(encoding="utf-8") if source.is_file() else ""
    generated = """\

# Generated by tools/render_reference_site.py.
theme: jekyll-theme-minimal
plugins:
  - jekyll-seo-tag
  - jemoji
  - jekyll-relative-links
  - jekyll-default-layout
  - jekyll-titles-from-headings
icons:
  LIBRARY_ALL_AC: "✅"
  LIBRARY_PARTIAL_AC: "☑️"
  LIBRARY_SOME_WA: "⚠️"
  LIBRARY_ALL_WA: "❌"
  LIBRARY_NO_TESTS: "➖"
  TEST_ACCEPTED: "✅"
  TEST_WRONG_ANSWER: "❌"
  TEST_WAITING_JUDGE: "⏳"
"""
    (destination / "_config.yml").write_text(
        content.rstrip() + "\n" + generated,
        encoding="utf-8",
    )


def copy_plain_markdown(root: Path, destination: Path, paths: list[Path]) -> None:
    for source in paths:
        relative = source.relative_to(root)
        target = destination / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)


def build_site(
    *,
    root: Path,
    docs_dir: Path,
    destination: Path,
    verify_files_path: Path,
    verify_result_path: Path,
) -> tuple[int, int]:
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

    documents, plain_markdown = discover_markdown(root)
    missing_targets = sorted(set(documents) - set(files))
    if missing_targets:
        fail(
            "documentation_of の対象が verify_files にありません:\n  - "
            + "\n  - ".join(missing_targets)
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

    flags = {
        path: result_flags(raw_results.get(path))
        for path in test_files
    }
    icons: dict[str, str] = {}
    for path in test_files:
        icons[path] = test_icon(flags[path])
    for path in library_files:
        aggregate: set[str] = set()
        for test in verified_with[path]:
            aggregate.update(flags[test])
        icons[path] = library_icon(frozenset(aggregate))

    pages = {
        path: Page(
            path=path,
            title=title_for(path, file_input, documents),
            is_verification=path in test_files,
            display=documents[path].display if path in documents else "visible",
            icon=icons[path],
        )
        for path, file_input in files.items()
    }

    if destination.exists():
        shutil.rmtree(destination)
    destination.mkdir(parents=True)
    write_config(docs_dir, destination)
    static_dir = docs_dir / "static"
    if static_dir.is_dir():
        shutil.copytree(static_dir, destination, dirs_exist_ok=True)
    copy_plain_markdown(root, destination, plain_markdown)

    timestamps, fallback_timestamp = get_git_timestamps(root)
    for path in sorted(files):
        page = pages[path]
        document = documents.get(path)
        content = document.content if document else ""
        file_input = files[path]

        def links(paths: set[str]) -> list[dict[str, str]]:
            return [
                render_link(pages[item])
                for item in sorted(paths, key=str.casefold)
                if pages[item].display != "never"
            ]

        page_data = {
            "path": path,
            "pathExtension": Path(path).suffix.lstrip("."),
            "title": page.title,
            "embedded": embedded_code(root, path, file_input),
            "timestamp": latest_timestamp(
                path,
                dependencies[path],
                timestamps,
                fallback_timestamp,
            ),
            "attributes": page_attributes(file_input),
            "isFailed": page.icon in {LIBRARY_SOME_WA, LIBRARY_ALL_WA, TEST_WRONG_ANSWER},
            "isVerificationFile": page.is_verification,
            "verificationStatus": page.icon,
            "documentPath": (
                document.path.relative_to(root).as_posix() if document else None
            ),
            "dependencies": [
                {"type": "Depends on", "files": links(dependencies[path])},
                {"type": "Required by", "files": links(required_by[path])},
                {"type": "Verified with", "files": links(verified_with[path])},
            ],
        }
        target = destination / f"{path}.md"
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(
            dump_front_matter(layout="document", title=page.title, data=page_data)
            + content,
            encoding="utf-8",
        )

    categories: dict[bool, dict[str, list[dict[str, str]]]] = {
        False: defaultdict(list),
        True: defaultdict(list),
    }
    for path in sorted(pages):
        page = pages[path]
        if page.display != "visible":
            continue
        category = Path(path).parent.as_posix()
        if category != ".":
            category += "/"
        categories[page.is_verification][category].append(render_link(page))

    def category_list(
        values: dict[str, list[dict[str, str]]],
    ) -> list[dict[str, Any]]:
        return [
            {"name": name, "pages": values[name]}
            for name in sorted(values, key=str.casefold)
        ]

    index_data = {
        "top": [
            {
                "type": "Library Files",
                "categories": category_list(categories[False]),
            },
            {
                "type": "Verification Files",
                "categories": category_list(categories[True]),
            },
        ]
    }
    index_content_path = docs_dir / "index.md"
    index_content = (
        index_content_path.read_text(encoding="utf-8")
        if index_content_path.is_file()
        else ""
    )
    (destination / "index.md").write_text(
        dump_front_matter(layout="toppage", title=None, data=index_data)
        + index_content,
        encoding="utf-8",
    )

    summary_path = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary_path:
        with Path(summary_path).open("a", encoding="utf-8") as summary:
            summary.write(
                "### Reference documentation\n\n"
                f"- Library pages: {len(library_files)}\n"
                f"- Verification pages: {len(test_files)}\n"
                f"- Destination: `{destination}`\n"
            )
    return len(library_files), len(test_files)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--verify-files", required=True, type=Path)
    parser.add_argument("--verify-result", required=True, type=Path)
    parser.add_argument("--destination", type=Path, default=Path("_jekyll"))
    parser.add_argument("--docs-dir", type=Path, default=DEFAULT_DOCS_DIR)
    args = parser.parse_args()

    try:
        library_count, verification_count = build_site(
            root=ROOT,
            docs_dir=args.docs_dir.resolve(),
            destination=args.destination.resolve(),
            verify_files_path=args.verify_files.resolve(),
            verify_result_path=args.verify_result.resolve(),
        )
    except ValueError as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    print(
        "reference site: "
        f"{library_count} library pages / "
        f"{verification_count} verification pages"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
