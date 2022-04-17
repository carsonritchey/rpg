#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>

#include "conf.h"

#define ITEM_PATH "art/sprites/items.png"

const std::string item_names[] = {
    "mushroom",
    "potion",
    "mega potion",
    "repel",
    "key",
};

class Item;
class Inventory;

class Item {
    private:

    public:
        // constructor & deconstructor
        Item(int, Inventory*);
        virtual ~Item();

        // variables
        sf::String name;
        int id;
        int count = 0;
        int cost;
        sf::Sprite sprite; 

        // functions
};

class Inventory {
    private:
        void loadTextures(std::string);

    public:
        // constructor & deconstructor
        Inventory();
        virtual ~Inventory();

        // variables
        std::vector<Item> items;
        std::vector<sf::Texture> textures;

        // functions
        void deltaStack(std::string, int); // change in stack count (i.e. -1 to remove 1, 5 to add 5)
        int nameToId(std::string);
};

#define ITEMBOX_WIDTH 110
#define OUTLINE_WIDTH 5
const int x_offset = WINDOW_WIDTH / 2 - TILE_SIZE * ZOOM_FACTOR * 1.5;
const int y_offset = -60;

class ItemBox {
    private:

    public:
        // constructors and deconstructors
        ItemBox(int, Inventory* inventory);
        virtual ~ItemBox();

        // variables
        sf::RectangleShape bg{sf::Vector2f(ITEMBOX_WIDTH, ITEMBOX_WIDTH)};

        sf::RectangleShape top{sf::Vector2f(ITEMBOX_WIDTH, OUTLINE_WIDTH)};
        sf::RectangleShape bottom{sf::Vector2f(ITEMBOX_WIDTH, OUTLINE_WIDTH)};
        sf::RectangleShape left{sf::Vector2f(OUTLINE_WIDTH, ITEMBOX_WIDTH)};
        sf::RectangleShape right{sf::Vector2f(OUTLINE_WIDTH, ITEMBOX_WIDTH)};

        sf::Color bg_color{255, 255, 255, 255};
        sf::Color hl_color{0, 0, 0, 255};

        sf::Texture* texture;
        sf::Sprite sprite;

        // functions
        void drawBox(sf::RenderWindow* window);
        void setPosition(sf::RenderWindow* window);
};

#endif
