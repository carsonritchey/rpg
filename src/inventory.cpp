#include "inventory.h"

#include <iostream>

/* inventory stuff */
Inventory::Inventory() {
    loadTextures(ITEM_PATH);

    for(std::size_t i = 0; i < sizeof(item_names) / sizeof(item_names[0]); i++) {
        items.push_back(Item(i, this));
    }
}

Inventory::~Inventory() {

}

void Inventory::deltaStack(std::string name, int dStack) {
    int id = nameToId(name);

    items[id].count += dStack;

    std::cout << name << "@id:" << id << " has " << items[id].count << std::endl;
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

int Inventory::nameToId(std::string name) {
    for(std::size_t i = 0; i < sizeof(item_names) / sizeof(item_names[0]); i++) {
        if(item_names[i] == name)
            return i;
    }

    return -1;
}

/* item stuff */
Item::Item(int id, Inventory* inventory) {
    this->id = id;

    sprite.setTexture(inventory->textures[id]);
}

Item::~Item() {

}

/* item box stuff */
ItemBox::ItemBox(int id, Inventory* inventory) {
    top.setFillColor(hl_color);
    bottom.setFillColor(hl_color);
    left.setFillColor(hl_color);
    right.setFillColor(hl_color);

    texture = &inventory->textures[id];
    sprite.setTexture(*texture);
    sprite.scale(ZOOM_FACTOR, ZOOM_FACTOR);
}

ItemBox::~ItemBox() {

}

void ItemBox::drawBox(sf::RenderWindow* window) {
    setPosition(window);

    window->draw(bg);
    window->draw(top);
    window->draw(bottom);
    window->draw(left);
    window->draw(right);
    window->draw(sprite); 
}

void ItemBox::setPosition(sf::RenderWindow* window) {
    bg.setPosition(window->mapPixelToCoords(sf::Vector2i(WINDOW_WIDTH / 2 - ITEMBOX_WIDTH / 2 + x_offset, WINDOW_HEIGHT / 2 - ITEMBOX_WIDTH / 2 - y_offset)));

    top.setPosition(window->mapPixelToCoords(sf::Vector2i(WINDOW_WIDTH / 2 - ITEMBOX_WIDTH / 2 + x_offset, WINDOW_HEIGHT / 2 - ITEMBOX_WIDTH / 2 - y_offset)));
    bottom.setPosition(window->mapPixelToCoords(sf::Vector2i(WINDOW_WIDTH / 2 - ITEMBOX_WIDTH / 2 + x_offset, WINDOW_HEIGHT / 2 + ITEMBOX_WIDTH / 2 - OUTLINE_WIDTH - y_offset)));
    left.setPosition(window->mapPixelToCoords(sf::Vector2i(WINDOW_WIDTH / 2 - ITEMBOX_WIDTH / 2 + x_offset, WINDOW_HEIGHT / 2 - ITEMBOX_WIDTH / 2 - y_offset)));
    right.setPosition(window->mapPixelToCoords(sf::Vector2i(WINDOW_WIDTH / 2 + ITEMBOX_WIDTH / 2 - OUTLINE_WIDTH + x_offset, WINDOW_HEIGHT / 2 - ITEMBOX_WIDTH / 2 - y_offset)));

    sprite.setPosition(window->mapPixelToCoords(sf::Vector2i(WINDOW_WIDTH / 2 - TILE_SIZE * ZOOM_FACTOR / 2 + x_offset, WINDOW_HEIGHT / 2 - y_offset - TILE_SIZE * ZOOM_FACTOR / 2)));
}
