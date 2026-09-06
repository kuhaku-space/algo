#!/usr/bin/env python3
"""日本語リファレンス（cpprefjp 風）の生成と検査。

情報源はヘッダの `///` コメントだけで、ページは常に生成物である。手書きの
Markdown は置かない。生成先は Git 管理外の `docs/generated/`。

    python3 tools/reference_docs.py build   # ページを生成する
    python3 tools/reference_docs.py check   # 生成したうえで品質を検査する
"""

from __future__ import annotations

import argparse
import shutil
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from reference.check import (  # noqa: E402
    Config,
    broken_links,
    documented_complexities,
    is_public,
    load_config,
    missing_complexities,
    run_example,
    undocumented_entities,
    unformatted_math,
)
from reference.model import Header  # noqa: E402
from reference.parse import (  # noqa: E402
    ROOT,
    library_headers,
    parse_header,
    problem_index,
)
from reference.render import ReferenceRenderer, write_files  # noqa: E402


DESTINATION = ROOT / "docs" / "generated"


def collect_headers(config: Config) -> list[Header]:
    problems = problem_index()
    return [parse_header(path, problems) for path in library_headers()]


def example_sources(headers: list[Header]) -> list[tuple[str, str, str]]:
    """(見出し, 出力キー, ソース) の一覧。"""
    sources: list[tuple[str, str, str]] = []
    for header in headers:
        for example in header.doc.examples:
            sources.append((header.include, header.slug, example))
        for entity in header.iter_entities():
            for example in entity.doc.examples:
                sources.append(
                    (
                        f"{header.include} :: {entity.qualified_name}",
                        f"{header.slug}#{entity.name}",
                        example,
                    )
                )
    return sources


def evaluate_examples(
    headers: list[Header],
) -> tuple[dict[str, list[str]], list[str]]:
    outputs: dict[str, list[str]] = {}
    errors: list[str] = []
    sources = example_sources(headers)
    if not sources:
        return outputs, errors
    if shutil.which("g++") is None:
        print("警告: g++ が見つからないため例の検査を省略します", file=sys.stderr)
        return outputs, errors
    with tempfile.TemporaryDirectory() as directory:
        workdir = Path(directory)
        for label, key, source in sources:
            error, stdout = run_example(source, workdir)
            if error:
                errors.append(f"{label}: 例が動作しません\n{error}")
                outputs.setdefault(key, []).append("")
            else:
                outputs.setdefault(key, []).append(stdout)
    return outputs, errors


def build(destination: Path = DESTINATION) -> tuple[list[Header], list[str]]:
    config = load_config()
    headers = collect_headers(config)
    renderer = ReferenceRenderer(headers)
    outputs, errors = evaluate_examples(headers)
    renderer.example_outputs = outputs
    files = renderer.render_all()
    if destination.exists():
        shutil.rmtree(destination)
    destination.mkdir(parents=True)
    write_files(destination, files)
    return headers, errors


def check(destination: Path = DESTINATION) -> int:
    config = load_config()
    headers, errors = build(destination)
    public = [header for header in headers if is_public(header, config)]

    documented_headers = 0
    entity_pages = 0
    complexities = 0
    for header in public:
        if header.title != header.include:
            documented_headers += 1
        else:
            errors.append(f"{header.relative_path}: ヘッダの概要（@file か主要な型の @brief）がありません")
        entity_pages += len(header.entities)
        complexities += documented_complexities(header)
        for entity in undocumented_entities(header):
            errors.append(
                f"{header.relative_path}: {entity.qualified_name} に @brief がありません"
            )
        for entity in missing_complexities(header):
            errors.append(
                f"{header.relative_path}: {entity.qualified_name} に @complexity がありません"
            )

    errors.extend(broken_links(destination))
    errors.extend(unformatted_math())

    undocumented = sum(len(undocumented_entities(header)) for header in public)
    if undocumented > config.maximum_undocumented:
        errors.append(
            f"説明のない公開 API が {undocumented} 個あります"
            f"（上限 {config.maximum_undocumented}）"
        )
    if documented_headers < config.minimum_headers:
        errors.append(
            f"概要のあるヘッダが {documented_headers} 個です"
            f"（下限 {config.minimum_headers}）"
        )
    if entity_pages < config.minimum_entity_pages:
        errors.append(
            f"エンティティページが {entity_pages} 個です（下限 {config.minimum_entity_pages}）"
        )
    if complexities < config.minimum_complexity:
        errors.append(
            f"計算量の記述が {complexities} 個です（下限 {config.minimum_complexity}）"
        )

    if errors:
        for error in errors:
            print(f"error: {error}", file=sys.stderr)
        return 1

    print(
        "リファレンス: "
        f"ヘッダ {len(headers)} 個（公開 {len(public)} 個）/ "
        f"エンティティ {entity_pages} 個 / 計算量 {complexities} 件"
    )
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command")
    subparsers.add_parser("build", help="リファレンスページを生成する")
    subparsers.add_parser("check", help="生成したうえで品質を検査する")
    arguments = parser.parse_args()

    if arguments.command == "check":
        return check()
    headers, errors = build()
    for error in errors:
        print(f"error: {error}", file=sys.stderr)
    print(f"リファレンスを生成しました: {DESTINATION.relative_to(ROOT)}（ヘッダ {len(headers)} 個）")
    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
