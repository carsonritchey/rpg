#include "gameScene.h"
#include "textBox.h"

#include <iostream>

GameScene::GameScene(sf::RenderWindow* window, sf::View* view) : Scene(window) {
    this->view = view;
}

GameScene::~GameScene() {

}

int GameScene::update(const float& dt, const sf::Event* event) {
    this->player.update(dt, &this->map);

    return RETURN_CODE_NOTHING;
}

void GameScene::render() {
    sf::Vector2f player_pos = this->player.sprite.getPosition(); 
    this->map.drawMap(this->window, this->view, player_pos.x, player_pos.y);
	this->window->draw(this->player.sprite);

    TextBox t(window, "please work\nblah\nifsdsdfnksjdfkjsndfkjsdnfkjn\n123456789012345678901234567890\nbruh");
    t.drawBox();
    t.drawText();
}

void GameScene::close_scene() {
    
}
