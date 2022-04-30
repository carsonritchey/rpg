#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>

#include "conf.h"
#include "entity.h"

class Monster : public Entity {
    public:
        // constructors and deconstructors
        Monster(std::string);
        Monster(std::string, float scale_down_factor);
        virtual ~Monster();

        // variables 
        std::string name = "filler name";
        int level = 1, xp = 0, level_up_threshold = 25; 
        float max_health, 20.f, health = 15.f;

        // functions
};

#endif 
