#include "partyDisplay.h"

PartyDisplay::PartyDisplay(sf::RenderWindow* window) {
    this->window = window;

    top    = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH - padding * 2, outline_width));
    bottom = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH - padding * 2, outline_width));
    left   = sf::RectangleShape(sf::Vector2f(outline_width, WINDOW_HEIGHT - padding * 2));
    right  = sf::RectangleShape(sf::Vector2f(outline_width, WINDOW_HEIGHT - padding * 2));

    top.setPosition(sf::Vector2f(padding, padding));
    bottom.setPosition(sf::Vector2f(padding, WINDOW_HEIGHT - padding));
    left.setPosition(sf::Vector2f(padding, padding));
    right.setPosition(sf::Vector2f(WINDOW_WIDTH - padding - outline_width, padding));

    top.setFillColor(outline_color);
    bottom.setFillColor(outline_color);
    left.setFillColor(outline_color);
    right.setFillColor(outline_color);
}

PartyDisplay::~PartyDisplay() {

}

void PartyDisplay::draw() {
    window->draw(top);
    window->draw(bottom);
    window->draw(left);
    window->draw(right);
}
