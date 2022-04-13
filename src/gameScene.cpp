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

    if(this->player.textbox != nullptr) {
        this->player.textbox->drawBox(window);
        this->player.textbox->drawText(window);
    }
    else if(this->player.interactable && this->player.direction == directions::up)
        this->window->draw(this->player.interactSprite.sprite);
}

void GameScene::close_scene() {
    
}
