#include "player.h"

#include <iostream>

Player::Player(std::string texture_path) : Entity(texture_path) {
    sprite.setPosition(2 * TILE_SIZE * ZOOM_FACTOR, 3.5f * TILE_SIZE * ZOOM_FACTOR);

    party = new std::vector<Monster*>;
    party->push_back(new Monster(1, 0.5f));
    party->push_back(new Monster(0, 0.5f));
    party->push_back(new Monster(6, 0.5f));
    party_display = new PartyDisplay(party);
}

Player::~Player() {
    delete party_display;

    party->clear();
    delete party;
}

void Player::animate() {
    if((up || down || left || right) && !(up && down)) {
        if(global_tick % animation_speed == 0) {
            if(h_dir == directions::left && !right)
                cycleTexture(l_frames, sizeof(l_frames) / sizeof(l_frames[0]));
            else if(h_dir == directions::right && !left)
                cycleTexture(r_frames, sizeof(r_frames) / sizeof(r_frames[0]));
        }
    }
    else {
        if(h_dir == directions::left) {
            setTexture(l_frames[0]);
        }
        else {
            setTexture(r_frames[0]);
        }
    }
}

void Player::checkInput(const sf::Event* event) {
    if(event->type == sf::Event::KeyPressed) {
        if(textbox != nullptr) {
            if(event->key.code == sf::Keyboard::Space) {
                if(textbox->progressText()) {
                    killTextBox();
                }
            }
        } else {
            if(event->key.code == sf::Keyboard::Left) {
                left = true;
                h_dir = directions::left;
            }
            else if(event->key.code == sf::Keyboard::Right) {
                right = true;
                h_dir = directions::right;
            }
            else if(event->key.code == sf::Keyboard::Up) {
                up = true;
                v_dir = directions::up;
            }
            else if(event->key.code == sf::Keyboard::Down) {
                down = true;
                v_dir = directions::down;
            }

            if(event->key.code == sf::Keyboard::Space) {
                interacting = true;
            }
            else if(event->key.code == sf::Keyboard::P) {
                party_display_on = !party_display_on;
            }
        }
    }
    else if(event->type == sf::Event::KeyReleased) {
        if(textbox == nullptr) {
            if(event->key.code == sf::Keyboard::Left) {
                left = false; 

                if(right)
                    h_dir = directions::right;
            }
            else if(event->key.code == sf::Keyboard::Right) {
                right = false;

                if(left)
                    h_dir = directions::left;
            }
            else if(event->key.code == sf::Keyboard::Up) {
                up = false;

                if(down)
                    v_dir = directions::down;
            }
            else if(event->key.code == sf::Keyboard::Down) {
                down = false;

                if(up)
                    v_dir = directions::up;
            }
        }

        if(event->key.code == sf::Keyboard::Space) {
            interacting = false;
        }
    }
}

bool Player::checkForInteractables(Map* map) {
    sf::Vector2f pos = sprite.getPosition(); 
    int tile_x = (int)(pos.x / TILE_SIZE / ZOOM_FACTOR);
    int tile_y = (int)(pos.y / TILE_SIZE / ZOOM_FACTOR);
    std::string text; 
    bool found = false;

    // above 
    if(map->tile_data[map->map_w * (tile_y - 1) + tile_x].length() != 0) {
        text = map->tile_data[map->map_w * (tile_y - 1) + tile_x];
        tile_y--;

        found = true;
    }
    else if(map->tile_data[map->map_w * (tile_y - 1) + tile_x + 1].length() != 0) {
        text = map->tile_data[map->map_w * (tile_y - 1) + tile_x + 1];
        tile_y--;
        tile_x++;

        found = true;
    }
    // below
    else if(map->tile_data[map->map_w * (tile_y + 2) + tile_x].length() != 0) {
        text = map->tile_data[map->map_w * (tile_y + 2) + tile_x];
        tile_y += 2;

        found = true;
    }
    else if(map->tile_data[map->map_w * (tile_y + 2) + tile_x + 1].length() != 0) {
        text = map->tile_data[map->map_w * (tile_y + 2) + tile_x + 1];
        tile_y += 2;
        tile_x++;

        found = true;
    }

    // if there's something to interact with above player and they pressed space 
    if(found && interacting) {
        up = false; down = false; left = false; right = false;
        // if talking to chest
        if(text.substr(0, strlen(TILEDAT_ITEM_PREFIX)) == TILEDAT_ITEM_PREFIX) {
            if(textbox == nullptr) {
                map->setTexture(tile_x, tile_y, FG, CHEST_OPEN_TEXTURE);
                inventory.deltaStack(text.substr(text.find(TILEDAT_SEPERATOR) + 1, text.substr(text.find(TILEDAT_SEPERATOR) + 1).find(TILEDAT_SEPERATOR)), 1);

                textbox = new TextBox(text.substr(text.find_last_of(TILEDAT_SEPERATOR) + 1));
            }
        }
        // if talking to door
        else if(text.substr(0, strlen(TILEDAT_DOOR_PREFIX)) == TILEDAT_DOOR_PREFIX) {
            std::string door_coords = text.substr(text.find(TILEDAT_SEPERATOR) + 1);
            int door_x = std::stoi(door_coords.substr(0, door_coords.find(TILEDAT_POS_SEPERATOR)));
            int door_y = std::stoi(door_coords.substr(door_coords.find(TILEDAT_POS_SEPERATOR) + 1));

            sprite.setPosition(sf::Vector2f(door_x * TILE_SIZE * ZOOM_FACTOR, door_y * TILE_SIZE * ZOOM_FACTOR));
            cycleCurrentMap();

            interacting = false;
        }
        // if talking to sign 
        else if(textbox == nullptr) {
            textbox = new TextBox(text);
        }
    }

    interactable = found;
    return found;
}

