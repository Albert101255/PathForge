#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "Cell.hpp"
#include "Grid.hpp"
#include "algorithms/AStar.hpp"
#include "algorithms/BFS.hpp"
#include "algorithms/DFS.hpp"
#include "algorithms/Dijkstra.hpp"
#include "algorithms/IPathfinder.hpp"

namespace {

void runToCompletion(IPathfinder& algo, Grid& grid, int maxSteps = 10000) {
    algo.init(grid);
    int steps = 0;
    while (algo.step()) {
        ++steps;
        assert(steps < maxSteps && "Algorithm exceeded maximum step limit");
    }
}

void assertValidPath(const std::vector<Cell*>& path, Cell* start, Cell* end) {
    assert(!path.empty());
    assert(path.front() == start);
    assert(path.back() == end);
    for (size_t i = 0; i < path.size(); ++i) {
        assert(path[i] != nullptr);
        assert(path[i]->state != CellState::Wall);
        if (i > 0) {
            int dist = std::abs(path[i]->row - path[i - 1]->row) +
                       std::abs(path[i]->col - path[i - 1]->col);
            assert(dist == 1 && "Path steps must be between orthogonal neighbors");
        }
    }
}

void testGridOperations() {
    Grid grid(10, 12);
    assert(grid.getRows() == 10);
    assert(grid.getCols() == 12);
    assert(grid.getCell(-1, 0) == nullptr);
    assert(grid.getCell(0, -1) == nullptr);
    assert(grid.getCell(10, 0) == nullptr);
    assert(grid.getCell(0, 12) == nullptr);

    grid.setStart(1, 1);
    grid.setEnd(8, 9);
    assert(grid.getStartNode() == grid.getCell(1, 1));
    assert(grid.getEndNode() == grid.getCell(8, 9));
    assert(grid.getStartNode()->state == CellState::Start);
    assert(grid.getEndNode()->state == CellState::End);

    // Walls cannot overwrite start or end
    grid.toggleWall(1, 1);
    grid.toggleWall(8, 9);
    assert(grid.getStartNode()->state == CellState::Start);
    assert(grid.getEndNode()->state == CellState::End);

    // Normal wall toggle
    grid.toggleWall(3, 4);
    assert(grid.getCell(3, 4)->state == CellState::Wall);
    grid.toggleWall(3, 4);
    assert(grid.getCell(3, 4)->state == CellState::Empty);

    // Weights and reset
    grid.setWeight(2, 2, 5);
    assert(grid.getCell(2, 2)->weight == 5);
    grid.reset();
    assert(grid.getStartNode() == nullptr);
    assert(grid.getEndNode() == nullptr);
    assert(grid.getCell(2, 2)->weight == 1);
}

void testShortestPathOpenGrid() {
    Grid grid(10, 10);
    grid.setStart(0, 0);
    grid.setEnd(4, 5);
    // Shortest Manhattan distance is 4 + 5 = 9 edges => 10 cells in path
    const size_t expectedCells = 10;

    BFS bfs;
    runToCompletion(bfs, grid);
    assert(bfs.foundPath());
    assert(bfs.getPath().size() == expectedCells);
    assertValidPath(bfs.getPath(), grid.getStartNode(), grid.getEndNode());

    Dijkstra dijkstra;
    runToCompletion(dijkstra, grid);
    assert(dijkstra.foundPath());
    assert(dijkstra.getPath().size() == expectedCells);
    assertValidPath(dijkstra.getPath(), grid.getStartNode(), grid.getEndNode());

    AStar astar;
    runToCompletion(astar, grid);
    assert(astar.foundPath());
    assert(astar.getPath().size() == expectedCells);
    assertValidPath(astar.getPath(), grid.getStartNode(), grid.getEndNode());

    DFS dfs;
    runToCompletion(dfs, grid);
    assert(dfs.foundPath());
    assert(dfs.getPath().size() >= expectedCells);
    assertValidPath(dfs.getPath(), grid.getStartNode(), grid.getEndNode());
}

void testObstacleAvoidance() {
    Grid grid(5, 5);
    grid.setStart(2, 0);
    grid.setEnd(2, 4);

    // Vertical wall at col 2 from row 1 to row 3, forcing detour through row 0 or row 4
    grid.toggleWall(1, 2);
    grid.toggleWall(2, 2);
    grid.toggleWall(3, 2);

    // Shortest path around wall: (2,0)->(1,0)->(0,0)->(0,1)->(0,2)->(0,3)->(0,4)->(1,4)->(2,4) = 9 cells
    const size_t expectedShortest = 9;

    std::vector<std::unique_ptr<IPathfinder>> shortestAlgos;
    shortestAlgos.push_back(std::make_unique<BFS>());
    shortestAlgos.push_back(std::make_unique<Dijkstra>());
    shortestAlgos.push_back(std::make_unique<AStar>());

    for (auto& algo : shortestAlgos) {
        runToCompletion(*algo, grid);
        assert(algo->foundPath());
        auto path = algo->getPath();
        assertValidPath(path, grid.getStartNode(), grid.getEndNode());
        assert(path.size() == expectedShortest);
    }

    DFS dfs;
    runToCompletion(dfs, grid);
    assert(dfs.foundPath());
    assertValidPath(dfs.getPath(), grid.getStartNode(), grid.getEndNode());
}

void testUnreachableTarget() {
    Grid grid(6, 6);
    grid.setStart(0, 0);
    grid.setEnd(5, 5);

    // Completely enclose (5, 5) with walls at (4, 5) and (5, 4)
    grid.toggleWall(4, 5);
    grid.toggleWall(5, 4);

    std::vector<std::unique_ptr<IPathfinder>> algos;
    algos.push_back(std::make_unique<BFS>());
    algos.push_back(std::make_unique<DFS>());
    algos.push_back(std::make_unique<Dijkstra>());
    algos.push_back(std::make_unique<AStar>());

    for (auto& algo : algos) {
        runToCompletion(*algo, grid);
        assert(!algo->foundPath());
        assert(algo->getPath().empty());
    }
}

void testStartEqualsEnd() {
    Grid grid(5, 5);
    grid.setStart(2, 2);
    grid.setEnd(2, 2);
    assert(grid.getStartNode() == grid.getEndNode());

    std::vector<std::unique_ptr<IPathfinder>> algos;
    algos.push_back(std::make_unique<BFS>());
    algos.push_back(std::make_unique<DFS>());
    algos.push_back(std::make_unique<Dijkstra>());
    algos.push_back(std::make_unique<AStar>());

    for (auto& algo : algos) {
        runToCompletion(*algo, grid);
        assert(algo->foundPath());
        auto path = algo->getPath();
        assert(path.size() == 1);
        assert(path.front() == grid.getStartNode());
    }
}

void testWeightedShortestPath() {
    Grid grid(3, 3);
    grid.setStart(1, 0);
    grid.setEnd(1, 2);
    // Direct middle cell (1,1) has heavy weight 20
    grid.setWeight(1, 1, 20);

    Dijkstra dijkstra;
    runToCompletion(dijkstra, grid);
    assert(dijkstra.foundPath());
    // Detour via row 0 or row 2 takes 4 steps of weight 1 (total cost 4 < 21)
    assert(grid.getEndNode()->gCost == 4);
    assert(dijkstra.getPath().size() == 5);

    AStar astar;
    runToCompletion(astar, grid);
    assert(astar.foundPath());
    assert(grid.getEndNode()->gCost == 4);
    assert(astar.getPath().size() == 5);
}

} // namespace

int main() {
    testGridOperations();
    testShortestPathOpenGrid();
    testObstacleAvoidance();
    testUnreachableTarget();
    testStartEqualsEnd();
    testWeightedShortestPath();

    std::cout << "All PathForge unit tests passed successfully.\n";
    return 0;
}
