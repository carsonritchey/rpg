#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>

#include "conf.h"
#include "entity.h"

class Monster : public Entity {
    public:
        // constructors and deconstructors
        Monster(std::string);
        virtual ~Monster();

        // variables 
        std::string name;
        int level = 1, xp = 0, level_up_threshold = 25; 
        float health;

        // functions
};

#endif 
