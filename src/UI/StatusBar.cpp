#include "StatusBar.hpp"

StatusBar::StatusBar(sf::RenderWindow& window, sf::Font& font)
    : window(window), font(font) {}

void StatusBar::render(const std::string& statusText) {
    float barHeight = 40.0f;
    float barWidth = window.getSize().x;
    float barY = window.getSize().y - barHeight;

    sf::RectangleShape bg(sf::Vector2f(barWidth, barHeight));
    bg.setPosition({0.f, barY});
    bg.setFillColor(sf::Color(20, 20, 40));
    window.draw(bg);

    sf::Text text(font, statusText, 14);
    text.setPosition({20.f, barY + 10.f});
    text.setFillColor(sf::Color(200, 200, 200));
    window.draw(text);
}
