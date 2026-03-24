#ifndef IPATHFINDER_HPP
#define IPATHFINDER_HPP

#include <vector>
#include <string>
#include "Grid.hpp"

class IPathfinder {
public:
    virtual ~IPathfinder() = default;
    
    virtual void init(Grid& grid) = 0;
    virtual bool step() = 0;         // Advance one step; returns false when done or no path
    virtual bool foundPath() const = 0;
    virtual std::vector<Cell*> getPath() const = 0;
    
    // For visualization
    virtual std::string getName() const = 0;
};

#endif // IPATHFINDER_HPP
