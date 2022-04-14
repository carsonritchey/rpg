#include "inventory.h"

Inventory::Inventory() {

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
