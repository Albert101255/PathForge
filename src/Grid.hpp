#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include "Cell.hpp"

class Grid {
public:
    Grid(int rows, int cols);

    void reset();
    void clearPath();
    void setStart(int row, int col);
    void setEnd(int row, int col);
    void toggleWall(int row, int col);
    void setWeight(int row, int col, int weight);

    int getRows() const { return rows; }
    int getCols() const { return cols; }
    Cell* getCell(int row, int col);
    const Cell* getCell(int row, int col) const;
    std::vector<Cell*> getNeighbors(Cell* cell);

    Cell* getStartNode() const { return startNode; }
    Cell* getEndNode() const { return endNode; }

private:
    int rows, cols;
    std::vector<std::vector<Cell>> cells;
    Cell* startNode = nullptr;
    Cell* endNode = nullptr;

    bool isValid(int row, int col) const;
};

#endif // GRID_HPP
