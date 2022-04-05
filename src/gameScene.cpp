#include "gameScene.h"
#include "conf.h"
#include "map.h"

GameScene::GameScene(sf::RenderWindow* window) : Scene(window) {
    this->map.init(this->map_path, this->texture_path);
}

GameScene::~GameScene() {

}

int GameScene::update(const float& dt, const sf::Event* event) {


    return RETURN_CODE_NOTHING;
}

void GameScene::render() {
    this->map.drawMap(window, 0, 0);
}

void GameScene::close_scene() {
    
}
