#include "gameScene.h"
#include "conf.h"
#include "map.h"

#include <iostream>

GameScene::GameScene(sf::RenderWindow* window) : Scene(window) {
    this->map.init(this->map_path, this->texture_path);
}

GameScene::~GameScene() {

}

void GameScene::update(const float& dt) {

}

void GameScene::render() {
	for(auto sprite : this->map.bg_sprites) {
		window->draw(sprite.second);
	}
	for(auto sprite : this->map.fg_sprites) {
		window->draw(sprite.second);
	}

}

void GameScene::close_scene() {
    
}
