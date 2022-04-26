#include "battleScene.h"

BattleScene::BattleScene(sf::RenderWindow* window) : Scene(window) {
    this->window = window;

    font.loadFromFile("art/PressStart2P.ttf");

    const int font_size = TILE_SIZE * ZOOM_FACTOR / 2;
    const_cast<sf::Texture&>(font.getTexture(font_size)).setSmooth(false);

    attack_text.setFont(font);
    attack_text.setString("ATTACK");
    attack_text.setCharacterSize(font_size);
    attack_text.setFillColor(base_color);
    attack_text.setPosition(sf::Vector2f(0, 0));

    item_text.setFont(font);
    item_text.setString("ITEM");
    item_text.setCharacterSize(font_size);
    item_text.setStyle(sf::Text::Bold | sf::Text::Italic);
    item_text.setFillColor(base_color);
    item_text.setPosition(sf::Vector2f(0, 100));

    party_text.setFont(font);
    party_text.setString("PARTY");
    party_text.setCharacterSize(font_size);
    party_text.setStyle(sf::Text::Bold | sf::Text::Italic);
    party_text.setFillColor(base_color);
    party_text.setPosition(sf::Vector2f(300, 0));

    run_text.setFont(font);
    run_text.setString("RUN");
    run_text.setCharacterSize(font_size);
    run_text.setStyle(sf::Text::Bold | sf::Text::Italic);
    run_text.setFillColor(base_color);
    run_text.setPosition(sf::Vector2f(300, 100));
}

BattleScene::~BattleScene() {

}

void BattleScene::drawBackground() {
    window->clear(sf::Color::White);
}

void BattleScene::drawText() {
    window->draw(attack_text); 
    window->draw(item_text); 
    window->draw(party_text); 
    window->draw(run_text); 

    switch(option) {
        case attack:
            attack_text.setFillColor(selected_color);

            item_text.setFillColor(base_color);
            party_text.setFillColor(base_color);
            run_text.setFillColor(base_color);

            attack_text.setStyle(sf::Text::Italic);
            party_text.setStyle(sf::Text::Regular);
            item_text.setStyle(sf::Text::Regular);
            run_text.setStyle(sf::Text::Regular);
            break;
        case item:
            item_text.setFillColor(selected_color);

            attack_text.setFillColor(base_color);
            party_text.setFillColor(base_color);
            run_text.setFillColor(base_color);

            item_text.setStyle(sf::Text::Italic);
            attack_text.setStyle(sf::Text::Regular);
            party_text.setStyle(sf::Text::Regular);
            run_text.setStyle(sf::Text::Regular);
            break;
        case party:
            party_text.setFillColor(selected_color);

            attack_text.setFillColor(base_color);
            item_text.setFillColor(base_color);
            run_text.setFillColor(base_color);

            party_text.setStyle(sf::Text::Italic);
            attack_text.setStyle(sf::Text::Regular);
            item_text.setStyle(sf::Text::Regular);
            run_text.setStyle(sf::Text::Regular);
            break;
        case run:
            run_text.setFillColor(selected_color);

            attack_text.setFillColor(base_color);
            item_text.setFillColor(base_color);
            party_text.setFillColor(base_color);

            run_text.setStyle(sf::Text::Italic);
            attack_text.setStyle(sf::Text::Regular);
            item_text.setStyle(sf::Text::Regular);
            party_text.setStyle(sf::Text::Regular);
            break;
    }
}

int BattleScene::update(const float& dt, const sf::Event* event) {
    if(event->type == sf::Event::KeyPressed) {
         if(event->key.code == sf::Keyboard::Up || event->key.code == sf::Keyboard::Down) {
            if(option == battle_options::attack) option = battle_options::item;
            else if(option == battle_options::item) option = battle_options::attack;
            else if(option == battle_options::party) option = battle_options::run;
            else if(option == battle_options::run) option = battle_options::party;
        }
        else if(event->key.code == sf::Keyboard::Left || event->key.code == sf::Keyboard::Right) {
            if(option == battle_options::attack) option = battle_options::party;
            else if(option == battle_options::item) option = battle_options::run;
            else if(option == battle_options::party) option = battle_options::attack;
            else if(option == battle_options::run) option = battle_options::item;
        }
    }

    return RETURN_CODE_NOTHING;
}

void BattleScene::render() {
    drawBackground();
    drawText();
}

void BattleScene::close_scene() {

}
