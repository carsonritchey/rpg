#include "battleScene.h"

BattleScene::BattleScene(sf::RenderWindow* window) : Scene(window) {
    this->window = window;
    old_view = &window->getView();

    window->setView(window->getDefaultView());

    font.loadFromFile("art/PressStart2P.ttf");

    const int font_size = TILE_SIZE * ZOOM_FACTOR / 2;
    const int name_font_size = TILE_SIZE * 2;
    const_cast<sf::Texture&>(font.getTexture(font_size)).setSmooth(false);

    const int v_padding = 50, h_padding = MAX_ATTACK_LENGTH / 2 * font_size, v_offset = 30, h_offset = 30;

    // adding monsters to player and enemy party
    player_party.push_back(*new Monster(0, 0.5f));
    enemy_party.push_back(*new Monster(1));
    enemy_party[0].sprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - enemy_party[current_enemy].slice_size * ZOOM_FACTOR / 2, v_offset));
    player_party[0].sprite.setPosition(sf::Vector2f(WINDOW_WIDTH - player_party[current_player].slice_size / player_scale_down * ZOOM_FACTOR - h_offset, WINDOW_HEIGHT - player_party[current_player].slice_size / player_scale_down * ZOOM_FACTOR - v_offset));

    // creating options text
    for(int i = 0; i < 4; i++) {
        texts[i].setFont(font);
        texts[i].setCharacterSize(font_size);
        texts[i].setFillColor(base_color);
    }
    texts[0].setString("ATTACK");
    texts[0].setPosition(sf::Vector2f(h_offset, WINDOW_HEIGHT - v_padding * 2 - v_offset));

    texts[1].setString("ITEM");
    texts[1].setPosition(sf::Vector2f(h_offset, WINDOW_HEIGHT - v_padding - v_offset));

    texts[2].setString("PARTY");
    texts[2].setPosition(sf::Vector2f(h_offset + h_padding, WINDOW_HEIGHT - v_padding * 2 - v_offset));

    texts[3].setString("RUN");
    texts[3].setPosition(sf::Vector2f(h_offset + h_padding, WINDOW_HEIGHT - v_padding - v_offset));

    sf::Vector2f pPos = player_party[current_player].sprite.getPosition();
    sf::Vector2f ePos = enemy_party[current_enemy].sprite.getPosition();

    playername_text.setFont(font);
    playername_text.setString(player_party[current_player].name);
    playername_text.setCharacterSize(name_font_size / player_scale_down);
    playername_text.setFillColor(base_color);
    playername_text.setPosition(sf::Vector2f(pPos.x, pPos.y - name_font_size / player_scale_down));

    enemyname_text.setFont(font);
    enemyname_text.setString(enemy_party[current_enemy].name);
    enemyname_text.setCharacterSize(name_font_size);
    enemyname_text.setFillColor(base_color);
    enemyname_text.setPosition(sf::Vector2f(ePos.x, ePos.y - name_font_size));

    sf::FloatRect pSize = player_party[current_player].sprite.getGlobalBounds();
    player_health = new HealthBar(window, pPos.x, pPos.y + pSize.height, pSize.width, 15, player_party[current_player].max_health, player_party[current_player].health);

    sf::FloatRect eSize = enemy_party[current_enemy].sprite.getGlobalBounds();
    enemy_health = new HealthBar(window, ePos.x, ePos.y + eSize.height, eSize.width, 15, enemy_party[current_enemy].max_health, enemy_party[current_enemy].health);
}

BattleScene::~BattleScene() {
    delete player_health;
    delete enemy_health;

    player_party.clear();
    enemy_party.clear();

    window->setView(*old_view);
}

