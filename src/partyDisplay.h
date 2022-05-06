#ifndef PARTYDISPLAY_H
#define PARTYDISPLAY_H

#include "conf.h"
#include "monster.h"

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

        const sf::Color bg_color{0xff, 0xff, 0xff, 0xff};
        const sf::Color outline_color{0x32, 0x32, 0x32};

        const int padding = TILE_SIZE * ZOOM_FACTOR * 2;
        const int outline_width = 4;
        sf::RectangleShape top;
        sf::RectangleShape bottom;
        sf::RectangleShape left;
        sf::RectangleShape right;

        sf::RectangleShape bg;

        const int font_size = MONSTER_TILE_SIZE;
        sf::Font font;
        sf::Text name_texts[MAX_PARTY_SIZE];
        sf::Sprite icons[MAX_PARTY_SIZE];

        // functions
        void draw();

};

#endif
