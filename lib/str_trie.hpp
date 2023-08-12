/**
 * STR_TRIE
 */
#ifndef JUMPAKU_STR_TRIE_HPP
#define JUMPAKU_STR_TRIE_HPP

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#include "atcoder.hpp"
#endif

#include <memory>
struct str_trie {
  struct Node;
  using NodePtr = std::shared_ptr<Node>;
  struct Node {
    vec<NodePtr> children;
    ll share;
    ll value;
    ll depth;
    ll id;
    Node(ll depth, ll value, ll size, ll id)
        : children(size), share(0), value(value), depth(depth), id(id) {}
    bool is_leaf() const {
      return count(children.begin(), children.end(), nullptr) ==
             children.size();
    }
  };
  ll size;
  NodePtr root;
  std::map<ll, NodePtr> id_to_node;
  ll max_node_id;
  str_trie(ll size)
      : size(size), max_node_id(0),
        root(std::make_shared<Node>(0, -1, size, 0)) {}
  NodePtr new_node(ll depth, ll value) {
    ++max_node_id;
    dump_vars(max_node_id);
    return std::make_shared<Node>(depth, value, size, max_node_id);
  }
  // inserts word and returns id of leaf node
  ll insert(vecl const &word) {
    ll n = word.size();
    auto node = root;
    ++(node->share);
    for (ll i = 0; i < n; i++) {
      ll c = word[i];
      if (node->children[c] == nullptr) {
        auto child = new_node(i, c);
        id_to_node[child->id] = node->children[c] = child;
      }
      node = node->children[c];
      ++(node->share);
    }
    return node->id;
  }
  // find node to which prefix matches from root
  NodePtr prefix_match(vecl const &prefix) {
    ll n = prefix.size();
    auto node = root;
    for (ll i = 0; i < n; i++) {
      ll c = prefix[i];
      if (node->children[c] == nullptr) {
        return nullptr;
      }
      node = node->children[c];
    }
    return node;
  }
};
vecl str_to_vecl(str const &s) {
  vecl v;
  transform(s.begin(), s.end(), back_inserter(v),
            [&](auto c) { return c - 'a'; });
  return v;
}

#endif
/* end of STR_TRIE */