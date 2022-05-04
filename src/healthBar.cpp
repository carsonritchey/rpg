#include "healthBar.h"

HealthBar::HealthBar() {}

HealthBar::HealthBar(sf::RenderWindow* window, int x, int y, int w, int h, float max_health, float* current_health) {
    this->window = window;

    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    
    this->max_health = max_health;
    this->current_health = current_health;

    this->top    = sf::RectangleShape(sf::Vector2f(w, box_outline_width));
    this->bottom = sf::RectangleShape(sf::Vector2f(w, box_outline_width));
    this->left   = sf::RectangleShape(sf::Vector2f(box_outline_width, h));
    this->right  = sf::RectangleShape(sf::Vector2f(box_outline_width, h));

    top.setPosition(sf::Vector2f(x, y));
    bottom.setPosition(sf::Vector2f(x, y + h));
    left.setPosition(sf::Vector2f(x, y));
    right.setPosition(sf::Vector2f(x + w - box_outline_width, y));

    this->bg = sf::RectangleShape(sf::Vector2f(w, h));
    bg.setPosition(sf::Vector2f(x, y));

    bg.setFillColor(bg_color);
    top.setFillColor(outline_color);
    bottom.setFillColor(outline_color);
    left.setFillColor(outline_color);
    right.setFillColor(outline_color);
}

HealthBar::~HealthBar() {

}

void HealthBar::draw() {
    window->draw(bg);

    sf::RectangleShape health(sf::Vector2f(w / max_health * *current_health, h));
    health.setPosition(sf::Vector2f(x, y));
    if(*current_health / max_health > bad_threshold)
        health.setFillColor(health_good_color);
    else
        health.setFillColor(health_bad_color);

    if(*current_health > 0)
        window->draw(health);

    window->draw(top);
    window->draw(bottom);
    window->draw(left);
    window->draw(right);
}
