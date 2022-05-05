#include "battleScene.h"

const int font_size = TILE_SIZE * ZOOM_FACTOR / 2;
const int name_font_size = TILE_SIZE * 2;
const int v_padding = 50, h_padding = MAX_ATTACK_LENGTH / 2 * font_size, v_offset = 30, h_offset = 30;

BattleScene::BattleScene(sf::RenderWindow* window) : Scene(window) {
    this->window = window;
    old_view = &window->getView();

    window->setView(window->getDefaultView());

    font.loadFromFile("art/PressStart2P.ttf");
    const_cast<sf::Texture&>(font.getTexture(font_size)).setSmooth(false);

    // adding monsters to player and enemy party
    player_party.push_back(new Monster(1, 0.5f));
    enemy_party.push_back(new Monster(5));
    enemy_party[0]->sprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - enemy_party[current_enemy]->slice_size * ZOOM_FACTOR / 2, v_offset));
    player_party[0]->sprite.setPosition(sf::Vector2f(WINDOW_WIDTH - player_party[current_player]->slice_size / player_scale_down * ZOOM_FACTOR - h_offset, WINDOW_HEIGHT - player_party[current_player]->slice_size / player_scale_down * ZOOM_FACTOR - v_offset));

    initOptionsText();
    initNameText(); 

    sf::Vector2f pPos = player_party[current_player]->sprite.getPosition();
    sf::FloatRect pSize = player_party[current_player]->sprite.getGlobalBounds();
    player_healthbar = new HealthBar(window, pPos.x, pPos.y + pSize.height, pSize.width, 15, player_party[current_player]->max_health, &player_party[current_player]->health);

    sf::Vector2f ePos = enemy_party[current_enemy]->sprite.getPosition();
    sf::FloatRect eSize = enemy_party[current_enemy]->sprite.getGlobalBounds();
    enemy_healthbar = new HealthBar(window, ePos.x, ePos.y + eSize.height, eSize.width, 15, enemy_party[current_enemy]->max_health, &enemy_party[current_enemy]->health);
}

BattleScene::~BattleScene() {
    delete player_healthbar;
    delete enemy_healthbar;

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
    window->draw(playername_text);
    window->draw(enemyname_text);

    for(int i = 0; i < 4; i++) {
        if(i == current_text) {
            texts[i].setFillColor(selected_color);
            texts[i].setStyle(sf::Text::Italic);
        }
        else {
            texts[i].setFillColor(base_color);
            texts[i].setStyle(sf::Text::Regular);
        }

        window->draw(texts[i]); 
    }
}

void BattleScene::initAttackText() {
    for(int i = 0; i < 4; i++) {
        texts[i].setCharacterSize(font_size / 2);
    }
    texts[0].setString(player_party[current_player]->attacks[0]);
    texts[1].setString(player_party[current_player]->attacks[1]);
    texts[2].setString(player_party[current_player]->attacks[2]);
    texts[3].setString(player_party[current_player]->attacks[3]);
}

void BattleScene::initOptionsText() {
    for(int i = 0; i < 4; i++) {
        texts[i].setFont(font);
        texts[i].setCharacterSize(font_size);
        texts[i].setFillColor(base_color);
    }
    texts[0].setString("ATTACK");
    texts[0].setPosition(sf::Vector2f(h_offset, WINDOW_HEIGHT - v_padding * 2 - v_offset));

    texts[1].setString("PARTY");
    texts[1].setPosition(sf::Vector2f(h_offset + h_padding, WINDOW_HEIGHT - v_padding * 2 - v_offset));

    texts[2].setString("ITEM");
    texts[2].setPosition(sf::Vector2f(h_offset, WINDOW_HEIGHT - v_padding - v_offset));

    texts[3].setString("RUN");
    texts[3].setPosition(sf::Vector2f(h_offset + h_padding, WINDOW_HEIGHT - v_padding - v_offset));
}

