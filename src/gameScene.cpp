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
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromFile("art/tiles/overworld.png");
    sprite.setTexture(texture);
    sprite.setPosition(window->mapPixelToCoords(sf::Vector2i(0, 0))); 

    window->draw(sprite);
}

void GameScene::close_scene() {
    
}
