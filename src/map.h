#ifndef MAP_H
#define MAP_H

#include "conf.h"
#include "npc.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <regex>

class NPC;

class Map {
    private:
		sf::Sprite createSprite(int, int, int);
        void killEntities();
        void loadTextures(std::string);
        void loadTileData(std::string);
        void loadMap(std::string);

    public:
        // constructor & deconstructor
        Map(std::string texture_path, std::string map_path);
        Map(std::string texture_path, std::string map_path, std::string tile_data_path);
        virtual ~Map();

        // variables
        int map_w, map_h;
        int buffer = 8; // number of tiles that are rendered offscreen in each direction
        std::vector<sf::Texture> textures;
		std::map<int, sf::Sprite> bg_sprites;
		std::map<int, sf::Sprite> fg_sprites;
        std::map<int, sf::Rect<float>*> tile_collision; 
        std::map<int, std::string> tile_data;

        std::vector<NPC*> npcs; 

        // functions
        void drawCollision(sf::RenderWindow*);
        void drawEntities(sf::RenderWindow*, sf::View*, float, float);
        void drawMap(sf::RenderWindow*, int, int);
        void drawMap(sf::RenderWindow*, sf::View*, float, float);
        void setTexture(int, int, int, int);
};

#endif
