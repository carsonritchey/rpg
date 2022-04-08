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

// drawing maps that fit the screen and won't be moved (i.e. title screen)
void Map::drawMap(sf::RenderWindow* window, int x, int y) {
    this->buffer = 2;

    int xbound = std::min(map_w, x + this->buffer + (WINDOW_WIDTH / (TILE_SIZE * ZOOM_FACTOR)));
    int ybound = std::min(map_h, y + this->buffer + (WINDOW_HEIGHT / (TILE_SIZE * ZOOM_FACTOR)));

    for(int i = std::max(0, x - this->buffer); i < xbound; i++) {
        for(int j = std::max(0, y - this->buffer); j < ybound; j++) {
            window->draw(this->bg_sprites[map_w * i + j]);
            window->draw(this->fg_sprites[map_w * i + j]);
        }
    }
}

// drwawing maps that won't fit the screen and need to be moved via the view
void Map::drawMap(sf::RenderWindow* window, sf::View* view, float player_x, float player_y) {
    int xmin = std::max(0, (int)(player_x - WINDOW_WIDTH / 2) / TILE_SIZE / ZOOM_FACTOR - this->buffer);
    int ymin = std::max(0, (int)(player_y - WINDOW_HEIGHT / 2) / TILE_SIZE / ZOOM_FACTOR - this->buffer);

    int xmax = std::min(map_w, (int)((player_x + WINDOW_WIDTH / 2) / TILE_SIZE / ZOOM_FACTOR) + this->buffer);
    int ymax = std::min(map_h, (int)((player_y + WINDOW_HEIGHT / 2) / TILE_SIZE / ZOOM_FACTOR) + this->buffer);

    for(int i = xmin; i < xmax; i++) {
        for(int j = ymin; j < ymax; j++) {
            window->draw(this->bg_sprites[map_w * i + j]);
            window->draw(this->fg_sprites[map_w * i + j]);
        }
    }

    view->setCenter(player_x + (TILE_SIZE / 2 * ZOOM_FACTOR), player_y + (TILE_SIZE / 2 * ZOOM_FACTOR));
}

void Map::init(std::string map_path, std::string texture_path) {
    Map::loadTextures(texture_path);
    Map::loadMap(map_path);
}

void Map::loadTextures(std::string path) {
    sf::Image image;
    image.loadFromFile(path);
    sf::Vector2u size = image.getSize();

    for(int j = 0; j < (int)size.y; j+= TILE_SIZE) {
        for(int i = 0; i < (int)size.x; i+= TILE_SIZE) {
            sf::Texture texture;
            texture.loadFromFile(path, sf::IntRect(i, j, TILE_SIZE, TILE_SIZE));

            this->textures.push_back(texture);
        }
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

    for(int j = 0; j < map_h; j++) {
        for(int i = 0; i < map_w; i++) {
			for(int k = 0; k < LAYERS; k++) {
				ss >> s;
				int texture_index = std::stoi(s);

				if(texture_index == EMPTY) continue;

				// background
				if(k == 0) {
					this->bg_sprites[map_w * i + j] = createSprite(texture_index, i, j);
				// foreground
				} else if(k == 1) {
					this->fg_sprites[map_w * i + j] = createSprite(texture_index, i, j);
				}
			}
        }
    }

    file.close();
}
