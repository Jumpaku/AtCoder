#include "../template.hpp"

/**
 * GRAPH_SEARCH
 */
namespace graph_search {

template <class V, class F,
          enable_if_t<is_invocable_v<F, opt<V>, V>, nullptr_t> = nullptr>
void dfs_impl(graph<V> const &g, V const &v, F const &process,
              u_set<V> &visited) {
  if (g.find(v) == g.end())
    return;
  for (auto const &u : g.at(v)) {
    if (visited.find(u) == visited.end()) {
      visited.insert(u);
      process(opt<V>{v}, u);
      dfs_impl(g, u, process, visited);
    }
  }
}
template <class V, class F,
          enable_if_t<is_invocable_v<F, opt<V>, V>, nullptr_t> = nullptr>
void dfs(graph<V> const &g, V const &root, F const &process) {
  u_set<V> visited{root};
  process(nullopt, root);
  dfs_impl(g, root, process, visited);
}
template <class V, class F,
          enable_if_t<is_invocable_v<F, opt<V>, V>, nullptr_t> = nullptr>
void bfs(graph<V> const &g, V const &root, F const &process) {
  list<pair<opt<V>, V>> l{{nullopt, root}};
  u_set<V> visited{root};
  while (!l.empty()) {
    auto [parent, v] = l.front();
    l.pop_front();
    process(parent, v);
    if (g.find(v) == g.end())
      return;
    for (auto const &u : g.at(v)) {
      if (visited.find(u) == visited.end()) {
        l.push_back({{v}, u});
        visited.insert(u);
      }
    }
  }
}
} // namespace graph_search

using graph_search::dfs, graph_search::bfs;
/* end of GRAPH_SEARCH */