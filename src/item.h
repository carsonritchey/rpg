#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>

//#include "inventory.h"
#include "conf.h"

const std::string item_names[] = {
    "mushroom",
    "potion",
    "mega potion",
    "repel",
    "key",
};

class Item {
    private:

    public:
        // constructor & deconstructor
        Item(int);
        virtual ~Item();

        // variables
        sf::String name;
        int id;
        int count = 0;
        int cost;
        sf::Texture* texture;
        sf::Sprite* sprite; 

        // functions
        void deltaStack(int); // change in stack count (i.e. -1 to remove 1, 5 to add 5)
};

#endif
