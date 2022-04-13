#include "gameScene.h"
#include "textBox.h"

#include <iostream>

GameScene::GameScene(sf::RenderWindow* window, sf::View* view) : Scene(window) {
    this->view = view;
}

GameScene::~GameScene() {

}

int GameScene::update(const float& dt, const sf::Event* event) {
    this->player.update(dt, this->current_map);

    // temporary level switch hotkey
    if(event->key.code == sf::Keyboard::O)
        current_map = &subworld_map;
    else if(event->key.code == sf::Keyboard::P)
        current_map = &overworld_map;

    if(player.current_map == maps::overworld)
        current_map = &overworld_map;
    else if(player.current_map == maps::subworld)
        current_map = &subworld_map;
    else
    {
        std::cout << "bruh" << std::endl;
    }

    return RETURN_CODE_NOTHING;
}

void GameScene::render() {
    sf::Vector2f player_pos = this->player.sprite.getPosition(); 
    this->current_map->drawMap(this->window, this->view, player_pos.x, player_pos.y);
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
