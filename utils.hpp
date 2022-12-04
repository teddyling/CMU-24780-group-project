//
//  utils.hpp
//  project
//
//  Created by Jinchi Zhang on 2022/11/26.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include <cassert>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#define assertm(exp, msg) assert(((void)msg, exp))

using namespace std;

enum ColorType
{
    RED = 0,
    SKYBLUE = 1,
    YELLOW = 2,
    GREEN = 3,
    BLUE = 4,
    PURPLE = 5,
};

enum WeaponType
{
    SHOTGUN = 0,
    SNIPER = 1,
    GRENADE = 2,
};

struct Pattern
{
    vector<pair<int, int>> fragile_boxes;
    vector<pair<int, int>> hard_boxes;
    vector<pair<int, int>> items;
};

void load_png(YsRawPngDecoder &png, const char *file_path);
void draw_png(YsRawPngDecoder &png, int x, int y);
Pattern read_pattern(const char *file, int w, int h, int dx, int dy);
bool collision(double xPosNew, double yPosNew, double width, double height, int obs_X, int obs_Y, int obs_Dx, int obs_Dy);

void SetColor(ColorType c, int &r, int &g, int &b);
int SetFireInterval(WeaponType w);
#endif /* utils_hpp */
