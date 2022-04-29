#include "battleScene.h"

Monster fortnite("art/sprites/battle/gay.png", 0.5f);
Monster twentyone("art/sprites/battle/nineplusten.png");

BattleScene::BattleScene(sf::RenderWindow* window) : Scene(window) {
    this->window = window;

    font.loadFromFile("art/PressStart2P.ttf");

    const int font_size = TILE_SIZE * ZOOM_FACTOR / 2;
    const_cast<sf::Texture&>(font.getTexture(font_size)).setSmooth(false);

    const int v_padding = 50, h_padding = 300, v_offset = 30, h_offset = 30;

    attack_text.setFont(font);
    attack_text.setString("ATTACK");
    attack_text.setCharacterSize(font_size);
    attack_text.setFillColor(base_color);
    attack_text.setPosition(sf::Vector2f(h_offset, WINDOW_HEIGHT - v_padding * 2 - v_offset));

    item_text.setFont(font);
    item_text.setString("ITEM");
    item_text.setCharacterSize(font_size);
    item_text.setFillColor(base_color);
    item_text.setPosition(sf::Vector2f(h_offset, WINDOW_HEIGHT - v_padding - v_offset));

    party_text.setFont(font);
    party_text.setString("PARTY");
    party_text.setCharacterSize(font_size);
    party_text.setFillColor(base_color);
    party_text.setPosition(sf::Vector2f(h_offset + h_padding, WINDOW_HEIGHT - v_padding * 2 - v_offset));

    run_text.setFont(font);
    run_text.setString("RUN");
    run_text.setCharacterSize(font_size);
    run_text.setFillColor(base_color);
    run_text.setPosition(sf::Vector2f(h_offset + h_padding, WINDOW_HEIGHT - v_padding - v_offset));

    player_party.push_back(fortnite);
    enemy_party.push_back(twentyone);

    enemy_party[0].sprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - enemy_party[0].slice_size * ZOOM_FACTOR / 2, v_offset));
    player_party[0].sprite.setPosition(sf::Vector2f(WINDOW_WIDTH - 64 / 2 * ZOOM_FACTOR - h_offset, WINDOW_HEIGHT - 64 / 2 * ZOOM_FACTOR - v_offset));
}

BattleScene::~BattleScene() {

}

bool BattleScene::canRun() {
    return false;
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

    return RETURN_CODE_NOTHING;
}

void BattleScene::processEvent(const sf::Event* event) {
    if(event->type == sf::Event::KeyPressed) {
        if(event->key.code == sf::Keyboard::Space) { // bruh 
            if(textbox != nullptr) { // if there's a textbox on screen 
                if(textbox->progressText()) {
                    delete textbox;
                    textbox = nullptr;
                }
            }
            else {
                switch(option) {
                    case battle_options::attack:
                        std::cout << "attack chose" << std::endl;
                        textbox = new TextBox("bruh");
                        break;
                    case battle_options::item:
                        std::cout << "item chose" << std::endl;
                        break;
                    case battle_options::party:
                        std::cout << "party chose" << std::endl;
                        break;
                    case battle_options::run:
                        std::cout << "run chose" << std::endl;
                        if(!canRun())
                            textbox = new TextBox("yeah, sorry no");
                        break;
                }
            }
        }

        else if(event->key.code == sf::Keyboard::Up) {
            if(option == battle_options::item) option = battle_options::attack;
            else if(option == battle_options::run) option = battle_options::party;
        }
        else if(event->key.code == sf::Keyboard::Down) {
            if(option == battle_options::attack) option = battle_options::item;
            else if(option == battle_options::party) option = battle_options::run;
        }
        else if(event->key.code == sf::Keyboard::Left) {
            if(option == battle_options::party) option = battle_options::attack;
            else if(option == battle_options::run) option = battle_options::item;
        }
        else if(event->key.code == sf::Keyboard::Right) {
            if(option == battle_options::attack) option = battle_options::party;
            else if(option == battle_options::item) option = battle_options::run;
        }
    }
}

void BattleScene::render() {
    drawBackground();
    drawText();

    window->draw(enemy_party[current_enemy].sprite);
    window->draw(player_party[current_player].sprite);
    if(textbox != nullptr)
        textbox->draw(window);
}

void BattleScene::close_scene() {

}