void Player::cycleCurrentMap() {
    if(current_map == maps::overworld)
        current_map = maps::subworld;
    else if(current_map == maps::subworld)
        current_map = maps::overworld;
    else {
        current_map = maps::overworld; 
    }
}

int Player::getCurrentTileTexture(Map* map, sf::Vector2f pos, int layer) {
    pos.x += TILE_SIZE * ZOOM_FACTOR / 2.0;
    pos.x += TILE_SIZE * ZOOM_FACTOR / 2.0;
    int tile_x = (int)(pos.x / TILE_SIZE / ZOOM_FACTOR);
    int tile_y = (int)(pos.y / TILE_SIZE / ZOOM_FACTOR);

    const sf::Texture* tile_texture;
    if(layer == BG)
        tile_texture = map->bg_sprites[map->map_w * tile_x + tile_y].getTexture();
    if(layer == FG)
        tile_texture = map->fg_sprites[map->map_w * tile_x + tile_y].getTexture();

    for(std::size_t i = 0; i < map->textures.size(); i++) {
        if(tile_texture == &map->textures[i]) {
            return i;
        }
    }

    return -1;
}

void Player::killItemBox() {
    delete itembox;
    itembox = nullptr;
}
void Player::killTextBox() {
    delete textbox;
    textbox = nullptr;
}

sf::Vector2f Player::movePlayer(const float dt, Map* map) {
    sf::Vector2f pos = sprite.getPosition(); 
    sf::Vector2f dPos(0.f, 0.f);

    // collision detection
    if(up) {
        dPos.y -= mvnt_speed * dt;
        if(movePlayerCalculateDPos(dt, map, pos, dPos) == 0)
            dPos.y = 0;
    }
    if(down) {
        dPos.y += mvnt_speed * dt;
        if(movePlayerCalculateDPos(dt, map, pos, dPos) == 0)
            dPos.y = 0;
    }
    if(left) {
        dPos.x -= mvnt_speed * dt;
        if(movePlayerCalculateDPos(dt, map, pos, dPos) == 0)
            dPos.x = 0;
    }
    if(right) {
        dPos.x += mvnt_speed * dt;
        if(movePlayerCalculateDPos(dt, map, pos, dPos) == 0)
            dPos.x = 0;
    }

    // edge of world
    if(pos.x + dPos.x < 0 || pos.x + TILE_SIZE * ZOOM_FACTOR + dPos.x > map->map_w * TILE_SIZE * ZOOM_FACTOR)
        dPos.x = 0;
    if(pos.y + dPos.y < 0 || pos.y + TILE_SIZE * ZOOM_FACTOR + dPos.y > map->map_h * TILE_SIZE * ZOOM_FACTOR)
        dPos.y = 0;

    animate();

    if((dPos.x != 0 && dPos.y != 0) &&rand() % battle_odds == 0 && getCurrentTileTexture(map, sprite.getPosition(), FG) == TALL_GRASS_TEXTURE) {
        need_battle = true;
    }

    return dPos;
}
float Player::movePlayerCalculateDPos(const float dt, Map* map, sf::Vector2f pos, sf::Vector2f dPos) {
    sf::RectangleShape player_rect(sf::Vector2f(TILE_SIZE * ZOOM_FACTOR, TILE_SIZE * ZOOM_FACTOR));
    player_rect.setPosition(pos + dPos);
    sf::Rect<float> player_bounds = player_rect.getGlobalBounds();

    int tile_x = (int)(pos.x / TILE_SIZE / ZOOM_FACTOR);
    int tile_y = (int)(pos.y / TILE_SIZE / ZOOM_FACTOR);
    // check all surrounding tiles
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(i == 1 && j == 1) continue;

            sf::Rect<float>* r = map->tile_collision[map->map_w * (tile_y + j) + (tile_x + i)];
            if(r != nullptr) {
                if(player_bounds.intersects(*r))
                    return 0;
            }
        }
    }

    // check for ALL (and i mean all) npcs for collision
    // needs to be optimized later
    for(std::size_t i = 0; i < map->npcs.size(); i++) {
        if(player_bounds.intersects(map->npcs[i]->sprite.getGlobalBounds()))
            return 0;
    }

    return mvnt_speed * dt;
}

void Player::processEvent(const sf::Event* event) {
    checkInput(event);
}

int Player::update(const float dt, Map* map) {
    // actually move player
    sprite.move(movePlayer(dt, map));

    // set position of space bar prompt
    if(checkForInteractables(map)) {
        sf::Vector2f pos = sprite.getPosition(); 
        pos.y += TILE_SIZE * ZOOM_FACTOR;
        interactSprite.sprite.setPosition(pos);

        if(global_tick % interactSprite_animation_speed == 0)
            interactSprite.cycleTexture(2);
    }

    if(need_battle) {
        need_battle = up = down = left = right = false;

        return RETURN_CODE_BATTLESCENE;
    }

    return RETURN_CODE_NOTHING;
}
