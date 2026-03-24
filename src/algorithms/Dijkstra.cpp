#include "Dijkstra.hpp"

void Dijkstra::init(Grid& grid) {
    this->grid = &grid;
    grid.clearPath();
    while(!frontier.empty()) frontier.pop();
    
    Cell* start = grid.getStartNode();
    if (start) {
        start->gCost = 0;
        start->state = CellState::Open;
        frontier.push(start);
    }
    pathFound = false;
    finished = false;
}

bool Dijkstra::step() {
    if (frontier.empty() || pathFound || finished) {
        finished = true;
        return false;
    }

    Cell* current = frontier.top();
    frontier.pop();

    if (current == grid->getEndNode()) {
        pathFound = true;
        // Backtrack path
        Cell* temp = current;
        while (temp) {
            if (temp != grid->getStartNode() && temp != grid->getEndNode()) {
                temp->state = CellState::Path;
            }
            temp = temp->parent;
        }
        return false;
    }

    if (current != grid->getStartNode() && current != grid->getEndNode()) {
        current->state = CellState::Closed;
    }

    for (Cell* neighbor : grid->getNeighbors(current)) {
        if (neighbor->state == CellState::Wall) continue;

        int newCost = current->gCost + neighbor->weight;
        if (newCost < neighbor->gCost) {
            neighbor->gCost = newCost;
            neighbor->parent = current;
            if (neighbor->state != CellState::End) {
                neighbor->state = CellState::Open;
            }
            frontier.push(neighbor);
        }
    }

    return true;
}

std::vector<Cell*> Dijkstra::getPath() const {
    std::vector<Cell*> path;
    if (!pathFound) return path;

    Cell* current = grid->getEndNode();
    while (current) {
        path.insert(path.begin(), current);
        current = current->parent;
    }
    return path;
}
