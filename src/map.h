#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class Map {
    private:
		sf::Sprite createSprite(int, int, int);
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
        int buffer = 8; // number of tiles that are rendered offscreen, just incase
        std::vector<sf::Texture> textures;
		std::map<int, sf::Sprite> bg_sprites;
		std::map<int, sf::Sprite> fg_sprites;
        std::map<int, int> tile_collision; 

        // functions
        void drawCollision(sf::RenderWindow* window);
        void drawMap(sf::RenderWindow*, int, int);
        void drawMap(sf::RenderWindow*, sf::View*, float, float);
        void init(std::string, std::string);
};

#endif
