#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define WINDOW_WIDTH 1072
#define WINDOW_HEIGHT 720

#define TILE_SIZE 16
#define ZOOM_FACTOR 1

#define LAYERS 3
#define BG 0 
#define FG 1
#define COLLISION 2
#define COLLISION_WALKABLE -1
#define COLLISION_WALL 0

#define EMPTY -1

std::string MAP_PATH = "overworld_map.dat";

void closeMap(int***);
void drawCollision(sf::RenderWindow*);
void drawGrid(sf::RenderWindow*);
void drawHighlight(sf::RenderWindow*);
void drawMapBackground(sf::RenderWindow*);
void drawText(std::vector<sf::Texture>, sf::RenderWindow*);
void generateFile(std::string, int, int);
std::vector<sf::Texture> loadTextures(std::string);
void loadMap(std::string);
void writeMap(int***, std::string);

int map_w = -1;
int map_h = -1;
sf::Vector2f view_mouse_pos;
int*** map;


int currentTileIndex = 0;
int current_layer = 0;
std::vector<sf::Texture> textures;
std::vector<sf::Sprite> bg_tiles;
std::vector<sf::Sprite> fg_tiles;

sf::Font font;

void printMap() {
    for(int j = 0; j < map_h; j++) {
        for(int i = 0; i < map_w; i++) {
            for(int k = 0; k < LAYERS; k++) {
                std::cout << map[i][j][k] << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "lvledit");
    window.setFramerateLimit(30);

    textures = loadTextures("../art/tiles/overworld.png");
	loadMap(MAP_PATH);

    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WINDOW_WIDTH / ZOOM_FACTOR, WINDOW_HEIGHT / ZOOM_FACTOR));


    if(!font.loadFromFile("../art/PressStart2P.ttf")) {
        std::cout << "unable to load font..." << std::endl;
        return -1;
    }


	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();

			// zooming
			if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Z)      // zoom out
					view.zoom(2);
				else if(event.key.code == sf::Keyboard::X) // zoom in
					view.zoom(.5);
				else if(event.key.code == sf::Keyboard::Q) // switch tile left
					currentTileIndex--;
				else if(event.key.code == sf::Keyboard::E) // switch tile right
					currentTileIndex++;
                else if(event.key.code == sf::Keyboard::C) // move up layer
                    current_layer = (current_layer + 1) % LAYERS;

			}
		}

		// scrolling with keyboard
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            view.move(-TILE_SIZE, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            view.move(TILE_SIZE, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            view.move(0, -TILE_SIZE);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            view.move(0, TILE_SIZE);

        view_mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		// placing tiles
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int x = (int)(view_mouse_pos.x / TILE_SIZE) * TILE_SIZE;
			int y = (int)(view_mouse_pos.y / TILE_SIZE) * TILE_SIZE;
			if(x >= 0 && x <= (map_w - 1) * TILE_SIZE &&
			   y >= 0 && y <= (map_h - 1) * TILE_SIZE){
                if(current_layer == COLLISION) {
                    map[x / TILE_SIZE][y / TILE_SIZE][current_layer] = COLLISION_WALL;
                }
                else if(map[x / TILE_SIZE][y / TILE_SIZE][current_layer] == EMPTY) {
                    sf::Sprite sprite;
                    sprite.setTexture(textures[currentTileIndex]);
                    sprite.setPosition(x, y);

                    map[x / TILE_SIZE][y / TILE_SIZE][current_layer] = currentTileIndex;
                    if(current_layer == BG)
                        bg_tiles.push_back(sprite);
                    else if(current_layer == FG)
                        fg_tiles.push_back(sprite);
                }
			}
        // removing tiles
		} else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if(current_layer == BG) {
                for(int i = 0; i < (int)bg_tiles.size(); i++) {
                    sf::Vector2f v = bg_tiles[i].getPosition();

                    if(v.x == (int)(view_mouse_pos.x / TILE_SIZE) * TILE_SIZE &&
                        v.y == (int)(view_mouse_pos.y / TILE_SIZE) * TILE_SIZE) {
                            bg_tiles.erase(bg_tiles.begin() + i);
                            map[(int)v.x / TILE_SIZE][(int)v.y / TILE_SIZE][current_layer] = EMPTY;
                    }
                }
            } else if(current_layer == FG) {
                for(int i = 0; i < (int)fg_tiles.size(); i++) {
                    sf::Vector2f v = fg_tiles[i].getPosition();

                    if(v.x == (int)(view_mouse_pos.x / TILE_SIZE) * TILE_SIZE &&
                        v.y == (int)(view_mouse_pos.y / TILE_SIZE) * TILE_SIZE) {
                            fg_tiles.erase(fg_tiles.begin() + i);
                            map[(int)v.x / TILE_SIZE][(int)v.y / TILE_SIZE][current_layer] = EMPTY;
                    }
                }
            }
            else if(current_layer == COLLISION) {
                map[(int)view_mouse_pos.x / TILE_SIZE][(int)view_mouse_pos.y / TILE_SIZE][COLLISION] = COLLISION_WALKABLE;
            }
        }

        // drawing
		window.clear();
        window.setView(view);

        drawMapBackground(&window);

        for(int i = 0; i < (int)bg_tiles.size(); i++)
            window.draw(bg_tiles[i]);
        for(int i = 0; i < (int)fg_tiles.size(); i++)
            window.draw(fg_tiles[i]);

        if(current_layer == 2)
            drawCollision(&window);
        drawHighlight(&window);
        drawGrid(&window);
        drawText(textures, &window);
		
        window.display();
	}	

    writeMap(map, MAP_PATH);
	closeMap(map);
}

