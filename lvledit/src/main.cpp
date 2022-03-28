#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define GAME_VIEW_WIDTH 800
#define GAME_VIEW_HEIGHT 600

#define TILE_SIZE 16
#define ZOOM_FACTOR 3

#define SEPERATOR ,
#define EMPTY -1

void closeMap(int**);
void drawGrid(sf::RenderWindow* window);
int** loadMap(std::string);
void writeMap(int**, std::string);

int map_w = -1;
int map_h = -1;

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "lvledit");
    sf::View view(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), sf::Vector2f(WINDOW_WIDTH / ZOOM_FACTOR, WINDOW_HEIGHT / ZOOM_FACTOR));

	int** map = loadMap(std::string("overworld.dat"));

    sf::Texture texture;
    //texture.loadFromFile("../art/sprites/miku.png");
    texture.loadFromFile("/archive/pictures/random_pics/miku on github.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);

	while(window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}	

        window.setView(view);
		window.clear();
        window.draw(sprite);

        drawGrid(&window);
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
    for(int i = 0; i < WINDOW_WIDTH; i += TILE_SIZE) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(i, 0)),
            sf::Vertex(sf::Vector2f(i, WINDOW_HEIGHT))
        };

        window->draw(line, 2, sf::Lines);
    }
    for(int j = 0; j < WINDOW_HEIGHT; j += TILE_SIZE) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, j)),
            sf::Vertex(sf::Vector2f(WINDOW_WIDTH, j))
        };

        window->draw(line, 2, sf::Lines);
    }
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
