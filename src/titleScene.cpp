#include "titleScene.h"
#include "conf.h"
#include "map.h"

#include <iostream>

TitleScene::TitleScene(sf::RenderWindow* window) : Scene(window) {
    this->map.init(this->map_path, this->texture_path);

    int font_size = TILE_SIZE * ZOOM_FACTOR;

	this->font.loadFromFile("art/PressStart2P.ttf");
    // disable anti-aliasing hack 
    const_cast<sf::Texture&>(font.getTexture(font_size)).setSmooth(false);
    
	this->text.setFont(font);
    this->text_backdrop.setFont(font);

	this->text.setString(WINDOW_NAME);
	this->text_backdrop.setString(WINDOW_NAME);

	this->text.setCharacterSize(font_size);
	this->text_backdrop.setCharacterSize(font_size);

	this->text.setStyle(sf::Text::Bold);
	this->text_backdrop.setStyle(sf::Text::Bold);

    this->text_backdrop.setFillColor(sf::Color::Black);

	this->text.setPosition(2 * TILE_SIZE * ZOOM_FACTOR, 1 * TILE_SIZE * ZOOM_FACTOR);
	this->text_backdrop.setPosition(2 * TILE_SIZE * ZOOM_FACTOR + 5, 1 * TILE_SIZE * ZOOM_FACTOR - 5);
}

TitleScene::~TitleScene() {

}

void TitleScene::update(const float& dt) {

}

void TitleScene::render() {
	for(auto sprite : this->map.bg_sprites) {
		window->draw(sprite.second);
	}
	for(auto sprite : this->map.fg_sprites) {
		window->draw(sprite.second);
	}

    sf::Texture texture;
    texture.loadFromFile("art/sprites/among.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.scale(ZOOM_FACTOR, ZOOM_FACTOR); 
    sprite.setPosition(0, 2 * TILE_SIZE * ZOOM_FACTOR);

    window->draw(sprite);
    window->draw(text_backdrop);
	window->draw(text);
}

void TitleScene::close_scene() {
    
}
