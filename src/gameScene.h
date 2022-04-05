#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "map.h"

class GameScene : public Scene {
    private:

    public:
		// functions 
        GameScene(sf::RenderWindow* window);
        virtual ~GameScene();

        int update(const float& dt, const sf::Event* event);
        void render();
        void close_scene();

		// variables 
        Map map;

        std::string texture_path = "art/tiles/overworld.png";
        std::string map_path = "lvledit/overworld_map.dat";
};

#endif
