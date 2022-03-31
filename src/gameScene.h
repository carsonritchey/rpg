#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "map.h"

class GameScene : public Scene {
    public:
        GameScene(sf::RenderWindow* window);
        virtual ~GameScene();

        Map map;

        void update(const float& dt);
        void render();
        void close_scene();

        std::string texture_path = "art/tiles/overworld.png";
        std::string map_path = "lvledit/overworld.dat";
};

#endif
