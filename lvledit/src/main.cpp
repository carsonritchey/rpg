#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define WINDOW_WIDTH 1072
#define WINDOW_HEIGHT 720

#define GAME_VIEW_WIDTH 800
#define GAME_VIEW_HEIGHT 600

#define TILE_SIZE 16
#define ZOOM_FACTOR 1

#define SEPERATOR ,
#define EMPTY -1

void closeMap(int**);
void drawGrid(sf::RenderWindow*);
void highlight(sf::RenderWindow*);
int** loadMap(std::string);
void writeMap(int**, std::string);

int map_w = -1;
int map_h = -1;
sf::Vector2i mouse_pos;

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "lvledit");
    window.setFramerateLimit(30);
    sf::View view(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), sf::Vector2f(WINDOW_WIDTH / ZOOM_FACTOR, WINDOW_HEIGHT / ZOOM_FACTOR));

	int** map = loadMap(std::string("overworld.dat"));

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            view.move(-TILE_SIZE, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view.move(TILE_SIZE, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.move(0, -TILE_SIZE);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.move(0, TILE_SIZE);

        mouse_pos = sf::Mouse::getPosition(window);

        window.setView(view);
		window.clear();

        highlight(&window);
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
    sf::Color color(255, 255, 255, 150);

    for(float i = 0; i < WINDOW_WIDTH; i += TILE_SIZE) {
        sf::Vertex line[] = {
            {{i, 0}, color},
            {{i, WINDOW_HEIGHT}, color}
        };

        window->draw(line, 2, sf::Lines);
    }
    for(float j = 0; j < WINDOW_HEIGHT; j += TILE_SIZE) {
        sf::Vertex line[] = {
            {{0, j}, color},
            {{WINDOW_WIDTH, j}, color}
        };

        window->draw(line, 2, sf::Lines);
    }
}

void highlight(sf::RenderWindow* window) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    rect.setPosition((int)(mouse_pos.x / TILE_SIZE) * TILE_SIZE, (int)(mouse_pos.y / TILE_SIZE) * TILE_SIZE);
    rect.setFillColor(sf::Color(50, 50, 255, 200));

    window->draw(rect);
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
