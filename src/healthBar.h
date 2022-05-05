#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "conf.h"
#include "monster.h"

#include <iostream>

class HealthBar {
    private:
        void drawBackground();
        void drawText();

    public:
        // constructors and deconstructors 
        HealthBar();
        HealthBar(sf::RenderWindow* window, int x, int y, int w, int h, float max_health, float current_health);
        virtual ~HealthBar();

        // variables
        sf::RenderWindow* window;

        int x, y, w, h;
        float max_health;
        float current_health;

        const sf::Color bg_color{0xff, 0xff, 0xff, 0xff};
        const sf::Color outline_color{0x32, 0x32, 0x32};
        const sf::Color health_good_color{0x1b, 0xd1, 0x4c, 0xff};
        const sf::Color health_bad_color{0xbf, 0x00, 0x29, 0xff};

        const float bad_threshold = .2; 

        const int box_outline_width = 2;
        sf::RectangleShape top;
        sf::RectangleShape bottom;
        sf::RectangleShape left;
        sf::RectangleShape right;

        sf::RectangleShape bg;

        // functions
        void draw();

};

#endif
