#include "titleScene.h"
#include "conf.h"
#include "map.h"

#include <iostream>

TitleScene::TitleScene(sf::RenderWindow* window) : Scene(window) {
    this->map.init(this->map_path, this->texture_path);

	this->font.loadFromFile("art/PressStart2P.ttf");
	this->text.setFont(font);
	this->text.setString(WINDOW_NAME);
	this->text.setCharacterSize(18);
	this->text.setStyle(sf::Text::Bold);
	this->text.setPosition(10, 10);
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

	window->draw(text);
}

void TitleScene::close_scene() {
    
}
