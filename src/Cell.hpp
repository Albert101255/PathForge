#ifndef CELL_HPP
#define CELL_HPP

#include <climits>

enum class CellState {
    Empty,
    Wall,
    Start,
    End,
    Open,       // In the frontier / to-be-visited
    Closed,     // Already visited
    Path        // Final path highlight
};

struct Cell {
    int row, col;
    CellState state = CellState::Empty;
    int gCost = INT_MAX;   // Cost from start (Dijkstra / A*)
    int hCost = 0;         // Heuristic cost (A* only)
    Cell* parent = nullptr;
    int weight = 1;        // For weighted node stretch feature

    int fCost() const {
        if (gCost == INT_MAX) return INT_MAX;
        return gCost + hCost;
    }

    void resetCosts() {
        gCost = INT_MAX;
        hCost = 0;
        parent = nullptr;
    }
};

#endif // CELL_HPP
