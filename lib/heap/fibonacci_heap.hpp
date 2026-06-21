#pragma once
#include <functional>
#include <utility>
#include <vector>

/// @brief フィボナッチヒープ（decrease-key 対応）
/// @details 順序基準の `Key` と付随データ `Value` を保持し、`Comp` で `Key` を比較する。
///          `Comp = std::greater<>` で `Key` 最小をルートにする最小ヒープになる
///          （`binary_heap` / `dary_heap` と同じ規約）。
///          ノードを `std::vector` のプールに置き `int` インデックスで連結する index-pool
///          実装で、`new`/`delete` を一切行わない（コピー・ムーブも自動で正しい）。
///          `push` は安定なハンドルを返し、`update` で decrease-key できる。
/// @note `pop` したノードはプールから物理削除しない（ハンドルの寿命は呼び出し側管理）。
template <class Key, class Value, class Comp = std::less<>>
struct fibonacci_heap {
  private:
    static constexpr int nil = -1;

    struct _node {
        Key key;
        Value value;
        int order;
        int left, right;  // 兄弟（双方向循環リスト）
        int parent, child;
        bool damaged;
    };

  public:
    /// @brief `push` が返す安定ハンドル。`update` に渡してその要素を decrease-key する。
    /// @details 既定構築（`handle{}`）は無効値で `bool` 文脈で `false`。
    struct handle {
        constexpr handle() : idx(nil) {}
        constexpr explicit operator bool() const { return idx >= 0; }
        constexpr bool operator==(const handle &) const = default;

      private:
        friend struct fibonacci_heap;
        constexpr explicit handle(int i) : idx(i) {}
        int idx;
    };

    fibonacci_heap() : pool(), _root(nil), _size(), comp() {}

    constexpr bool empty() const { return _size == 0; }
    constexpr int size() const { return _size; }
    std::pair<Key, Value> top() const { return {pool[_root].key, pool[_root].value}; }

    handle push(Key key, Value value) {
        ++_size;
        int node = make_node(std::move(key), std::move(value));
        if (_root == nil) {
            _root = node;
        } else {
            insert_left(_root, node);
            if (comp(pool[_root].key, pool[node].key)) _root = node;
        }
        return handle(node);
    }
    handle emplace(Key key, Value value) { return push(std::move(key), std::move(value)); }

    void pop() {
        --_size;
        int root = _root;
        // root の子をすべてルートリストへ昇格する（parent を nil に戻す）
        if (pool[root].child != nil) {
            int child = pool[root].child;
            do {
                pool[child].parent = nil;
                child = pool[child].right;
            } while (child != pool[root].child);
            // root と child の双方向リストを連結する
            int left = pool[child].left;
            pool[pool[root].left].right = child;
            pool[pool[child].left].right = root;
            pool[child].left = pool[root].left;
            pool[root].left = left;
            pool[root].child = nil;
        }
        _root = unlink(root);
        if (_root == nil) return;

        // 同じ order の木を併合する（consolidate）
        int nodes[64];
        for (int &x : nodes) x = nil;
        while (_root != nil) {
            int node = _root;
            _root = unlink(node);
            pool[node].damaged = false;
            int order = pool[node].order;
            while (nodes[order] != nil) {
                if (comp(pool[node].key, pool[nodes[order]].key)) std::swap(node, nodes[order]);
                add_child(node, nodes[order]);
                nodes[order] = nil;
                ++order;
            }
            nodes[order] = node;
        }

        // 併合後の木をルートリストへ繋ぎ直し、最上位を _root にする
        for (int node : nodes) {
            if (node == nil) continue;
            if (_root == nil) {
                _root = node;
            } else {
                insert_left(_root, node);
                if (comp(pool[_root].key, pool[node].key)) _root = node;
            }
        }
    }

    /// @brief ハンドルの順序基準 `key` を更新する（ルート側へ近づく更新のみ反映）。
    /// @details 最小ヒープ（`greater<>`）では「より小さい key」への更新、つまり
    ///          decrease-key に対応する。逆向きの更新は無視する。
    void update(handle h, Key key) {
        int node = h.idx;
        if (!comp(pool[node].key, key)) return;
        pool[node].key = std::move(key);
        int parent = pool[node].parent;
        // ルート上のノードなら最上位判定のみ
        if (parent == nil) {
            if (comp(pool[_root].key, pool[node].key)) _root = node;
            return;
        }
        // ヒープ条件を満たしているなら何もしない
        if (!comp(pool[parent].key, pool[node].key)) return;
        // node を切り離し、親へカスケードカットを伝播させる
        cut(node, parent);
        cascading_cut(parent);
        if (comp(pool[_root].key, pool[node].key)) _root = node;
    }

  private:
    std::vector<_node> pool;
    int _root;
    int _size;
    Comp comp;

    int make_node(Key key, Value value) {
        int idx = (int)pool.size();
        pool.push_back({std::move(key), std::move(value), 0, idx, idx, nil, nil, false});
        return idx;
    }

    // parent の子リストへ node を追加する。parent と order を更新する
    void add_child(int parent, int node) {
        pool[node].parent = parent;
        if (pool[parent].child != nil) insert_left(pool[parent].child, node);
        else pool[parent].child = node;
        ++pool[parent].order;
    }

    // pos の左隣（前）へ node を挿入する
    void insert_left(int pos, int node) {
        int l = pool[pos].left;
        pool[node].right = pos;
        pool[node].left = l;
        pool[l].right = node;
        pool[pos].left = node;
    }

    // node を兄弟リストから外す（parent は触らない）。
    // 外したあと参照できる兄弟（なければ nil）を返す
    int unlink(int node) {
        if (pool[node].left == node) { return nil; }
        int l = pool[node].left, r = pool[node].right;
        pool[l].right = r;
        pool[r].left = l;
        pool[node].left = pool[node].right = node;
        return l;
    }

    // node を親 parent から切り離してルートリストへ移す
    void cut(int node, int parent) {
        int sibling = unlink(node);
        if (pool[parent].child == node) pool[parent].child = sibling;
        --pool[parent].order;
        pool[node].parent = nil;
        pool[node].damaged = false;
        insert_left(_root, node);
    }

    // 親方向へカスケードカットを伝播させる
    void cascading_cut(int node) {
        int parent;
        while ((parent = pool[node].parent) != nil) {
            if (!pool[node].damaged) {
                pool[node].damaged = true;
                break;
            }
            cut(node, parent);
            node = parent;
        }
    }
};
