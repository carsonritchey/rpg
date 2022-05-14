#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <stack>
#include <string>

#include "titleScene.h"
#include "gameScene.h"
#include "battleScene.h"

#include <iostream>

class Game {
    public:
        // constructor & deconstructor
        Game();
        virtual ~Game();

        // variables 
        bool running   = true;

        sf::RenderWindow* window;
        sf::View* view;

        sf::Clock dtClock;
        float dt;

        std::stack<Scene*> scenes;
        TitleScene* titlescene = nullptr;
        GameScene* gamescene = nullptr;
        BattleScene* battlescene = nullptr;

        // functions
        void close();
        void update();
        void render();
        void tick_dt();
};

#endif
