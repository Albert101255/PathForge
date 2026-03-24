#include "Application.hpp"
#include "algorithms/AStar.hpp"
#include "algorithms/Dijkstra.hpp"
#include "algorithms/BFS.hpp"
#include "algorithms/DFS.hpp"
#include <iostream>

Application::Application()
    : window(sf::VideoMode(sf::Vector2u(1200, 800)), "PathForge Pathfinding Visualizer"),
      grid(40, 40),
      renderer(window),
      inputHandler(window, grid),
      sidebar(window, font),
      statusBar(window, font) {
    
    if (!font.openFromFile("assets/font.ttf")) {
        std::cerr << "Error loading font\n";
    }
    
    // Default algorithm
    changeAlgorithm(1);
    
    // Set default start/end
    grid.setStart(10, 10);
    grid.setEnd(30,30);
}

void Application::changeAlgorithm(int algoId) {
    switch (algoId) {
        case 1: pathfinder = std::make_unique<AStar>(); break;
        case 2: pathfinder = std::make_unique<Dijkstra>(); break;
        case 3: pathfinder = std::make_unique<BFS>(); break;
        case 4: pathfinder = std::make_unique<DFS>(); break;
        default: pathfinder = std::make_unique<AStar>(); break;
    }
    state = AppState::Idle;
    steps = 0;
    grid.clearPath();
}

void Application::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        inputHandler.handleEvents();
        
        if (inputHandler.getSelectedAlgorithm() != 0) { // Check if switched via keys
            // Logic to check if algo changed can be improved via InputHandler state
            // For now, let's just use the InputHandler's selectedAlgo
        }
        
        update(deltaTime);
        render();
    }
}

void Application::update(float deltaTime) {
    // Check for user triggers
    if (inputHandler.isSpacePressed()) {
        if (state == AppState::Idle) {
            pathfinder->init(grid);
            state = AppState::Running;
            steps = 0;
        } else if (state == AppState::Running) {
            state = AppState::Idle; // Pause
        }
        inputHandler.resetTriggers();
    }
    
    if (state == AppState::Running) {
        stepTimer += deltaTime;
        float currentDelay = stepDelay / inputHandler.getSpeedFactor();
        if (stepTimer >= currentDelay) {
            stepTimer = 0;
            if (pathfinder->step()) {
                steps++;
            } else {
                state = AppState::Done;
                sidebar.updateStats(steps, pathfinder->getPath().size());
            }
        }
    }
    
    // Check for algo change
    static int lastAlgo = 1;
    if (inputHandler.getSelectedAlgorithm() != lastAlgo) {
        lastAlgo = inputHandler.getSelectedAlgorithm();
        changeAlgorithm(lastAlgo);
    }
    
    if (state != AppState::Running) {
        sidebar.updateStats(steps, pathfinder->foundPath() ? pathfinder->getPath().size() : 0);
    }
}

void Application::render() {
    window.clear(sf::Color(10, 10, 20));
    
    renderer.render(grid);
    sidebar.render(inputHandler.getSelectedAlgorithm(), inputHandler.getSpeedFactor());
    
    std::string status = "Status: ";
    if (state == AppState::Idle) status += "Idle";
    else if (state == AppState::Running) status += "Running... " + pathfinder->getName();
    else if (state == AppState::Done) {
        status += "Done. ";
        if (pathfinder->foundPath()) status += "Path Found!";
        else status += "No Path Exists.";
    }
    statusBar.render(status);
    
    window.display();
}
