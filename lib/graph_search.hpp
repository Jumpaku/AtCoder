
#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

/**
 * GRAPH_SEARCH
 */
namespace graph_search {

template <class V, class F,
          enable_if_t<std::is_constructible<fun<void(opt<V>, V)>, F>::value,
                      nullptr_t> = nullptr>
void dfs_impl(graph<V> const &g, V const &v, F const &process,
              u_set<V> &visited) {
  if (g.find(v) == g.end())
    return;
  for (auto const &u : g.at(v)) {
    if (visited.find(u) == visited.end()) {
      visited.insert(u);
      process(opt<V>(v), u);
      dfs_impl(g, u, process, visited);
    }
  }
} // namespace graph_search
template <class V, class F,
          enable_if_t<std::is_constructible<fun<void(opt<V>, V)>, F>::value,
                      nullptr_t> = nullptr>
void dfs(graph<V> const &g, V const &root, F const &process) {
  u_set<V> visited{root};
  process(opt<V>(nullptr), root);
  dfs_impl(g, root, process, visited);
}
template <class V, class F,
          enable_if_t<std::is_constructible<fun<void(opt<V>, V)>, F>::value,
                      nullptr_t> = nullptr>
void bfs(graph<V> const &g, V const &root, F const &process) {
  list<pair<opt<V>, V>> l{{opt<V>(nullptr), root}};
  u_set<V> visited{root};
  while (!l.empty()) {
    auto parent = l.front().first;
    auto v = l.front().second;
    l.pop_front();
    process(parent, v);
    if (g.find(v) == g.end())
      return;
    for (auto const &u : g.at(v)) {
      if (visited.find(u) == visited.end()) {
        l.push_back({opt<V>(v), u});
        visited.insert(u);
      }
    }
  }
}
} // namespace graph_search

using graph_search::bfs;
using graph_search::dfs;
/* end of GRAPH_SEARCH */