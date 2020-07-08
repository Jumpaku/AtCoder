
#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

/**
 * DIJKSTRA
 */
template <class V, class F,
          enable_if_t<std::is_constructible<fun<ll(V, V)>, F>::value,
                      nullptr_t> = nullptr>
u_map<V, ll> dijkstra(V const start, graph<V> const &g, F const &dist,
                      u_set<V> const &vs) {
  ll constexpr inf = 0x7fff'ffff'ffff'ffff;
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