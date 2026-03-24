#include "Sidebar.hpp"

Sidebar::Sidebar(sf::RenderWindow& window, sf::Font& font)
    : window(window), font(font) {}

void Sidebar::updateStats(int steps, int pathLength) {
    this->steps = steps;
    this->pathLength = pathLength;
}

void Sidebar::render(int selectedAlgo, float speed) {
    float sidebarX = window.getSize().x - 250.0f;
    
    sf::RectangleShape bg(sf::Vector2f(250.0f, window.getSize().y));
    bg.setPosition({sidebarX, 0.f});
    bg.setFillColor(sf::Color(30, 30, 50));
    window.draw(bg);

    sf::Text title(font, "PathForge Controls", 20);
    title.setPosition({sidebarX + 20, 20});
    title.setFillColor(sf::Color::White);
    window.draw(title);

    // Algorithm selection
    sf::Text algoTitle(font, "Algorithm (1-4):", 16);
    algoTitle.setPosition({sidebarX + 20, 70});
    window.draw(algoTitle);

    drawButton("1. A* Search", {sidebarX + 20, 100}, selectedAlgo == 1);
    drawButton("2. Dijkstra",  {sidebarX + 20, 130}, selectedAlgo == 2);
    drawButton("3. BFS",       {sidebarX + 20, 160}, selectedAlgo == 3);
    drawButton("4. DFS",       {sidebarX + 20, 190}, selectedAlgo == 4);

    if (selectedAlgo == 4) {
        sf::Text dfsWarn(font, "(Not guaranteed shortest path)", 12);
        dfsWarn.setPosition({sidebarX + 20, 215});
        dfsWarn.setFillColor(sf::Color(255, 100, 100));
        window.draw(dfsWarn);
    }

    // Speed
    char speedStr[32];
    snprintf(speedStr, sizeof(speedStr), "Speed: %.1fx", speed);
    sf::Text speedText(font, speedStr, 16);
    speedText.setPosition({sidebarX + 20, 250});
    window.draw(speedText);

    // Stats
    sf::Text statsTitle(font, "Statistics:", 16);
    statsTitle.setPosition({sidebarX + 20, 300});
    window.draw(statsTitle);

    sf::Text stepText(font, "Steps: " + std::to_string(steps), 14);
    stepText.setPosition({sidebarX + 20, 330});
    window.draw(stepText);

    sf::Text lengthText(font, "Path Length: " + (pathLength > 0 ? std::to_string(pathLength) : "N/A"), 14);
    lengthText.setPosition({sidebarX + 20, 360});
    window.draw(lengthText);

    // Instructions
    sf::Text instr(font, "Controls:\nL-Click: Wall\nR-Click: Erase\nS+Click: Start\nE+Click: End\nSpace: Run\nR: Reset Path\nC: Clear All\n+/-: Speed", 12);
    instr.setPosition({sidebarX + 20.f, static_cast<float>(window.getSize().y) - 150.f});
    window.draw(instr);
}

void Sidebar::drawButton(const std::string& text, sf::Vector2f pos, bool selected) {
    sf::Text btnText(font, text, 14);
    btnText.setPosition(pos);
    btnText.setFillColor(selected ? sf::Color::Yellow : sf::Color(180, 180, 180));
    window.draw(btnText);
}
