#ifndef game_hpp
#define game_hpp

// TODO: fill color and weapon
#include "utils.hpp"

class Pregame_msg
{
public:
    // Pregame_msg();
    ColorType color1;
    ColorType color2;
    WeaponType weapon1;
    WeaponType weapon2;
    int map_no;

};

class Ingame_msg
{
public:
    // Ingame_msg();
    double color1_ratio;
    double color2_ratio;
    int p1Health;
    int p2Health;
    int p1Ink;
    int p2Ink;
    int death1;
    int death2;
    double damage1;
    double damage2;
};

Pregame_msg pregame();

Ingame_msg ingame(Pregame_msg msg);

void postgame(Ingame_msg msg);

#endif
