#include "DFS.hpp"

void DFS::init(Grid& grid) {
    this->grid = &grid;
    grid.clearPath();
    while(!frontier.empty()) frontier.pop();
    
    Cell* start = grid.getStartNode();
    Cell* end = grid.getEndNode();
    pathFound = false;
    finished = false;
    if (start && end) {
        frontier.push(start);
    } else {
        finished = true;
    }
}

bool DFS::step() {
    if (frontier.empty() || pathFound || finished) {
        finished = true;
        return false;
    }

    Cell* current = frontier.top();
    frontier.pop();

    if (current == grid->getEndNode()) {
        pathFound = true;
        finished = true;
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
        if ((neighbor->state == CellState::Empty || neighbor->state == CellState::End) &&
            neighbor != grid->getStartNode() && neighbor->parent == nullptr) {
            neighbor->parent = current;
            if (neighbor->state != CellState::End) {
                neighbor->state = CellState::Open;
            }
            frontier.push(neighbor);
        }
    }

    return true;
}

std::vector<Cell*> DFS::getPath() const {
    std::vector<Cell*> path;
    if (!pathFound) return path;

    Cell* current = grid->getEndNode();
    while (current) {
        path.insert(path.begin(), current);
        current = current->parent;
    }
    return path;
}
