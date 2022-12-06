//  map.cpp
//  project
//  Created by Jinchi Zhang on 2022/11/22.
#include "map.hpp"
#include "fssimplewindow.h"
#include "utils.hpp"
#include "iostream"

YsRawPngDecoder F_Obstacle::png_f;
YsRawPngDecoder H_Obstacle::png_h;
YsRawPngDecoder Enhancement::base_png;
YsRawPngDecoder Enhancement::health_png;
YsRawPngDecoder Enhancement::ink_png;
YsRawPngDecoder Enhancement::fire_png;
YsRawPngDecoder Enhancement::brush_png;

F_Obstacle::F_Obstacle(int x, int y)
{
    X = x;
    Y = y + UI_OFFSET;
    Dx = BOX_DX;
    Dy = BOX_DY;
    is_exist = true;
    endurance = BOX_ENDURANCE;
}

void F_Obstacle::draw()
{
    if (is_exist)
    {
        draw_png(png_f, X, Y);
    }
    return;
}

H_Obstacle::H_Obstacle(int x, int y)
{
    is_exist = true;
    endurance = -1;
    X = x;
    Y = y + UI_OFFSET;
    Dx = BOX_DX;
    Dy = BOX_DY;
}

void H_Obstacle::draw()
{
    draw_png(png_h, X, Y);
}

Enhancement::Enhancement(int x, int y)
{
    X = x;
    Y = y + UI_OFFSET;
}

void Enhancement::draw()
{
    if (mode == None)
    {
        draw_png(base_png, X, Y);
    }
    else if (mode == Health)
    {
        draw_png(health_png, X, Y);
    }
    else if (mode == Ink)
    {
        draw_png(ink_png, X, Y);
    }
    else if (mode == Weapon_attack)
    {
        draw_png(fire_png, X, Y);
    }
    else if (mode == Weapon_painting)
    {
        draw_png(brush_png, X, Y);
    }
}

Map::Map(int w, int h, int p)
{
    width = w;
    height = h;
    load_pattern(p);

    // load images
    load_png(H_Obstacle::png_h, "images/iron50.png");
    load_png(F_Obstacle::png_f, "images/box50.png");
    load_png(Enhancement::base_png, "images/item_base.png");
    load_png(Enhancement::health_png, "images/heart40.png");
    load_png(Enhancement::ink_png, "images/drink.png");
    load_png(Enhancement::fire_png, "images/fire.png");
    load_png(Enhancement::brush_png, "images/brush.png");

    // load_png(F_Obstacle::png_f, "/home/kinova/Documents/shiqi/24-780/GroupProject/images/box50.png");
    // load_png(Enhancement::base_png, "/home/kinova/Documents/shiqi/24-780/GroupProject/images/item_base.png");
    // load_png(Enhancement::health_png, "/home/kinova/Documents/shiqi/24-780/GroupProject/images/heart40.png");
    // load_png(Enhancement::ink_png, "/home/kinova/Documents/shiqi/24-780/GroupProject/images/drink.png");
    // load_png(Enhancement::fire_png, "/home/kinova/Documents/shiqi/24-780/GroupProject/images/fire.png");
    // load_png(Enhancement::brush_png, "/home/kinova/Documents/shiqi/24-780/GroupProject/images/brush.png");
}

void Map::load_pattern(int p)
{
    Pattern pattern;
    string base_path = "patterns/map";
    base_path.append(to_string(p));
    base_path.append(".txt");
    if(p != 3){
        pattern = read_pattern(base_path.c_str(), width, height, BOX_DX, BOX_DY);
    } else {
        pattern = read_pattern(base_path.c_str(), width, height, BOX_DX, BOX_DY, true);
    }
    
    for (auto f_box : pattern.fragile_boxes)
    {
        F_Obstacle *obs = new F_Obstacle(f_box.first, f_box.second);
        Obstacles.push_back(obs);
    }
    for (auto h_box : pattern.hard_boxes)
    {
        H_Obstacle *obs = new H_Obstacle(h_box.first, h_box.second);
        Obstacles.push_back(obs);
    }
    for (auto item : pattern.items)
    {
        Enhancement *en = new Enhancement(item.first, item.second);
        Items.push_back(en);
    }
}

void Map::update(int time_left, int game_time) {
    if(time_left != (game_time/2)) {
        return;
    }
    for(auto item : Items){
        if(item -> can_gen){
            int item_num = rand() % 4 + 1;
            item -> mode = Item_mode(item_num);
            item -> can_gen = false;
        }
    }
    return;
}

void Map::draw()
{
    for (auto obs : Obstacles)
    {
        obs->draw();
    }
    for (auto item : Items)
    {
        item->draw();
    }
    return;
}

void Map::draw_floor()
{
    if (is_buffer)
    {
        glWindowPos2i(0, 0);
        glDrawPixels(800, 600, GL_RGB, GL_UNSIGNED_BYTE, &color_map);
    }
    is_buffer = true;

    return;
}

void Map::read_floor()
{
    glReadPixels(0, 0, 800, 600, GL_RGB, GL_UNSIGNED_BYTE, &color_map);
    return;
}

pair<double, double> Map::game_summary(vector<int> c1, vector<int> c2)
{
    long num1, num2;
    num1 = 0;
    num2 = 0;
    int i1, i2, i3;
    for (int i = 0; i < width * height; i++)
    {
        i1 = i * 3;
        i2 = i * 3 + 1;
        i3 = i * 3 + 2;
        if (color_map[i1] == c1[0] && color_map[i2] == c1[1] && color_map[i3] == c1[2])
            num1++;
        if (color_map[i1] == c2[0] && color_map[i2] == c2[1] && color_map[i3] == c2[2])
            num2++;
    }
    double ratio1 = (double)num1 / (width * height);
    double ratio2 = (double)num2 / (width * height);
    return {ratio1, ratio2};
}
