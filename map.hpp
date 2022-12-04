//
//  map.hpp
//  project
//
//  Created by jinchiz on 2022/11/22.

#ifndef map_hpp
#define map_hpp

#include <stdio.h>
#include <vector>
#include <ctime>
#include "yspng.h"
#include "fssimplewindow.h"
using namespace std;

enum Item_mode
{
    None,
    Health,
    Ink,
    Weapon_painting,
    Weapon_attack
};

// set const config
const int BOX_ENDURANCE = 5;
const int BOX_DX = 50;
const int BOX_DY = 50;
const int ITEM_DX = 40;
const int ITEM_DY = 40;
const int UI_OFFSET = 200;
const int MAP_WIDTH = 800;
const int MAP_HEI = 600;
const int HEAlTH_REC = 50;
const int INK_REC = 30;

class Map_item
{
public:
    virtual void draw() = 0;
    int X;
    int Y;
};

class Obstacle : public Map_item
{
public:
    bool is_exist;
    virtual void draw() = 0;
    int endurance;
    int Dx, Dy;
};

class F_Obstacle : public Obstacle
{
public:
    F_Obstacle(int, int);
    static YsRawPngDecoder png_f;
    void draw();
    // TODO: Update function
};

class H_Obstacle : public Obstacle
{
public:
    H_Obstacle(int, int);
    static YsRawPngDecoder png_h;
    void draw();
    // TODO: Update function
};

class Enhancement : public Map_item
{
public:
    static YsRawPngDecoder base_png;
    static YsRawPngDecoder health_png;
    static YsRawPngDecoder ink_png;
    static YsRawPngDecoder fire_png;
    static YsRawPngDecoder brush_png;
    Enhancement(int x, int y);
    Item_mode mode = Weapon_attack;
    void draw();
};

// TODO: Ink mark class

class Map
{
public:
    Map(int w, int h, int p);
    void draw();
    void load_pattern(int p);
    void draw_floor();
    void read_floor();
    pair<double, double> game_summary(vector<int> c1, vector<int> c2);
    vector<Obstacle *> Obstacles;
    vector<Enhancement *> Items;
    GLubyte color_map[3 * 800 * 800];

private:
    int width, height;
    bool is_buffer = false;
};

#endif /* map_hpp */
