#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "IPathfinder.hpp"
#include <queue>
#include <vector>
#include <string>
#include <vector>

class Dijkstra : public IPathfinder {
public:
    void init(Grid& grid) override;
    bool step() override;
    bool foundPath() const override { return pathFound; }
    std::vector<Cell*> getPath() const override;
    std::string getName() const override { return "Dijkstra's Algorithm"; }

private:
    Grid* grid = nullptr;
    struct QueueEntry {
        Cell* cell;
        int gCost;
        bool operator>(const QueueEntry& other) const {
            return gCost > other.gCost;
        }
    };
    std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry>> frontier;
    bool pathFound = false;
    bool finished = false;
};

#endif // DIJKSTRA_HPP
