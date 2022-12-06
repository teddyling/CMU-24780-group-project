//
//  utils.cpp
//  project
//
//  Created by on 2022/11/26.

#include "utils.hpp"
#include "weapon.h"

void load_png(YsRawPngDecoder &png, const char *file_path)
{
    png.Decode(file_path);
    png.Flip();
    assertm((png.wid != 0 && png.hei != 0), "Loading image failed\n");
    return;
}

void draw_png(YsRawPngDecoder &png, int x, int y)
{
    glRasterPos2d(x, y);
    glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
}

void SetColor(ColorType c, int &r, int &g, int &b)
{
    switch (c)
    {
    case RED:
        r = 255;
        g = 0;
        b = 0;
        break;
    case SKYBLUE:
        r = 0;
        g = 255;
        b = 255;
        break;
    case YELLOW:
        r = 255;
        g = 255;
        b = 0;
        break;
    case GREEN:
        r = 0;
        g = 255;
        b = 0;
        break;
    case BLUE:
        r = 0;
        g = 0;
        b = 255;
        break;
    case PURPLE:
        r = 255;
        g = 0;
        b = 255;
        break;
    default:
        r = 0;
        g = 0;
        b = 0;
        break;
    }
}

int SetFireInterval(WeaponType w)
{
    switch (w)
    {
    case SHOTGUN:
        return 10;
    case SNIPER:
        return 10;
    case GRENADE:
        return 10;
    }
    return 10;
}

int GetFireInterval(WeaponType w)
{
    switch (w)
    {
    case SHOTGUN:
        return 30;
    case SNIPER:
        return 20;
    case GRENADE:
        return 50;
    }
    return 10;
}
int GetFireReqInk(WeaponType w)
{
    switch (w)
    {
    case SHOTGUN:
        return 50;
    case SNIPER:
        return 30;
    case GRENADE:
        return 70;
    }
    return 10;
}

// Weapon SetWeapon(WeaponType w, int r, int g, int b)
// {
//     switch (w)
//     {
//     case SHOTGUN:
//         return new Weapon_Shotgun;
//         break;
//     case SNIPER:
//         break;
//     default:
//         break;
//     }
// }
Pattern read_pattern(const char *file, int w, int h, int dx, int dy, bool is_special)
{
    string line;
    ifstream my_read_file(file);
    Pattern pattern;

    while (getline(my_read_file, line))
    {
        char c;
        int x, y;
        stringstream line_stream(line);
        line_stream >> c >> x >> y;
        if (c == 'f')
        {
            pattern.fragile_boxes.push_back({x, y});
        }
        else if (c == 'h')
        {
            // symetrically set box
            pattern.hard_boxes.push_back({x, y});
        }
        else if (c == 'e')
        {
            pattern.items.push_back({x, y});
        }
    }
    return pattern;
}

Pattern read_pattern(const char *file, int w, int h, int dx, int dy)
{
    string line;
    ifstream my_read_file(file);
    Pattern pattern;

    while (getline(my_read_file, line))
    {
        char c;
        int x, y;
        stringstream line_stream(line);
        line_stream >> c >> x >> y;
        if (c == 'f')
        {
            // symetrically set box
            pattern.fragile_boxes.push_back({x, y});
            pattern.fragile_boxes.push_back({w - x - dx, y});
            pattern.fragile_boxes.push_back({x, h - y + dy});
            pattern.fragile_boxes.push_back({w - x - dx, h - y + dy});
        }
        else if (c == 'h')
        {
            // symetrically set box
            pattern.hard_boxes.push_back({x, y});
            pattern.hard_boxes.push_back({w - x - dx, y});
            pattern.hard_boxes.push_back({x, h - y + dy});
            pattern.hard_boxes.push_back({w - x - dx, h - y + dy});
        }
        else if (c == 'e')
        {
            pattern.items.push_back({x, y});
        }
    }
    return pattern;
}

bool collision(double xPosNew, double yPosNew, double width, double height, int bx, int by, int obs_Dx, int obs_Dy)
{
    // double bx = obs_X + obs_Dx / 2.0;
    // double by = obs_Y - obs_Dy / 2.0;
    double dx = abs(xPosNew - bx);
    double dy = abs(yPosNew - by);
    double x_size = (width + obs_Dx) / 2;
    double y_size = (height + obs_Dy) / 2;
    return dx <= x_size && dy <= y_size;
}
