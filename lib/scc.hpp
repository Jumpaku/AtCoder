/**
 * GEOM
 */

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#endif

namespace scc {
using Node = ll;
using Cost = ll;

class Graph {
  using Edge = std::pair<Node, Cost>;
  using Edges = std::vector<Edge>;

  const int m_n;
  std::vector<Edges> m_graph;

public:
  Graph(int n) : m_n(n), m_graph(n) {}

  auto addEdge(const Node &f, const Node &t, const Cost &c = 1) {
    m_graph[f].emplace_back(t, c);
  }
  auto addEdgeUndirected(const Node &f, const Node &t, const Cost &c = 1) {
    addEdge(f, t, c);
    addEdge(t, f, c);
  }
  auto getEdges(const Node &from) const {
    class EdgesRange {
      const typename Edges::const_iterator b, e;

    public:
      EdgesRange(const Edges &edges) : b(edges.begin()), e(edges.end()) {}
      auto begin() const { return b; }
      auto end() const { return e; }
    };
    return EdgesRange(m_graph[from]);
  }
  auto getEdgesAll() const {
    std::deque<std::pair<Node, Edge>> edges;
    for (Node from = 0; from < m_n; ++from)
      for (const auto &edge : getEdges(from)) {
        edges.emplace_back(from, edge);
      }
    return edges;
  }
  auto getEdgesAll2() const {
    std::deque<std::pair<Node, Node>> edges;
    for (Node from = 0; from < m_n; ++from)
      for (const auto &[to, _] : getEdges(from)) {
        edges.emplace_back(from, to);
      }
    return edges;
  }
  auto reverse() const {
    auto rev = Graph(m_n);
    for (const auto &[from, edge] : getEdgesAll()) {
      auto [to, c] = edge;
      rev.addEdge(to, from, c);
    }
    return rev;
  }
  auto size() const { return m_n; };
};
class StronglyConnectedComponents {

  struct HashPair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2> &p) const {
      auto hash1 = std::hash<T1>{}(p.first);
      auto hash2 = std::hash<T2>{}(p.second);
      size_t seed = 0;
      seed ^= hash1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      seed ^= hash2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      return seed;
    }
  };

  const Graph m_graph;
  const std::vector<int> m_group;

  template <class F>
  static inline auto dfs(const Graph &graph, int from,
                         std::vector<bool> &is_used, const F &f) -> void {
    is_used[from] = true;
    for (const auto &[to, _] : graph.getEdges(from)) {
      if (is_used[to]) {
        continue;
      }
      dfs(graph, to, is_used, f);
    }
    f(from);
  }

  static inline auto constructGroup(const Graph &graph) {
    int n = graph.size();
    std::vector<int> order;
    order.reserve(n);
    std::vector<bool> is_used(n);
    for (int from = 0; from < n; ++from)
      if (!is_used[from]) {
        dfs(graph, from, is_used, [&](int f) { order.emplace_back(f); });
      }

    int g = 0;
    std::vector<int> group(n);
    std::vector<bool> is_used2(n);
    auto rev = graph.reverse();
    for (int i = n - 1; i >= 0; --i)
      if (!is_used2[order[i]]) {
        dfs(rev, order[i], is_used2, [&](int f) { group[f] = g; });
        ++g;
      }
    return group;
  }
  auto constructGroupNodes() const {}

public:
  StronglyConnectedComponents(const Graph &graph)
      : m_graph(graph), m_group(constructGroup(m_graph)) {}
  // graphのコピーコストが大きいのでこっち推奨
  StronglyConnectedComponents(Graph &&graph)
      : m_graph(std::move(graph)), m_group(constructGroup(m_graph)) {}

  auto isSameGroup(int a, int b) const { return m_group[a] == m_group[b]; }
  auto getGroupNodes() const {
    auto size = *std::max_element(m_group.begin(), m_group.end()) + 1;
    std::vector<std::vector<int>> groupNodes(size);
    for (int gi = 0; gi < m_graph.size(); ++gi) {
      groupNodes[m_group[gi]].emplace_back(gi);
    }
    return groupNodes;
  }
  auto getGroupGraph() const {
    std::unordered_set<std::pair<int, int>, HashPair> st;
    st.reserve(m_graph.size());
    for (int f = 0; f < m_graph.size(); ++f)
      for (const auto &[t, _] : m_graph.getEdges(f))
        if (!isSameGroup(f, t)) {
          st.emplace(m_group[f], m_group[t]);
        }
    Graph ret(m_graph.size());
    for (const auto &[f, t] : st) {
      ret.addEdge(f, t);
    }
    return ret;
  }
};
} // namespace scc

using scc::StronglyConnectedComponents;

/* end of GEOM */