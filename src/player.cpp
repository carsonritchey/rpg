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
		if(event->key.code == sf::Keyboard::Right) {
			right = true;
            direction = directions::right;
        }
		if(event->key.code == sf::Keyboard::Up) {
			up = true;
            direction = directions::up;
        }
		if(event->key.code == sf::Keyboard::Down) {
			down = true;
            direction = directions::down;
        }
	}
	else if(event->type == sf::Event::KeyReleased) {
		if(event->key.code == sf::Keyboard::Left) {
			left = false; 
            if(!left && !right && !up && !down)
                direction = directions::left;
        }
		if(event->key.code == sf::Keyboard::Right) {
			right = false;
            if(!left && !right && !up && !down)
                direction = directions::right;
        }
		if(event->key.code == sf::Keyboard::Up) {
			up = false;
            if(!left && !right && !up && !down)
                direction = directions::up;
        }
		if(event->key.code == sf::Keyboard::Down) {
			down = false;
            if(!left && !right && !up && !down)
                direction = directions::down;
        }
	}
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
        if(up && (map->tile_collision[map->map_h * tile_y + tile_x] == COLLISION_WALL || map->tile_collision[map->map_h * tile_y + tile_x + 1] == COLLISION_WALL)) {
            dPos.y = 0;
        }
    }
	if(down) {
        dPos.y += mvnt_speed * dt;
        pos = sprite.getPosition();
        tile_x = (int)((pos.x + dPos.x) / TILE_SIZE / ZOOM_FACTOR);
        tile_y = (int)((pos.y + dPos.y) / TILE_SIZE / ZOOM_FACTOR);
        if(down && (map->tile_collision[map->map_h * (tile_y + 1) + tile_x] == COLLISION_WALL || map->tile_collision[map->map_h * (tile_y + 1) + tile_x + 1] == COLLISION_WALL)) {
            dPos.y = 0;
        }
    }
	if(left) {
        dPos.x -= mvnt_speed * dt;
        pos = sprite.getPosition();
        tile_x = (int)((pos.x + dPos.x) / TILE_SIZE / ZOOM_FACTOR);
        tile_y = (int)((pos.y + dPos.y) / TILE_SIZE / ZOOM_FACTOR);
        if(left && (map->tile_collision[map->map_h * tile_y + tile_x] == COLLISION_WALL || map->tile_collision[map->map_h * (tile_y + 1) + tile_x] == COLLISION_WALL)) {
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
        if(right && (map->tile_collision[map->map_h * tile_y + tile_x + 1] == COLLISION_WALL || map->tile_collision[map->map_h * (tile_y + 1) + tile_x + 1] == COLLISION_WALL)) {
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
    sprite.move(movePlayer(dt, map));
}
