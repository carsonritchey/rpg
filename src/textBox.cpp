#include <SFML/Graphics.hpp>

#include "conf.h"
#include "textBox.h"

TextBox::TextBox(sf::RenderWindow* window, std::string content) {
    this->content = content;

    font.loadFromFile(FONT_PATH);

    text.setFont(font);
    text.setCharacterSize(TILE_SIZE * TEXT_ZOOM_FACTOR);
    text.setFillColor(text_color);

    bg.setFillColor(bg_color);

    top.setFillColor(hl_color);
    left.setFillColor(hl_color);
    right.setFillColor(hl_color);
    bottom.setFillColor(hl_color);

    text.setLineSpacing(LINE_SPACING);

    this->window = window;

    setPosition();
}

TextBox::~TextBox() {

}

void TextBox::drawBox() {
    window->draw(bg);
    window->draw(top);
    window->draw(left);
    window->draw(right);
    window->draw(bottom);
}

void TextBox::drawText() {
    text.setString(content);

    window->draw(text);
}

void TextBox::setPosition() {
    bg.setPosition(sf::Vector2f(SPACING, WINDOW_HEIGHT - WINDOW_HEIGHT / 3 - SPACING));

    top.setPosition(sf::Vector2f(SPACING, WINDOW_HEIGHT - WINDOW_HEIGHT / 3 - SPACING));
    left.setPosition(sf::Vector2f(SPACING, WINDOW_HEIGHT - WINDOW_HEIGHT / 3 - SPACING));
    right.setPosition(sf::Vector2f(WINDOW_WIDTH - SPACING - OUTLINE_WIDTH, WINDOW_HEIGHT - WINDOW_HEIGHT / 3 - SPACING));
    bottom.setPosition(sf::Vector2f(SPACING, WINDOW_HEIGHT - SPACING - OUTLINE_WIDTH));

    text.setPosition(sf::Vector2f(SPACING * 2, WINDOW_HEIGHT - WINDOW_HEIGHT / 3));
}
