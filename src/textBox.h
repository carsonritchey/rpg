#ifndef TEXTBOX_H
#define TEXTBOX_H

#define TEXT_ZOOM_FACTOR 2
#define SPACING 25
#define OUTLINE_WIDTH 5
#define LINE_SPACING 1.5

#include <string>
#include <regex>

#include <SFML/Graphics.hpp>
#include "entity.h"

class TextBox {
    private:

    public:
        // constructor & deconstructor
        TextBox(std::string);
        virtual ~TextBox();

        // variables
        sf::RenderWindow* window;
        sf::Font font;
        sf::Text text;
        std::string title;
        std::string content;

        int head; // last character to be drawn (i.e. final character before line break or end of string)
        int tail; // start of text to be drawn to screen 

        sf::RectangleShape bg{sf::Vector2f(WINDOW_WIDTH - SPACING * 2, WINDOW_HEIGHT / 3)};

        sf::RectangleShape top{sf::Vector2f(WINDOW_WIDTH - SPACING * 2, OUTLINE_WIDTH)};
        sf::RectangleShape left{sf::Vector2f(OUTLINE_WIDTH, WINDOW_HEIGHT / 3)};
        sf::RectangleShape right{sf::Vector2f(OUTLINE_WIDTH, WINDOW_HEIGHT / 3)};
        sf::RectangleShape bottom{sf::Vector2f(WINDOW_WIDTH - SPACING * 2, OUTLINE_WIDTH)};

        sf::Color bg_color{255, 255, 255, 255};
        sf::Color hl_color{0, 0, 0, 255};
        sf::Color text_color{0, 0, 0, 255};

        Entity space_sprite{"art/sprites/space.png"};

        // functions
        void draw(sf::RenderWindow* window);
        void drawBox(sf::RenderWindow* window);
        void drawText(sf::RenderWindow* window);
        bool progressText();
        void setPosition(sf::RenderWindow* window);
};

#endif
