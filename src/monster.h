#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <random>

#include "conf.h"
#include "entity.h"

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
        std::string name;
        int level = 1, xp = 0, level_up_threshold = 10; 
        const float level_up_multiplier = 1.15;
        int max_pps[4];
        float max_health, health;
        float attack, defense, speed;

        int id;

        static const int highest_dex = 21;

        std::string attacks[4];
        int move_count = 0;
        float attack_values[4][2];

        // functions
        void giveXP(int);
};

const std::string texture_paths[] = {
    "art/sprites/battle/nineplusten.png",
    "art/sprites/battle/sponge.png",
    "art/sprites/battle/steve.png",
    "art/sprites/battle/jared.png",
    "art/sprites/battle/jfk.png",
    "art/sprites/battle/corolla.png",
    "art/sprites/battle/wordle.png",
    "art/sprites/battle/bush.png",
    "art/sprites/battle/celery.png",
    "art/sprites/battle/e.png",
    "art/sprites/battle/france.png",
    "art/sprites/battle/integral.png",
    "art/sprites/battle/iphone.png",
    "art/sprites/battle/jesus.png",
    "art/sprites/battle/boeing.png",
    "art/sprites/battle/boris.png",
    "art/sprites/battle/lick.png",
    "art/sprites/battle/mark.png",
    "art/sprites/battle/mozart.png",
    "art/sprites/battle/saul.png",
    "art/sprites/battle/uranium.png",

    "art/sprites/battle/3090.png",
    "art/sprites/battle/carbonemissions.png",
    "art/sprites/battle/chad.png",
    "art/sprites/battle/chicken.png",
    "art/sprites/battle/cinderblock.png",
    "art/sprites/battle/cockatiel.png",
    "art/sprites/battle/cory.png",
    "art/sprites/battle/david.png",
    "art/sprites/battle/dino.png",
    "art/sprites/battle/drake.png",
    "art/sprites/battle/drillpress.png",
    "art/sprites/battle/fidgetspinner.png",
    "art/sprites/battle/fortnite.png",
    "art/sprites/battle/hogrider.png",
    "art/sprites/battle/icecream.png",
    "art/sprites/battle/m&m.png",
    "art/sprites/battle/microwave.png",
    "art/sprites/battle/ninja.png",
    "art/sprites/battle/peanutbutter.png",
    "art/sprites/battle/psy.png",
    "art/sprites/battle/quarter.png",
    "art/sprites/battle/rosie.png",
    "art/sprites/battle/stop.png",
    "art/sprites/battle/tetris.png",
    "art/sprites/battle/therock.png",
    "art/sprites/battle/ti84.png",
    "art/sprites/battle/tux.png",
    "art/sprites/battle/usb.png",
    "art/sprites/battle/nft.png",
};

const std::string names[] {
    "9+10 kid",
    "spoinkbub",
    "Steve",
    "Jared Fogle",
    "John F. Kennedy",
    "2008 Toyota Corolla",
    "WORDLE",
    "a bush",
    "some celery",
    "E",
    "France",
    "Integral",
    "iPhone 3",
    "Jesus Christ",
    "Boeing 747",
    "Boris Johnson",
    "The Lick",
    "Mark Cuban",
    "Mozart",
    "Saul Goodman",
    "Uranium-238",

    "nvidia RTX 3090",
    "carbon emissions",
    "Gigachad",
    "a chicken leg",
    "a cinderblock",
    "cockatiel",
    "Cory Baxter",
    "The Statue of David",
    "Brachiosaurus",
    "champagnepapi",
    "drill press",
    "fidget spinner",
    "fortnite guy",
    "hog rider",
    "ice cream",
    "green m&m",
    "microwave",
    "Ninja \"fortnite\" Blevins",
    "peanut butter",
    "Psy",
    "a quarter",
    "Rosie the Riveter",
    "a stop sign",
    "Tetris T-Piece",
    "Dwayne Johnson",
    "ti-84",
    "Linux Tux",
    "a usb drive",
    "a Non-Fungible Token",
};

