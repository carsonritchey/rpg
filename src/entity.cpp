#include "entity.h"

#include <iostream>

Entity::Entity(std::string texture_path) {
    this->texture_path = texture_path;

    this->loadTextures();
    this->sprite.setTexture(this->textures[0]);
    this->sprite.scale(ZOOM_FACTOR, ZOOM_FACTOR);
}

Entity::~Entity() {

}

void Entity::cycleTexture(int* frame_indexes, int length) {
    frame_offset = (frame_offset + 1) % length;

    setTexture(frame_indexes[0] + frame_offset);
}

void Entity::loadTextures() {
    sf::Image image;
    image.loadFromFile(this->texture_path);
    sf::Vector2u size = image.getSize();

    for(int j = 0; j < (int)size.y; j += TILE_SIZE) {
        for(int i = 0; i < (int)size.x; i += TILE_SIZE) {
            sf::Texture texture;
            texture.loadFromFile(this->texture_path, sf::IntRect(i, j, TILE_SIZE, TILE_SIZE));
            this->textures.push_back(texture);
        }
    }
}

void Entity::setTexture(int index) {
    this->sprite.setTexture(this->textures[index]);
}
