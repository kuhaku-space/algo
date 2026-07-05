#pragma once
#include <cstddef>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

/// @brief hash-consing (不変な木/DAG ノードのインターン)
/// @details @c (tag, 子 id の列) の組を一意な整数 id に写す。構造的に等しい
///   ノードは必ず同じ id になるため、木・式・型の等価判定が O(1) の整数比較に
///   なる。子は既にインターン済みの id で渡す (葉から根へボトムアップに構築)。
///   共通する部分木は 1 ノードに共有されるので、生成されるのは DAG。
///   式/型の等価判定、相異なる部分木の数え上げ・重複排除、共通部分式の共有
///   などに使う。
/// @tparam Tag ノードのラベル型。@c std::hash と @c == を持つ型
///   (@c int ・@c char ・@c std::string 等)。
template <class Tag = int>
struct HashCons {
    /// @brief ノード @c (tag, children) をインターンして id を返す
    /// @details 同じ @c (tag, children) に対しては常に同じ id を返す。
    ///   @c children は各要素が既存の id (@c [0, size()) の範囲) であること。
    int intern(const Tag &tag, std::vector<int> children = {}) {
        Key key{tag, std::move(children)};
        if (auto it = ids.find(key); it != ids.end()) return it->second;
        int id = static_cast<int>(nodes.size());
        nodes.push_back(key);
        ids.emplace(std::move(key), id);
        return id;
    }

    /// @brief ノード @c id のラベル
    const Tag &tag(int id) const { return nodes[id].tag; }
    /// @brief ノード @c id の子 id 列
    const std::vector<int> &children(int id) const { return nodes[id].children; }
    /// @brief ノード @c id の @c k 番目の子 id
    int child(int id, std::size_t k) const { return nodes[id].children[k]; }
    /// @brief ノード @c id の子の数
    std::size_t arity(int id) const { return nodes[id].children.size(); }
    /// @brief 相異なるノード (id) の総数
    int size() const { return static_cast<int>(nodes.size()); }

  private:
    struct Key {
        Tag tag;
        std::vector<int> children;
        bool operator==(const Key &o) const { return tag == o.tag && children == o.children; }
    };
    struct KeyHash {
        std::size_t operator()(const Key &k) const {
            std::size_t h = std::hash<Tag>{}(k.tag);
            for (int c : k.children) h ^= std::hash<int>{}(c) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
            return h;
        }
    };

    std::vector<Key> nodes;
    std::unordered_map<Key, int, KeyHash> ids;
};
