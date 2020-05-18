#include "../template.hpp"

/**
 * DIJKSTRA
 */
template <class V>
u_map<V, ll> dijkstra(V const start, graph<V> const &g,
                      fun<ll(V, V)> const &dist, u_set<V> const &vs,
                      ll const inf = 1e16) {
  auto d = u_map<V, ll>{};
  for (auto &&v : vs)
    d[v] = inf;
  auto cmp = [](auto &t0, auto &t1) { return get<0>(t0) < get<0>(t1); };
  auto q = multiset<tuple<ll, V>, decltype(cmp)>(cmp);
  q.insert(make_tuple(d[start] = 0, start));
  while (!q.empty()) {
    auto u = get<1>(*q.begin());
    q.erase(q.begin());
    if (g.find(u) == g.end())
      continue;
    for (auto const &v : g.at(u)) {
      auto alt = d[u] + dist(u, v);
      if (d[v] > alt)
        q.insert(make_tuple(d[v] = alt, v));
    }
  }
  return d;
}
/* end of DIJKSTRA */
