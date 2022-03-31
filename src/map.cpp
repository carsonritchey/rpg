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
    this->map_h = std::stoi(s);

    for(int i = 0; i < map_h; i++) {
        for(int j = 0; j < map_w; j++) {
            
        }
    }

    file.close();
}
