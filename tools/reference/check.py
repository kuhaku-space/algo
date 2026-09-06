"""生成したリファレンスの品質ゲート。

ヘッダのコメントが唯一の情報源なので、検査対象もヘッダ側の記述であり、
生成物の書式ではない。「説明のない公開 API を増やさない」「計算量の記述を
減らさない」「例が壊れていない」の 3 点を守る。
"""

from __future__ import annotations

import subprocess
import tomllib
from dataclasses import dataclass
from pathlib import Path

from .model import Entity, Header
from .parse import ROOT


CONFIG_PATH = ROOT / "docs" / "reference.toml"
NEEDS_COMPLEXITY = frozenset({"function", "operator", "constructor"})


@dataclass(frozen=True)
class Config:
    excluded_directories: frozenset[str]
    minimum_headers: int
    minimum_entity_pages: int
    minimum_complexity: int
    maximum_undocumented: int


def load_config(path: Path = CONFIG_PATH) -> Config:
    with path.open("rb") as file:
        data = tomllib.load(file)
    coverage = data["coverage"]
    return Config(
        excluded_directories=frozenset(coverage["excluded_directories"]),
        minimum_headers=coverage["minimum_documented_headers"],
        minimum_entity_pages=coverage["minimum_entity_pages"],
        minimum_complexity=coverage["minimum_documented_complexities"],
        maximum_undocumented=coverage["maximum_undocumented_entities"],
    )


def is_public(header: Header, config: Config) -> bool:
    return header.category not in config.excluded_directories


def undocumented_entities(header: Header) -> list[Entity]:
    return [
        entity
        for entity in header.iter_entities()
        if not entity.doc.brief and not entity.doc.details
    ]


def documented_complexities(header: Header) -> int:
    return sum(
        1
        for entity in header.iter_entities()
        if entity.kind in NEEDS_COMPLEXITY and entity.complexities()
    )


def missing_complexities(header: Header) -> list[Entity]:
    return [
        entity
        for entity in header.iter_entities()
        if entity.kind in NEEDS_COMPLEXITY and not entity.complexities()
    ]


def run_example(source: str, workdir: Path) -> tuple[str | None, str]:
    """例をコンパイルして実行し、(エラー, 標準出力) を返す。"""
    binary = workdir / "example"
    build = subprocess.run(
        [
            "g++",
            "-std=c++23",
            "-I",
            str(ROOT / "lib"),
            "-Wall",
            "-Wextra",
            "-o",
            str(binary),
            "-x",
            "c++",
            "-",
        ],
        input=source,
        text=True,
        capture_output=True,
        check=False,
    )
    if build.returncode != 0:
        return build.stderr.strip(), ""
    try:
        run = subprocess.run(
            [str(binary)],
            input="",
            text=True,
            capture_output=True,
            check=False,
            timeout=20,
        )
    except subprocess.TimeoutExpired:
        return "例の実行がタイムアウトしました", ""
    if run.returncode != 0:
        return f"例の実行に失敗しました (exit {run.returncode})\n{run.stderr}", ""
    return None, run.stdout


def broken_links(destination: Path) -> list[str]:
    """生成ページ同士の相対リンクが実在するか調べる。"""
    import re

    link_re = re.compile(r"\]\(([^)]+\.md)(?:#[^)]*)?\)")
    errors: list[str] = []
    for path in sorted(destination.glob("**/*.md")):
        text = path.read_text(encoding="utf-8")
        for target in link_re.findall(text):
            if target.startswith(("http://", "https://", "/")):
                continue
            if not (path.parent / target).resolve().is_file():
                relative = path.relative_to(destination).as_posix()
                errors.append(f"{relative}: リンク切れ {target}")
    return errors
