#!/usr/bin/env python3
"""日本語リファレンスの雛形生成と品質検査。

competitive-verifier が API ページそのものを生成するため、このスクリプトは
人が書く `docs/**/*.md` の一貫性と網羅率を管理する。
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
import tomllib
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CONFIG_PATH = ROOT / "docs" / "reference.toml"
GENERATED_DOCS_DIR = ROOT / "docs" / "generated"
FRONT_MATTER_RE = re.compile(r"\A---\s*\n(.*?)\n---\s*\n", re.DOTALL)
PROBLEM_RE = re.compile(r"competitive-verifier:\s*PROBLEM\s+(\S+)")
BRIEF_RE = re.compile(r"^\s*///\s*@brief\s+(.+?)\s*$", re.MULTILINE)
DOXYGEN_RE = re.compile(r"^\s*///", re.MULTILINE)
CPP_BLOCK_RE = re.compile(r"```cpp\s*\n(.*?)```", re.DOTALL)
DOXYGEN_TAG_RE = re.compile(r"^@([a-zA-Z_]+)(?:\s+(.*))?$")
NAMESPACE_OPEN_RE = re.compile(
    r"^\s*namespace\s+([A-Za-z_][A-Za-z0-9_:]*)\s*\{"
)
NAMESPACE_CLOSE_RE = re.compile(
    r"^\s*}\s*//\s*namespace(?:\s+([A-Za-z_][A-Za-z0-9_:]*))?\s*$"
)
CLASS_TOKEN_RE = re.compile(r"\b(struct|class)\s+([A-Za-z_][A-Za-z0-9_]*)")
ACCESS_RE = re.compile(r"^\s*(public|protected|private)\s*:\s*$")
API_SECTION_RE = re.compile(r"^## API\s*\n(.*?)(?=^## |\Z)", re.MULTILINE | re.DOTALL)
MARKDOWN_TABLE_RE = re.compile(
    r"^\|.+\|\s*\n\|\s*:?-+.*\|\s*$",
    re.MULTILINE,
)


@dataclass(frozen=True)
class Config:
    excluded_directories: frozenset[str]
    required_sections: tuple[str, ...]
    minimum_doxygen_headers: int
    minimum_reference_pages: int
    minimum_compiled_examples: int
    maximum_undocumented_headers: int


@dataclass(frozen=True)
class ReferencePage:
    path: Path
    target: Path
    title: str
    content: str
    compile_example: bool


@dataclass
class DocEntity:
    signature: str = ""
    namespace: str = ""
    brief: str = ""
    details: list[str] | None = None
    tparams: list[tuple[str, str]] | None = None
    params: list[tuple[str, str]] | None = None
    returns: list[str] | None = None
    complexities: list[str] | None = None
    notes: list[str] | None = None
    warnings: list[str] | None = None
    references: list[str] | None = None

    def __post_init__(self) -> None:
        self.details = self.details or []
        self.tparams = self.tparams or []
        self.params = self.params or []
        self.returns = self.returns or []
        self.complexities = self.complexities or []
        self.notes = self.notes or []
        self.warnings = self.warnings or []
        self.references = self.references or []



TITLE_OVERRIDES = {
    "lib/algorithm/interval.hpp": "区間演算",
    "lib/convolution/fft.hpp": "FFT・実数畳み込み",
    "lib/dp/monotone_minima.hpp": "Monotone Minima・min-plus畳み込み",
    "lib/graph/graph.hpp": "グラフ表現 (list_graph / csr_graph)",
    "lib/math/math.hpp": "整数数学ユーティリティ",
    "lib/number_theory/prime_number.hpp": "素数列挙・判定",
    "lib/random/split_mix_64.hpp": "疑似乱数生成器 SplitMix64",
    "lib/string/misc.hpp": "文字列ユーティリティ",
    "lib/tree/tree_function.hpp": "木の基本関数",
}

SUMMARY_OVERRIDES = {
    "lib/algorithm/interval.hpp": (
        "半開区間 $[l,r)$ と閉区間 $[l,r]$ の包含・交差判定と共通部分を提供する。"
    ),
    "lib/convolution/fft.hpp": (
        "複素FFTによる実数列の変換・逆変換と、整数列・実数列の畳み込みを提供する。"
    ),
    "lib/dp/monotone_minima.hpp": (
        "行列の各行の最小値位置が単調に移動する場合の最小値探索と、"
        "凸列を含むmin-plus畳み込みを提供する。"
    ),
    "lib/graph/graph.hpp": (
        "重み付き・重みなしグラフを、更新しやすい隣接リストまたは"
        "連続領域のCSRとして表現する。共通conceptにより各グラフアルゴリズムへ渡せる。"
    ),
    "lib/math/math.hpp": (
        "複数整数のGCD・LCM、床・天井除算、四捨五入、素数判定を提供する。"
    ),
    "lib/number_theory/prime_number.hpp": (
        "整数の素数判定、区間の素数列挙、線形篩、最小素因数を使った素因数分解を提供する。"
    ),
    "lib/random/split_mix_64.hpp": (
        "64 bit整数を高速に生成する SplitMix64。単体の疑似乱数生成器として利用できるほか、"
        "他の乱数生成器へ状態列を供給するシード生成器としても利用できる。"
    ),
    "lib/string/misc.hpp": (
        "最長共通接頭辞、最小・最大部分列など、独立した文字列アルゴリズムをまとめて提供する。"
    ),
    "lib/tree/tree_function.hpp": (
        "木の高さ、直径、中心、重心など、木全体に対する基本的な問い合わせを提供する。"
    ),
}


def relative(path: Path) -> str:
    return path.relative_to(ROOT).as_posix()


def load_config() -> Config:
    with CONFIG_PATH.open("rb") as file:
        data = tomllib.load(file)
    coverage = data["coverage"]
    style = data["style"]
    return Config(
        excluded_directories=frozenset(coverage["excluded_directories"]),
        required_sections=tuple(style["required_sections"]),
        minimum_doxygen_headers=coverage["minimum_doxygen_headers"],
        minimum_reference_pages=coverage["minimum_reference_pages"],
        minimum_compiled_examples=coverage["minimum_compiled_examples"],
        maximum_undocumented_headers=coverage["maximum_undocumented_headers"],
    )


def public_headers(config: Config) -> list[Path]:
    return sorted(
        path
        for path in (ROOT / "lib").glob("*/*.hpp")
        if path.parent.name not in config.excluded_directories
    )


def parse_front_matter(path: Path) -> tuple[dict[str, str], str]:
    content = path.read_text(encoding="utf-8")
    match = FRONT_MATTER_RE.match(content)
    if match is None:
        return {}, content

    values: dict[str, str] = {}
    for line in match.group(1).splitlines():
        if ":" not in line:
            continue
        key, value = line.split(":", 1)
        values[key.strip()] = value.strip().strip("\"'")
    return values, content[match.end() :]


def reference_pages() -> tuple[list[ReferencePage], list[str]]:
    pages: list[ReferencePage] = []
    errors: list[str] = []
    for path in sorted((ROOT / "docs").glob("**/*.md")):
        front_matter, content = parse_front_matter(path)
        documentation_of = front_matter.get("documentation_of")
        if documentation_of is None:
            continue
        if not documentation_of.startswith("//"):
            errors.append(f"{relative(path)}: documentation_of は // から始めてください")
            continue
        target = ROOT / documentation_of.removeprefix("//")
        pages.append(
            ReferencePage(
                path=path,
                target=target,
                title=front_matter.get("title", ""),
                content=content,
                compile_example=front_matter.get("compile_example") == "true",
            )
        )
    return pages, errors


def compile_first_example(page: ReferencePage) -> str | None:
    match = CPP_BLOCK_RE.search(page.content)
    if match is None:
        return "コンパイル対象の C++ コードブロックがありません"

    includes: list[str] = []
    body: list[str] = []
    for line in match.group(1).splitlines():
        if line.lstrip().startswith("#include"):
            includes.append(line)
        else:
            body.append(line)
    source = "\n".join(includes)
    source += "\n\nint main() {\n"
    source += "\n".join(f"    {line}" if line else "" for line in body)
    source += "\n    return 0;\n}\n"

    result = subprocess.run(
        [
            "g++",
            "-std=c++23",
            "-I",
            str(ROOT / "lib"),
            "-Wall",
            "-Wextra",
            "-fsyntax-only",
            "-x",
            "c++",
            "-",
        ],
        input=source,
        text=True,
        capture_output=True,
        check=False,
    )
    if result.returncode == 0:
        return None
    return result.stderr.strip()


def validate(config: Config) -> int:
    errors: list[str] = []
    pages, parse_errors = reference_pages()
    errors.extend(parse_errors)
    headers = public_headers(config)
    header_set = set(headers)
    targets: dict[Path, Path] = {}
    compiled_examples = 0

    for page in pages:
        page_name = relative(page.path)
        if not page.target.is_file():
            errors.append(f"{page_name}: 対象ヘッダ {relative(page.target)} が存在しません")
            continue
        if page.target not in header_set:
            errors.append(f"{page_name}: internal/template は公開リファレンスの対象外です")
        if page.target in targets:
            errors.append(
                f"{page_name}: {relative(page.target)} は "
                f"{relative(targets[page.target])} と重複しています"
            )
        targets[page.target] = page.path
        if not page.title:
            errors.append(f"{page_name}: title がありません")
        for section in config.required_sections:
            if f"## {section}" not in page.content:
                errors.append(f"{page_name}: 「## {section}」がありません")
        api_section = API_SECTION_RE.search(page.content)
        if api_section is not None and MARKDOWN_TABLE_RE.search(api_section.group(1)) is None:
            errors.append(f"{page_name}: 「## API」をMarkdown表にしてください")
        include = f'#include "{page.target.relative_to(ROOT / "lib").as_posix()}"'
        if include not in page.content:
            errors.append(f"{page_name}: 使用例に `{include}` がありません")
        if "TODO" in page.content or "（執筆中）" in page.content:
            errors.append(f"{page_name}: 未完成のプレースホルダが残っています")
        if page.compile_example:
            compiled_examples += 1
            compile_error = compile_first_example(page)
            if compile_error is not None:
                errors.append(f"{page_name}: 使用例をコンパイルできません\n{compile_error}")

    doxygen_headers = [
        path
        for path in headers
        if DOXYGEN_RE.search(path.read_text(encoding="utf-8"))
    ]
    documented = set(doxygen_headers) | set(targets)
    undocumented = [path for path in headers if path not in documented]

    if len(doxygen_headers) < config.minimum_doxygen_headers:
        errors.append(
            "Doxygenコメント付き公開ヘッダが基準を下回りました: "
            f"{len(doxygen_headers)} < {config.minimum_doxygen_headers}"
        )
    if len(pages) < config.minimum_reference_pages:
        errors.append(
            "詳細リファレンス数が基準を下回りました: "
            f"{len(pages)} < {config.minimum_reference_pages}"
        )
    if compiled_examples < config.minimum_compiled_examples:
        errors.append(
            "コンパイル検査付き使用例が基準を下回りました: "
            f"{compiled_examples} < {config.minimum_compiled_examples}"
        )
    if len(undocumented) > config.maximum_undocumented_headers:
        errors.append(
            "未文書化ヘッダ数が基準を超えました: "
            f"{len(undocumented)} > {config.maximum_undocumented_headers}"
        )

    print(
        "reference docs: "
        f"{len(pages)} detailed / "
        f"{compiled_examples} compiled examples / "
        f"{len(doxygen_headers)} doxygen / "
        f"{len(headers)} public headers"
    )
    if undocumented:
        print("undocumented public headers:")
        for path in undocumented:
            print(f"  - {relative(path)}")

    if errors:
        print("\nerrors:", file=sys.stderr)
        for error in errors:
            print(f"  - {error}", file=sys.stderr)
        return 1
    return 0


def find_problem_urls(header: Path) -> list[str]:
    include = f'#include "{header.relative_to(ROOT / "lib").as_posix()}"'
    urls: set[str] = set()
    for test in (ROOT / "test").glob("**/*.test.cpp"):
        content = test.read_text(encoding="utf-8")
        if include not in content:
            continue
        match = PROBLEM_RE.search(content)
        if match:
            urls.add(match.group(1))
    return sorted(urls)


def normalize_doc_text(text: str) -> str:
    text = re.sub(r"@ref\s+([A-Za-z_][A-Za-z0-9_:<>]*)", r"`\1`", text)
    text = re.sub(r"@(p|c)\s+([A-Za-z_][A-Za-z0-9_]*)", r"`\2`", text)
    return " ".join(text.split())


def strip_constructor_initializer(signature: str) -> str:
    paren_depth = 0
    saw_parameter_list = False
    for index, character in enumerate(signature):
        if character == "(":
            paren_depth += 1
        elif character == ")":
            paren_depth -= 1
            if paren_depth == 0:
                saw_parameter_list = True
        elif (
            character == ":"
            and paren_depth == 0
            and saw_parameter_list
            and (index == 0 or signature[index - 1] != ":")
            and (index + 1 == len(signature) or signature[index + 1] != ":")
        ):
            return signature[:index].rstrip()
    return signature


def declaration_after(lines: list[str], index: int) -> str:
    declaration: list[str] = []
    while index < len(lines) and not lines[index].strip():
        index += 1
    while index < len(lines) and len(declaration) < 12:
        line = lines[index].strip()
        if not line or line.startswith("///"):
            break
        if line.startswith("//") or line.startswith("#"):
            index += 1
            continue
        before_body = line.split("{", 1)[0].rstrip()
        if before_body:
            declaration.append(before_body)
        if "{" in line or ";" in line:
            break
        index += 1
    return strip_constructor_initializer(" ".join(declaration))


def append_continuation(entity: DocEntity, field: str, text: str) -> None:
    values = getattr(entity, field)
    assert isinstance(values, list)
    if not values:
        values.append(text)
    elif isinstance(values[-1], tuple):
        name, description = values[-1]
        values[-1] = (name, f"{description} {text}".strip())
    else:
        values[-1] = f"{values[-1]} {text}".strip()


def parse_doc_block(
    block: list[str],
    signature: str,
    namespace: str = "",
) -> DocEntity:
    entity = DocEntity(signature=signature, namespace=namespace)
    current_field = "details"
    for raw in block:
        text = re.sub(r"^\s*///\s?", "", raw).strip()
        if not text:
            continue
        tag_match = DOXYGEN_TAG_RE.match(text)
        if tag_match is None:
            append_continuation(entity, current_field, normalize_doc_text(text))
            continue

        tag, value = tag_match.group(1), normalize_doc_text(tag_match.group(2) or "")
        if tag == "brief":
            entity.brief = value
            current_field = "details"
        elif tag == "details":
            entity.details.append(value)
            current_field = "details"
        elif tag in ("tparam", "param"):
            name, _, description = value.partition(" ")
            field = "tparams" if tag == "tparam" else "params"
            getattr(entity, field).append((name, description))
            current_field = field
        elif tag in ("return", "returns"):
            entity.returns.append(value)
            current_field = "returns"
        elif tag == "complexity":
            entity.complexities.append(value)
            current_field = "complexities"
        elif tag == "note":
            entity.notes.append(value)
            current_field = "notes"
        elif tag == "warning":
            entity.warnings.append(value)
            current_field = "warnings"
        elif tag in ("see", "sa"):
            entity.references.append(value)
            current_field = "references"
        else:
            entity.details.append(f"`@{tag}` {value}".strip())
            current_field = "details"
    return entity


def namespace_contexts(lines: list[str]) -> list[str]:
    contexts: list[str] = []
    stack: list[str] = []
    for line in lines:
        contexts.append("::".join(stack))
        open_match = NAMESPACE_OPEN_RE.match(line)
        if open_match is not None:
            stack.extend(open_match.group(1).split("::"))
            continue
        close_match = NAMESPACE_CLOSE_RE.match(line)
        if close_match is not None and stack:
            name = close_match.group(1)
            count = len(name.split("::")) if name else 1
            del stack[-count:]
    return contexts


def public_access_contexts(lines: list[str]) -> list[bool]:
    contexts: list[bool] = []
    stack: list[list[object]] = []
    brace_depth = 0
    for raw_line in lines:
        contexts.append(not stack or stack[-1][1] == "public")
        line = re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', "", raw_line)
        line = line.split("//", 1)[0]
        access_match = ACCESS_RE.match(line)
        if access_match is not None and stack:
            stack[-1][1] = access_match.group(1)

        opening = line.find("{")
        if opening >= 0:
            class_tokens = list(CLASS_TOKEN_RE.finditer(line[:opening]))
            if class_tokens:
                token = class_tokens[-1]
                suffix = line[token.end() : opening]
                if "(" not in suffix:
                    kind = token.group(1)
                    stack.append(
                        [brace_depth + 1, "public" if kind == "struct" else "private"]
                    )

        brace_depth += line.count("{") - line.count("}")
        while stack and brace_depth < stack[-1][0]:
            stack.pop()
    return contexts


def extract_doc_entities(source: str) -> list[DocEntity]:
    lines = source.splitlines()
    contexts = namespace_contexts(lines)
    public_contexts = public_access_contexts(lines)
    entities: list[DocEntity] = []
    index = 0
    while index < len(lines):
        if not lines[index].lstrip().startswith("///"):
            index += 1
            continue
        block: list[str] = []
        while index < len(lines) and lines[index].lstrip().startswith("///"):
            block.append(lines[index])
            index += 1
        namespace = contexts[index] if index < len(contexts) else ""
        entity = parse_doc_block(
            block,
            declaration_after(lines, index),
            namespace,
        )
        is_public = public_contexts[index] if index < len(public_contexts) else True
        if is_public and (entity.brief or entity.details):
            entities.append(entity)
    return entities


def symbol_from_signature(signature: str) -> str:
    work = signature.strip()
    if work.startswith("template"):
        start = work.find("<")
        depth = 0
        for index in range(start, len(work)):
            if work[index] == "<":
                depth += 1
            elif work[index] == ">":
                depth -= 1
                if depth == 0:
                    work = work[index + 1 :].lstrip()
                    break

    type_match = re.search(
        r"\b(?:struct|class|concept|using)\s+([A-Za-z_][A-Za-z0-9_]*)",
        work,
    )
    if type_match:
        return type_match.group(1)

    function_match = re.search(r"\b([A-Za-z_~][A-Za-z0-9_:~]*)\s*\(", work)
    if function_match:
        return function_match.group(1).split("::")[-1]

    variable_match = re.search(
        r"\b([A-Za-z_][A-Za-z0-9_]*)\s*(?:=|;)(?:\s|$)",
        work,
    )
    if variable_match:
        return variable_match.group(1)
    return ""


def escape_table_cell(text: str) -> str:
    return text.replace("|", r"\|").replace("\n", "<br>")


def display_signature(entity: DocEntity) -> str:
    signature = entity.signature
    if not signature or not entity.namespace:
        return signature
    using_match = re.fullmatch(
        r"using\s+([A-Za-z_][A-Za-z0-9_:]*)\s*;",
        signature,
    )
    if using_match is not None:
        return f"{entity.namespace}::{using_match.group(1).split('::')[-1]}"
    symbol = symbol_from_signature(signature)
    if not symbol:
        return signature
    return re.sub(
        rf"\b{re.escape(symbol)}\s*(?=\()",
        f"{entity.namespace}::{symbol}",
        signature,
        count=1,
    )


def render_entity_group(entities: list[DocEntity], index: int) -> str:
    entity = entities[0]
    signatures = [
        f"`{escape_table_cell(signature)}`"
        for signature in dict.fromkeys(display_signature(item) for item in entities)
        if signature
    ]
    api = "<br>".join(signatures) if signatures else f"`API {index}`"
    parts: list[str] = []
    if entity.brief:
        parts.append(entity.brief)
    parts.extend(entity.details)
    if entity.tparams:
        values = "、".join(
            f"`{param}`: {description}" for param, description in entity.tparams
        )
        parts.append(f"**テンプレート引数:** {values}")
    if entity.params:
        values = "、".join(
            f"`{param}`: {description}" for param, description in entity.params
        )
        parts.append(f"**引数:** {values}")
    if entity.returns:
        parts.append(f"**戻り値:** {' '.join(entity.returns)}")
    parts.extend(f"**注意:** {warning}" for warning in entity.warnings)
    parts.extend(f"**備考:** {note}" for note in entity.notes)
    if entity.references:
        references: list[str] = []
        for reference in entity.references:
            if reference.startswith(("https://", "http://")):
                references.append(f"[{reference}]({reference})")
            else:
                references.append(reference)
        parts.append(f"**参考:** {'、'.join(references)}")
    description = escape_table_cell("<br>".join(parts)) if parts else "—"
    complexity = (
        escape_table_cell("<br>".join(entity.complexities))
        if entity.complexities
        else "—"
    )
    return f"| {api} | {description} | {complexity} |"


def render_entity(entity: DocEntity, index: int) -> str:
    return render_entity_group([entity], index)


def group_doc_entities(entities: list[DocEntity]) -> list[list[DocEntity]]:
    groups: list[list[DocEntity]] = []
    keys: list[tuple[object, ...]] = []
    for entity in entities:
        key = (
            entity.namespace,
            symbol_from_signature(entity.signature),
            entity.brief,
            tuple(entity.details),
            tuple(entity.tparams),
            tuple(entity.params),
            tuple(entity.returns),
            tuple(entity.complexities),
            tuple(entity.notes),
            tuple(entity.warnings),
            tuple(entity.references),
        )
        try:
            group_index = keys.index(key)
        except ValueError:
            keys.append(key)
            groups.append([entity])
        else:
            groups[group_index].append(entity)
    return groups


def signature_opens_scope(signature: str) -> bool:
    work = signature.strip()
    if work.startswith("template"):
        start = work.find("<")
        depth = 0
        for index in range(start, len(work)):
            if work[index] == "<":
                depth += 1
            elif work[index] == ">":
                depth -= 1
                if depth == 0:
                    work = work[index + 1 :].lstrip()
                    break

    if re.match(r"^(?:struct|class|namespace)\b", work):
        return True
    return re.match(r"^requires\b.*?\b(?:struct|class)\b", work) is not None


def render_generated_page(header: Path) -> str:
    relative_header = header.relative_to(ROOT).as_posix()
    include = header.relative_to(ROOT / "lib").as_posix()
    source = header.read_text(encoding="utf-8")
    entities = extract_doc_entities(source)
    stem = header.stem.replace("_", "").lower()

    def primary_score(entity: DocEntity) -> int:
        symbol = symbol_from_signature(entity.signature).replace("_", "").lower()
        brief = entity.brief.replace("_", "").lower()
        score = 0
        if symbol == stem:
            score += 100
        if stem in brief:
            score += 40
        if signature_opens_scope(entity.signature):
            score += 60
        if "concept " in entity.signature:
            score -= 10
        return score

    primary = max(entities, key=primary_score)
    title = TITLE_OVERRIDES.get(relative_header, primary.brief or include)
    summary_parts = [primary.brief, *primary.details]
    summary = "\n\n".join(part for part in summary_parts if part)
    summary = SUMMARY_OVERRIDES.get(relative_header, summary)
    api_entities = entities
    if len(entities) > 1 and signature_opens_scope(primary.signature):
        api_entities = [
            entity
            for entity in entities
            if not re.match(r"^namespace\b", entity.signature)
            and entity is not primary
        ]
    api_rows = [
        render_entity_group(group, i + 1)
        for i, group in enumerate(group_doc_entities(api_entities))
    ]
    notes: list[str] = []

    api = "\n".join(
        [
            "| API | 内容 | 計算量 |",
            "| --- | --- | --- |",
            *api_rows,
        ]
    )

    verifications: list[str] = []
    include_directive = f'#include "{include}"'
    for test in sorted((ROOT / "test").glob("**/*.test.cpp")):
        content = test.read_text(encoding="utf-8")
        if include_directive not in content:
            continue
        match = PROBLEM_RE.search(content)
        if match:
            verifications.append(
                f"- [{test.relative_to(ROOT).as_posix()}]({match.group(1)})"
            )
    if not verifications:
        verifications.append(
            "このヘッダを直接インクルードする検証問題はありません。"
            "依存先を通した検証は生成ページの「自動検証」に表示されます。"
        )

    note_lines = [f"- {note}" for note in notes]
    note_lines.append(
        "- 依存するヘッダ、このヘッダを利用するライブラリ、検証プログラム、実装全文は"
        "生成ページ下部から確認できる。"
    )
    return f"""---
