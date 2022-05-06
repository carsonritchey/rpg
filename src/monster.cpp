#include "monster.h"

void Monster::init(int _id) {
    //health = rand() % (int)max_health;
    id = _id;

    name = names[id];

    // loading base stats
    attack  = stats[id][0];
    defense = stats[id][1];
    speed   = stats[id][2];

    // loading attack data
    for(int i = 0; i < 4; i++) {
        attack_values[i][0] = attack_values_matrix[id][i][0];
        attack_values[i][1] = attack_values_matrix[id][i][1];
    }  

    for(int i = 0; i < 4; i++) {
        if(attack_names[id][i].size() == 0) { move_count = i; break; }
        attacks[i] = attack_names[id][i];
    }

    //std::cout << "'" << name << "' loaded with a:" << attack << ", d:" << defense << ", s:" << speed << std::endl;
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
