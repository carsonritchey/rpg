#include "player.h"

#include <iostream>

Player::Player(std::string texture_path) : Entity(texture_path) {
    sprite.setPosition(2 * TILE_SIZE * ZOOM_FACTOR, 3 * TILE_SIZE * ZOOM_FACTOR);
}

Player::~Player() {

}

void Player::checkInput(const sf::Event* event) {
    if(event->type == sf::Event::KeyPressed) {
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
	else if(event->type == sf::Event::KeyReleased) {
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

        if(event->key.code == sf::Keyboard::Space) {
            interacting = false;
        }
	}
}

bool Player::checkForInteractables(Map* map) {
    sf::Vector2f pos = sprite.getPosition(); 
    int tile_x = (int)(pos.x / TILE_SIZE / ZOOM_FACTOR);
    int tile_y = (int)(pos.y / TILE_SIZE / ZOOM_FACTOR);
    int x, y;
    std::string text; 
    bool found = false;

    if(map->tile_data[map->map_w * (tile_y - 1) + tile_x].length() != 0) {
        x = tile_x;
        y = tile_y; 
        text = map->tile_data[map->map_w * (tile_y - 1) + tile_x];

        found = true;
    }
    else if(map->tile_data[map->map_w * (tile_y - 1) + tile_x + 1].length() != 0) {
        x = tile_x;
        y = tile_y; 
        text = map->tile_data[map->map_w * (tile_y - 1) + tile_x + 1];

        found = true;
    }

    if(found && interacting && textbox == nullptr) {
        textbox = new TextBox(text);
    }

    interactable = found;
    return found;
}

sf::Vector2f Player::movePlayer(const float dt, Map* map) {
    sf::Vector2f pos; 
    sf::Vector2f dPos(0.f, 0.f);
    int tile_x, tile_y;
	if(up) {
        dPos.y -= mvnt_speed * dt;
        pos = sprite.getPosition();
        tile_x = (int)((pos.x + dPos.x) / TILE_SIZE / ZOOM_FACTOR);
        tile_y = (int)((pos.y + dPos.y) / TILE_SIZE / ZOOM_FACTOR);
        if(up && (map->tile_collision[map->map_w * tile_y + tile_x] == COLLISION_WALL || map->tile_collision[map->map_w * tile_y + tile_x + 1] == COLLISION_WALL)) {
            dPos.y = 0;
        }
    }
	if(down) {
        dPos.y += mvnt_speed * dt;
        pos = sprite.getPosition();
        tile_x = (int)((pos.x + dPos.x) / TILE_SIZE / ZOOM_FACTOR);
        tile_y = (int)((pos.y + dPos.y) / TILE_SIZE / ZOOM_FACTOR);
        if(down && (map->tile_collision[map->map_w * (tile_y + 1) + tile_x] == COLLISION_WALL || map->tile_collision[map->map_w * (tile_y + 1) + tile_x + 1] == COLLISION_WALL)) {
            dPos.y = 0;
        }
    }
	if(left) {
        dPos.x -= mvnt_speed * dt;
        pos = sprite.getPosition();
        tile_x = (int)((pos.x + dPos.x) / TILE_SIZE / ZOOM_FACTOR);
        tile_y = (int)((pos.y + dPos.y) / TILE_SIZE / ZOOM_FACTOR);
        if(left && (map->tile_collision[map->map_w * tile_y + tile_x] == COLLISION_WALL || map->tile_collision[map->map_w * (tile_y + 1) + tile_x] == COLLISION_WALL)) {
            dPos.x = 0;
        }
        if(!right)
            cycleTexture(l_frames, sizeof(l_frames) / sizeof(l_frames[0]));
    }
	if(right) {
        dPos.x += mvnt_speed * dt;
        pos = sprite.getPosition();
        tile_x = (int)((pos.x + dPos.x) / TILE_SIZE / ZOOM_FACTOR);
        tile_y = (int)((pos.y + dPos.y) / TILE_SIZE / ZOOM_FACTOR);
        if(right && (map->tile_collision[map->map_w * tile_y + tile_x + 1] == COLLISION_WALL || map->tile_collision[map->map_w * (tile_y + 1) + tile_x + 1] == COLLISION_WALL)) {
            dPos.x = 0;
        }
        if(!left)
            cycleTexture(r_frames, sizeof(r_frames) / sizeof(r_frames[0]));
    }

    // TL edge of word
    if(pos.x + dPos.x < 0)
        dPos.x = 0;
    else if(pos.x + dPos.x > map->map_w * TILE_SIZE * ZOOM_FACTOR - TILE_SIZE * ZOOM_FACTOR)
        dPos.x = 0;
    if(pos.y + dPos.y < 0)
        dPos.y = 0;
    else if(pos.y + dPos.y > map->map_h * TILE_SIZE * ZOOM_FACTOR - TILE_SIZE * ZOOM_FACTOR)
        dPos.y = 0;

    if(!left && !right && !up && !down) {
        if(direction == directions::left)
            setTexture(l_frames[0]);
        else 
            setTexture(r_frames[0]);
    }

    return dPos;
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
    }

    // progress text box if neccessary
    if(interacting) {
        std::cout << "bruh" << std::endl;
    }
}
