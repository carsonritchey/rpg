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

}

sf::Sprite Map::createSprite(int texture_index, int x, int y) {
	sf::Sprite sprite;
	sprite.setTexture(textures[texture_index]);

	sprite.setPosition(x * TILE_SIZE * ZOOM_FACTOR, y * TILE_SIZE * ZOOM_FACTOR);
    sprite.scale(ZOOM_FACTOR, ZOOM_FACTOR);

	return sprite;
}

// drawing maps that fit the screen and won't be moved (i.e. title screen)
void Map::drawMap(sf::RenderWindow* window, int x, int y) {
    buffer = 2;

    int xbound = std::min(map_w, x + buffer + (WINDOW_WIDTH / (TILE_SIZE * ZOOM_FACTOR)));
    int ybound = std::min(map_h, y + buffer + (WINDOW_HEIGHT / (TILE_SIZE * ZOOM_FACTOR)));

    for(int i = std::max(0, x - buffer); i < xbound; i++) {
        for(int j = std::max(0, y - buffer); j < ybound; j++) {
            window->draw(bg_sprites[map_w * i + j]);
            window->draw(fg_sprites[map_w * i + j]);
        }
    }
}

// drwawing maps that won't fit the screen and need to be moved via the view
void Map::drawMap(sf::RenderWindow* window, sf::View* view, float player_x, float player_y) {
    int xmin = std::max(0, (int)(player_x - WINDOW_WIDTH / 2) / TILE_SIZE / ZOOM_FACTOR - buffer);
    int ymin = std::max(0, (int)(player_y - WINDOW_HEIGHT / 2) / TILE_SIZE / ZOOM_FACTOR - buffer);

    int xmax = std::min(map_w, (int)((player_x + WINDOW_WIDTH / 2) / TILE_SIZE / ZOOM_FACTOR) + buffer);
    int ymax = std::min(map_h, (int)((player_y + WINDOW_HEIGHT / 2) / TILE_SIZE / ZOOM_FACTOR) + buffer);

    for(int i = xmin; i < xmax; i++) {
        for(int j = ymin; j < ymax; j++) {
            window->draw(bg_sprites[map_w * i + j]);
            window->draw(fg_sprites[map_w * i + j]);
        }
    }

    float camera_x = player_x + (TILE_SIZE / 2 * ZOOM_FACTOR);
    float camera_y = player_y + (TILE_SIZE / 2 * ZOOM_FACTOR);
    if(player_x <= WINDOW_WIDTH / 2 - (TILE_SIZE / 2 * ZOOM_FACTOR)) camera_x = WINDOW_WIDTH / 2;
    if(player_y <= WINDOW_HEIGHT / 2 - (TILE_SIZE / 2 * ZOOM_FACTOR)) camera_y = WINDOW_HEIGHT / 2;

    view->setCenter(camera_x, camera_y);
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

            textures.push_back(texture);
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
    map_w = std::stoi(s);
    ss >> s; 
    map_h = std::stoi(s);

    for(int j = 0; j < map_h; j++) {
        for(int i = 0; i < map_w; i++) {
			for(int k = 0; k < LAYERS; k++) {
				ss >> s;
				int texture_index = std::stoi(s);

                // collision
                if(k == COLLISION) {
                    tile_collision[map_h * j + i] = texture_index;
                    continue;
                }
				if(texture_index == EMPTY) continue;

				// background
				if(k == BG) {
					bg_sprites[map_w * i + j] = createSprite(texture_index, i, j);
				// foreground
				} else if(k == FG) {
					fg_sprites[map_w * i + j] = createSprite(texture_index, i, j);
				}
			}
        }
    }

    file.close();
}
