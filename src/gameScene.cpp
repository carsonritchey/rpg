#include "gameScene.h"
#include "textBox.h"
#include "inventory.h"

GameScene::GameScene(sf::RenderWindow* window, sf::View* view) : Scene(window) {
    this->view = view;
}

GameScene::~GameScene() {

}

int GameScene::update(const float& dt, const sf::Event* event) {
    this->player.update(dt, this->current_map);

    // updates ALL npcs on map
    // needs to be optimized to only update npcs on screen later 
    for(std::size_t i = 0; i < this->current_map->npcs.size(); i++)
        this->current_map->npcs[i]->update(dt, this->current_map);

    if(player.current_map == maps::overworld)
        current_map = &overworld_map;
    else if(player.current_map == maps::subworld)
        current_map = &subworld_map;

    return RETURN_CODE_NOTHING;
}

void GameScene::render() {
    sf::Vector2f player_pos = this->player.sprite.getPosition(); 
    this->current_map->drawMap(this->window, this->view, player_pos.x, player_pos.y);
    this->current_map->drawEntities(this->window, this->view, player_pos.x, player_pos.y);
	this->window->draw(this->player.sprite);

    if(this->player.textbox != nullptr) {
        this->player.textbox->drawBox(window);
        this->player.textbox->drawText(window);
    }
    else if(this->player.interactable)
        this->window->draw(this->player.interactSprite.sprite);
}

void GameScene::close_scene() {
    
}
