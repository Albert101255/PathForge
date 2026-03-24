#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <string>
#include <vector>

class Renderer {
public:
    Renderer(sf::RenderWindow& window);

    void render(const Grid& grid);
    void updateCell(int row, int col, CellState state); // Optimization if needed

private:
    sf::RenderWindow& window;
    sf::Font font;
    
    // Color palette
    sf::Color colorEmpty;
    sf::Color colorWall;
    sf::Color colorStart;
    sf::Color colorEnd;
    sf::Color colorOpen;
    sf::Color colorClosed;
    sf::Color colorPath;

    sf::Color getCellColor(CellState state) const;
};

#endif // RENDERER_HPP
