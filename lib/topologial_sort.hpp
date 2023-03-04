/**
 * TOPOLOGICAL_SORT
 */
#ifndef JUMPAKU_TOPOLOGICAL_SORT_HPP
#define JUMPAKU_TOPOLOGICAL_SORT_HPP

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

vecl topologicalSort(const vec<std::set<ll>> &graph) {
  vecl indegree(graph.size());
  for (const auto &v : graph) {
    for (const auto &to : v) {
      ++indegree[to];
    }
  }

  std::queue<ll> q;
  for (int i = 0; i < (int)graph.size(); ++i) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }

  vecl result;
  while (!q.empty()) {
    const auto from = q.front();
    q.pop();
    result.push_back(from);
    for (const auto &to : graph.at(from)) {
      --indegree[to];
      if (indegree[to] == 0) {
        q.push(to);
      }
    }
  }

  if (result.size() != graph.size()) {
    return {};
  }

  return result;
}

#endif
/* end of TOPOLOGICAL_SORT */