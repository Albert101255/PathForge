#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#include <SFML/Graphics.hpp>
#include <string>

class StatusBar {
public:
    StatusBar(sf::RenderWindow& window, sf::Font& font);

    void render(const std::string& statusText);

private:
    sf::RenderWindow& window;
    sf::Font& font;
};

#endif // STATUSBAR_HPP
