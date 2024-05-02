#include "node.h"

int main()
{
  auto a = Node::create('A', { 2, 3 });
  Node::create('B', { 5, 1 });
  a->add_edge('B');
  node_ptr b = Node::all_nodes['B'];
  auto another_b = a->adj.at(0).first;
  std::cout << (b.get() == another_b.get()) << std::endl;

  return 0;
}