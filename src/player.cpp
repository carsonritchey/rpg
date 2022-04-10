#include "player.h"

#include <iostream>

Player::Player(std::string texture_path) : Entity(texture_path) {
    sprite.setPosition(0 * TILE_SIZE * ZOOM_FACTOR, 0 * TILE_SIZE * ZOOM_FACTOR);
}

Player::~Player() {

}

void Player::checkInput(const sf::Event* event) {
    if(event->type == sf::Event::KeyPressed) {
		if(event->key.code == sf::Keyboard::Left)
			left = true;
		if(event->key.code == sf::Keyboard::Right)
			right = true;
		if(event->key.code == sf::Keyboard::Up)
			up = true;
		if(event->key.code == sf::Keyboard::Down)
			down = true;
	}
	else if(event->type == sf::Event::KeyReleased) {
		if(event->key.code == sf::Keyboard::Left)
			left = false;
		if(event->key.code == sf::Keyboard::Right)
			right = false;
		if(event->key.code == sf::Keyboard::Up)
			up = false;
		if(event->key.code == sf::Keyboard::Down)
			down = false;
	}
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        left = false;
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        right = false;
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        up = false;
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        down = false;
}

sf::Vector2f Player::movePlayer(const float dt, Map* map) {
    sf::Vector2f dPos(0.f, 0.f);
	if(up) {
        dPos.y -= mvnt_speed * dt;
    }
	if(down) {
        dPos.y += mvnt_speed * dt;
    }
	if(left) {
        dPos.x -= mvnt_speed * dt;
        if(!right)
            cycleTexture(l_frames, sizeof(l_frames) / sizeof(l_frames[0]));
    }
	if(right) {
        dPos.x += mvnt_speed * dt;
        if(!left)
            cycleTexture(r_frames, sizeof(r_frames) / sizeof(r_frames[0]));
    }


    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE * ZOOM_FACTOR, TILE_SIZE * ZOOM_FACTOR));
    sf::Vector2f pos = sprite.getPosition();
    int tile_x = (int)(pos.x / TILE_SIZE / ZOOM_FACTOR);
    int tile_y = (int)(pos.y / TILE_SIZE / ZOOM_FACTOR);

    //std::cout << (int)pos.x / TILE_SIZE / ZOOM_FACTOR << " " << (int)pos.y / TILE_SIZE / ZOOM_FACTOR << std::endl;
    //std::cout << map->tile_collision[map->map_h * (int)(pos.y / TILE_SIZE / ZOOM_FACTOR) + (int)(pos.x / TILE_SIZE / ZOOM_FACTOR)] << std::endl;
    
    ///*
    if(up && (map->tile_collision[map->map_h * tile_y + tile_x] == COLLISION_WALL || map->tile_collision[map->map_h * tile_y + tile_x + 1] == COLLISION_WALL)) {
        dPos.y = 0;
    }
    if(down && (map->tile_collision[map->map_h * (tile_y + 1) + tile_x] == COLLISION_WALL || map->tile_collision[map->map_h * (tile_y + 1) + tile_x + 1] == COLLISION_WALL)) {
        dPos.y = 0;
    }
    if(left && (map->tile_collision[map->map_h * tile_y + tile_x] == COLLISION_WALL || map->tile_collision[map->map_h * (tile_y + 1) + tile_x] == COLLISION_WALL)) {
        dPos.x = 0;
    }
    if(right && (map->tile_collision[map->map_h * tile_y + tile_x + 1] == COLLISION_WALL || map->tile_collision[map->map_h * (tile_y + 1) + tile_x + 1] == COLLISION_WALL)) {
        dPos.x = 0;
    }
    //*/

    // TL edge of word
    if(pos.x + dPos.x < 0)
        dPos.x = 0;
    else if(pos.x + dPos.x > map->map_w * TILE_SIZE * ZOOM_FACTOR - TILE_SIZE * ZOOM_FACTOR)
        dPos.x = 0;
    if(pos.y + dPos.y < 0)
        dPos.y = 0;
    else if(pos.y + dPos.y > map->map_h * TILE_SIZE * ZOOM_FACTOR - TILE_SIZE * ZOOM_FACTOR)
        dPos.y = 0;

    return dPos;
}

void Player::update(const float dt, const sf::Event* event, Map* map) {
    checkInput(event);
    sprite.move(movePlayer(dt, map));
}
