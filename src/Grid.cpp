#include "Grid.hpp"
#include <iostream>

Grid::Grid(int rows, int cols)
    : rows(rows), cols(cols), cells(rows, std::vector<Cell>(cols)) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cells[r][c].row = r;
            cells[r][c].col = c;
        }
    }
}

void Grid::reset() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cells[r][c].state = CellState::Empty;
            cells[r][c].resetCosts();
            cells[r][c].weight = 1;
        }
    }
    startNode = nullptr;
    endNode = nullptr;
}

void Grid::clearPath() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            Cell& cell = cells[r][c];
            if (cell.state == CellState::Open || cell.state == CellState::Closed || cell.state == CellState::Path) {
                cell.state = CellState::Empty;
            }
            cell.resetCosts();
        }
    }
}

void Grid::setStart(int row, int col) {
    if (!isValid(row, col)) return;
    if (startNode) startNode->state = CellState::Empty;
    startNode = &cells[row][col];
    startNode->state = CellState::Start;
}

void Grid::setEnd(int row, int col) {
    if (!isValid(row, col)) return;
    if (endNode) endNode->state = CellState::Empty;
    endNode = &cells[row][col];
    endNode->state = CellState::End;
}

void Grid::toggleWall(int row, int col) {
    if (!isValid(row, col)) return;
    Cell& cell = cells[row][col];
    if (cell.state == CellState::Start || cell.state == CellState::End) return;

    if (cell.state == CellState::Wall) {
        cell.state = CellState::Empty;
    } else {
        cell.state = CellState::Wall;
    }
}

void Grid::setWeight(int row, int col, int weight) {
    if (!isValid(row, col)) return;
    cells[row][col].weight = weight;
}

Cell* Grid::getCell(int row, int col) {
    if (isValid(row, col)) return &cells[row][col];
    return nullptr;
}

const Cell* Grid::getCell(int row, int col) const {
    if (isValid(row, col)) return &cells[row][col];
    return nullptr;
}

std::vector<Cell*> Grid::getNeighbors(Cell* cell) {
    std::vector<Cell*> neighbors;
    if (!cell) return neighbors;

    static const int dr[] = {-1, 1, 0, 0};
    static const int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int nr = cell->row + dr[i];
        int nc = cell->col + dc[i];
        if (isValid(nr, nc)) {
            neighbors.push_back(&cells[nr][nc]);
        }
    }

    return neighbors;
}

bool Grid::isValid(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}
