"""モデルから cpprefjp 風の Markdown ページを書き出す。

ページの粒度（ヘッダページとエンティティページの 2 段）は
docs/current/reference-pipeline.md を参照。
"""

from __future__ import annotations

import json
import re
from dataclasses import dataclass
from pathlib import Path

from .model import DocBlock, Entity, Header

OPERATOR_SLUGS = {
    "[]": "subscript",
    "()": "call",
    "<=>": "compare",
    "<<": "shift-left",
    ">>": "shift-right",
    "==": "equal",
    "!=": "not-equal",
    "<=": "less-equal",
    ">=": "greater-equal",
    "<": "less",
    ">": "greater",
    "=": "assign",
    "+=": "add-assign",
    "-=": "subtract-assign",
    "*=": "multiply-assign",
    "/=": "divide-assign",
    "%=": "modulo-assign",
    "^=": "xor-assign",
    "&=": "and-assign",
    "|=": "or-assign",
    "<<=": "shift-left-assign",
    ">>=": "shift-right-assign",
    "++": "increment",
    "--": "decrement",
    "+": "add",
    "-": "subtract",
    "*": "multiply",
    "/": "divide",
    "%": "modulo",
    "^": "xor",
    "&": "and",
    "|": "or",
    "~": "complement",
    "!": "not",
    "->": "arrow",
    ",": "comma",
}

KIND_LABELS = {
    "header": "ヘッダ",
    "class": "クラス",
    "concept": "コンセプト",
    "alias": "型エイリアス",
    "function": "関数",
    "operator": "演算子",
    "variable": "変数",
    "constructor": "コンストラクタ",
    "destructor": "デストラクタ",
}

MEMBER_GROUPS = (
    ("構築・破棄", ("constructor", "destructor")),
    ("メンバ関数", ("function",)),
    ("演算子", ("operator",)),
    ("静的メンバ関数", ("static-function",)),
    ("メンバ型", ("alias", "class", "concept")),
    ("メンバ変数", ("variable",)),
)

# 実装詳細と提出用テンプレート。リンク先としてページは作るが、一覧では最後に置く。
SUPPORTING_CATEGORIES = ("internal", "template")

HEADER_GROUPS = (
    ("クラス", ("class",)),
    ("コンセプト", ("concept",)),
    ("関数", ("function", "operator")),
    ("型エイリアス", ("alias",)),
    ("変数", ("variable",)),
)


def category_order(name: str) -> tuple[int, str]:
    return (1 if name in SUPPORTING_CATEGORIES else 0, name)


def slugify(name: str) -> str:
    if name.startswith("operator"):
        token = name.removeprefix("operator").strip()
        if not token:
            return "operator"
        if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_ ]*", token):
            return "operator-" + token.replace(" ", "-").lower()
        return "operator-" + OPERATOR_SLUGS.get(token, "symbol")
    if name.startswith("~"):
        return "destructor-" + name[1:]
    return name


def escape_cell(text: str) -> str:
    return text.replace("|", r"\|").replace("\n", "<br>")


def code(text: str) -> str:
    return f"`{text}`" if text else ""


def member_kind(entity: Entity) -> str:
    if entity.is_static and entity.kind in ("function", "operator"):
        return "static-function"
    return entity.kind


@dataclass(frozen=True)
class PageRef:
    """生成するページ 1 枚の識別子。"""

    path: str
    title: str
    kind: str
    header_slug: str
    entity: str = ""

    @property
    def url(self) -> str:
        return self.path.removesuffix(".md") + ".html"


class Section:
    """見出しと本文を順に積む小さなビルダ。"""

    def __init__(self) -> None:
        self.parts: list[str] = []

    def add(self, text: str) -> None:
        text = text.strip("\n")
        if text:
            self.parts.append(text)

    def heading(self, level: int, title: str, anchor: str = "") -> None:
        suffix = f" {{#{anchor}}}" if anchor else ""
        self.parts.append(f"{'#' * level} {title}{suffix}")

    def table(self, columns: list[str], rows: list[list[str]]) -> None:
        if not rows:
            return
        self.parts.append(
            "\n".join(
                [
                    "| " + " | ".join(columns) + " |",
                    "|" + "|".join(" --- " for _ in columns) + "|",
                    *("| " + " | ".join(row) + " |" for row in rows),
                ]
            )
        )

    def cpp(self, text: str) -> None:
        self.parts.append(f"```cpp\n{text.strip()}\n```")

    def render(self) -> str:
        return "\n\n".join(self.parts) + "\n"


def front_matter(values: dict[str, str]) -> str:
    lines = ["---"]
    for key, value in values.items():
        lines.append(f"{key}: {json.dumps(value, ensure_ascii=False)}")
    lines.append("---")
    return "\n".join(lines) + "\n\n"


