#include "map.h"

Map::Map(std::string texture_path, std::string map_path) {
    loadTextures(texture_path);
    loadMap(map_path);
}
Map::Map(std::string texture_path, std::string map_path, std::string tile_data_path) {
    loadTextures(texture_path);
    loadMap(map_path);
    loadTileData(tile_data_path);
}

Map::~Map() {
    killEntities();

    for(int i = 0; i < map_w; i++) {
        for(int j = 0; j < map_h; j++) {
            if(tile_collision[map_w * j + i] != nullptr)
                delete tile_collision[map_w * j + i];
        }
    }
}

sf::Sprite Map::createSprite(int texture_index, int x, int y) {
	sf::Sprite sprite;
	sprite.setTexture(textures[texture_index]);

	sprite.setPosition(x * TILE_SIZE * ZOOM_FACTOR, y * TILE_SIZE * ZOOM_FACTOR);
    sprite.scale(ZOOM_FACTOR, ZOOM_FACTOR);

	return sprite;
}

/*
void Map::drawCollision(sf::RenderWindow* window) {
    for(int i = 0; i < map_w; i++) {
        for(int j = 0; j < map_h; j++) {
            if(tile_collision[map_h * j + i] != COLLISION_WALL) continue;
            sf::RectangleShape rect(sf::Vector2f(TILE_SIZE * ZOOM_FACTOR, TILE_SIZE * ZOOM_FACTOR));
            rect.setPosition(i * TILE_SIZE * ZOOM_FACTOR, j * TILE_SIZE * ZOOM_FACTOR);
            rect.setFillColor(sf::Color(255, 0, 0, 200));

            window->draw(rect);
        }
    }
}
*/

void Map::drawEntities(sf::RenderWindow* window, sf::View* view, float player_x, float player_y) {
    for(std::size_t i = 0; i < npcs.size(); i++) {
        window->draw(npcs[i]->sprite);
    }
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

void Map::killEntities() {
    for(std::size_t i = 0; i < npcs.size(); i++)
        delete npcs[i];
}

void Map::loadTextures(std::string path) {
    sf::Image image;
    if(!image.loadFromFile(path))
        std::cout << "map-loadTextures: unable to load image " << path << std::endl;
    sf::Vector2u size = image.getSize();

    for(int j = 0; j < (int)size.y; j+= TILE_SIZE) {
        for(int i = 0; i < (int)size.x; i+= TILE_SIZE) {
            sf::Texture texture;
            if(!texture.loadFromFile(path, sf::IntRect(i, j, TILE_SIZE, TILE_SIZE)))
                std::cout << "map-loadTextures: unable to load texture " << path << std::endl;

            textures.push_back(texture);
        }
    }
}

void Map::loadTileData(std::string path) {
    std::string line;
    std::ifstream file;
    file.open(path);

    while(std::getline(file, line)) {
        int x, y;

        std::string pos = line.substr(0, line.find(TILEDAT_SEPERATOR));
        std::string text = line.substr(line.find(TILEDAT_SEPERATOR) + 1);
        text = std::regex_replace(text, std::regex("NEWLINE"), "\n");

        x = std::stoi(pos.substr(0, pos.find(TILEDAT_POS_SEPERATOR)));
        y = std::stoi(pos.substr(pos.find(TILEDAT_POS_SEPERATOR) + 1));

        if(text.substr(0, strlen(TILEDAT_NPC_PREFIX)) == TILEDAT_NPC_PREFIX) {
            //std::cout << text.substr(text.find(TILEDAT_SEPERATOR) + 1, text.substr(text.find(TILEDAT_SEPERATOR) + 1).find(TILEDAT_SEPERATOR)) << std::endl;

            NPC* npc = new NPC(std::stoi(text.substr(text.find(TILEDAT_SEPERATOR) + 1, text.substr(text.find(TILEDAT_SEPERATOR) + 1).find(TILEDAT_SEPERATOR))), x, y);
            npcs.push_back(npc);

            continue;
        }

        tile_data[y * map_w + x] = text;
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
                    if(texture_index == COLLISION_WALKABLE)
                        continue;

                    const float leeway = TILE_SIZE * ZOOM_FACTOR / 10;
                    sf::RectangleShape r(sf::Vector2f(TILE_SIZE * ZOOM_FACTOR - leeway, TILE_SIZE * ZOOM_FACTOR - leeway));
                    r.setPosition(sf::Vector2f(i * TILE_SIZE * ZOOM_FACTOR, j * TILE_SIZE * ZOOM_FACTOR));

                    sf::Rect<float>* r_ = new sf::Rect<float>;
                    *r_ = r.getGlobalBounds();
                    tile_collision[map_w * j + i] = r_;

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

void Map::setTexture(int tile_x, int tile_y, int layer, int texture_index) {
    if(layer == BG)
        bg_sprites[map_w * tile_x + tile_y].setTexture(textures[texture_index]);
    else if(layer == FG)
        fg_sprites[map_w * tile_x + tile_y].setTexture(textures[texture_index]);
}
