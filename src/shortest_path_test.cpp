#include "node.h"
#include "shortest_path.h"

int main()
{
  auto u = Node::create('U', { 0, 2 });
  auto v = Node::create('V', { 2, 4 });
  auto w = Node::create('W', { 5, 4 });
  auto z = Node::create('Z', { 8, 0 });
  auto y = Node::create('Y', { 5, 3 });
  auto x = Node::create('X', { 3, 1 });

  u->add_edge('V', 2);
  u->add_edge('W', 5);
  u->add_edge('X', 1);

  v->add_edge('X', 2);
  v->add_edge('W', 3);

  x->add_edge('W', 3);
  x->add_edge('Y', 1);

  w->add_edge('Z', 5);
  w->add_edge('Y', 1);

  y->add_edge('Z', 2);

  auto res = shortest_path(u, w);

  for (int i = 0; i < res.size(); i++) {
    std::cout << std::get<0>(res[i])->label << " (" << std::get<2>(res[i])
              << ")";

    std::cout << " --> ";
    if (i == res.size() - 1) {
      std::cout << std::get<1>(res[i])->label;
    }
  }
  std::cout << std::endl;
  return 0;
}