const std::string attack_names[][4] = {
    {"add", "\"you stupid\"", "", ""},
    {"blow bubble", "swing spatula", "", ""},
    {"punch", "craft", "", ""},
    {"pray on children", "make sandwhich", "", ""},
    {"", "", "", ""},
    {"drive", "other move", "", ""},
    {"PUNCH", "SMACK", "THROW", "SHOCK"},
    {"poke", "shimmy", "", ""},
    {"stab", "hydrate", "", ""},
    {"E", "E", "E", "E"},
    {"surrender", "", "", ""},
    {"integrate", "", "", ""},
    {"shock", "reboot", "", ""},
    {"impale", "preach", "", ""},
    {"wind blast", "", "", ""},
    {"blabble", "stammer", "tomfoolery", "take the piss"},
    {"play in G", "play in c#", "play in Eb", "play in a"},
    {"BUY!!", "SELL!!", "INVEST!!", ""},
    {"compose", "", "", ""},
    {"rubuttal", "objection", "", ""},
    {"alpha decay", "beta decay", "gamma decay", "radiate"},

    {"render polygon", "mine", "", ""},
    {"polute", "warm", "", ""},
    {"flex", "intimidate", "", ""},
    {"", "", "", ""},
    {"cinderblock", "do nothing", "", ""},
    {"peck", "chirp", "wing slap", ""},
    {"", "", "", ""},
    {"", "", "", ""},
    {"stomp", "roar", "", ""},
    {"", "", "", ""},
    {"drill", "press", "", ""},
    {"spin", "throw", "", ""},
    {"shoot", "", "", ""},
    {"", "", "", ""},
    {"", "", "", ""},
    {"flirt", "", "", ""},
    {"microwave", "spin contents", "", ""},
    {"stream", "", "", ""},
    {"", "", "", ""},
    {"dance", "sing", "", ""},
    {"", "", "", ""},
    {"punch", "", "", ""},
    {"stop", "hault", "freeze", "yield"},
    {"spin", "", "", ""},
    {"punch", "wrestle", "cook", ""},
    {"compute", "calculate", "graph", ""},
    {"compile headers", "'grep '", "'awk'", "'ls -a /'"},
    {"", "", "", ""},
    {"depreciate", "", "", ""},
};

// (damage, PP) for each 4 moves
const float attack_values_matrix[][4][2] = {
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{2.5, 15}, {5, 5}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{2.5, 5}, {2.5, 5}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{1, 10}, {4, 5}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
};

// base (attack, defense, speed, max_health) stats for each monster
const float stats[][4] {
    {0.5, 1, 1.2, 10},
    {0.5, 1, 0.8, 10},
    {1.0, 1, 1.0, 12},
    {0.8, 1, 0.5, 12},
    {1.2, 1, 1.0, 15},
    {1.5, 1, 4.0, 20},
    {0.5, 1, 1.0, 10},
    {0.2, 1, 0.0, 5},
    {0.2, 1, 0.3, 3},
    {1.0, 1, 1.0, 10},
    {1.2, 1, 1.0, 20},
    {1.0, 1, 1.0, 13},
    {0.5, 1, 0.7, 7},
    {1.5, 1, 1.2, 15},
    {2.0, 1, 5.0, 25},
    {0.7, 1, 0.7, 15},
    {0.7, 1, 1.0, 10},
    {0.8, 1, 1.0, 13},
    {0.6, 1, 1.1, 10},
    {1.0, 1, 1.3, 13},
    {1.5, 1, 1.0, 35},

    {1.5, 1, 3.0, 13},
    {2.0, 1, 0.2, 20},
    {2.0, 1, 2.0, 30},
    {0.5, 1, 1.0, 5},
    {1.4, 1, 1.2, 20},
    {0.9, 1, 1.4, 5},
    {0.7, 1, 0.8, 10},
    {1.0, 1, 1.2, 14},
    {1.7, 1, 0.2, 20},
    {0.2, 1, 0.8, 6},
    {1.8, 1, 1.0, 25},
    {0.6, 1, 1.1, 5},
    {1.1, 1, 1.0, 15},
    {1.0, 1, 1.5, 12},
    {0.7, 1, 0.5, 8},
    {0.5, 1, 0.6, 8},
    {1.3, 1, 0.8, 12},
    {0.4, 1, 0.4, 2},
    {0.5, 1, 0.5, 5},
    {1.0, 1, 1.0, 10},
    {0.6, 1, 1.0, 8},
    {1.5, 1, 1.2, 17},
    {0.7, 1, 0.2, 8},
    {0.3, 1, 0.8, 10},
    {1.7, 1, 1.4, 25},
    {0.8, 1, 0.5, 10},
    {1.0, 1, 1.2, 10},
    {0.6, 1, 0.8, 8},
    {0.01, 1, 0.01, 1},
};

#endif 
