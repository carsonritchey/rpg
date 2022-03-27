#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"

class GameScene : public Scene {
    public:
        GameScene(sf::RenderWindow* window);
        virtual ~GameScene();

    void update(const float& dt);
    void render();
    void close_scene();
};

#endif