def describe_paragraphs(section: Section, doc: DocBlock) -> None:
    for detail in doc.details:
        section.add(detail)


def render_parameters(section: Section, doc: DocBlock, level: int = 2) -> None:
    if doc.tparams:
        section.heading(level, "テンプレートパラメータ")
        section.table(
            ["名前", "説明"],
            [[code(name), escape_cell(text) or "—"] for name, text in doc.tparams],
        )
    if doc.params:
        section.heading(level, "パラメータ")
        section.table(
            ["名前", "説明"],
            [[code(name), escape_cell(text) or "—"] for name, text in doc.params],
        )


def render_result(section: Section, doc: DocBlock, level: int = 2) -> None:
    if doc.returns:
        section.heading(level, "戻り値")
        for value in doc.returns:
            section.add(value)
    if doc.preconditions:
        section.heading(level, "事前条件")
        section.add("\n".join(f"- {value}" for value in doc.preconditions))
    if doc.complexities:
        section.heading(level, "計算量")
        section.add("\n".join(f"- {value}" for value in doc.complexities))


def render_notes(section: Section, doc: DocBlock, level: int = 2) -> None:
    if doc.warnings:
        section.heading(level, "注意")
        section.add("\n".join(f"- {value}" for value in doc.warnings))
    if doc.notes:
        section.heading(level, "備考")
        section.add("\n".join(f"- {value}" for value in doc.notes))


def render_references(section: Section, doc: DocBlock) -> None:
    if not doc.references:
        return
    section.heading(2, "参照")
    items = []
    for reference in doc.references:
        if reference.startswith(("http://", "https://")):
            items.append(f"- [{reference}]({reference})")
        else:
            items.append(f"- {reference}")
    section.add("\n".join(items))


def render_examples(section: Section, doc: DocBlock, outputs: list[str]) -> None:
    if not doc.examples:
        return
    section.heading(2, "例")
    for index, example in enumerate(doc.examples):
        section.cpp(example)
        output = outputs[index] if index < len(outputs) else ""
        if output:
            section.heading(3, "出力")
            section.parts.append(f"```\n{output.rstrip()}\n```")


def overload_groups(entity: Entity) -> list[tuple[list[int], DocBlock]]:
    """同じ記述のオーバーロードをまとめ、(番号, 記述) の並びにする。"""
    groups: list[tuple[list[int], DocBlock]] = []
    for index, overload in enumerate(entity.overloads, start=1):
        for numbers, doc in groups:
            if doc.key() == overload.doc.key():
                numbers.append(index)
                break
        else:
            groups.append(([index], overload.doc))
    return groups


def overload_label(numbers: list[int]) -> str:
    return "、".join(f"({number})" for number in numbers)


def signature_block(entity: Entity) -> str:
    if len(entity.overloads) == 1:
        return entity.signatures[0]
    return "\n\n".join(
        f"// ({number})\n{signature}"
        for number, signature in enumerate(entity.signatures, start=1)
    )


def doc_bullets(doc: DocBlock) -> str:
    """パラメータや戻り値を箇条書き 1 つにまとめる。"""
    bullets: list[str] = []
    bullets.extend(
        f"- **テンプレートパラメータ** {code(name)}: {text}" for name, text in doc.tparams
    )
    bullets.extend(f"- **パラメータ** {code(name)}: {text}" for name, text in doc.params)
    bullets.extend(f"- **戻り値**: {value}" for value in doc.returns)
    bullets.extend(f"- **事前条件**: {value}" for value in doc.preconditions)
    bullets.extend(f"- **計算量**: {value}" for value in doc.complexities)
    bullets.extend(f"- **注意**: {value}" for value in doc.warnings)
    bullets.extend(f"- **備考**: {value}" for value in doc.notes)
    return "\n".join(bullets)


def column_values(groups: list[tuple[list[int], DocBlock]], select) -> str:
    """一覧表のセルを、必要ならオーバーロード番号付きで組み立てる。"""
    labelled: list[tuple[str, str]] = []
    for numbers, doc in groups:
        values = select(doc)
        if not values:
            continue
        text = "、".join(values) if isinstance(values, list) else values
        labelled.append((overload_label(numbers), text))
    if not labelled:
        return "—"
    unique = {text for _, text in labelled}
    if len(unique) == 1:
        return escape_cell(labelled[0][1])
    return escape_cell("<br>".join(f"{label} {text}" for label, text in labelled))



def inline_description(doc: DocBlock) -> str:
    """一覧表の 1 セルに入れる短い説明。"""
    text = doc.brief or (doc.details[0] if doc.details else "")
    return escape_cell(text) or "—"


def member_anchor(entity: Entity) -> str:
    return f"member-{slugify(entity.name)}"


def needs_detail(entity: Entity) -> bool:
    if len(entity.overloads) > 1:
        return True
    if entity.members:
        return True
    return entity.doc.has_detail_beyond_brief()


