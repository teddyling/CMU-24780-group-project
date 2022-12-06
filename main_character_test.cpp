// Author: Shiqi Liu

#include <istream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "fssimplewindow.h"
#include "character.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void RunGame()
{
    Character player1 = Character();
    Character player2 = Character();
    // set key for each player
    const int keys1[] = {FSKEY_W, FSKEY_A, FSKEY_S, FSKEY_D, FSKEY_E, FSKEY_Q, FSKEY_R, FSKEY_F};
    const int keys2[] = {FSKEY_I, FSKEY_J, FSKEY_K, FSKEY_L, FSKEY_O, FSKEY_U, FSKEY_P, FSKEY_SEMICOLON};
    player1.SetKey(keys1);
    player2.SetKey(keys2);
    // set player color
    player1.SetColor(255, 255, 0);
    player2.SetColor(0, 255, 0);
    // set players initial positions
    player1.SetPos(100, 500);
    player2.SetPos(600, 500);
    // play
    const int tmp = 800 * 600 * 3;
    int pixels[tmp];
    bool isBuffer = false;
    GLubyte color[3 * 800 * 600];

    while (true)
    {
        FsPollDevice();
        if (FsInkey() == FSKEY_ESC)
        {
            return;
        }

        player1.Step();
        player2.Step();

        // Draw objects
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (isBuffer)
        {
            // draw Buffer
            glDrawPixels(800, 600, GL_RGB, GL_UNSIGNED_BYTE, &color);
        }

        // player1.Draw();

        // save buffer

        glReadPixels(0, 0, 800, 600, GL_RGB, GL_UNSIGNED_BYTE, &color);
        isBuffer = true;
        player1.Draw();
        player2.Draw();
        glFlush();
        FsSwapBuffers();
        FsSleep(25);
    }
}
//
//int main(void)
//{
//    // Set random seed
//    srand(time(NULL));
//    FsOpenWindow(16, 16, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
//    glShadeModel(GL_SMOOTH);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_BLEND);
//    RunGame();
//    return 0;
//}
