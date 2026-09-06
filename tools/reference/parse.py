"""ヘッダの Doxygen コメントを読み、リファレンスのモデルを組み立てる。

対象は `///` で書かれた行コメントのみ（規約でブロックコメントは使わない）。
名前空間・クラスのスコープを追いながら走査し、コメント直後の宣言を
そのコメントの対象とみなす。
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path

from .model import DocBlock, Entity, Header, Overload

ROOT = Path(__file__).resolve().parents[2]
LIB_DIR = ROOT / "lib"
TEST_DIR = ROOT / "test"

DOC_PREFIX_RE = re.compile(r"^\s*///\s?")
DOC_LINE_RE = re.compile(r"^\s*///")
TAG_RE = re.compile(r"^@([a-zA-Z_]+)(?:\s+(.*))?$")
ACCESS_RE = re.compile(r"^\s*(public|protected|private)\s*:")
NAMESPACE_HEAD_RE = re.compile(r"\bnamespace\s+([A-Za-z_][A-Za-z0-9_:]*)?\s*$")
CLASS_TOKEN_RE = re.compile(r"\b(struct|class)\s+([A-Za-z_][A-Za-z0-9_]*)")
STRING_RE = re.compile(r"\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'")
PROBLEM_RE = re.compile(r"competitive-verifier:\s*PROBLEM\s+(\S+)")
SPECIFIERS = (
    "constexpr",
    "consteval",
    "constinit",
    "static",
    "inline",
    "explicit",
    "friend",
    "virtual",
    "extern",
)


@dataclass(frozen=True)
class Scope:
    namespace: str
    class_path: tuple[str, ...]
    public: bool


@dataclass
class _Frame:
    depth: int
    kind: str
    name: str
    access: str


def strip_code_noise(line: str) -> str:
    """文字列リテラルと行コメントを取り除き、波括弧の対応だけを残す。"""
    line = STRING_RE.sub("", line)
    return line.split("//", 1)[0]


def classify_head(buffer: str) -> tuple[str, str, str] | None:
    """`{` の直前までのテキストから、開こうとしているスコープを判定する。"""
    text = " ".join(buffer.split())
    namespace = NAMESPACE_HEAD_RE.search(text)
    if namespace is not None:
        return ("namespace", namespace.group(1) or "", "public")
    if re.search(r"\benum\b", text):
        return None
    tokens = list(CLASS_TOKEN_RE.finditer(text))
    if not tokens:
        return None
    token = tokens[-1]
    suffix = text[token.end() :]
    if "(" in suffix or ")" in suffix:
        return None
    kind = token.group(1)
    return ("class", token.group(2), "public" if kind == "struct" else "private")


def scope_contexts(lines: list[str]) -> list[Scope]:
    """各行を読み始める時点でのスコープを返す。"""
    contexts: list[Scope] = []
    stack: list[_Frame] = []
    depth = 0
    buffer = ""

    for raw in lines:
        namespace = "::".join(
            frame.name for frame in stack if frame.kind == "namespace" and frame.name
        )
        class_path = tuple(frame.name for frame in stack if frame.kind == "class")
        public = all(
            frame.access == "public" for frame in stack if frame.kind == "class"
        )
        contexts.append(Scope(namespace, class_path, public))

        if raw.lstrip().startswith("#"):
            continue
        line = strip_code_noise(raw)
        access = ACCESS_RE.match(line)
        if access is not None:
            for frame in reversed(stack):
                if frame.kind == "class":
                    frame.access = access.group(1)
                    break
            continue

        for character in line:
            if character == "{":
                depth += 1
                head = classify_head(buffer)
                if head is None:
                    stack.append(_Frame(depth, "other", "", "public"))
                else:
                    stack.append(_Frame(depth, head[0], head[1], head[2]))
                buffer = ""
            elif character == "}":
                while stack and stack[-1].depth >= depth:
                    stack.pop()
                depth -= 1
                buffer = ""
            elif character == ";":
                buffer = ""
            else:
                buffer += character
        buffer += " "
    return contexts


def normalize_text(text: str) -> str:
    text = re.sub(r"@ref\s+([A-Za-z_][A-Za-z0-9_:<>]*)", r"`\1`", text)
    text = re.sub(r"@(p|c)\s+([A-Za-z_][A-Za-z0-9_]*)", r"`\2`", text)
    return " ".join(text.split())


def parse_doc_block(block: list[str]) -> DocBlock:
    doc = DocBlock()
    current: list[str] | None = doc.details
    example: list[str] | None = None

    for raw in block:
        text = DOC_PREFIX_RE.sub("", raw).rstrip()
        if example is not None:
            if text.strip() in ("@endcode", "@endexample"):
                doc.examples.append("\n".join(example).strip("\n"))
                example = None
            else:
                example.append(text)
            continue
        stripped = text.strip()
        if not stripped:
            continue
        tag = TAG_RE.match(stripped)
        if tag is None:
            if current is not None:
                append_continuation(current, normalize_text(stripped))
            continue

        name = tag.group(1)
        value = normalize_text(tag.group(2) or "")
        if name in ("code", "example"):
            example = []
            current = None
        elif name == "file":
            doc.is_file_doc = True
            current = doc.details
        elif name == "brief":
            doc.brief = value
            current = doc.details
        elif name == "details":
            doc.details.append(value)
            current = doc.details
        elif name in ("tparam", "param"):
            parameter, _, description = value.partition(" ")
            target = doc.tparams if name == "tparam" else doc.params
            target.append((parameter.strip("[]"), description))
            current = None
            current = _ParameterTail(target)  # type: ignore[assignment]
        elif name in ("return", "returns"):
            doc.returns.append(value)
            current = doc.returns
        elif name == "complexity":
            doc.complexities.append(value)
            current = doc.complexities
        elif name in ("pre", "precondition"):
            doc.preconditions.append(value)
            current = doc.preconditions
        elif name == "note":
            doc.notes.append(value)
            current = doc.notes
        elif name == "warning":
            doc.warnings.append(value)
            current = doc.warnings
        elif name in ("see", "sa"):
            doc.references.append(value)
            current = doc.references
        else:
            doc.details.append(f"`@{name}` {value}".strip())
            current = doc.details
    if example is not None:
        doc.examples.append("\n".join(example).strip("\n"))
    return doc


class _ParameterTail(list):
    """`@param` の続き行を直前の説明へ連結するためのビュー。"""

    def __init__(self, target: list[tuple[str, str]]) -> None:
        super().__init__()
        self.target = target

    def append(self, value: str) -> None:  # type: ignore[override]
        if not self.target:
            return
        name, description = self.target[-1]
        self.target[-1] = (name, f"{description} {value}".strip())


def concept_declaration_after(lines: list[str], index: int) -> str:
    """concept は本体まで見せたいので、対応する `;` まで読む。"""
    collected: list[str] = []
    depth = 0
    started = False
    while index < len(lines) and len(collected) < 40:
        raw = lines[index].rstrip()
        index += 1
        stripped = raw.strip()
        if not stripped or stripped.startswith("//"):
            continue
        collected.append(raw)
        depth += stripped.count("{") - stripped.count("}")
        if "{" in stripped:
            started = True
        if stripped.endswith(";") and (depth <= 0 or not started):
            break
    if not collected:
        return ""
    indent = len(collected[0]) - len(collected[0].lstrip())
    return "\n".join(
        line[indent:] if line[:indent].isspace() or not indent else line.lstrip()
        for line in collected
    )


def append_continuation(target: list, text: str) -> None:
    if isinstance(target, _ParameterTail):
        target.append(text)
    elif target:
        target[-1] = f"{target[-1]} {text}".strip()
    else:
        target.append(text)


def strip_constructor_initializer(signature: str) -> str:
    depth = 0
    saw_parameters = False
    for index, character in enumerate(signature):
        if character == "(":
            depth += 1
        elif character == ")":
            depth -= 1
            if depth == 0:
                saw_parameters = True
        elif (
            character == ":"
            and depth == 0
            and saw_parameters
            and (index == 0 or signature[index - 1] != ":")
            and (index + 1 == len(signature) or signature[index + 1] != ":")
        ):
            return signature[:index].rstrip()
    return signature


def declaration_after(lines: list[str], index: int) -> str:
    declaration: list[str] = []
    while index < len(lines) and not lines[index].strip():
        index += 1
    while index < len(lines) and len(declaration) < 16:
        line = lines[index].strip()
        if not line or DOC_LINE_RE.match(line):
            break
        if line.startswith(("//", "#")):
            index += 1
            continue
        before_body = line.split("{", 1)[0].rstrip()
        if before_body:
            declaration.append(before_body)
        if "{" in line or ";" in line:
            break
        index += 1
    return strip_constructor_initializer(" ".join(declaration))


def matching_angle(text: str, start: int) -> int:
    """`<` に対応する `>` の位置を返す。括弧の中の `<<` などは数えない。"""
    if start < 0 or start >= len(text) or text[start] != "<":
        return -1
    depth = 0
    paren = 0
    for index in range(start, len(text)):
        character = text[index]
        if character in "([":
            paren += 1
        elif character in ")]":
            paren -= 1
        elif paren > 0:
            continue
        elif character == "<":
            depth += 1
        elif character == ">":
            depth -= 1
            if depth == 0:
                return index
    return -1


def split_template_prefix(declaration: str) -> tuple[str, str]:
    work = declaration.strip()
    prefix: list[str] = []
    while work.startswith("template"):
        end = matching_angle(work, work.find("<"))
        if end < 0:
            break
        prefix.append(work[: end + 1].strip())
        work = work[end + 1 :].lstrip()
    clause, work = split_requires_clause(work)
    if clause:
        prefix.append(clause)
    return " ".join(part for part in prefix if part), work


def matching_bracket(text: str, start: int, opening: str, closing: str) -> int:
    depth = 0
    for index in range(start, len(text)):
        if text[index] == opening:
            depth += 1
        elif text[index] == closing:
            depth -= 1
            if depth == 0:
                return index
    return -1


def split_requires_clause(text: str) -> tuple[str, str]:
    """先頭の requires 節と、それに続く宣言へ分ける。

    制約は `A<...> && B(...)` のような論理積の連なりなので、原子を 1 つ読んでは
    次が `&&` / `||` かを見る、という単純な走査で終端が決まる。
    """
    if not re.match(r"requires\b", text):
        return "", text
    index = len("requires")
    length = len(text)
    while True:
        while index < length and text[index].isspace():
            index += 1
        if index >= length:
            return text.strip(), ""
        if text[index] == "(":
            end = matching_bracket(text, index, "(", ")")
        else:
            name = re.match(r"[A-Za-z_][A-Za-z0-9_:]*", text[index:])
            if name is None:
                return text[:index].strip(), text[index:].lstrip()
            end = index + name.end() - 1
            probe = end + 1
            while probe < length and text[probe].isspace():
                probe += 1
            if probe < length and text[probe] == "<":
                end = matching_angle(text, probe)
            elif probe < length and text[probe] == "(":
                end = matching_bracket(text, probe, "(", ")")
        if end < 0:
            return text[:index].strip(), text[index:].lstrip()
        index = end + 1
        probe = index
        while probe < length and text[probe].isspace():
            probe += 1
        if text[probe : probe + 2] in ("&&", "||"):
            index = probe + 2
            continue
        return text[:index].strip(), text[index:].lstrip()


def symbol_and_kind(declaration: str, owner: str) -> tuple[str, str, bool] | None:
    """宣言から (名前, 種別, static か) を求める。対象外なら None。"""
    _, work = split_template_prefix(declaration)
    if not work or work.startswith("namespace"):
        return None
    is_static = bool(re.match(r"^(?:[a-z_]+\s+)*static\b", work)) or " static " in f" {work} "

    match = re.match(r"^(?:struct|class)\s+([A-Za-z_][A-Za-z0-9_]*)", work)
    if match:
        return (match.group(1), "class", False)
    match = re.match(r"^concept\s+([A-Za-z_][A-Za-z0-9_]*)", work)
    if match:
        return (match.group(1), "concept", False)
    match = re.match(r"^using\s+([A-Za-z_][A-Za-z0-9_]*)\s*=", work)
    if match:
        return (match.group(1), "alias", False)
    match = re.match(r"^using\s+([A-Za-z_][A-Za-z0-9_:]*)\s*;", work)
    if match:
        return (match.group(1).split("::")[-1], "alias", False)
    match = re.search(r"\boperator\s*(\(\)|\[\]|[^\s(]+)\s*\(", work)
    if match:
        token = match.group(1)
        separator = " " if re.match(r"^[A-Za-z_]", token) else ""
        return (f"operator{separator}{token}", "operator", is_static)
    match = re.search(r"~\s*([A-Za-z_][A-Za-z0-9_]*)\s*\(", work)
    if match:
        return (f"~{match.group(1)}", "destructor", False)
    match = re.search(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(", work)
    if match:
        name = match.group(1)
        if name in ("if", "for", "while", "switch", "return", "sizeof", "decltype"):
            return None
        kind = "constructor" if owner and name == owner else "function"
        return (name, kind, is_static)
    match = re.search(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*(?:=|;|$)", work)
    if match:
        return (match.group(1), "variable", is_static)
    return None


def format_signature(declaration: str) -> str:
    """cpprefjp 風に、テンプレート宣言部を改行して見せる。"""
    if "\n" in declaration:
        first, _, rest = declaration.partition("\n")
        prefix, work = split_template_prefix(first)
        body = f"{work}\n{rest}" if work else rest
        return f"{prefix}\n{body}" if prefix else body
    prefix, work = split_template_prefix(declaration)
    work = " ".join(work.split())
    if work and not work.endswith((";", ",")):
        work += ";"
    lines = [" ".join(part.split()) for part in prefix.split("\x00") if part.strip()]
    if prefix:
        template, _, requires = prefix.partition("requires")
        lines = [" ".join(template.split())]
        if requires:
            lines.append("requires " + " ".join(requires.split()))
    return "\n".join([*lines, work]) if prefix else work


def extract_entities(source: str) -> tuple[DocBlock, list[Entity]]:
    lines = source.splitlines()
    contexts = scope_contexts(lines)
    file_doc = DocBlock()
    roots: list[Entity] = []
    by_path: dict[tuple[str, ...], Entity] = {}

    index = 0
    while index < len(lines):
        if not DOC_LINE_RE.match(lines[index]):
            index += 1
            continue
        block: list[str] = []
        start = index
        while index < len(lines) and DOC_LINE_RE.match(lines[index]):
            block.append(lines[index])
            index += 1

        doc = parse_doc_block(block)
        scope = contexts[start]
        if doc.is_file_doc:
            file_doc = doc
            continue
        if doc.is_empty():
            continue
        declaration = declaration_after(lines, index)
        if not declaration:
            continue
        owner = scope.class_path[-1] if scope.class_path else ""
        symbol = symbol_and_kind(declaration, owner)
        if symbol is None:
            continue
        name, kind, is_static = symbol
        if kind == "concept":
            declaration = concept_declaration_after(lines, index)
        if not scope.public:
            continue

        key = (scope.namespace, *scope.class_path, name)
        parent_key = (scope.namespace, *scope.class_path)
        overload = Overload(signature=format_signature(declaration), doc=doc)
        existing = by_path.get(key)
        if existing is not None and existing.kind not in ("class", "concept"):
            existing.overloads.append(overload)
            continue

        entity = Entity(
            name=name,
            kind=kind,
            overloads=[overload],
            namespace=scope.namespace,
            owner="::".join(scope.class_path),
            is_static=is_static,
        )
        by_path[key] = entity
        parent = by_path.get(parent_key) if scope.class_path else None
        if parent is not None:
            parent.members.append(entity)
        elif scope.class_path:
            parent = ensure_placeholder(by_path, roots, scope, parent_key)
            parent.members.append(entity)
        else:
            roots.append(entity)
    return file_doc, roots


def ensure_placeholder(
    by_path: dict[tuple[str, ...], Entity],
    roots: list[Entity],
    scope: Scope,
    parent_key: tuple[str, ...],
) -> Entity:
    """記述のないクラスの中に記述付きメンバがある場合の受け皿を作る。"""
    entity = by_path.get(parent_key)
    if entity is not None:
        return entity
    name = parent_key[-1]
    entity = Entity(
        name=name,
        kind="class",
        overloads=[Overload(signature=f"struct {name};", doc=DocBlock())],
        namespace=scope.namespace,
        owner="::".join(parent_key[1:-1]),
    )
    by_path[parent_key] = entity
    if len(parent_key) == 2:
        roots.append(entity)
    else:
        grandparent = ensure_placeholder(by_path, roots, scope, parent_key[:-1])
        grandparent.members.append(entity)
    return entity


def problem_index() -> dict[str, list[tuple[str, str]]]:
    """`#include` しているヘッダごとに、検証プログラムと問題URLを集める。"""
    index: dict[str, list[tuple[str, str]]] = {}
    for test in sorted(TEST_DIR.glob("**/*.test.cpp")):
        content = test.read_text(encoding="utf-8")
        problem = PROBLEM_RE.search(content)
        if problem is None:
            continue
        relative = test.relative_to(ROOT).as_posix()
        for include in re.findall(r'#include\s+"([^"]+)"', content):
            index.setdefault(include, []).append((relative, problem.group(1)))
    return index


def primary_entity(header_stem: str, entities: list[Entity]) -> Entity | None:
    stem = header_stem.replace("_", "").lower()
    if not entities:
        return None

    def score(entity: Entity) -> int:
        value = 0
        if entity.name.replace("_", "").lower() == stem:
            value += 100
        if stem in entity.doc.brief.replace("_", "").lower():
            value += 40
        if entity.kind == "class":
            value += 60
        if entity.kind == "concept":
            value -= 10
        if entity.is_internal:
            value -= 80
        return value

    return max(entities, key=score)


def parse_header(
    path: Path,
    problems: dict[str, list[tuple[str, str]]] | None = None,
) -> Header:
    source = path.read_text(encoding="utf-8")
    file_doc, entities = extract_entities(source)
    include = path.relative_to(LIB_DIR).as_posix()
    primary = primary_entity(path.stem, entities)

    if file_doc.brief:
        title = file_doc.brief
        summary_doc = file_doc
    elif primary is not None:
        title = primary.doc.brief or include
        summary_doc = primary.doc
    else:
        title = include
        summary_doc = DocBlock()
    summary = "\n\n".join(part for part in summary_doc.details if part)

    return Header(
        path=path,
        relative_path=path.relative_to(ROOT).as_posix(),
        include=include,
        category=path.parent.relative_to(LIB_DIR).as_posix(),
        stem=path.stem,
        doc=file_doc,
        entities=entities,
        title=title,
        summary=summary,
        problems=(problems or {}).get(include, []),
    )


def library_headers(excluded: frozenset[str] = frozenset()) -> list[Path]:
    return sorted(
        path
        for path in LIB_DIR.glob("**/*.hpp")
        if path.parent.relative_to(LIB_DIR).as_posix() not in excluded
    )
