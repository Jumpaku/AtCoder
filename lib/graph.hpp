#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

namespace graphs {
struct Graph {
  vec<vec<int>> arrows;
  vec<bool> nodes;
  Graph(int const &nNodes) : arrows(nNodes), nodes(nNodes) {}
  Graph(vec<vec<int>> arrows, vec<bool> nodes) : arrows(arrows), nodes(nodes) {}
  static Graph of(graph<int> const &g) {
    int nNodes =
        1 + max_element(g.begin(), g.end(), [&](auto const &u, auto const &v) {
              return u.first < v.first;
            })->first;
    vec<bool> nodes(nNodes, false);
    vec<vec<int>> arrows(nNodes);
    for (auto const &[v, us] : g) {
      nodes[v] = true;
      arrows[v] = vec<int>(us.begin(), us.end());
    }
    return Graph(arrows, nodes);
  }
  bool contains(int const &v) const { return nodes[v]; }
  void insert(int const &from, int const &to) {
    nodes[from] = true;
    nodes[to] = true;
    arrows[from].push_back(to);
  }
  void insert(int const &v) { nodes[v] = true; }
  vec<int> const &operator[](int const &v) const { return arrows[v]; }
  template <class F,
            enable_if_t<std::is_constructible<fun<ll(int, int)>, F>::value,
                        nullptr_t> = nullptr>
  vec<ll> dijkstra(int const start, F const &dist) {
    ll constexpr inf = 0x7fff'ffff'ffff'ffff;
    vecl d(nodes.size(), inf);
    auto cmp = [](auto &t0, auto &t1) { return get<0>(t0) < get<0>(t1); };
    auto q = multiset<tuple<ll, int>, decltype(cmp)>(cmp);
    q.insert(make_tuple(d[start] = 0, start));
    while (!q.empty()) {
      auto u = get<1>(*q.begin());
      q.erase(q.begin());
      if (!contains(u))
        continue;
      auto const &du = d[u];
      for (auto const &v : arrows.at(u)) {
        auto alt = du + dist(u, v);
        if (d[v] > alt)
          q.insert(make_tuple(d[v] = alt, v));
      }
    }
    return d;
  }
  template <
      class F,
      enable_if_t<std::is_constructible<fun<void(opt<int>, int)>, F>::value,
                  nullptr_t> = nullptr>
  void dfs(int const &root, F const &process) {
    vec<bool> visited(nodes.size());
    visited[root] = true;
    process(opt<int>(nullptr), root);
    dfs_impl(root, process, visited);
  }
  template <
      class F,
      enable_if_t<std::is_constructible<fun<void(opt<int>, int)>, F>::value,
                  nullptr_t> = nullptr>
  void bfs(int const &root, F const &process) {
    list<pair<opt<int>, int>> l{{opt<int>(nullptr), root}};
    vec<bool> visited(nodes.size());
    while (!l.empty()) {
      auto parent = l.front().first;
      auto v = l.front().second;
      l.pop_front();
      process(parent, v);
      if (!contains(v))
        return;
      for (auto const &u : arrows.at(v)) {
        if (!visited[u]) {
          l.push_back({opt<int>(v), u});
          visited[u] = true;
        }
      }
    }
  }

private:
  template <
      class F,
      enable_if_t<std::is_constructible<fun<void(opt<int>, int)>, F>::value,
                  nullptr_t> = nullptr>
  void dfs_impl(int const &v, F const &process, vec<bool> &visited) {
    if (!contains(v))
      return;
    for (auto const &u : arrows.at(v)) {
      if (!visited[u]) {
        visited[u] = true;
        process(opt<int>(v), u);
        dfs_impl(u, process, visited);
      }
    }
  }
};
} // namespace graphs
using graphs::Graph;