void BattleScene::initNameText() {
    sf::Vector2f pPos = player_party[current_player]->sprite.getPosition();
    sf::FloatRect pSize = player_party[current_player]->sprite.getGlobalBounds();

    sf::Vector2f ePos = enemy_party[current_enemy]->sprite.getPosition();
    sf::FloatRect eSize = enemy_party[current_enemy]->sprite.getGlobalBounds();

    playername_text.setFont(font);
    playername_text.setString(player_party[current_player]->name);
    playername_text.setCharacterSize(name_font_size / player_scale_down);
    playername_text.setFillColor(base_color);
    playername_text.setPosition(sf::Vector2f(pPos.x - (float)player_party[current_player]->name.size() * name_font_size / 2 / 2 + pSize.width / 2, pPos.y - name_font_size / player_scale_down));

    enemyname_text.setFont(font);
    enemyname_text.setString(enemy_party[current_enemy]->name);
    enemyname_text.setCharacterSize(name_font_size);
    enemyname_text.setFillColor(base_color);
    enemyname_text.setPosition(sf::Vector2f(ePos.x - (float)enemy_party[current_enemy]->name.size() * name_font_size / 2 + eSize.width / 2, ePos.y - name_font_size));
}

int BattleScene::update(const float& dt, const sf::Event* event) {

    return RETURN_CODE_NOTHING;
}

void BattleScene::processEvent(const sf::Event* event) {
    if(event->type == sf::Event::KeyPressed) {
        // using textbox
        if(textbox != nullptr && event->key.code == sf::Keyboard::Space) {
            if(textbox->progressText()) {
                delete textbox;
                textbox = nullptr;
            }
        }
        else if(event->key.code == sf::Keyboard::Space || event->key.code == sf::Keyboard::Enter) { 
            // selecting option on main menu
            if(option == options::none) {
                switch(current_text) {
                    case 0:
                        initAttackText();

                        option = options::attack;
                        break;
                    case 1:
                        option = options::party;
                        break;
                    case 2:
                        option = options::item;
                        break;
                    case 3:
                        //option = options::run;
                        textbox = new TextBox("bruhhhhh yuhhuusdf");
                        break;
                }
            }
            // selecting move in attack 
            else if(option == options::attack) {
                //enemy_party[current_enemy]->health -= player_party[current_player]->attack_values[current_text][0];
                turn();
            }
        }
        // returning to menu
        else if((event->key.code == sf::Keyboard::Escape || event->key.code == sf::Keyboard::BackSpace) && option != options::none) {
            initOptionsText();

            option = options::none;
        }
        else if(event->key.code == sf::Keyboard::Up) {
            if(current_text == 2 || current_text == 3) current_text -= 2;
        }
        else if(event->key.code == sf::Keyboard::Down) {
            if(current_text == 0 || current_text == 1) current_text += 2;
        }
        else if(event->key.code == sf::Keyboard::Left) {
            if(current_text == 1 || current_text == 3) current_text -= 1;
        }
        else if(event->key.code == sf::Keyboard::Right) {
            if(current_text == 0 || current_text == 2) current_text += 1;
        }
    }
}

void BattleScene::turn() {
    // if player is faster or they tie 
    if(player_party[current_player]->speed >= enemy_party[current_enemy]->speed) {
        enemy_party[current_enemy]->health -= player_party[current_player]->attack_values[current_text][0];
        player_party[current_player]->health -= enemy_party[current_enemy]->attack_values[rand() % enemy_party[current_enemy]->move_count][0];
    }
    // if enemy is faster
    else {
        player_party[current_player]->health -= enemy_party[current_enemy]->attack_values[rand() % enemy_party[current_enemy]->move_count][0];

        textbox = new TextBox(player_party[current_player]->name + " used '" + player_party[current_player]->attacks[current_text] + "'!"); 

        enemy_party[current_enemy]->health -= player_party[current_player]->attack_values[current_text][0];
    }
}

void BattleScene::render() {
    drawBackground();
    drawText();

    window->draw(enemy_party[current_enemy]->sprite);
    window->draw(player_party[current_player]->sprite);

    enemy_healthbar->draw();
    player_healthbar->draw();

    //std::cout << (textbox == nullptr ? "none" : "one") << std::endl;

    if(textbox != nullptr) {
        textbox->drawBox(window);
        textbox->drawText(window);
    }
}

void BattleScene::close_scene() {

}
