#include "kruskals.h"

struct tupleCompare {
  constexpr bool
  operator()(const tuple<int, shared_ptr<Node>, shared_ptr<Node>> &lhs,
             const tuple<int, shared_ptr<Node>, shared_ptr<Node>> &rhs) const {
    return get<0>(lhs) > get<0>(rhs);
  };
};

// similar to prim's however reading in all edges into priority queue and then
// popping and comparing with seen set to make sure all nodes are visited once
vector<tuple<shared_ptr<Node>, shared_ptr<Node>, int>>
kruskals_algo(shared_ptr<Node> &node_ptr) {
  vector<tuple<shared_ptr<Node>, shared_ptr<Node>, int>> MST;

  priority_queue<tuple<int, shared_ptr<Node>, shared_ptr<Node>>,
                 vector<tuple<int, shared_ptr<Node>, shared_ptr<Node>>>,
                 tupleCompare>
      adj_queue;

  unordered_set<char> seen;

  for (auto it : node_ptr->all_nodes) {
    for (auto iter : it.second->adj) {
      adj_queue.emplace(iter.second, it.second, iter.first);
    }
  }

  // insert first node of prio queue which will be the "start"
  seen.insert(get<1>(adj_queue.top())->label);
  while (!adj_queue.empty()) {
    auto min_edge = adj_queue.top();
    adj_queue.pop();

    if ((seen.find((get<2>(min_edge))->label) != seen.end())) {
      continue;
    }

    MST.emplace_back(get<1>(min_edge), get<2>(min_edge), get<0>(min_edge));
    seen.insert((get<2>(min_edge)->label));
  }

  return MST;
}
