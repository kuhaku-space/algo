#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief LowLink
 *
 * @tparam T
 */
template <class T>
struct LowLink {
    LowLink(const Graph<T> &_graph)
        : graph(_graph), ord(_graph.size()), low(_graph.size()), used(_graph.size()) {
        this->build();
    }

    /**
     * @brief Get the articulation points object
     *
     * @return std::vector<int>
     */
    auto get_articulation_points() { return this->articulation_points; }
    /**
     * @brief Get the bridges object
     *
     * @return std::vector<typename Graph<T>::edge_type>
     */
    auto get_bridges() { return this->bridges; }

  private:
    const Graph<T> &graph;
    std::vector<int> ord, low;
    std::vector<bool> used;
    std::vector<int> articulation_points;               // 関節点
    std::vector<typename Graph<T>::edge_type> bridges;  // 橋

    void build() {
        int number = 0;
        for (int i = 0; i < this->graph.size(); i++) {
            if (!this->used[i]) number = this->dfs(i, number, -1);
        }
    }

    int dfs(int index, int number, int parent) {
        this->used[index] = true;
        this->ord[index] = number++;
        this->low[index] = this->ord[index];
        bool is_articulation_point = false;
        int count = 0;
        for (auto &e : this->graph[index]) {
            if (!this->used[e.to]) {
                ++count;
                number = this->dfs(e.to, number, index);
                chmin(low[index], low[e.to]);
                is_articulation_point |= ~parent && this->low[e.to] >= this->ord[index];
                if (this->ord[index] < this->low[e.to]) this->bridges.emplace_back(e);
            } else if (e.to != parent) {
                chmin(this->low[index], this->ord[e.to]);
            }
        }
        is_articulation_point |= parent == -1 && count > 1;
        if (is_articulation_point) this->articulation_points.emplace_back(index);
        return number;
    }
};

template <>
struct LowLink<void> {
    LowLink(const Graph<void> &_graph)
        : graph(_graph), ord(_graph.size()), low(_graph.size()), used(_graph.size()) {
        this->build();
    }

    auto get_articulation_points() { return this->articulation_points; }
    auto get_bridges() { return this->bridges; }

  private:
    const Graph<void> &graph;
    std::vector<int> ord, low;
    std::vector<bool> used;
    std::vector<int> articulation_points;                  // 関節点
    std::vector<typename Graph<void>::edge_type> bridges;  // 橋

    void build() {
        int number = 0;
        for (int i = 0; i < this->graph.size(); i++) {
            if (!this->used[i]) number = this->dfs(i, number, -1);
        }
    }

    int dfs(int index, int number, int parent) {
        this->used[index] = true;
        this->ord[index] = number++;
        this->low[index] = this->ord[index];
        bool is_articulation_point = false;
        int count = 0;
        for (auto &e : this->graph[index]) {
            if (!this->used[e]) {
                ++count;
                number = this->dfs(e, number, index);
                chmin(low[index], low[e]);
                is_articulation_point |= ~parent && this->low[e] >= this->ord[index];
                if (this->ord[index] < this->low[e]) this->bridges.emplace_back(index, e);
            } else if (e != parent) {
                chmin(this->low[index], this->ord[e]);
            }
        }
        is_articulation_point |= parent == -1 && count > 1;
        if (is_articulation_point) this->articulation_points.emplace_back(index);
        return number;
    }
};
