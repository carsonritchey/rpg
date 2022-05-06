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
        int level = 1, xp = 0, level_up_threshold = 25; 
        float max_health = 20.f, health = max_health;
        float attack, defense, speed;

        int id;

        std::string attacks[4];
        int move_count = 0;
        float attack_values[4][2];

        // functions
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
    "art/sprites/battle/buford.png",
    "art/sprites/battle/carbonemissions.png",
    "art/sprites/battle/cat.png",
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
    "art/sprites/battle/minon.png",
    "art/sprites/battle/ninja.png",
    "art/sprites/battle/peanutbutter.png",
    "art/sprites/battle/psy.png",
    "art/sprites/battle/quarter.png",
    "art/sprites/battle/rosie.png",
    "art/sprites/battle/stop.png",
    "art/sprites/battle/tesseract.png",
    "art/sprites/battle/tetris.png",
    "art/sprites/battle/therock.png",
    "art/sprites/battle/ti84.png",
    "art/sprites/battle/tux.png",
    "art/sprites/battle/usb.png",
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
    "jesus",
    "Boeing 747",
    "Boris Johnson",
    "The Lick",
    "Mark Cuban",
    "Wolfgang Amadeus Mozart",
    "Saul Goodman",
    "Uranium-238",

    "nvidia RTX 3090",
    "Buford Van Stomm",
    "carbon emissions",
    "gay cat",
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
    "anti-vax minon",
    "Ninja \"fortnite\" Blevins",
    "peanut butter",
    "Psy",
    "a quarter",
    "Rosie the Riveter",
    "a stop sign",
    "The Tesseract Joint",
    "Tetris T-Piece",
    "Dwayne Johnson",
    "ti-84",
    "Linux Tux",
    "a usb drive",
};

const std::string attack_names[][4] = {
    {"add", "\"you stupid\"", "", ""},
    {"blow bubble", "swing spatula", "", ""},
    {"punch", "craft", "", ""},
    {"pray on children", "make sandwhich", "", ""},
    {"", "", "", ""},
    {"drive", "", "", ""},
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
};

// (damage, PP) for each 4 moves
const float attack_values_matrix[][4][2] = {
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{2.5, 15}, {0, 0}, {0, 0}, {0, 0}},
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
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
};

// base (attack, defense, speed) stats for each monster
const float stats[][3] {
    {0, 0, 0},
    {1, 1, 1},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {1, 1, 2},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};

#endif 
