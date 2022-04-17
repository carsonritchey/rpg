#include "itemBox.h"

ItemBox::ItemBox(int id) {
    bg.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - ITEMBOX_WIDTH / 2, WINDOW_HEIGHT / 2 - ITEMBOX_WIDTH / 2));

    top.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - ITEMBOX_WIDTH / 2, WINDOW_HEIGHT / 2 - ITEMBOX_WIDTH / 2));
    bottom.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - ITEMBOX_WIDTH / 2, WINDOW_HEIGHT / 2 + ITEMBOX_WIDTH / 2 - OUTLINE_WIDTH));
    left.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - ITEMBOX_WIDTH / 2, WINDOW_HEIGHT / 2 - ITEMBOX_WIDTH / 2));
    right.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 + ITEMBOX_WIDTH / 2 - OUTLINE_WIDTH, WINDOW_HEIGHT / 2 - ITEMBOX_WIDTH / 2));

    top.setFillColor(hl_color);
    bottom.setFillColor(hl_color);
    left.setFillColor(hl_color);
    right.setFillColor(hl_color);
}

ItemBox::~ItemBox() {

}

void ItemBox::drawBox(sf::RenderWindow* window) {
    window->draw(bg);
    window->draw(top);
    window->draw(bottom);
    window->draw(left);
    window->draw(right);
}
