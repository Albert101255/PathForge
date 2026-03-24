#ifndef SIDEBAR_HPP
#define SIDEBAR_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Sidebar {
public:
    Sidebar(sf::RenderWindow& window, sf::Font& font);

    void render(int selectedAlgo, float speed);
    void updateStats(int steps, int pathLength);

private:
    sf::RenderWindow& window;
    sf::Font& font;
    
    int steps = 0;
    int pathLength = 0;

    void drawButton(const std::string& text, sf::Vector2f pos, bool selected);
};

#endif // SIDEBAR_HPP
