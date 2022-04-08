#include "player.h"

Player::Player(std::string texture_path) : Entity(texture_path) {

}

Player::~Player() {

}

void Player::update(const float dt, const sf::Event* event, Map* map) {
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
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->left = false;
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->right = false;
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->up = false;
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->down = false;

    sf::Vector2f dPos(0.f, 0.f);
	if(up) {
        dPos.y -= mvnt_speed * dt;
    }
	if(down) {
        dPos.y += mvnt_speed * dt;
    }
	if(left) {
        dPos.x -= mvnt_speed * dt;
        this->setTexture(this->l_frames[0]);
    }
	if(right) {
        dPos.x += mvnt_speed * dt;
        this->setTexture(this->r_frames[0]);
    }

    sf::Vector2f pos = this->sprite.getPosition();

    if(pos.x + dPos.x < 0)
        dPos.x = 0;
    else if(pos.x + dPos.x > map->map_w * TILE_SIZE * ZOOM_FACTOR - TILE_SIZE * ZOOM_FACTOR)
        dPos.x = 0;

    if(pos.y + dPos.y < 0)
        dPos.y = 0;
    else if(pos.y + dPos.y > map->map_h * TILE_SIZE * ZOOM_FACTOR - TILE_SIZE * ZOOM_FACTOR)
        dPos.y = 0;

    this->sprite.move(dPos);
}
