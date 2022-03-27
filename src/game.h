#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <stack>

#include "gameScene.h"

class Game {
    public:
        bool running = true;

        sf::RenderWindow* window;
        sf::VideoMode videoMode;

        sf::Clock dtClock;
        float dt;

        std::stack<Scene*> scenes;

        Game();
        virtual ~Game();

        void update();
        void render();
        void tick_dt();

        // exists game loop
        void close();
};

#endif