// frees map array 
void closeMap(int*** map) {
	for(int i = 0; i < map_w; i++) {
        for(int j = 0; j < map_h; j++) {
            delete[] map[i][j];
        }
		delete[] map[i];
    }

	delete[] map;

	map_w = -1;
	map_h = -1;
}

void drawCollision(sf::RenderWindow* window) {
    for(int i = 0; i < map_w; i++) {
        for(int j = 0; j < map_h; j++) {
            if(map[i][j][COLLISION] == COLLISION_WALL) {
                sf::RectangleShape rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                rect.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                rect.setFillColor(sf::Color(255, 0, 0, 200));

                window->draw(rect);
            }
        }
    }
}

void drawGrid(sf::RenderWindow* window) {
    sf::Color color(255, 255, 255, 150);

    for(float i = 0; i <= map_w * TILE_SIZE; i += TILE_SIZE) {
        sf::Vertex line[] = {
            {{i, 0}, color},
            {{i, (float)map_h * TILE_SIZE}, color}
        };

        window->draw(line, 2, sf::Lines);
    }
    for(float j = 0; j <= map_h * TILE_SIZE; j += TILE_SIZE) {
        sf::Vertex line[] = {
            {{0, j}, color},
            {{(float)map_w * TILE_SIZE, j}, color}
        };

        window->draw(line, 2, sf::Lines);
    }
}

void drawHighlight(sf::RenderWindow* window) {
    int x = (int)(view_mouse_pos.x / TILE_SIZE) * TILE_SIZE;
    if(x < 0 || x > (map_w - 1) * TILE_SIZE) return;
    int y = (int)(view_mouse_pos.y / TILE_SIZE) * TILE_SIZE;
    if(y < 0 || y > (map_h - 1) * TILE_SIZE) return;
    

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color(50, 50, 255, 200));

    window->draw(rect);
}

void drawMapBackground(sf::RenderWindow* window) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(map_w * TILE_SIZE, map_h * TILE_SIZE));
    rect.setFillColor(sf::Color(20, 20, 20));

    window->draw(rect);
}

