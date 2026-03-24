# PathForge — Pathfinding Visualizer

![PathForge Demo](assets/demo.gif)

A high-performance, interactive pathfinding algorithm visualizer built in C++17 using the SFML 3 multimedia library. Designed as a showcase of core Data Structures & Algorithms (DSA) concepts, clean Object-Oriented Architecture, and robust C++ memory management.

## Features

- **Real-Time Visuals**: Watch algorithms search nodes and find optimal paths dynamically.
- **Multiple Algorithms**:
  - **A* Search** (Fastest, uses Manhattan distance heuristic)
  - **Dijkstra's Algorithm** (Guarantees shortest path without heuristics)
  - **Breadth-First Search (BFS)** (Unweighted shortest path)
  - **Depth-First Search (DFS)** (Explores as deeply as possible)
- **Interactive Grid**:
  - Left-Click & Drag to draw walls/obstacles
  - Right-Click to erase walls
  - `S` + Click to place the **Start** node
  - `E` + Click to place the **End** node
- **Dynamic Speed Control**: Speed up or slow down the visualization using `+` / `-` keys.
- **Statistics**: View the number of computation steps and the final path length.

## Technical Highlights (Under the Hood)
- **Time Complexity Focus:** A* is implemented leveraging heuristic limits, reducing average complexity natively, while Dijkstra holds `O((V+E) log V)` guarantees via `<queue>`.
- **Memory Safety:** Smart pointers (`std::unique_ptr`) dictate program boundaries and interface polymorphism—no raw `new/delete` memory leaks.
- **Interface Segregation:** Uses `IPathfinder` interface to decouple frontend SFML UI updates from backend mathematical graph traversal steps, maximizing maintainability.
- **Performance:** Designed to easily run at a fluid 60FPS lock natively utilizing simple structs instead of bloated objects, maintaining CPU cache hit-rate across the grid allocations.

## Controls

| Action | Input |
|---|---|
| Draw Wall | Left-Click (Drag) |
| Erase Wall | Right-Click |
| Set Start Node | S + Left-Click |
| Set End Node | E + Left-Click |
| Run Algorithm | Spacebar |
| Reset Path | R |
| Clear Grid | C |
| Select Algorithm | 1 (A*), 2 (Dijkstra), 3 (BFS), 4 (DFS) |
| Adjust Speed | + or - |

## Build Instructions

### Dependencies (Windows - MSYS2/MinGW)
This project uses **SFML 3.x**. You can install it on MSYS2 (UCRT64 environment) using:
```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

### Dependencies (Linux)
Install CMake, compiler, and SFML 3.x dependencies from your package manager:
```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev
```
*(Note: Ensure your distribution provides SFML 3.x or compile SFML from source).*

### Compiling with CMake
1. Create a build directory: `mkdir build`
2. Navigate to it: `cd build`
3. Configure the project:
```bash
cmake -S .. -B . -G "MinGW Makefiles"
```
4. Compile the target:
```bash
mingw32-make -j8
```
5. Run the executable: `./PathForge.exe`

## Technologies Used

- **Language:** C++17
- **Graphics/UI:** SFML 3 (Simple and Fast Multimedia Library)
- **Build System:** CMake 3.20+
- **Compiler:** GCC (MinGW-w64 UCRT)

## Architecture
- **Data Layer:** `Grid` and `Cell` abstractions for scalable graph state management.
- **Logic / Algorithms:** Modular `IPathfinder` interface enabling plug-and-play algorithm implementations.
- **Rendering Layer:** Encapsulated `Renderer`, `Sidebar`, and `StatusBar` managing SFML graphical states.

## Author
[Albert](https://github.com/Albert101255)
