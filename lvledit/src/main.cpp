#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define GAME_VIEW_WIDTH 800
#define GAME_VIEW_HEIGHT 600

void closeMap(int**);
int** loadMap(std::string);

int map_w = -1;
int map_h = -1;

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "lvledit");

	int** map = loadMap(std::string("overworld.dat"));

	for(int i = 0; i < map_w; i++) {
		for(int j = 0; j < map_h; j++) {
			std::cout << map[i][j] << " ";
		}

		std::cout << "\n";
	}

	closeMap(map);

	while(window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}	

		window.clear();
		window.display();
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
	int n = 0;
	for(int i = 0; i < h; i++) {
		map[i] = new int[w];
		for(int j = 0; j < w; j++) {
			map[i][j] = n++;
		}
	}

	map_w = w;
	map_h = h;
	return map;
}

// frees map array 
void closeMap(int** map) {
	int l = sizeof(map) / sizeof(map[0]);

	for(int i = 0; i < l; i++)
		delete[] map[i];

	delete[] map;

	map_w = -1;
	map_h = -1;
}
