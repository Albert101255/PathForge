#include "Dijkstra.hpp"

void Dijkstra::init(Grid& grid) {
    this->grid = &grid;
    grid.clearPath();
    while(!frontier.empty()) frontier.pop();
    
    Cell* start = grid.getStartNode();
    Cell* end = grid.getEndNode();
    pathFound = false;
    finished = false;
    if (start && end) {
        start->gCost = 0;
        frontier.push({start, 0});
    } else {
        finished = true;
    }
}

bool Dijkstra::step() {
    if (frontier.empty() || pathFound || finished) {
        finished = true;
        return false;
    }

    Cell* current = nullptr;
    while (!frontier.empty()) {
        QueueEntry top = frontier.top();
        frontier.pop();
        if (top.cell->state != CellState::Closed && top.gCost <= top.cell->gCost) {
            current = top.cell;
            break;
        }
    }

    if (!current) {
        finished = true;
        return false;
    }

    if (current == grid->getEndNode()) {
        pathFound = true;
        finished = true;
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
        if (neighbor->state == CellState::Wall || neighbor->state == CellState::Closed) continue;

        int newCost = current->gCost + neighbor->weight;
        if (newCost < neighbor->gCost) {
            neighbor->gCost = newCost;
            neighbor->parent = current;
            if (neighbor != grid->getStartNode() && neighbor != grid->getEndNode()) {
                neighbor->state = CellState::Open;
            }
            frontier.push({neighbor, newCost});
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
