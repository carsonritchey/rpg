#include "partyDisplay.h"

PartyDisplay::PartyDisplay(sf::RenderWindow* window, std::vector<Monster*> party) {
    this->window = window;
    this->party  = party;

    // outline stuff 
    bg     = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH - padding * 2, WINDOW_HEIGHT - padding * 2));

    top    = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH - padding * 2, outline_width));
    bottom = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH - padding * 2, outline_width));
    left   = sf::RectangleShape(sf::Vector2f(outline_width, WINDOW_HEIGHT - padding * 2));
    right  = sf::RectangleShape(sf::Vector2f(outline_width, WINDOW_HEIGHT - padding * 2));

    bg.setPosition(sf::Vector2f(padding, padding));

    top.setPosition(sf::Vector2f(padding, padding));
    bottom.setPosition(sf::Vector2f(padding, WINDOW_HEIGHT - padding));
    left.setPosition(sf::Vector2f(padding, padding));
    right.setPosition(sf::Vector2f(WINDOW_WIDTH - padding - outline_width, padding));

    bg.setFillColor(bg_color);

    top.setFillColor(outline_color);
    bottom.setFillColor(outline_color);
    left.setFillColor(outline_color);
    right.setFillColor(outline_color);

    // text stuff 
    font.loadFromFile(FONT_PATH);
    const_cast<sf::Texture&>(font.getTexture(font_size)).setSmooth(false);

    for(std::size_t i = 0; i < party.size(); i++) {
        name_texts[i].setFont(font);
        name_texts[i].setString(party[i]->name);
        name_texts[i].setCharacterSize(font_size / 2);
        name_texts[i].setFillColor(outline_color);

        name_texts[i].setPosition(sf::Vector2f(font_size + padding + outline_width * 2 + outline_width, padding + outline_width * 2 + (font_size * i) + font_size / 4 + (outline_width * i)));

        icons[i].setTexture(*party[i]->sprite.getTexture());
        const float scale = MONSTER_TILE_SIZE / font_size;
        icons[i].setScale(scale, scale);
        icons[i].setPosition(sf::Vector2f(padding + outline_width * 2, padding + outline_width * 2 + (font_size * i) + (outline_width * i)));
    }
}

PartyDisplay::~PartyDisplay() {

}

void PartyDisplay::draw() {
    window->draw(bg);

    window->draw(top);
    window->draw(bottom);
    window->draw(left);
    window->draw(right);

    for(std::size_t i = 0; i < party.size(); i++) {
        window->draw(icons[i]);
        window->draw(name_texts[i]);
    }
}
