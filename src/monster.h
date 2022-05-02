#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <random>

#include "conf.h"
#include "entity.h"

const std::string monster_texture_paths[] = {
    "art/sprites/battle/nineplusten.png",
    "art/sprites/battle/sponge.png",
    "art/sprites/battle/steve.png",
    "art/sprites/battle/jared.png",
    "art/sprites/battle/jfk.png",
    "art/sprites/battle/corolla.png",
    "art/sprites/battle/wordle.png",
};

const std::string monster_names[] {
    "9+10 kid",
    "spoinkbub",
    "Steve",
    "Jared Fogle",
    "John F. Kennedy",
    "2008 Toyota Corolla",
    "WORDLE",
};

class Monster : public Entity {
    protected:
        void init(int);

    public:
        // constructors and deconstructors
        Monster(int _id);
        Monster(int _id, float scale_down_factor);
        virtual ~Monster();

        // variables 
        bool default_name = true;
        std::string name = "filler name";
        int level = 1, xp = 0, level_up_threshold = 25; 
        float max_health = 20.f, health = max_health;

        int id;

        // functions
};

#endif 
