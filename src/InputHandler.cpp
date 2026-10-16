#include "InputHandler.hpp"
#include <iostream>

InputHandler::InputHandler(sf::RenderWindow& window, Grid& grid)
    : window(window), grid(grid) {}

void InputHandler::handleEvents() {
#if SFML_VERSION_MAJOR >= 3
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            handleKeyboardInput(*keyPressed);
        }
    }
#else
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            handleKeyboardInput(event.key);
        }
    }
#endif
    handleMouseInput();
}

void InputHandler::handleMouseInput() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        // Grid coordinates calculation
        float gridYStart = 50.0f;
        float gridXStart = 5.0f;
        float gridHeight = window.getSize().y * 0.8f;
        float cellSize = gridHeight / grid.getRows();

        int col = static_cast<int>((mousePos.x - gridXStart) / cellSize);
        int row = static_cast<int>((mousePos.y - gridYStart) / cellSize);

        if (row >= 0 && row < grid.getRows() && col >= 0 && col < grid.getCols()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                grid.setStart(row, col);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
                grid.setEnd(row, col);
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                // If it's a regular click, toggle wall
                // Note: toggleWall might toggle back and forth if held down.
                // For a "drag to draw" experience, we should only set to Wall if not already start/end
                Cell* cell = grid.getCell(row, col);
                if (cell && cell->state != CellState::Start && cell->state != CellState::End) {
                    cell->state = CellState::Wall;
                }
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                Cell* cell = grid.getCell(row, col);
                if (cell && cell->state == CellState::Wall) {
                    cell->state = CellState::Empty;
                }
            }
        }
    }
}

#if SFML_VERSION_MAJOR >= 3
void InputHandler::handleKeyboardInput(const sf::Event::KeyPressed& event) {
#else
void InputHandler::handleKeyboardInput(const sf::Event::KeyEvent& event) {
#endif
    switch (event.code) {
        case sf::Keyboard::Key::Space:
            spacePressed = true;
            break;
        case sf::Keyboard::Key::R:
            rPressed = true;
            grid.clearPath();
            break;
        case sf::Keyboard::Key::C:
            cPressed = true;
            grid.reset();
            break;
        case sf::Keyboard::Key::Num1: selectedAlgo = 1; break;
        case sf::Keyboard::Key::Num2: selectedAlgo = 2; break;
        case sf::Keyboard::Key::Num3: selectedAlgo = 3; break;
        case sf::Keyboard::Key::Num4: selectedAlgo = 4; break;
        case sf::Keyboard::Key::Add:
        case sf::Keyboard::Key::Equal:
            speedFactor *= 1.2f;
            break;
        case sf::Keyboard::Key::Subtract:
        case sf::Keyboard::Key::Hyphen:
            speedFactor /= 1.2f;
            break;
        default:
            break;
    }
}
