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
        PartyDisplay(sf::RenderWindow* window);
        virtual ~PartyDisplay();

        // variables
        sf::RenderWindow* window;

        const sf::Color bg_color{0xff, 0xff, 0xff, 0xff};
        const sf::Color outline_color{0x32, 0x32, 0x32};

        const int padding = TILE_SIZE * ZOOM_FACTOR;
        const int outline_width = 4;
        sf::RectangleShape top;
        sf::RectangleShape bottom;
        sf::RectangleShape left;
        sf::RectangleShape right;

        sf::RectangleShape bg;

        // functions
        void draw();

};

#endif
