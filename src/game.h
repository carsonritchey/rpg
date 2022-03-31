#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <stack>

#include "gameScene.h"

class Game {
    public:
        // constructor & deconstructor
        Game();
        virtual ~Game();

        // variables 
        bool running = true;

        sf::Clock dtClock;
        float dt;

        std::stack<Scene*> scenes;

        // functions
        void close();

        sf::RenderWindow* window;
        sf::View* view;

        void update();
        void render();
        void tick_dt();
};

#endif
