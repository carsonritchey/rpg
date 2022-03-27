#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game {
    public:
        bool running = true;

        sf::RenderWindow* window;
        sf::VideoMode videoMode;

        Game();
        virtual ~Game();

        void update();
        void render();

        // exists game loop
        void close();
};

#endif
