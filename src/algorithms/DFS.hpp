#ifndef DFS_HPP
#define DFS_HPP

#include "IPathfinder.hpp"
#include <stack>
#include <vector>
#include <string>

class DFS : public IPathfinder {
public:
    void init(Grid& grid) override;
    bool step() override;
    bool foundPath() const override { return pathFound; }
    std::vector<Cell*> getPath() const override;
    std::string getName() const override { return "Depth-First Search (DFS)"; }

private:
    Grid* grid = nullptr;
    std::stack<Cell*> frontier;
    bool pathFound = false;
    bool finished = false;
};

#endif // DFS_HPP