title: {json.dumps(title, ensure_ascii=False)}
documentation_of: //{relative_header}
compile_example: true
generated_reference: true
---

{summary}

## 使い方

```cpp
#include "{include}"
```

## API

{api}

## 補足

{chr(10).join(note_lines)}

## 検証

{chr(10).join(verifications)}
"""


def replace_api_section(content: str, generated: str) -> str:
    current_match = API_SECTION_RE.search(content)
    generated_match = API_SECTION_RE.search(generated)
    if current_match is None or generated_match is None:
        raise ValueError("API セクションが見つかりません")
    replacement = f"## API\n\n{generated_match.group(1).strip()}\n\n"
    return content[: current_match.start()] + replacement + content[current_match.end() :]


def generate_missing() -> int:
    config = load_config()
    pages, errors = reference_pages()
    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        return 1
    documented = {page.target for page in pages}
    created = 0
    for header in public_headers(config):
        if header in documented:
            continue
        output = GENERATED_DOCS_DIR / header.relative_to(ROOT / "lib").with_suffix(".md")
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(render_generated_page(header), encoding="utf-8")
        print(f"created: {relative(output)}")
        created += 1
    print(f"generated {created} reference pages")
    return 0


def sync_generated() -> int:
    config = load_config()
    pages, errors = reference_pages()
    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        return 1

    headers = public_headers(config)
    header_set = set(headers)
    manual_targets = {
        page.target
        for page in pages
        if parse_front_matter(page.path)[0].get("generated_reference") != "true"
    }
    manual_pages = [
        page
        for page in pages
        if parse_front_matter(page.path)[0].get("generated_reference") != "true"
    ]

    removed = 0
    for path in sorted(GENERATED_DOCS_DIR.glob("**/*.md")):
        front_matter, _ = parse_front_matter(path)
        documentation_of = front_matter.get("documentation_of", "")
        target = ROOT / documentation_of.removeprefix("//")
        if target in header_set and target not in manual_targets:
            continue
        path.unlink()
        print(f"removed: {relative(path)}")
        removed += 1

    updated = 0
    manual_updated = 0
    for page in manual_pages:
        content = page.path.read_text(encoding="utf-8")
        synced = replace_api_section(content, render_generated_page(page.target))
        if synced != content:
            page.path.write_text(synced, encoding="utf-8")
            print(f"updated API: {relative(page.path)}")
            manual_updated += 1

    for header in headers:
        if header in manual_targets:
            continue
        path = GENERATED_DOCS_DIR / header.relative_to(ROOT / "lib").with_suffix(".md")
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(render_generated_page(header), encoding="utf-8")
        print(f"updated: {relative(path)}")
        updated += 1
    print(
        f"updated {updated} generated pages / {manual_updated} manual API sections"
        f" / removed {removed} generated reference pages"
    )
    return 0


def make_stub(header_arg: str) -> int:
    config = load_config()
    header = (ROOT / header_arg.removeprefix("//")).resolve()
    try:
        header.relative_to(ROOT)
    except ValueError:
        print("ヘッダはリポジトリ内を指定してください", file=sys.stderr)
        return 1
    if not header.is_file() or header.suffix != ".hpp" or ROOT / "lib" not in header.parents:
        print(f"公開ヘッダが見つかりません: {header_arg}", file=sys.stderr)
        return 1
    if header.parent.name in config.excluded_directories:
        print(f"{header.parent.name}/ は公開リファレンスの対象外です", file=sys.stderr)
        return 1

    relative_header = header.relative_to(ROOT)
    relative_include = header.relative_to(ROOT / "lib")
    output = ROOT / "docs" / relative_include.with_suffix(".md")
    if output.exists():
        print(f"既に存在します: {relative(output)}", file=sys.stderr)
        return 1

    source = header.read_text(encoding="utf-8")
    match = BRIEF_RE.search(source)
    title = match.group(1) if match else relative_include.stem
    verifications = find_problem_urls(header)
    verification_lines = (
        "\n".join(f"- [{url}]({url})" for url in verifications)
        if verifications
        else "- （執筆中）"
    )
    content = f"""---
title: {title}
documentation_of: //{relative_header.as_posix()}
---

（執筆中）

## 使い方

```cpp
#include "{relative_include.as_posix()}"
```

## API

（執筆中）

## 補足

（執筆中）

## 検証

{verification_lines}
"""
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(content, encoding="utf-8")
    print(f"created: {relative(output)}")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)
    subparsers.add_parser("check", help="リファレンスの形式と網羅率を検査する")
    stub_parser = subparsers.add_parser("stub", help="公開ヘッダのMarkdown雛形を作る")
    stub_parser.add_argument("header", help="例: lib/segtree/segment_tree.hpp")
    subparsers.add_parser(
        "generate-missing",
        help="Doxygenコメントから未作成の全公開ヘッダページを生成する",
    )
    subparsers.add_parser(
        "sync-generated",
        help="自動生成された公開ヘッダページを現在のコメントと宣言に同期する",
    )
    args = parser.parse_args()

    if args.command == "check":
        return validate(load_config())
    if args.command == "stub":
        return make_stub(args.header)
    if args.command == "generate-missing":
        return generate_missing()
    if args.command == "sync-generated":
        return sync_generated()
    raise AssertionError(args.command)


if __name__ == "__main__":
    raise SystemExit(main())
