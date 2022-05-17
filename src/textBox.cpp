#include <SFML/Graphics.hpp>

#include "conf.h"
#include "textBox.h"

TextBox::TextBox(std::string content) {
    this->content = content;

    this->content = std::regex_replace(this->content, std::regex(enter_marker), "\n");
    this->content = std::regex_replace(this->content, std::regex(newline_marker), "\t");
    //std::cout << "textbox loaded with: " << this->content << std::endl;

    tail = 0;
    std::size_t found = this->content.find("\n");
    head = (found != std::string::npos) ? found : this->content.length();

    //cout << tail << " " << head << " " << this->content.subtring(tail, head + 1) << std::endl;

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
    // text is stored with \n as line breaks that require enter to be pressed to progress and \t for a line break that doesn't need enter 
    // when drawing text \t is replaced with \n
    text.setString(std::regex_replace(content.substr(tail, head + 1), std::regex("\t"), "\n"));

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
