#include "node.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <tuple>
#include <unordered_set>

using namespace std;

struct tupleCompare;
vector<tuple<shared_ptr<Node>, shared_ptr<Node>, int>>
prims_algo(shared_ptr<Node> &src_ptr);