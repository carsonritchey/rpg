#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "conf.h"
#include "scene.h"

#include <iostream>

enum battle_options {
    attack = 0,
    item = 1,
    party = 2,
    run = 3,
};

class BattleScene : public Scene {
    private:
        void drawBackground();
        void drawText();

        sf::Font font;
        sf::Text attack_text;
        sf::Text item_text;
        sf::Text party_text;
        sf::Text run_text;

        sf::Color selected_color{0x40, 0x90, 0xff, 0xff};
        sf::Color base_color{0x0, 0x0, 0x0, 0xff};

    public:
        // constructors and deconstructors 
        BattleScene(sf::RenderWindow* window);
        virtual ~BattleScene();

        // functions
        int update(const float& dt, const sf::Event* event);
        void render();
        void close_scene();

        // variables
        sf::RenderWindow* window;
        battle_options option = battle_options::attack; 
};

#endif
