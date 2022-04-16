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


#endif
