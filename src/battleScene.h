#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "conf.h"
#include "scene.h"
#include "monster.h"
#include "textBox.h"
#include "healthBar.h"

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

        /*
         * attack party 
         * item   run 
         */
        sf::Font font;

        sf::Text attack_text;
        sf::Text item_text;
        sf::Text party_text;
        sf::Text run_text;

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
        battle_options option = battle_options::attack; 

        int current_player = 0, current_enemy = 0;
        std::vector<Monster> player_party;
        std::vector<Monster> enemy_party;

        TextBox* textbox;

        HealthBar* player_health;
        HealthBar* enemy_health;
};

#endif
