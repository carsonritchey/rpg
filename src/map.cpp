#include "conf.h"
#include "map.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

Map::Map() {

}

Map::~Map() {
    // free tile collision
}

sf::Sprite Map::createSprite(int texture_index, int x, int y) {
	sf::Sprite sprite;
	sprite.setTexture(this->textures[texture_index]);

	sprite.setPosition(x * TILE_SIZE * ZOOM_FACTOR, y * TILE_SIZE * ZOOM_FACTOR);
    sprite.scale(ZOOM_FACTOR, ZOOM_FACTOR);

	return sprite;
}

void Map::init(std::string map_path, std::string texture_path) {
    Map::loadTextures(texture_path);
    Map::loadMap(map_path);
}

void Map::loadTextures(std::string path) {
    int TEMP_TEXTURE_LOADING_LENGTH = 16;
    for(int i = 0; i < TEMP_TEXTURE_LOADING_LENGTH; i++) {
        sf::Texture texture;
        texture.loadFromFile(path, sf::IntRect(i * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));

        this->textures.push_back(texture);
    }
}

void Map::loadMap(std::string path) {
    std::string line;
    std::ifstream file;
    file.open(path);

    std::string s;
    while(std::getline(file, line)) s += line + "\n";
    std::stringstream ss(s);

    ss >> s; 
    this->map_w = std::stoi(s);
    ss >> s; 
    this->map_h = std::stoi(s);

    for(int i = 0; i < map_h; i++) {
        for(int j = 0; j < map_w; j++) {
			for(int k = 0; k < LAYERS; k++) {
				ss >> s;
				int texture_index = std::stoi(s);

				if(texture_index == EMPTY) continue;

				// background
				if(k == 0) {
					this->bg_sprites[map_w * i + j] = createSprite(texture_index, i, j);
				// foreground
				} else {
					this->fg_sprites[map_w * i + j] = createSprite(texture_index, i, j);
				}
			}
        }
    }

    file.close();
}
