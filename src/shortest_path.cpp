#include "shortest_path.h"
#include <algorithm>
#include <climits>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using graph_path = std::tuple<node_ptr, node_ptr, uint32_t>;

std::vector<graph_path> shortest_path(node_ptr source, node_ptr dest)
{
  // Create all nodes
  // Create edges based on picture

  std::unordered_map<char, node_ptr> seen;
  auto cmp = [](const graph_path& g1, const graph_path& g2) {
    return std::get<2>(g1) > std::get<2>(g2);
  };

  auto pq =
    std::priority_queue<graph_path, std::vector<graph_path>, decltype(cmp)>(
      cmp);

  auto charted_path = std::vector<graph_path>();
  int total_cost = 0;
  pq.push(std::make_tuple(nullptr, source, 0));  // dummy entry
  while (!pq.empty()) {
    auto cur_tuple = pq.top();
    pq.pop();
    auto current_node = std::get<1>(cur_tuple);
    if (seen.contains(current_node->label)) {
      continue;
    }

    if (current_node == dest || current_node->label == dest->label) {
      auto res = std::vector<graph_path>();
      auto parent_node = std::get<0>(cur_tuple);
      res.push_back(cur_tuple);
      while (parent_node != source) {
        current_node = parent_node;
        int min_dist = INT_MAX;
        graph_path min_graph_path(nullptr, nullptr, -1);
        for (auto g : charted_path) {
          if (std::get<1>(g) == current_node && std::get<2>(g) < min_dist) {
            min_graph_path = g;
            min_dist = std::get<2>(g);
          }
        }
        if (std::get<1>(min_graph_path) == nullptr &&
            std::get<2>(min_graph_path) == -1) {
          throw std::out_of_range("HUH??");
        }

        res.push_back(min_graph_path);
        parent_node = std::get<0>(min_graph_path);
      }

      std::reverse(res.begin(), res.end());
      return res;
    }

    seen[current_node->label] = current_node;
    total_cost = std::get<2>(cur_tuple);

    if (std::get<0>(cur_tuple) != nullptr) {
      charted_path.push_back(cur_tuple);
    }

    for (auto neighbor_pair : current_node->adj) {
      pq.push(std::make_tuple(
        current_node, neighbor_pair.first, neighbor_pair.second + total_cost));
    }
  }

  return {};  // didn't find it

  // Now, set up priority queue, pq will have 3 things: parent
  // node, current node, and cost to get to current node (prev adjency cost +
  // weight from parent to current)

  // Priorty given to smallest
  // append starting location (source) to pq, parent is null
  // while pq is not empty, pop queue, validate node (have we seen it? if we
  // have, ignore). append all neighbors to the priority queue, their parent is
  // the popped node goes into the seen list
  // if popped node is dest, great, walk back the list until you hit null, thats
  // your path
  // If you break out of the while loop, doesn't exist
}