void drawText(std::vector<sf::Texture> textures, sf::RenderWindow* window) {
    sf::Text text;
    text.setFont(font);

    std::string s;
    int x = (int)(view_mouse_pos.x / TILE_SIZE) * TILE_SIZE;
    int y = (int)(view_mouse_pos.y / TILE_SIZE) * TILE_SIZE;
    if(x < 0 || x > (map_w - 1) * TILE_SIZE || y < 0 || y > (map_h - 1) * TILE_SIZE)
        s += "tx:\nty:";
    else
        s += "tx:" + std::to_string((int)view_mouse_pos.x / TILE_SIZE) + "\nty:" + std::to_string((int)view_mouse_pos.y / TILE_SIZE);
    
    s += "\n" + std::to_string(current_layer);

    text.setString(s);

    text.setCharacterSize(TILE_SIZE);
    text.setFillColor(sf::Color(255, 255, 0, 200));
	text.setPosition(window->mapPixelToCoords(sf::Vector2i(0, 0)));

	sf::Sprite currentTile;
	currentTile.setPosition(window->mapPixelToCoords(sf::Vector2i(0, 3 * TILE_SIZE)));
	currentTile.setTexture(textures[currentTileIndex]);

	window->draw(currentTile);
    window->draw(text);
}

void generateFile(std::string path, int w, int h) {
    std::cout << "we generating" << std::endl; 
    std::ofstream file(path, std::ofstream::trunc);

    file << w << " " << h << std::endl;

    for (int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            for(int k = 0; k < LAYERS; k++) {
                file << EMPTY << " ";
            }
        }
        file << "\n";
    }

    file.close();
}

// returns an vector of textures from the given spritesheet
std::vector<sf::Texture> loadTextures(std::string file) {
        std::vector<sf::Texture> v;

        sf::Image image;
        image.loadFromFile(file);
        sf::Vector2u size = image.getSize();
        for(int j = 0; j < (int)size.y; j += TILE_SIZE) {
            for(int i = 0; i < (int)size.x; i += TILE_SIZE) {
                sf::Texture texture;
                texture.loadFromFile(file, sf::IntRect(i, j, TILE_SIZE, TILE_SIZE));

                v.push_back(texture);
            }
        }

        return v;
}

// reads data from given file into an int array 
void loadMap(std::string path) {
	std::string line;
	std::ifstream file;
	file.open(path);

	std::string s;
    int line_count = 0;
	while(std::getline(file, line)) {
        line_count++;
        s += line + "\n";
    }
	std::stringstream ss(s);

	ss >> s;
	int w = std::stoi(s);
	ss >> s;
	int h = std::stoi(s);

    if(line_count == 1) {
        std::cout << "size defined but map not defined... filling map" << std::endl;

        file.close(); 
        generateFile(path, w, h);
        loadMap(path);
        return;
    }

	map = new int**[w];
    for(int i = 0; i < w; i++) {
		map[i] = new int*[h];
        for(int j = 0; j < h; j++) {
            map[i][j] = new int[LAYERS];
        }
    }

    for(int j = 0; j < h; j++) {
        for(int i = 0; i < w; i++) {
            for(int k = 0; k < LAYERS; k++) {
                ss >> s;
                int texture_index = std::stoi(s);
                map[i][j][k] = texture_index;

                if(k == COLLISION) {

                    continue;
                }
                if(texture_index == EMPTY)
                    continue;

                sf::Sprite sprite;
                sprite.setTexture(textures[texture_index]);
                sprite.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                if(k == BG)
                     bg_tiles.push_back(sprite);
                else if(k == FG)
                    fg_tiles.push_back(sprite);
            }
        }
    }

	map_w = w;
	map_h = h;

    //std::cout << "map being loaded" << std::endl;
    //printMap();
    file.close();
}

void writeMap(int*** map, std::string path) {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::trunc);

    file << map_w << " " << map_h << std::endl;
    for(int j = 0; j < map_h; j++) {
        for(int i = 0; i < map_w; i++) {
            for(int k = 0; k < LAYERS; k++) {
                file << map[i][j][k] << " ";
            }
        }
        file << std::endl;
    }

    //std::cout << "\nmap being written" << std::endl;  
    //printMap();
    file.close();
}

