# PathForge — Pathfinding Visualizer

![PathForge Demo](assets/demo.gif)

An interactive C++17 pathfinding visualizer built with SFML. It lets you draw obstacles, choose a search algorithm, and watch the algorithm explore the grid before reconstructing a path.

## Algorithms

- **A\*** — uses a heuristic to guide exploration toward the target
- **Dijkstra** — computes shortest paths for non-negative edge costs
- **Breadth-First Search (BFS)** — finds a shortest path in an unweighted grid
- **Depth-First Search (DFS)** — explores deeply but does not guarantee a shortest path

A* is often faster than uninformed search when the heuristic is informative, but performance depends on the map, heuristic and implementation.

## What this project demonstrates

- C++17
- Graph/grid traversal
- Queues and priority queues
- Heuristics
- Object-oriented design
- SFML rendering/input
- CMake builds
- Separation between algorithm logic and visualization

## Controls

| Action | Input |
|---|---|
| Draw wall | Left-click / drag |
| Erase wall | Right-click |
| Place start | S + left-click |
| Place end | E + left-click |
| Run | Space |
| Reset path | R |
| Clear grid | C |
| Select algorithm | 1 A*, 2 Dijkstra, 3 BFS, 4 DFS |
| Adjust speed | + / - |

## Architecture

```text
Grid / Cell state
      |
      v
Pathfinding algorithm
      |
      v
Search-step updates
      |
      v
SFML renderer / UI
```

The `IPathfinder` abstraction keeps the algorithm implementation separate from the visualization layer so different search strategies can be selected without rewriting the UI.

## Complexity notes

For a graph with `V` vertices and `E` edges:

- BFS: `O(V + E)`
- DFS: `O(V + E)`
- Dijkstra with a binary heap: approximately `O((V + E) log V)`
- A*: worst-case behavior depends on the heuristic and graph, while a useful heuristic can significantly reduce explored nodes in practice

## Build

### Linux

Install a compiler, CMake and an SFML development package compatible with the project:

```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev
```

### Windows / MSYS2

```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

### Compile

```bash
cmake -S . -B build
cmake --build build
```

## Project status

This is a DSA visualization/learning project. The next useful additions are automated algorithm tests, more maze/grid scenarios, and a short explanation of the implementation decisions for each algorithm.

## Author

[Albert](https://github.com/Albert101255)
