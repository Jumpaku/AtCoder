/**
 * GRAPHS
 */

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

namespace graphs {
/**
 * dist is a function that takes two nodes u and v,
 *  and returns a distance between from u to v.
 */
template <class F>
vecl dijkstra(ll const start, vec<vecl> const &G, F const &dist) {
  ll constexpr inf = 1e18;
  vecl out(G.size(), inf);
  auto cmp = [](auto &t0, auto &t1) { return get<0>(t0) > get<0>(t1); };

  auto q = priority_queue<tuple<ll, ll>, decltype(cmp)>(cmp);
  q.emplace(out[start] = 0, start);
  while (!q.empty()) {
    auto [d, u] = q.top();
    q.pop();
    if (out[u] < d)
      continue;
    for (auto const &v : G.at(u)) {
      auto alt = out[u] + dist(u, v);
      if (out[v] > alt)
        q.emplace(out[v] = alt, v);
    }
  }
  return out;
}
} // namespace graphs

using graphs::dijkstra;
/* Tests
graphs::dijkstra : https://atcoder.jp/contests/abc176/submissions/16475847
*/

/* end of GRAPHS */
