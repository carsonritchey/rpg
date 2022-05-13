#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "conf.h"
#include "scene.h"
#include "monster.h"
#include "healthBar.h"
#include "textBox.h"
#include "partyDisplay.h"

#include <iostream>
#include <random>

enum options {
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

        void initAttackText();
        void initOptionsText();
        void initNameText();

        void turn();

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
        sf::Color fainted_color{0x30, 0x30, 0x30, 0xff};

    public:
        // constructors and deconstructors 
        BattleScene(sf::RenderWindow* window, sf::View* old_view, std::vector<Monster*>* _player_party);
        virtual ~BattleScene();

        // variables
        sf::RenderWindow* window;

        sf::View* old_view;
        sf::Vector2f old_view_center;

        options option = options::none; 

        TextBox* textbox = nullptr;
        PartyDisplay* party_display = nullptr;

        int current_player = 0, current_enemy = 0;
        std::vector<Monster*>* player_party;
        std::vector<Monster*> enemy_party;

        HealthBar* player_healthbar;
        HealthBar* enemy_healthbar;

        int turn_start = -1;
        bool turn_playing = false, player_dead;

        // functions
        int update(const float& dt, const sf::Event* event);
        void render();

        void box(int, int, int, int);
        bool canRun();
        void close_scene();
        int headCount(std::vector<Monster*>*);
        void processEvent(const sf::Event* event);
        void updateCurrentMember();
};

#endif
