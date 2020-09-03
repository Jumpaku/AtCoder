/**
 * GRAPHS
 */

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

namespace graphs {
template <class G, class V> struct graph_helper {};
template <class V> struct graph_helper<u_graph<V>, V> {
  using graph_type = u_graph<V>;
  using node_type = V;
  template <class U> using buffer_type = u_map<V, U>;
  static vec<V> vertices(u_graph<V> const &g) {
    auto result = vec<V>(g.size());
    transform(g.begin(), g.end(), back_inserter(result),
              [](auto const &a) { return a.first; });
    return result;
  }
};
template <> struct graph_helper<v_graph, int> {
  using graph_type = v_graph;
  using node_type = int;
  template <class U> using buffer_type = vec<U>;
  static vec<int> vertices(v_graph const &g) {
    return vec<int>(begin(), end(g.size()));
  }
};

using longlong = long long int;

template <class G, class V, class F, class Helper = graph_helper<G, V>,
          class Buffer = typename Helper::template buffer_type<longlong>,
          std::enable_if_t<std::is_invocable_r_v<longlong, F, V, V>,
                           nullptr_t> = nullptr>
Buffer dijkstra(V const start, G const &g, F const &dist) {
  Buffer out(g.size());
  longlong constexpr inf = 1e18;
  for (auto &&v : Helper::vertices(g))
    out[v] = inf;
  auto cmp = [](auto &t0, auto &t1) { return get<0>(t0) > get<0>(t1); };

  auto q = priority_queue<tuple<longlong, V>, decltype(cmp)>(cmp);
  q.emplace(out[start] = 0, start);
  while (!q.empty()) {
    auto u = get<1>(q.top());
    q.pop();
    for (auto const &v : g.at(u)) {
      auto alt = out[u] + dist(u, v);
      if (out[v] > alt)
        q.emplace(out[v] = alt, v);
    }
  }
  return out;
}

template <class G, class V, class F, class Helper = graph_helper<G, V>,
          class Buffer = typename Helper::template buffer_type<opt<V>>,
          std::enable_if_t<std::is_invocable_v<F, opt<V>, V> &&
                               (std::is_same_v<G, u_graph<V>> ||
                                (std::is_same_v<G, v_graph> &&
                                 std::is_integral_v<V>)),
                           std::nullptr_t> = nullptr>
void dfs(G const &g, V const &v, F const &process, Buffer &out) {
  process(opt<V>(), v);
  struct {
    G const &g;
    V const &root;
    F const &process;
    Buffer &out;
    void dfs_impl(V const &v) {
      for (V const &u : g.at(v)) {
        if (auto &prev = out[u]; u != root && !prev) {
          process(prev = v, u);
          dfs_impl(u);
        }
      }
    }
  } DFS{g, v, process, out};
  DFS.dfs_impl(v);
}
template <class G, class V, class F, class Helper = graph_helper<G, V>,
          class Buffer = typename Helper::template buffer_type<opt<V>>,
          std::enable_if_t<std::is_invocable_v<F, opt<V>, V> &&
                               (std::is_same_v<G, u_graph<V>> ||
                                (std::is_same_v<G, v_graph> &&
                                 std::is_integral_v<V>)),
                           std::nullptr_t> = nullptr>
void bfs(G const &g, V const &root, F const &process, Buffer &out) {
  list<V> q{root};
  while (!q.empty()) {
    auto v = q.front();
    q.pop_front();
    process(out[v], v);
    for (auto const &u : g.at(v)) {
      if (auto &&prev = out[u]; u != root && !prev) {
        prev = v;
        q.emplace_back(u);
      }
    }
  }
}
} // namespace graphs

using graphs::bfs;
using graphs::dfs;
using graphs::dijkstra;
/* Tests
graphs::dfs : https://atcoder.jp/contests/abc177/submissions/16475352
graphs::bfs : https://atcoder.jp/contests/abc177/submissions/16475366
graphs::dijkstra : https://atcoder.jp/contests/abc176/submissions/16475847
*/

/* end of GRAPHS */
