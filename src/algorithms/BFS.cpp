#include "BFS.hpp"
#include <vector>
#include <string>

void BFS::init(Grid& grid) {
    this->grid = &grid;
    grid.clearPath();
    while(!frontier.empty()) frontier.pop();
    
    Cell* start = grid.getStartNode();
    if (start) {
        frontier.push(start);
        start->state = CellState::Open;
    }
    pathFound = false;
    finished = false;
}

bool BFS::step() {
    if (frontier.empty() || pathFound || finished) {
        finished = true;
        return false;
    }

    Cell* current = frontier.front();
    frontier.pop();

    if (current == grid->getEndNode()) {
        pathFound = true;
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
        if (neighbor->state == CellState::Empty || neighbor->state == CellState::End) {
            neighbor->parent = current;
            if (neighbor->state != CellState::End) {
                neighbor->state = CellState::Open;
            }
            frontier.push(neighbor);
        }
    }

    return true;
}

std::vector<Cell*> BFS::getPath() const {
    std::vector<Cell*> path;
    if (!pathFound) return path;

    Cell* current = grid->getEndNode();
    while (current) {
        path.insert(path.begin(), current);
        current = current->parent;
    }
    return path;
}
