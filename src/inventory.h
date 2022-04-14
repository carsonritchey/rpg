#ifndef INVENTORY_H
#define INVENTORY_H


#include <string>
#include <vector>
#include <map>

#include "item.h"

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
        std::vector<sf::Sprite*> sprites;

        // functions
};

#endif
