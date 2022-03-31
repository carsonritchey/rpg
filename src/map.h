#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
    private:
        void loadTextures(std::string);
        void loadMap(std::string);

    public:
        // constructor & deconstructor
        Map();
        virtual ~Map();

        // variables

        /*
           0 - walkable
           1 - wall
           2 - door
           3 - item/chest
        */
        int map_w, map_h;
        int** tile_collision;
        std::vector<sf::Texture> textures;
        std::vector<sf::Sprite>  bg_tiles;

        // functions
        void init(std::string, std::string);
};

#endif
