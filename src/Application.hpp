#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include "Grid.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include "algorithms/IPathfinder.hpp"
#include "UI/Sidebar.hpp"
#include "UI/StatusBar.hpp"

enum class AppState {
    Idle,
    Running,
    Done
};

class Application {
public:
    Application();
    void run();

private:
    void update(float deltaTime);
    void render();
    void changeAlgorithm(int algoId);

    sf::RenderWindow window;
    sf::Font font;
    Grid grid;
    Renderer renderer;
    InputHandler inputHandler;
    Sidebar sidebar;
    StatusBar statusBar;

    std::unique_ptr<IPathfinder> pathfinder;
    AppState state = AppState::Idle;
    
    int steps = 0;
    float stepTimer = 0.0f;
    float stepDelay = 0.015f; // 15ms
};

#endif // APPLICATION_HPP
