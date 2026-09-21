# Project Recall — PathForge

## One-line explanation
C++/SFML application that visualizes how A*, Dijkstra, BFS and DFS explore a grid and find paths.

## Core flow
1. User edits the grid.
2. Start/end points are selected.
3. A pathfinding implementation explores cells.
4. Search state is sent to the visual layer.
5. The final path is reconstructed and displayed.

## Concepts to remember
- BFS uses a queue.
- DFS explores depth-first and is not guaranteed shortest.
- Dijkstra uses priority-based exploration for shortest paths with non-negative costs.
- A* adds a heuristic, such as Manhattan distance, to guide search toward the target.
- Algorithm logic is separated from SFML rendering.

## Interview questions
1. Why does BFS find a shortest path on an unweighted grid?
2. What is the difference between Dijkstra and A*?
3. What makes a heuristic admissible?
4. Why is DFS unsuitable when shortest path is required?
5. Why separate the pathfinder interface from rendering?

## Next improvements
- Unit tests for path correctness
- Weighted terrain
- Additional heuristics
- Better performance measurements
