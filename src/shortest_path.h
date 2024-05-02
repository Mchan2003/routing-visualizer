#pragma once
#include "node.h"
#include <vector>

using graph_path = std::tuple<node_ptr, node_ptr, uint32_t>;

std::vector<graph_path> shortest_path(node_ptr source, node_ptr dest);