void BattleScene::box(int x, int y, int w, int h) {
    const int outline_width = 2;

    sf::RectangleShape bg(sf::Vector2f(w, h));
    bg.setPosition(sf::Vector2f(x, y));
    
    sf::RectangleShape top(sf::Vector2f(w, outline_width));
    sf::RectangleShape bottom(sf::Vector2f(w, outline_width));
    sf::RectangleShape left(sf::Vector2f(outline_width, h));
    sf::RectangleShape right(sf::Vector2f(outline_width, h));

    top.setPosition(sf::Vector2f(x, y));
    bottom.setPosition(sf::Vector2f(x, y + h));
    left.setPosition(sf::Vector2f(x, y));
    right.setPosition(sf::Vector2f(x + w - outline_width, y));

    top.setFillColor(base_color);
    bottom.setFillColor(base_color);
    left.setFillColor(base_color);
    right.setFillColor(base_color);

    window->draw(bg);
    window->draw(top);
    window->draw(bottom);
    window->draw(left);
    window->draw(right);
}

bool BattleScene::canRun() {
    return false;
}

void BattleScene::drawBackground() {
    window->clear(sf::Color::White);
}

void BattleScene::drawText() {
    for(int i = 0; i < 4; i++)
        window->draw(texts[i]); 

    window->draw(playername_text);
    window->draw(enemyname_text);

    switch(option) {
        case attack:
            texts[0].setFillColor(selected_color);

            texts[1].setFillColor(base_color);
            texts[2].setFillColor(base_color);
            texts[3].setFillColor(base_color);

            texts[0].setStyle(sf::Text::Italic);
            texts[2].setStyle(sf::Text::Regular);
            texts[1].setStyle(sf::Text::Regular);
            texts[3].setStyle(sf::Text::Regular);
            break;
        case item:
            texts[1].setFillColor(selected_color);

            texts[0].setFillColor(base_color);
            texts[2].setFillColor(base_color);
            texts[3].setFillColor(base_color);

            texts[1].setStyle(sf::Text::Italic);
            texts[0].setStyle(sf::Text::Regular);
            texts[2].setStyle(sf::Text::Regular);
            texts[3].setStyle(sf::Text::Regular);
            break;
        case party:
            texts[2].setFillColor(selected_color);

            texts[0].setFillColor(base_color);
            texts[1].setFillColor(base_color);
            texts[3].setFillColor(base_color);

            texts[2].setStyle(sf::Text::Italic);
            texts[0].setStyle(sf::Text::Regular);
            texts[1].setStyle(sf::Text::Regular);
            texts[3].setStyle(sf::Text::Regular);
            break;
        case run:
            texts[3].setFillColor(selected_color);

            texts[0].setFillColor(base_color);
            texts[1].setFillColor(base_color);
            texts[2].setFillColor(base_color);

            texts[3].setStyle(sf::Text::Italic);
            texts[0].setStyle(sf::Text::Regular);
            texts[1].setStyle(sf::Text::Regular);
            texts[2].setStyle(sf::Text::Regular);
            break;
    }
}

int BattleScene::update(const float& dt, const sf::Event* event) {

    return RETURN_CODE_NOTHING;
}

void BattleScene::processEvent(const sf::Event* event) {
    if(event->type == sf::Event::KeyPressed) {
        if(event->key.code == sf::Keyboard::Space) { // bruh 
                switch(option) {
                    case battle_options::attack:

                        std::cout << player_party[current_player].attacks[0] << std::endl;

                        texts[0].setString(player_party[current_player].attacks[0]);
                        texts[2].setString(player_party[current_player].attacks[1]);
                        texts[1].setString(player_party[current_player].attacks[2]);
                        texts[3].setString(player_party[current_player].attacks[3]);
                        std::cout << "attack chose" << std::endl;
                        break;
                    case battle_options::item:
                        std::cout << "item chose" << std::endl;
                        break;
                    case battle_options::party:
                        std::cout << "party chose" << std::endl;
                        break;
                    case battle_options::run:
                        std::cout << "run chose" << std::endl;
                        if(!canRun()) {}
                        break;
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

    enemy_health->draw();
    player_health->draw();
}

void BattleScene::close_scene() {

}
