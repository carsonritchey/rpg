#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define GAME_VIEW_WIDTH 800
#define GAME_VIEW_HEIGHT 600

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "lvledit");

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
