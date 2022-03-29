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

#define SEPERATOR ,
#define EMPTY -1

void closeMap(int**);
void drawGrid(sf::RenderWindow*);
void drawHighlight(sf::RenderWindow*);
void drawMapBackground(sf::RenderWindow*);
void drawText(std::vector<sf::Texture>, sf::RenderWindow*);
std::vector<sf::Texture> loadTextures(std::string);
int** loadMap(std::string);
void writeMap(int**, std::string);

int map_w = -1;
int map_h = -1;
sf::Vector2f view_mouse_pos;

int currentTileIndex = 0;

sf::Font font;

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "lvledit");
    window.setFramerateLimit(30);

	int** map = loadMap(std::string("overworld.dat"));
    sf::View view(sf::Vector2f(map_w * TILE_SIZE / 2, map_h * TILE_SIZE / 2), sf::Vector2f(WINDOW_WIDTH / ZOOM_FACTOR, WINDOW_HEIGHT / ZOOM_FACTOR));

    std::vector<sf::Texture> textures = loadTextures("../art/tiles/overworld.png");
    std::vector<sf::Sprite> sprites;

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
				if(event.key.code == sf::Keyboard::Z)
					view.zoom(2);
				else if(event.key.code == sf::Keyboard::X)
					view.zoom(.5);
				else if(event.key.code == sf::Keyboard::Q)
					currentTileIndex--;
				else if(event.key.code == sf::Keyboard::E)
					currentTileIndex++;

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

		// placing and removing tiles
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int x = (int)(view_mouse_pos.x / TILE_SIZE) * TILE_SIZE;
			int y = (int)(view_mouse_pos.y / TILE_SIZE) * TILE_SIZE;
			if(x >= 0 && x <= (map_w - 1) * TILE_SIZE &&
			   y >= 0 && y <= (map_h - 1) * TILE_SIZE){
                if(map[x / TILE_SIZE][y / TILE_SIZE] == EMPTY) {
                    sf::Sprite sprite;
                    sprite.setTexture(textures[currentTileIndex]);
                    sprite.setPosition(x, y);

                    map[x / TILE_SIZE][y / TILE_SIZE] = currentTileIndex;
                    sprites.push_back(sprite);
                }
			}
		} else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			for(int i = 0; i < sprites.size(); i++) {
				sf::Vector2f v = sprites[i].getPosition();

				if(v.x == (int)(view_mouse_pos.x / TILE_SIZE) * TILE_SIZE &&
					v.y == (int)(view_mouse_pos.y / TILE_SIZE) * TILE_SIZE) {
						sprites.erase(sprites.begin() + i);
                        map[(int)v.x / TILE_SIZE][(int)v.y / TILE_SIZE] = EMPTY;
				}
			}
		}

        // drawing
		window.clear();
        window.setView(view);

        drawMapBackground(&window);

        for(int i = 0; i < sprites.size(); i++)
            window.draw(sprites[i]);

        drawHighlight(&window);
        drawGrid(&window);
        drawText(textures, &window);
		
        std::cout << sprites.size() << std::endl;

        window.display();
	}	

	closeMap(map);
}

// frees map array 
void closeMap(int** map) {
	for(int i = 0; i < map_h; i++)
		delete[] map[i];

	delete[] map;

	map_w = -1;
	map_h = -1;
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

    text.setString(s);

    text.setCharacterSize(TILE_SIZE);
    text.setFillColor(sf::Color(255, 255, 0, 200));
	text.setPosition(window->mapPixelToCoords(sf::Vector2i(0, 0)));

	sf::Sprite currentTile;
	currentTile.setPosition(window->mapPixelToCoords(sf::Vector2i(0, 2 * TILE_SIZE)));
	currentTile.setTexture(textures[currentTileIndex]);

	window->draw(currentTile);
    window->draw(text);
}

// returns an vector of textures from the given spritesheet
std::vector<sf::Texture> loadTextures(std::string file) {
        std::vector<sf::Texture> v;
        for(int i = 0; i < 4; i++) {
            sf::Texture texture;
            texture.loadFromFile(file, sf::IntRect(i * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));

            v.push_back(texture);
        }

        return v;
}

// reads data from given file into an int array 
int** loadMap(std::string path) {
	std::string line;
	std::ifstream file;
	file.open(path);

	std::getline(file, line);
	std::stringstream ss(line);
	std::string s;

	ss >> s;
	int w = std::stoi(s);
	ss >> s;
	int h = std::stoi(s);

	int** map = new int*[h];
	for(int i = 0; i < h; i++) {
		map[i] = new int[w];
		for(int j = 0; j < w; j++) {
			map[i][j] = EMPTY;
		}
	}

	map_w = w;
	map_h = h;
	return map;
}
