#include "gameScene.h"

GameScene::GameScene(sf::RenderWindow* window) : Scene(window) {

}

GameScene::~GameScene() {

}

void GameScene::update(const float& dt) {

}

void GameScene::render() {
    sf::RectangleShape rectangle(sf::Vector2f(128.0f,128.0f));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(320,240);

    window->draw(rectangle);
}

void GameScene::close_scene() {
    
}
