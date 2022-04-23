#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "scene.h"

class BattleScene : public Scene {
    public:
        // constructors and deconstructors 
        BattleScene(sf::RenderWindow* window);
        virtual ~BattleScene();

        // functions
        int update(const float& dt, const sf::Event* event);
        void render();

        // variables
}
