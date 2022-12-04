// Author: Shiqi Liu

#include <istream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include "fssimplewindow.h"
#include "map.hpp"
#include "character.h"
#include "weapon.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;

void RunGame()
{
    FsChangeToProgramDir();
    // setup map
    Map map = Map(800, 600, 1);

    Character player1;
    Character player2;
    // set key for each player
    const int keys1[] = {FSKEY_W, FSKEY_A, FSKEY_S, FSKEY_D, FSKEY_E, FSKEY_Q, FSKEY_R, FSKEY_F};
    const int keys2[] = {FSKEY_I, FSKEY_J, FSKEY_K, FSKEY_L, FSKEY_O, FSKEY_U, FSKEY_P, FSKEY_SEMICOLON};
    player1.SetKey(keys1);
    player2.SetKey(keys2);
    // set player weapon
    player1.SetWeapon(1, SHOTGUN);
    player2.SetWeapon(2, SNIPER);
    // set player color
    player1.SetColor(0, 255, 0);
    player2.SetColor(0, 0, 255);
    // set player weapon
    Weapon_Shotgun weapon1;
    Weapon_Sniper weapon2;
    Weapon_Grenade weapon3;
    // set players initial positions
    player1.SetPos(100, 500);
    player2.SetPos(600, 500);
    // play
    const int tmp = 800 * 600 * 3;
    int pixels[tmp];
    bool isBuffer = false;
    GLubyte color[3 * 800 * 800];

    bool isFire1, isFire2;
    Item_mode im1, im2;
    // GLint raspos[2];
    // glGetIntegerv(GL_CURRENT_RASTER_POSITION, raspos);
    // GLint windpos[2];
    // glGetIntergv(GL_CURREN)
    while (true)
    {
        FsPollDevice();
        if (FsInkey() == FSKEY_ESC)
        {
            return;
        }

        bool isFire1 = player1.Step(player2, map, im1);
        bool isFire2 = player2.Step(player1, map, im2);
        weapon1.update(im1);
        weapon2.update(im2);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        map.draw_floor();

        if (isFire1)
        {
            printf("player 1 fire.\n");
            weapon1.Fire(player1, map.Obstacles, player2);
            // weapon1.CheckHit(player2);
        }

        if (isFire2)
        {
            printf("player 2 fire.\n");
            weapon2.Fire(player2, map.Obstacles, player1);
        }

        map.read_floor();

        // Draw objects
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // if (isBuffer)
        // {
        //     // draw Buffer
        //     glDrawPixels(800, 600, GL_RGB, GL_UNSIGNED_BYTE, &color);
        // }

        // player1.Draw();

        // save buffer

        // glReadPixels(0, 0, 800, 600, GL_RGB, GL_UNSIGNED_BYTE, &color);
        auto ratio = map.game_summary({0, 255, 0}, {255, 0, 0});
        printf("color1 : %f, color2 : %f\n", ratio.first, ratio.second);

        map.draw();
        player1.Draw();
        player2.Draw();

        weapon1.firePlayer.KeepPlaying();
        weapon2.firePlayer.KeepPlaying();

        glFlush();
        FsSwapBuffers();
        FsSleep(25);
    }
}

int main(void)
{
    // Set random seed
    srand(time(NULL));
    FsOpenWindow(16, 16, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    RunGame();
    return 0;
}
