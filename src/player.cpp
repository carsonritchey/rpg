#include "player.h"

#include <iostream>

Player::Player(std::string texture_path) : Entity(texture_path) {
    sprite.setPosition(2 * TILE_SIZE * ZOOM_FACTOR, 3.5f * TILE_SIZE * ZOOM_FACTOR);
}

Player::~Player() {

}

void Player::checkInput(const sf::Event* event) {
    if(event->type == sf::Event::KeyPressed) {
        if(textbox != nullptr) {
            if(event->key.code == sf::Keyboard::Space) {
                if(textbox->progressText()) {
                    // prevents space sprite from flashing
                    direction = directions::right;
                    killTextBox();
                }
            }
        } else {
            if(event->key.code == sf::Keyboard::Left) {
                left = true;
                direction = directions::left;
            }
            else if(event->key.code == sf::Keyboard::Right) {
                right = true;
                direction = directions::right;
            }
            else if(event->key.code == sf::Keyboard::Up) {
                up = true;
                direction = directions::up;
            }
            else if(event->key.code == sf::Keyboard::Down) {
                down = true;
                direction = directions::down;
            }

            if(direction == directions::up || textbox != nullptr) {
                if(event->key.code == sf::Keyboard::Space) {
                    interacting = true;
                }
            }
        }
    }
    else if(event->type == sf::Event::KeyReleased) {
        if(textbox == nullptr) {
            if(event->key.code == sf::Keyboard::Left) {
                left = false; 
                if(!left && !right && !up && !down)
                    direction = directions::left;
            }
            else if(event->key.code == sf::Keyboard::Right) {
                right = false;
                if(!left && !right && !up && !down)
                    direction = directions::right;
            }
            else if(event->key.code == sf::Keyboard::Up) {
                up = false;
                if(!left && !right && !up && !down)
                    direction = directions::up;
            }
            else if(event->key.code == sf::Keyboard::Down) {
                down = false;
                if(!left && !right && !up && !down)
                    direction = directions::down;
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

    // if there's something to interact with above player and they pressed space 
    if(found && interacting) {
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

    return dPos;
}
float Player::movePlayerCalculateDPos(const float dt, Map* map, sf::Vector2f pos, sf::Vector2f dPos) {
    sf::RectangleShape player_rect(sf::Vector2f(TILE_SIZE * ZOOM_FACTOR, TILE_SIZE * ZOOM_FACTOR));
    player_rect.setPosition(pos + dPos);
    sf::Rect player_bounds = player_rect.getGlobalBounds();

    int tile_x = (int)(pos.x / TILE_SIZE / ZOOM_FACTOR);
    int tile_y = (int)(pos.y / TILE_SIZE / ZOOM_FACTOR);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(i == 1 && j == 1) continue;

            sf::RectangleShape* r = map->tile_collision[map->map_w * (tile_y + j) + (tile_x + i)];
            if(r != nullptr) {
                if(player_bounds.intersects(r->getGlobalBounds()))
                    return 0;
            }
        }
    }

    return mvnt_speed * dt;
}

void Player::processEvent(const sf::Event* event) {
    checkInput(event);
}

void Player::update(const float dt, Map* map) {
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
}
