/**
 * SEARCH
 */

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

/** // BFS Template
using V = tuple<ll, ll>;
using Graph = u_map<V, u_set<V>>;
using Visited = u_set<V>;
using F = fun<void(V)>;
void bfs(Graph const &g, V const &start, Visited &visited, F const &f) {
  auto isVisited = [&](V const &v) -> bool {
    return visited.count(v); // visited
  };
  auto visit = [&](V const &v) -> void {
    visited.insert(v); // mark visited
  };
  if (isVisited(start))
    return;
  list<V> Q{start};
  while (!Q.empty()) {
    auto u = Q.front();
    Q.erase(Q.begin());
    if (isVisited(u))
      continue;
    f(u);
    visit(u);
    for (auto const &v : g.at(u)) {
      if (isVisited(v))
        continue;
      Q.push_back(v);
    }
  }
}
//*/

/* end of SEARCH */