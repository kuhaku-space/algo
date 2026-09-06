"""リファレンス生成の中間表現。

`parse` がヘッダを読んでこのモデルを組み立て、`render` が cpprefjp 風の
Markdown へ変換する。モデルは「ヘッダ 1 つ = Header、名前空間直下の型・関数
= Entity、クラスの中身 = Entity.members、同名のオーバーロード = Entity.overloads」
という素直な木構造にする。
"""

from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path

TYPE_KINDS = frozenset({"class", "concept", "alias"})
FUNCTION_KINDS = frozenset({"function", "constructor", "destructor", "operator"})


@dataclass
class DocBlock:
    """1 つの `///` コメント塊から取り出した記述。"""

    brief: str = ""
    details: list[str] = field(default_factory=list)
    tparams: list[tuple[str, str]] = field(default_factory=list)
    params: list[tuple[str, str]] = field(default_factory=list)
    returns: list[str] = field(default_factory=list)
    complexities: list[str] = field(default_factory=list)
    preconditions: list[str] = field(default_factory=list)
    notes: list[str] = field(default_factory=list)
    warnings: list[str] = field(default_factory=list)
    references: list[str] = field(default_factory=list)
    examples: list[str] = field(default_factory=list)
    is_file_doc: bool = False

    def is_empty(self) -> bool:
        return not (self.brief or self.details)

    def has_detail_beyond_brief(self) -> bool:
        """一覧表の 1 行に収まらない情報を持つか。"""
        return bool(
            self.details
            or self.tparams
            or self.params
            or self.returns
            or self.preconditions
            or self.notes
            or self.warnings
            or self.references
            or self.examples
        )

    def key(self) -> tuple:
        return (
            self.brief,
            tuple(self.details),
            tuple(self.tparams),
            tuple(self.params),
            tuple(self.returns),
            tuple(self.complexities),
            tuple(self.preconditions),
            tuple(self.notes),
            tuple(self.warnings),
            tuple(self.references),
            tuple(self.examples),
        )


@dataclass
class Overload:
    """1 つの宣言と、それに付いていた記述。"""

    signature: str
    doc: DocBlock


@dataclass
class Entity:
    """型・関数・エイリアスなど、リファレンスの見出しになる単位。"""

    name: str
    kind: str
    overloads: list[Overload]
    namespace: str = ""
    owner: str = ""
    is_static: bool = False
    members: list[Entity] = field(default_factory=list)

    @property
    def doc(self) -> DocBlock:
        return self.overloads[0].doc

    @property
    def signatures(self) -> list[str]:
        return [overload.signature for overload in self.overloads]

    @property
    def qualified_name(self) -> str:
        parts = [part for part in (self.namespace, self.owner, self.name) if part]
        return "::".join(parts)

    @property
    def is_internal(self) -> bool:
        return self.namespace.split("::")[0] == "internal"

    @property
    def is_type(self) -> bool:
        return self.kind in TYPE_KINDS

    def complexities(self) -> list[str]:
        values: list[str] = []
        for overload in self.overloads:
            for complexity in overload.doc.complexities:
                if complexity not in values:
                    values.append(complexity)
        return values

    def iter_all(self):
        yield self
        for member in self.members:
            yield from member.iter_all()


@dataclass
class Header:
    """1 つのヘッダと、そこから生成するページの材料。"""

    path: Path
    relative_path: str
    include: str
    category: str
    stem: str
    doc: DocBlock
    entities: list[Entity]
    title: str
    summary: str = ""
    problems: list[tuple[str, str]] = field(default_factory=list)

    @property
    def slug(self) -> str:
        return f"{self.category}/{self.stem}"

    def iter_entities(self):
        for entity in self.entities:
            yield from entity.iter_all()
