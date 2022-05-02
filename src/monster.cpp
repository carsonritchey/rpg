#include "monster.h"

void Monster::init(int _id) {
    health = rand() % (int)max_health;
    id = _id;

    name = names[id];

    for(int i = 0; i < 4; i++) {
        if(attack_names[id][i].size() == 0) break;
        attacks[i] = attack_names[id][i];
    }
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
