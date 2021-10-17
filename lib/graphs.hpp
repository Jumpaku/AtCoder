/**
 * GRAPHS
 */

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

namespace graphs {

template <class F>
vec<ll> dijkstra(ll const start, vec<u_set<ll>> const &g, F const &dist) {
  ll N = g.size();
  vecl out(N);
  ll constexpr inf = 1e16;
  for (auto &&v : range(N))
    d[v] = inf;
  auto cmp = [](auto &t0, auto &t1) { return get<0>(t0) > get<0>(t1); };

  auto q = priority_queue<tuple<ll, ll>, decltype(cmp)>(cmp);
  q.emplace(d[start] = 0, start);
  while (!q.empty()) {
    auto u = get<1>(q.top());
    q.pop();
    dump(u, g.at(u), d, n);
    for (auto const &v : g.at(u)) {
      auto alt = d[u] + dist(u, v);
      auto dv = d[v];
      dump(v, d[v], alt);
      if (dv > alt) {
        q.emplace(alt, v);
        d[v] = alt;
      }
    }
    dump(q.size());
  }
  return out;
}
} // namespace graphs

using graphs::dijkstra;
/* Tests
graphs::dfs : https://atcoder.jp/contests/abc177/submissions/16475352
graphs::bfs : https://atcoder.jp/contests/abc177/submissions/16475366
graphs::dijkstra : https://atcoder.jp/contests/abc176/submissions/16475847
*/

/* end of GRAPHS */
