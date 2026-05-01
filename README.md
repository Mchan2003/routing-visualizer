# Routing Visualizer

An interactive C++ graph visualization tool for exploring classic routing and spanning tree algorithms. Build weighted graphs interactively, then watch Dijkstra's shortest path, Prim's MST, and Kruskal's MST render in a real-time SFML window — with results highlighted directly on the graph.

![CI](https://github.com/your-username/routing-visualizer/actions/workflows/ci.yml/badge.svg)

Authors: Ryan Smith, Michael Chan, 

---

## Features

- **Interactive graph builder** — add labeled nodes (A–Z) with 2D coordinates and weighted edges via a CLI menu
- **Dijkstra's shortest path** — finds and visualizes the minimum-cost path between any two nodes
- **Prim's MST** — builds a minimum spanning tree greedily from a chosen source node
- **Kruskal's MST** — builds a minimum spanning tree by globally sorting edges
- **Live SFML rendering** — algorithm results are overlaid in red on the full green graph; press `Backspace` to return to the menu
- **Cross-platform** — CI-verified on Windows (VS2019/VS2022), Linux (GCC & Clang), and macOS

---

## Getting Started

### Prerequisites

| Tool | Minimum version |
|------|----------------|
| C++ compiler | C++20 support (GCC 10+, Clang 12+, MSVC 2019+) |
| CMake | 3.16+ |
| Git | any recent |

> **Linux only:** install the SFML system dependencies first:
> ```bash
> sudo apt-get install libxrandr-dev libxcursor-dev libudev-dev \
>   libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev
> ```
> SFML itself is fetched automatically by CMake via `FetchContent`.

### Build

```bash
git clone https://github.com/your-username/routing-visualizer.git
cd routing-visualizer

cmake -S . -B build
cmake --build build --config Release
```

The compiled binary lands at `build/bin/CMakeSFMLProject` (Linux/macOS) or `build\bin\Release\CMakeSFMLProject.exe` (Windows).

### Run

```bash
./build/bin/CMakeSFMLProject
```

---

## Usage

The program presents a text menu. Type the option name and press Enter.

```
Enter Option:
```

| Option | Description |
|--------|-------------|
| `Add Node` | Add a node with a label (single character), X/Y coordinates, and edges to existing nodes |
| `Display Graph` | Open an SFML window rendering the current graph |
| `Find Shortest Path` | Run Dijkstra's algorithm between two nodes and display the result |
| `Find Spanning Tree` | Choose `Prim` or `Kuskals` and visualize the MST from a source node |
| `exit` | Quit the program |

### Example session

```
Enter Option: Add Node
Enter Node: A
Enter X Coordinate: 100
Enter Y Coordinate: 200
Add edge to node (z to exit): B
Add edge to node (z to exit): z

Enter Option: Find Shortest Path
Enter Source Node: A
Enter Destination Node: C
source: A destination: B weight: 2
source: B destination: C weight: 3
```

### Demo / unit test

A standalone shortest-path demo is included in `demos/shortest_path_test.cpp`. It builds a six-node graph programmatically and prints the optimal path — useful for verifying algorithm correctness without the GUI.

```bash
# Build the demo separately (not included in the default CMake target)
g++ -std=c++20 demos/shortest_path_test.cpp src/node.cpp src/shortest_path.cpp -I src -o sp_demo
./sp_demo
```

---

## Project Structure

```
routing-visualizer/
├── src/
│   ├── main.cpp          # CLI menu and SFML draw functions
│   ├── node.h / node.cpp # Weighted graph node (adjacency list)
│   ├── shortest_path.h/cpp  # Dijkstra's algorithm
│   ├── prims.h/cpp       # Prim's MST
│   └── kruskals.h/cpp    # Kruskal's MST
├── demos/
│   ├── shortest_path_test.cpp
│   └── example_test.cpp
├── .github/workflows/ci.yml
└── CMakeLists.txt
```

---

## How It Works

Nodes are identified by a single character label and stored in a global `unordered_map<char, shared_ptr<Node>>`. Edges are bidirectional and carry an integer weight. All three algorithms operate on this shared graph structure:

- **Shortest path** — min-heap Dijkstra that tracks parent pointers and reconstructs the path on arrival at the destination.
- **Prim's MST** — expands the tree greedily by always picking the cheapest edge leaving the visited set.
- **Kruskal's MST** — loads *all* edges into a global min-heap and picks cheapest non-cycle-forming edges until the tree is complete.

Coordinates are bounded to 900×900 pixels (`COORD_MAX`) so every node fits inside the 1000×1000 SFML window.

---

---

## License
This project was created for academic use.