class ReferenceRenderer:
    """1 つのライブラリ全体を Markdown ツリーへ変換する。"""

    def __init__(self, headers: list[Header]) -> None:
        self.headers = headers
        self.pages: list[PageRef] = []
        self.example_outputs: dict[str, list[str]] = {}
        self._entity_slugs: dict[str, dict[int, str]] = {}
        for header in headers:
            self._entity_slugs[header.slug] = self._assign_slugs(header)

    def _assign_slugs(self, header: Header) -> dict[int, str]:
        used: dict[str, int] = {}
        slugs: dict[int, str] = {}
        for entity in header.entities:
            slug = slugify(entity.name)
            key = slug.lower()
            count = used.get(key, 0)
            used[key] = count + 1
            slugs[id(entity)] = slug if count == 0 else f"{slug}-{count + 1}"
        return slugs

    def entity_slug(self, header: Header, entity: Entity) -> str:
        return self._entity_slugs[header.slug][id(entity)]

    def header_page_path(self, header: Header) -> str:
        return f"{header.category}/{header.stem}.md"

    def entity_page_path(self, header: Header, entity: Entity) -> str:
        return f"{header.category}/{header.stem}/{self.entity_slug(header, entity)}.md"

    def entity_link(self, header: Header, entity: Entity, *, from_header: bool) -> str:
        slug = self.entity_slug(header, entity)
        target = f"{header.stem}/{slug}.md" if from_header else f"{slug}.md"
        return f"[{code(entity.name)}]({target})"

    def render_all(self) -> dict[str, str]:
        files: dict[str, str] = {}
        for header in self.headers:
            files[self.header_page_path(header)] = self.render_header(header)
            for entity in header.entities:
                path = self.entity_page_path(header, entity)
                files[path] = self.render_entity(header, entity)
        files["index.md"] = self.render_index()
        files["reference.json"] = json.dumps(
            self.build_index(), ensure_ascii=False, indent=1
        )
        return files

    def outputs_for(self, header: Header, entity: Entity | None = None) -> list[str]:
        key = header.slug if entity is None else f"{header.slug}#{entity.name}"
        return self.example_outputs.get(key, [])

    def render_header(self, header: Header) -> str:
        section = Section()
        section.heading(1, header.title)
        section.add(f"*{header.relative_path}*")
        if header.summary:
            section.heading(2, "概要")
            section.add(header.summary)
        section.heading(2, "インクルード")
        section.cpp(f'#include "{header.include}"')

        for label, kinds in HEADER_GROUPS:
            entities = [
                entity
                for entity in header.entities
                if entity.kind in kinds and not entity.is_internal
            ]
            if not entities:
                continue
            section.heading(2, label)
            section.table(
                ["名前", "説明"],
                [
                    [
                        self.entity_link(header, entity, from_header=True),
                        inline_description(entity.doc),
                    ]
                    for entity in entities
                ],
            )
        internal = [entity for entity in header.entities if entity.is_internal]
        if internal:
            section.heading(2, "内部実装")
            section.add("直接使うことは想定していないが、公開 API の基底として現れる。")
            section.table(
                ["名前", "説明"],
                [
                    [
                        self.entity_link(header, entity, from_header=True),
                        inline_description(entity.doc),
                    ]
                    for entity in internal
                ],
            )

        render_examples(section, header.doc, self.outputs_for(header))
        render_notes(section, header.doc)
        render_references(section, header.doc)
        if header.problems:
            section.heading(2, "検証")
            section.add(
                "\n".join(
                    f"- [{path}]({url})" for path, url in sorted(set(header.problems))
                )
            )
        return (
            front_matter(
                {
                    "title": header.title,
                    "reference_kind": "header",
                    "reference_category": header.category,
                    "reference_slug": header.slug,
                    "reference_source": header.relative_path,
                    "reference_include": header.include,
                }
            )
            + section.render()
        )

    def render_entity(self, header: Header, entity: Entity) -> str:
        section = Section()
        section.heading(1, entity.name)
        section.add(
            f"*{KIND_LABELS.get(entity.kind, entity.kind)}* · "
            f"[{header.title}](../{header.stem}.md)"
        )
        section.cpp(signature_block(entity))
        self.render_description(section, entity)
        if entity.members:
            self.render_members(section, entity)
        render_examples(section, entity.doc, self.outputs_for(header, entity))
        self.render_related(section, header, entity)
        render_references(section, entity.doc)
        return (
            front_matter(
                {
                    "title": entity.name,
                    "reference_kind": entity.kind,
                    "reference_category": header.category,
                    "reference_slug": header.slug,
                    "reference_source": header.relative_path,
                    "reference_include": header.include,
                    "reference_entity": entity.qualified_name,
                }
            )
            + section.render()
        )

    def render_description(self, section: Section, entity: Entity) -> None:
        """概要以下を書く。オーバーロードで記述が違えば番号を振って並べる。"""
        groups = overload_groups(entity)
        if len(groups) == 1:
            doc = groups[0][1]
            if doc.brief or doc.details:
                section.heading(2, "概要")
                section.add(doc.brief)
                describe_paragraphs(section, doc)
            render_parameters(section, doc)
            render_result(section, doc)
            render_notes(section, doc)
            return

        section.heading(2, "概要")
        for numbers, doc in groups:
            label = overload_label(numbers)
            section.add(f"**{label}** {doc.brief}".strip())
            describe_paragraphs(section, doc)
            section.add(doc_bullets(doc))

    def render_members(self, section: Section, entity: Entity) -> None:
        detailed: list[Entity] = []
        for label, kinds in MEMBER_GROUPS:
            members = [
                member for member in entity.members if member_kind(member) in kinds
            ]
            if not members:
                continue
            section.heading(2, label)
            rows: list[list[str]] = []
            for member in members:
                display = (
                    "(constructor)" if member.kind == "constructor" else member.name
                )
                groups = overload_groups(member)
                if needs_detail(member):
                    detailed.append(member)
                    name = f"[{code(display)}](#{member_anchor(member)})"
                else:
                    name = code(display)
                rows.append(
                    [
                        name,
                        column_values(groups, lambda doc: doc.brief),
                        column_values(groups, lambda doc: doc.complexities),
                    ]
                )
            section.table(["名前", "説明", "計算量"], rows)

        if not detailed:
            return
        section.heading(2, "メンバの詳細")
        for member in detailed:
            display = "(constructor)" if member.kind == "constructor" else member.name
            section.heading(3, display, member_anchor(member))
            section.cpp(signature_block(member))
            for numbers, doc in overload_groups(member):
                prefix = (
                    f"**{overload_label(numbers)}** "
                    if len(member.overloads) > 1
                    else ""
                )
                section.add(f"{prefix}{doc.brief}".strip())
                describe_paragraphs(section, doc)
                section.add(doc_bullets(doc))
            if member.members:
                section.table(
                    ["メンバ", "説明"],
                    [
                        [code(nested.name), inline_description(nested.doc)]
                        for nested in member.members
                    ],
                )

    def render_related(self, section: Section, header: Header, entity: Entity) -> None:
        siblings = [item for item in header.entities if item is not entity]
        if not siblings:
            return
        section.heading(2, "関連項目")
        section.add(
            "\n".join(
                f"- {self.entity_link(header, item, from_header=False)}"
                f" — {inline_description(item.doc)}"
                for item in siblings
            )
        )

    def render_index(self) -> str:
        section = Section()
        section.heading(1, "ライブラリリファレンス")
        section.add(
            "競技プログラミング向け C++23 ヘッダオンリーライブラリの日本語リファレンス。"
        )
        by_category: dict[str, list[Header]] = {}
        for header in self.headers:
            by_category.setdefault(header.category, []).append(header)
        for category in sorted(by_category, key=category_order):
            section.heading(2, category)
            section.table(
                ["ヘッダ", "説明"],
                [
                    [
                        f"[{code(header.include)}]({header.category}/{header.stem}.md)",
                        escape_cell(header.title),
                    ]
                    for header in by_category[category]
                ],
            )
        return front_matter({"title": "リファレンス", "reference_kind": "index"}) + section.render()

    def build_index(self) -> dict:
        categories: dict[str, list[dict]] = {}
        entries: list[dict] = []
        for header in self.headers:
            page = f"{header.category}/{header.stem}"
            children = []
            for entity in header.entities:
                slug = self.entity_slug(header, entity)
                children.append(
                    {
                        "name": entity.name,
                        "kind": entity.kind,
                        "url": f"{page}/{slug}.html",
                    }
                )
                entries.append(
                    {
                        "name": entity.name,
                        "kind": entity.kind,
                        "header": header.include,
                        "title": entity.doc.brief,
                        "url": f"{page}/{slug}.html",
                    }
                )
            categories.setdefault(header.category, []).append(
                {
                    "name": header.stem,
                    "include": header.include,
                    "title": header.title,
                    "url": f"{page}.html",
                    "entities": children,
                }
            )
            entries.append(
                {
                    "name": header.include,
                    "kind": "header",
                    "header": header.include,
                    "title": header.title,
                    "url": f"{page}.html",
                }
            )
        return {
            "categories": [
                {"name": name, "headers": categories[name]}
                for name in sorted(categories, key=category_order)
            ],
            "entries": entries,
        }


def write_files(destination: Path, files: dict[str, str]) -> None:
    for name, content in files.items():
        target = destination / name
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(content, encoding="utf-8")
