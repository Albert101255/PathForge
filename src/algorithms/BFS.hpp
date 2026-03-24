#ifndef BFS_HPP
#define BFS_HPP

#include "IPathfinder.hpp"
#include <queue>
#include <string>
#include <vector>

class BFS : public IPathfinder {
public:
    void init(Grid& grid) override;
    bool step() override;
    bool foundPath() const override { return pathFound; }
    std::vector<Cell*> getPath() const override;
    std::string getName() const override { return "Breadth-First Search (BFS)"; }

private:
    Grid* grid = nullptr;
    std::queue<Cell*> frontier;
    bool pathFound = false;
    bool finished = false;
};

#endif // BFS_HPP
