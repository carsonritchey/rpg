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

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "lvledit");

	loadMap(std::string("overworld.dat"));

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

	int** array = new int*[h];
	for(int i = 0; i < h; i++)
		array[i] = new int[w];

	return array;
}

void closeMap(int** map) {
	int l = sizeof(map) / sizeof(map[0]);

	for(int i = 0; i < l; i++)
		delete[] map[i];

	delete[] map;
}
