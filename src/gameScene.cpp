#include "gameScene.h"

#include <iostream>
int x = 0;
int y = 0;

GameScene::GameScene(sf::RenderWindow* window, sf::View* view) : Scene(window) {
    this->map.init(this->map_path, this->texture_path);

    this->view = view;
}

GameScene::~GameScene() {

}

int GameScene::update(const float& dt, const sf::Event* event) {
    if (event->type == sf::Event::KeyPressed)
    {
        if (event->key.code == sf::Keyboard::Left)
            x--;
        else if (event->key.code == sf::Keyboard::Right)
            x++;
        else if (event->key.code == sf::Keyboard::Up)
            y--;
        else if (event->key.code == sf::Keyboard::Down)
            y++;
    }

    return RETURN_CODE_NOTHING;
}

void GameScene::render() {
    this->map.drawMap(this->window, this->view, x, y);
	this->window->draw(this->player.sprite);
}

void GameScene::close_scene() {
    
}
