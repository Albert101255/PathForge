#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

class InputHandler {
public:
    InputHandler(sf::RenderWindow& window, Grid& grid);

    void handleEvents();
    
    // Getters for state changes triggered by input
    bool isSpacePressed() const { return spacePressed; }
    bool isRPressed() const { return rPressed; }
    bool isCPressed() const { return cPressed; }
    int getSelectedAlgorithm() const { return selectedAlgo; }
    float getSpeedFactor() const { return speedFactor; }

    void resetTriggers() {
        spacePressed = false;
        rPressed = false;
        cPressed = false;
    }

private:
    sf::RenderWindow& window;
    Grid& grid;

    bool spacePressed = false;
    bool rPressed = false;
    bool cPressed = false;
    int selectedAlgo = 1; // 1=A*, 2=Dijkstra, 3=BFS, 4=DFS
    float speedFactor = 1.0f;

    void handleMouseInput();
    void handleKeyboardInput(const sf::Event::KeyPressed& event);
};

#endif // INPUTHANDLER_HPP
