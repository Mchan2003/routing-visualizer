#include "prims.h"

struct tupleCompare {
  constexpr bool
  operator()(const tuple<int, shared_ptr<Node>, shared_ptr<Node>> &lhs,
             const tuple<int, shared_ptr<Node>, shared_ptr<Node>> &rhs) const {
    return get<0>(lhs) > get<0>(rhs);
  };
};

vector<tuple<shared_ptr<Node>, shared_ptr<Node>, int>>
prims_algo(shared_ptr<Node> &src_ptr) {
  // tuple containing nodes and edges in spanning tree
  vector<tuple<shared_ptr<Node>, shared_ptr<Node>, int>> MST;

  // priority queue to add adjacent edges as we visit nodes in the graph
  // the priority queue will be used to sort stored adjacent edges so we can
  // find minimum as we traverse the graph
  priority_queue<tuple<int, shared_ptr<Node>, shared_ptr<Node>>,
                 vector<tuple<int, shared_ptr<Node>, shared_ptr<Node>>>,
                 tupleCompare>
      adj_queue;

  // list of names of nodes to check if the node has been seen or not
  unordered_set<char> seen;
  // put starting node in seen
  char starting_node_label = src_ptr->label;
  seen.insert(starting_node_label);

  // push adjacent nodes from starting node into priority queue
  for (const auto &it : src_ptr->adj) {
    adj_queue.emplace(it.second, src_ptr, it.first);

    // cout << get<0>(adj_queue.top()) << " " << get<1>(adj_queue.top())->label
    //      << " " << get<2>(adj_queue.top())->label << "\n";
  }

  shared_ptr<Node> new_adj_node = nullptr;
  while (!adj_queue.empty()) {
    // cout << "Nodes in seen set: \n";
    // for (auto i : seen) {
    //   cout << i << '\n';
    // }
    // printf("looping\n");

    // pop from priority queue and check if destination has been seen
    // values from top will be the minimum edges that are adjacent to visited
    // nodes
    auto min_edge = adj_queue.top();
    adj_queue.pop();

    // cout << "node at top of queue\n"
    //      << "source: " << get<1>(min_edge)->label << " "
    //      << "destination: " << get<2>(min_edge)->label << " "
    //      << "weight: " << get<0>(min_edge) << " \n\n";

    // check to see if label for adjacent (destination) node is already in seen
    // set and move to next loop
    if ((seen.find((get<2>(min_edge))->label) != seen.end())) {
      continue;
    }

    // add current edge to MST in format (src_ptr, dest_ptr, weight)
    MST.emplace_back(get<1>(min_edge), get<2>(min_edge), get<0>(min_edge));

    // mark the destination node as visited by adding char label to seen set
    seen.insert((get<2>(min_edge)->label));
    new_adj_node = get<2>(min_edge);

    // add visited node's adjacent edges to the priority queue
    for (const auto &next_set_of_edges : new_adj_node->adj) {
      adj_queue.emplace(next_set_of_edges.second, new_adj_node,
                        next_set_of_edges.first);
    }
  }

  //   cout << "Nodes in spanning tree\n";
  //   for (auto i : MST) {
  //     cout << "source: " << get<0>(i)->label << " "
  //          << "destination: " << get<1>(i)->label << " "
  //          << "weight: " << get<2>(i) << "\n";
  //   }
  return MST;
}
