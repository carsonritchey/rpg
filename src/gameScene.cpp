#include "gameScene.h"

#include <iostream>
int n = 0;

GameScene::GameScene(sf::RenderWindow* window, sf::View* view) : Scene(window) {
    this->map.init(this->map_path, this->texture_path);

    this->view = view;
}

GameScene::~GameScene() {

}

int GameScene::update(const float& dt, const sf::Event* event) {
    if (event->type == sf::Event::KeyPressed)
    {
        if (event->key.code == sf::Keyboard::Right)
        {
            n++;
        }
    }


    return RETURN_CODE_NOTHING;
}

void GameScene::render() {
    this->map.drawMap(this->window, this->view, n, 0);
	this->window->draw(this->player.sprite);
}

void GameScene::close_scene() {
    
}
