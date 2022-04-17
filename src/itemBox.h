#ifndef ITEMBOX_H
#define ITEMBOX_H

#include <SFML/Graphics.hpp>

#include "conf.h"

#define ITEMBOX_WIDTH 256
#define OUTLINE_WIDTH 5

class ItemBox {
    private:

    public:
        // constructors and deconstructors
        ItemBox(int);
        virtual ~ItemBox();

        // variables
        sf::RectangleShape bg{sf::Vector2f(ITEMBOX_WIDTH, ITEMBOX_WIDTH)};

        sf::RectangleShape top{sf::Vector2f(ITEMBOX_WIDTH, OUTLINE_WIDTH)};
        sf::RectangleShape bottom{sf::Vector2f(ITEMBOX_WIDTH, OUTLINE_WIDTH)};
        sf::RectangleShape left{sf::Vector2f(OUTLINE_WIDTH, ITEMBOX_WIDTH)};
        sf::RectangleShape right{sf::Vector2f(OUTLINE_WIDTH, ITEMBOX_WIDTH)};

        sf::Color bg_color{255, 255, 255, 255};
        sf::Color hl_color{0, 0, 0, 255};

        // functions
        void drawBox(sf::RenderWindow* window);
};

#endif
