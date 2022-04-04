#include "player.h"

Player::Player(std::string texture_path) : Entity(texture_path) {

}

Player::~Player() {

}

void Player::update(const float dt, const sf::Event* event) {
	if(event->type == sf::Event::KeyPressed) {
		if(event->key.code == sf::Keyboard::Left)
			this->left = true;
		if(event->key.code == sf::Keyboard::Right)
			this->right = true;
		if(event->key.code == sf::Keyboard::Up)
			this->up = true;
		if(event->key.code == sf::Keyboard::Down)
			this->down = true;
	}
	else if(event->type == sf::Event::KeyReleased) {
		if(event->key.code == sf::Keyboard::Left)
			this->left = false;
		if(event->key.code == sf::Keyboard::Right)
			this->right = false;
		if(event->key.code == sf::Keyboard::Up)
			this->up = false;
		if(event->key.code == sf::Keyboard::Down)
			this->down = false;
	}

	if(up) this->sprite.move(0.f, -TILE_SIZE * ZOOM_FACTOR * dt * mvnt_speed);
	if(down) this->sprite.move(0.f, TILE_SIZE * ZOOM_FACTOR * dt * mvnt_speed);
	if(left) this->sprite.move(-TILE_SIZE * ZOOM_FACTOR * dt * mvnt_speed, 0.f);
	if(right) this->sprite.move(TILE_SIZE * ZOOM_FACTOR * dt * mvnt_speed, 0.f);
}
