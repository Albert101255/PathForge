#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(sf::RenderWindow& window) : window(window) {
    if (!font.openFromFile("assets/font.ttf")) {
        // Fallback or error handling
        std::cerr << "Error: Could not load assets/font.ttf\n";
    }

    // Initialize color palette
    colorEmpty  = sf::Color(0x1A, 0x1A, 0x2E);
    colorWall   = sf::Color(0xE9, 0x45, 0x60);
    colorStart  = sf::Color(0x0F, 0x9B, 0x58);
    colorEnd    = sf::Color(0xF5, 0xA6, 0x23);
    colorOpen   = sf::Color(0x4A, 0x90, 0xD9);
    colorClosed = sf::Color(0x2C, 0x3E, 0x6B);
    colorPath   = sf::Color(0xFF, 0xD7, 0x00);
}

sf::Color Renderer::getCellColor(CellState state) const {
    switch (state) {
        case CellState::Empty:  return colorEmpty;
        case CellState::Wall:   return colorWall;
        case CellState::Start:  return colorStart;
        case CellState::End:    return colorEnd;
        case CellState::Open:   return colorOpen;
        case CellState::Closed: return colorClosed;
        case CellState::Path:   return colorPath;
        default:                return colorEmpty;
    }
}

void Renderer::render(const Grid& grid) {
    int rows = grid.getRows();
    int cols = grid.getCols();
    
    sf::Vector2u windowSize = window.getSize();
    // Grid canvas is 80% of window height, stats panel is on the right
    float gridHeight = windowSize.y * 0.8f;
    float gridWidth = gridHeight; // Keep it square for simplicity or use available width
    float cellSize = gridHeight / rows;

    sf::RectangleShape cellRect(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            const Cell* cell = grid.getCell(r, c);
            cellRect.setPosition({c * cellSize + 5.0f, r * cellSize + 50.0f}); // Offset for top bar
            cellRect.setFillColor(getCellColor(cell->state));
            window.draw(cellRect);

            // Draw weight if > 1
            if (cell->weight > 1) {
                sf::Text text(font);
                text.setString(std::to_string(cell->weight));
                text.setCharacterSize(static_cast<unsigned int>(cellSize * 0.5f));
                text.setFillColor(sf::Color::White);
                
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.getCenter());
                text.setPosition({c * cellSize + cellSize/2.0f + 5.0f, r * cellSize + cellSize/2.0f + 50.0f});
                
                window.draw(text);
            }
        }
    }
}
