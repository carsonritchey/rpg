#include <SFML/Graphics.hpp>

#include "conf.h"
#include "textBox.h"

TextBox::TextBox(std::string content) {
    this->content = content;
    //content = std::regex_replace(content, std::regex("NEWLINE"), "\n");
    tail = 0;
    std::size_t found = content.find("\n");
    head = (found != std::string::npos) ? found : content.length();

    //cout << tail << " " << head << " " << content.subtring(tail, head + 1) << std::endl;

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
}

TextBox::~TextBox() {

}

void TextBox::draw(sf::RenderWindow* window) {
    drawBox(window);
    drawText(window);
}

void TextBox::drawBox(sf::RenderWindow* window) {
    setPosition(window);
    window->draw(bg);
    window->draw(top);
    window->draw(left);
    window->draw(right);
    window->draw(bottom);
}

void TextBox::drawText(sf::RenderWindow* window) {
    text.setString(content.substr(tail, head + 1));

    window->draw(text);
}

bool TextBox::progressText() {
    if(head >= (int)content.length() - 1)
        return true;

    std::size_t found = content.find("\n", head + 1);
    head = (found != std::string::npos) ? found : content.length();

    return false;
}

void TextBox::setPosition(sf::RenderWindow* window) {
    bg.setPosition(window->mapPixelToCoords(sf::Vector2i(SPACING, WINDOW_HEIGHT - WINDOW_HEIGHT / 3 - SPACING)));

    top.setPosition(window->mapPixelToCoords(sf::Vector2i(SPACING, WINDOW_HEIGHT - WINDOW_HEIGHT / 3 - SPACING)));
    left.setPosition(window->mapPixelToCoords(sf::Vector2i(SPACING, WINDOW_HEIGHT - WINDOW_HEIGHT / 3 - SPACING)));
    right.setPosition(window->mapPixelToCoords(sf::Vector2i(WINDOW_WIDTH - SPACING - OUTLINE_WIDTH, WINDOW_HEIGHT - WINDOW_HEIGHT / 3 - SPACING)));
    bottom.setPosition(window->mapPixelToCoords(sf::Vector2i(SPACING, WINDOW_HEIGHT - SPACING - OUTLINE_WIDTH)));

    text.setPosition(window->mapPixelToCoords(sf::Vector2i(SPACING * 2, WINDOW_HEIGHT - WINDOW_HEIGHT / 3)));
}
