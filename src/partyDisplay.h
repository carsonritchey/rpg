#ifndef PARTYDISPLAY_H
#define PARTYDISPLAY_H

#include "conf.h"
#include "monster.h"
#include "healthBar.h"

#include <iostream>

class PartyDisplay {
    private:
        void drawBackground();
        void drawText();

    public:
        // constructors and deconstructors 
        PartyDisplay(sf::RenderWindow* window, std::vector<Monster*> party);
        virtual ~PartyDisplay();

        // variables
        sf::RenderWindow* window;

        std::vector<Monster*> party;
        std::vector<HealthBar*> health_bars;

        int current_member = 0;

        const sf::Color bg_color{0xff, 0xff, 0xff, 0xff};
        const sf::Color outline_color{0x32, 0x32, 0x32};
        const sf::Color text_color{0x0, 0x0, 0x0, 0xff};
        const sf::Color select_color{0x40, 0x90, 0xff, 0xff};

        const int padding = TILE_SIZE * ZOOM_FACTOR * 2;
        const int outline_width = 4;
        const int bar_width = 300;
        sf::RectangleShape top;
        sf::RectangleShape bottom;
        sf::RectangleShape left;
        sf::RectangleShape right;

        sf::RectangleShape bg;

        const int font_size = MONSTER_TILE_SIZE;
        sf::Font font;
        sf::Text name_texts[MAX_PARTY_SIZE];
        sf::Text level_texts[MAX_PARTY_SIZE];
        sf::Sprite icons[MAX_PARTY_SIZE];

        // functions
        void draw();
        void processEvent(const sf::Event* event);
};

#endif
