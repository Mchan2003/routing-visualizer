#include "node.h"
#include <cmath>
#include <functional>
#include <stdexcept>
#include <utility>

uint32_t distance_function(std::pair<uint32_t, uint32_t> p1,
                           std::pair<uint32_t, uint32_t> p2)
{
  int a = (int)abs((int)p1.first - (int)p2.first);
  int b = (int)abs((int)p2.second - (int)p2.second);
  return std::hypot(a, b);
}

void Node::add_edge(char dest, int p_weight)
{
  // Pull ptr from map, both dest and source, assume all nodes exist
  std::shared_ptr<Node> dest_ptr;
  try {
    dest_ptr = all_nodes.at(dest);
  } catch (...) {
    printf("Node doesn't exist, please create it first!\n");
    throw std::out_of_range("Node doesn't exist, please create it first!");
  }
  if (dest_ptr.get() == nullptr) {
    throw std::invalid_argument("some how dest_ptr was not set");
  }
  auto source_ptr = all_nodes.at(label);
  int weight;
  if (p_weight == 0) {
    weight = distance_function(source_ptr->coords, dest_ptr->coords);
  } else {
    weight = p_weight;
  }
  source_ptr->adj.push_back(std::make_pair(dest_ptr, weight));
  dest_ptr->adj.push_back(std::make_pair(source_ptr, weight));
}

void Node::remove_edge(char dest)
{
  auto dest_ptr = all_nodes.at(dest);
  adj.erase(std::find_if(adj.begin(), adj.end(), [&dest_ptr](const auto& p) {
    return p.first == dest_ptr;
  }));
  auto source_ptr = all_nodes.at(label);

  dest_ptr->adj.erase(std::find_if(
    dest_ptr->adj.begin(), dest_ptr->adj.end(), [&](const auto& p) {
      return p.first == dest_ptr;
    }));

  if (dest_ptr.use_count() == 1) {
    all_nodes.erase(
      std::find_if(all_nodes.begin(), all_nodes.end(), [&](const auto& p) {
        return p.second == dest_ptr;
      }));
  }
}