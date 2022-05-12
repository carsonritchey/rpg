#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <stack>

#include "titleScene.h"
#include "gameScene.h"
#include "battleScene.h"

class Game {
    public:
        // constructor & deconstructor
        Game();
        virtual ~Game();

        // variables 
        bool running   = true;
        bool need_view = true;

        sf::RenderWindow* window;
        sf::View* view;

        sf::Clock dtClock;
        float dt;

        std::stack<Scene*> scenes;

        // functions
        void close();
        void update();
        void render();
        void tick_dt();
};

#endif
