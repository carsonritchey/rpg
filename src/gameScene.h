#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "map.h"
#include "player.h"
#include "npc.h"
#include "conf.h"

class GameScene : public Scene {
    private:

    public:
        // constructors and deconstructors
        GameScene(sf::RenderWindow* window, sf::View* view);
        virtual ~GameScene();

		// variables 
		Player player{"art/sprites/among.png"};
        sf::View* view;

        std::string overworld_texture_path = "art/tiles/overworld.png";
        std::string overworld_map_path = "lvledit/overworld_map.dat";
        std::string overworld_tile_data_path = "lvledit/overworld.dat";
        Map overworld_map{overworld_texture_path, overworld_map_path, overworld_tile_data_path};

        std::string subworld_texture_path = "art/tiles/subworld.png";
        std::string subworld_map_path = "lvledit/subworld_map.dat";
        std::string subworld_tile_data_path = "lvledit/subworld.dat";
        Map subworld_map{subworld_texture_path, subworld_map_path, subworld_tile_data_path};

        Map* current_map = &overworld_map; 

		// functions 
        int update(const float& dt, const sf::Event* event);
        void render();
        void close_scene();
};

#endif
