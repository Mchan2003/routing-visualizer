#include "node.h"

void Node::add_edge(char dest, int weight)
{
  // Pull ptr from map, both dest and source, assume all nodes exist
  std::shared_ptr<Node> dest_ptr;
  try {
    dest_ptr = all_nodes.at(dest);
  } catch (...) {
    printf("out of range?\n");
    dest_ptr = std::make_shared<Node>(Node(dest));
    all_nodes[dest] = dest_ptr;
  }
  if (dest_ptr.get() != nullptr) {
    throw std::invalid_argument("some how dest_ptr was not set");
  }
  auto source_ptr = all_nodes.at(label);
  adj.push_back(std::make_pair(dest_ptr, weight));
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