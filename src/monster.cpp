#include "monster.h"

void Monster::init(int _id) {
    //health = rand() % (int)max_health;
    id = _id;

    name = names[id];

    // loading base stats
    attack     = stats[id][0];
    defense    = stats[id][1];
    speed      = stats[id][2];
    max_health = stats[id][3];
    health = max_health;

    // loading attack data
    for(int i = 0; i < 4; i++) {
        attack_values[i][0] = attack_values_matrix[id][i][0];
        attack_values[i][1] = attack_values_matrix[id][i][1];
        max_pps[i]          = attack_values_matrix[id][i][1];
    }  

    for(int i = 0; i < 4; i++) {
        if(attack_names[id][i].size() == 0) { move_count = i; break; }
        attacks[i] = attack_names[id][i];
    }

    std::cout << "'" << name << "' loaded with a:" << attack << ", d:" << defense << ", s:" << speed << ", h:" << health << std::endl;
}
Monster::Monster(int _id) : Entity(texture_paths[_id], MONSTER_TILE_SIZE) {
    init(_id);
}
Monster::Monster(int _id, float scale_down_factor) : Entity(texture_paths[_id], MONSTER_TILE_SIZE) {
    init(_id);

    sprite.scale(scale_down_factor, scale_down_factor);
}

Monster::~Monster() {

}

void Monster::giveXP(int amount) {
    if(xp + amount < level_up_threshold) {
        xp += amount;
    }
    else {
        xp = (xp + amount) % level_up_threshold;

        level += 1;

        max_health *= level_up_multiplier;
        health *= level_up_multiplier;
        attack *= level_up_multiplier;
        defense *= level_up_multiplier;
        speed *= level_up_multiplier;
        level_up_threshold *= level_up_multiplier;

        for(int i = 0; i < 4; i++) {
            if(attacks[i].size() == 0) break;

            attack_values[i][1] = max_pps[i];
        }
    }
}
