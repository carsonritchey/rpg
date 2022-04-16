#include "inventory.h"

#include <iostream>

/* inventory stuff */
Inventory::Inventory() {
    loadTextures(ITEM_PATH);

    for(std::size_t i = 0; i < size(item_names); i++) {
        items.push_back(Item(i, this));
    }
}

Inventory::~Inventory() {

}

void Inventory::loadTextures(std::string path) {
    sf::Image image;
    image.loadFromFile(path);
    sf::Vector2u size = image.getSize();

    for(int j = 0; j < (int)size.y; j+= TILE_SIZE) {
        for(int i = 0; i < (int)size.x; i+= TILE_SIZE) {
            sf::Texture texture;
            texture.loadFromFile(path, sf::IntRect(i, j, TILE_SIZE, TILE_SIZE));

            textures.push_back(texture);
        }
    }
}

/* item stuff */
Item::Item(int id, Inventory* inventory) {
    this->id = id;

    sprite.setTexture(inventory->textures[id]);
}

Item::~Item() {

}
