/**
 * GRAPHS
 */

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#endif

namespace graphs
{
  /**
   * dist is a function that takes two nodes u and v,
   *  and returns a distance between from u to v.
   */
  template <class F>
  vecl dijkstra(ll const start, vec<std::set<ll>> const &G, F const &dist)
  {
    ll n = G.size();
    ll const INF = 1e16;
    vecl d(n, INF);
    using P = std::pair<ll, ll>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    d[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
      auto [current_dist, u] = pq.top();
      pq.pop();

      if (current_dist > d[u])
      {
        continue;
      }

      for (ll v : G.at(u))
      {
        ll cost = dist(u, v);

        if (d[u] + cost < d[v])
        {
          d[v] = d[u] + cost;
          pq.push({d[v], v});
        }
      }
    }
    return d;
  }
} // namespace graphs

using graphs::dijkstra;
/* Tests
graphs::dijkstra : https://atcoder.jp/contests/abc176/submissions/16475847
*/

/* end of GRAPHS */
