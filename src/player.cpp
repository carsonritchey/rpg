#include "player.h"

Player::Player(std::string texture_path) : Entity(texture_path) {

}

Player::~Player() {

}

void Player::update(const sf::Event* event) {
	sf::Vector2f position = this->sprite.getPosition();

	if(event->type == sf::Event::KeyPressed) {
		if(event->key.code == sf::Keyboard::Left)
			position.x -= TILE_SIZE * ZOOM_FACTOR;
		if(event->key.code == sf::Keyboard::Right)
			position.x += TILE_SIZE * ZOOM_FACTOR;
		if(event->key.code == sf::Keyboard::Up)
			position.y -= TILE_SIZE * ZOOM_FACTOR;
		if(event->key.code == sf::Keyboard::Down)
			position.y += TILE_SIZE * ZOOM_FACTOR;

		this->sprite.setPosition(position);
	}
}
