#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "conf.h"
#include "scene.h"
#include "monster.h"
#include "healthBar.h"

#include <iostream>
#include <random>

enum battle_options {
    none = -1,
    attack = 0,
    item = 1,
    party = 2,
    run = 3,
};

class BattleScene : public Scene {
    private:
        void drawBackground();
        void drawText();

        /*
         * attack party 
         * item   run 
         */
        sf::Font font;

        sf::Text texts[4];
        int current_text = 0;

        sf::Text playername_text;
        sf::Text enemyname_text;

        const int player_scale_down = 2;

        sf::Color selected_color{0x40, 0x90, 0xff, 0xff};
        sf::Color base_color{0x0, 0x0, 0x0, 0xff};

    public:
        // constructors and deconstructors 
        BattleScene(sf::RenderWindow* window);
        virtual ~BattleScene();

        // functions
        int update(const float& dt, const sf::Event* event);
        void render();

        void box(int, int, int, int);
        bool canRun();
        void close_scene();
        void processEvent(const sf::Event* event);

        // variables
        sf::RenderWindow* window;
        const sf::View* old_view;
        battle_options option = battle_options::none; 

        int current_player = 0, current_enemy = 0;
        std::vector<Monster> player_party;
        std::vector<Monster> enemy_party;

        HealthBar* player_health;
        HealthBar* enemy_health;
};

#endif
