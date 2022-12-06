// Author: Shiqi Liu

#include <istream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include "fssimplewindow.h"
#include "game.hpp"
#include "map.hpp"
#include "character.h"
#include "utils.hpp"

const double Pi = 3.1415926;

Character::Character()
{
    width = 25.0;
    height = 25.0;
    drawCharacterSize = 50.0;
    drawSplashSize = 30.0;
    inkRecoverSpeed = 1.0;
    speed = 3.0;
    rotateSpeed = 3.0;
    health = 100.0;
    inkMount = 100.0;
    fireReqInk = 20.0;
    isAlive = true;
    isSwim = false;
    theta = 0.0;
    rebornTime = 0;
    totalRebornTime = 200;
    fireCoolTime = 0;
    totalFireCoolTime = 5;
    swimCoolTime = 0;
    totalSwimCoolTime = 5;
    takeDamage = 0.0;
    deathNum = 0;
    SetSplash();
    deadPlayer.MakeCurrent();
    deadPlayer.Start();
    if (YSOK != deadWav.LoadWav("music/killsoundeffect.wav"))
    {
        printf("Can not find killsoundeffect.wav\n");
    }
}

// Set the control keys for the character: [Up, Left, Down, Right, Fire, Swim, Rotate, RotateCounter]
void Character::SetKey(const int keys[])
{
    keyUp = keys[0];
    keyLeft = keys[1];
    keyDown = keys[2];
    keyRight = keys[3];
    keyFire = keys[4];
    keySwim = keys[5];
    keyRotate = keys[6];
    keyRotateCounter = keys[7];
}

// Set the control keys for the character: [Up, Left, Down, Right, Fire, Swim, Rotate, RotateCounter]
void Character::SetWeapon(int playerId, WeaponType weaponType)
{
    totalFireCoolTime = GetFireInterval(weaponType);
    fireReqInk = GetFireReqInk(weaponType);
    if (playerId == 1)
    {
        if (weaponType == SHOTGUN)
        {
            playerPng.Decode("images/p1shotgun.png");
            printf("set player 1 to shotgun\n");
        }
        else if (weaponType == SNIPER)
        {
            playerPng.Decode("images/p1sniper.png");
            printf("set player 1 to sniper\n");
        }
        else
        {
            playerPng.Decode("images/p1rpg.png");
            printf("set player 1 to rpg\n");
        }
    }
    else
    {
        if (weaponType == SHOTGUN)
        {
            playerPng.Decode("images/p2shotgun.png");
            printf("set player 2 to shotgun\n");
        }
        else if (weaponType == SNIPER)
        {
            playerPng.Decode("images/p2sniper.png");
            printf("set player 2 to sniper\n");
        }
        else
        {
            playerPng.Decode("images/p2rpg.png");
            printf("set player 2 to rpg\n");
        }
    }
    playerPng.Flip();

    glGenTextures(1, &playerTexture);            // Reserve one texture identifier
    glBindTexture(GL_TEXTURE_2D, playerTexture); // Making the texture identifier current (or bring it to the deck)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,
                 0, // Level of detail
                 GL_RGBA,
                 playerPng.wid,
                 playerPng.hei,
                 0, // Border width, but not supported and needs to be 0.
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 playerPng.rgba);
}

void Character::SetSplash()
{
    playerSwimPng.Decode("images/splash.png");
    playerSwimPng.Flip();

    glGenTextures(1, &playerSwimTexture);            // Reserve one texture identifier
    glBindTexture(GL_TEXTURE_2D, playerSwimTexture); // Making the texture identifier current (or bring it to the deck)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,
                 0, // Level of detail
                 GL_RGBA,
                 playerSwimPng.wid,
                 playerSwimPng.hei,
                 0, // Border width, but not supported and needs to be 0.
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 playerSwimPng.rgba);
}

// Set the initial position of the character
void Character::SetPos(double x0, double y0, double t)
{
    theta = t;
    xPos = x0;
    yPos = y0;
    xPosInit = x0;
    yPosInit = y0;
}

// Set fire interval
void Character::SetFireInterval(int x)
{
    totalFireCoolTime = x;
}

// Draw the character of the window
void Character::Draw()
{
    double angle;
    double angleDraw;
    double size;
    if (isAlive && !isSwim)
    {
        // glColor3ub(0, 0, 0);
        // glBegin(GL_QUADS);
        // glVertex2i(xPos - width / 2, yPos - height / 2);
        // glVertex2i(xPos + width / 2, yPos - height / 2);
        // glVertex2i(xPos + width / 2, yPos + height / 2);
        // glVertex2i(xPos - width / 2, yPos + height / 2);
        // glEnd();

        // GLubyte color[3];
        // glReadPixels(int(xPos), 600 - int(yPos), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color);

        // if character is alive, draw the character and fire angle
        glLineWidth(1.0);
        // if (isSwim)
        // {
        //     glColor3ub(0.8 * colorR, 0.8 * colorG, 0.8 * colorB);
        // }
        // else
        // {
        //     glColor3ub(colorR, colorG, colorB);
        // }
        // glBegin(GL_QUADS);
        // glVertex2d(xPos - width / 2, yPos - height / 2);
        // glVertex2d(xPos + width / 2, yPos - height / 2);
        // glVertex2d(xPos + width / 2, yPos + height / 2);
        // glVertex2d(xPos - width / 2, yPos + height / 2);
        // glEnd();

        // draw bbox
        // glColor3ub(0, 0, 0);
        // glBegin(GL_LINE_LOOP);
        // glVertex2d(xPos - width / 2, yPos - height / 2);
        // glVertex2d(xPos + width / 2, yPos - height / 2);
        // glVertex2d(xPos + width / 2, yPos + height / 2);
        // glVertex2d(xPos - width / 2, yPos + height / 2);
        // glEnd();

        // draw aiming angle
        angle = theta / 180 * Pi;
        glColor3ub(0, 0, 0);
        glBegin(GL_LINE_STRIP);
        glVertex2d(xPos, yPos);
        glVertex2d(xPos + 30 * cos(angle), yPos + 30 * sin(angle));
        glEnd();

        // draw character png
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(1.0, 1.0, 1.0, 1.0);

        glEnable(GL_TEXTURE_2D); // Begin using texture mapping

        glBindTexture(GL_TEXTURE_2D, playerTexture);

        glBegin(GL_QUADS);

        // glTexCoord2d(0.0, 0.0);
        // glVertex2d(xPos - width / 2, yPos - height / 2);
        // glTexCoord2d(1.0, 0.0);
        // glVertex2d(xPos + width / 2, yPos - height / 2);
        // glTexCoord2d(1.0, 1.0);
        // glVertex2d(xPos + width / 2, yPos + height / 2);
        // glTexCoord2d(0.0, 1.0);
        // glVertex2d(xPos - width / 2, yPos + height / 2);

        angleDraw = -angle + 3 * Pi / 4.0;
        size = drawCharacterSize;

        glTexCoord2d(0.0, 0.0); // For each vertex, assign texture coordinate before vertex coordinate.
        glVertex2d(xPos + size * cos(angleDraw), yPos - size * sin(angleDraw));

        glTexCoord2d(1.0, 0.0);
        glVertex2d(xPos + size * cos(angleDraw + Pi / 2.0), yPos - size * sin(angleDraw + Pi / 2.0));

        glTexCoord2d(1.0, 1.0);
        glVertex2d(xPos + size * cos(angleDraw + Pi), yPos - size * sin(angleDraw + Pi));

        glTexCoord2d(0.0, 1.0);
        glVertex2d(xPos + size * cos(angleDraw - Pi / 2.0), yPos - size * sin(angleDraw - Pi / 2.0));

        glEnd();

        glDisable(GL_TEXTURE_2D);

        // printf("R:%d G:%d B:%d\n", color[0], color[1], color[2]);
    }
    else if (isAlive && isSwim)
    {

        // draw character png
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(1.0, 1.0, 1.0, 1.0);

        glEnable(GL_TEXTURE_2D); // Begin using texture mapping

        glBindTexture(GL_TEXTURE_2D, playerSwimTexture);

        glBegin(GL_QUADS);

        angleDraw = -3 * Pi / 4.0;
        size = drawSplashSize;

        glTexCoord2d(0.0, 0.0); // For each vertex, assign texture coordinate before vertex coordinate.
        glVertex2d(xPos + size * cos(angleDraw), yPos - size * sin(angleDraw));

        glTexCoord2d(1.0, 0.0);
        glVertex2d(xPos + size * cos(angleDraw + Pi / 2.0), yPos - size * sin(angleDraw + Pi / 2.0));

        glTexCoord2d(1.0, 1.0);
        glVertex2d(xPos + size * cos(angleDraw + Pi), yPos - size * sin(angleDraw + Pi));

        glTexCoord2d(0.0, 1.0);
        glVertex2d(xPos + size * cos(angleDraw - Pi / 2.0), yPos - size * sin(angleDraw - Pi / 2.0));

        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
    else if (--rebornTime < 0)
    {
        // if character is dead, draw circle that represent remain reborn time.
    }
}

// Change character state based on the player input. This function should be called in the main loop,
bool Character::Step(Character &player2, Map &map, Item_mode &im)
{
    bool isFire = false;
    if (isAlive)
    {
        Move(player2, map.Obstacles, map.color_map, map.Items, im);
        isFire = Fire();
        Rotate();
        Swim(map.color_map);
    }
    else if (--rebornTime < 0)
    {
        // reborn character
        Reborn();
    }

    return isFire;
}

// Change the character position on the map based on the player input key.
void Character::Move(Character &player2, std::vector<Obstacle *> obstacles, const GLubyte color_map[], std::vector<Enhancement *> &items, Item_mode &im)
{
    int pressUp, pressDown, pressLeft, pressRight;
    int xMove = 0, yMove = 0;
    double xPosNew, yPosNew;
    bool is_update_loc = true;
    pressUp = FsGetKeyState(keyUp);
    pressLeft = FsGetKeyState(keyLeft);
    pressDown = FsGetKeyState(keyDown);
    pressRight = FsGetKeyState(keyRight);
    // printf("%d, %d, %d, %d\n", pressUp, pressLeft, pressDown, pressRight);

    // change character position on the map
    if (pressUp == 1 && pressDown == 0)
    {
        // move up
        yMove = -1;
    }
    else if (pressDown == 1 && pressUp == 0)
    {
        // move down
        yMove = 1;
    }

    if (pressLeft == 1 && pressRight == 0)
    {
        // move left
        xMove = -1;
    }
    else if (pressRight == 1 && pressLeft == 0)
    {
        // move right
        xMove = 1;
    }

    // update Position
    if (isSwim)
    {
        xPosNew = xPos + xMove * speed * 2;
        yPosNew = yPos + yMove * speed * 2;
    }
    else
    {
        xPosNew = xPos + xMove * speed;
        yPosNew = yPos + yMove * speed;
    }

    Character::UpdateMove(xPos, yPosNew, player2, obstacles, color_map, items, im);
    Character::UpdateMove(xPosNew, yPos, player2, obstacles, color_map, items, im);

    // update item
    for (Enhancement *item : items)
    {
        if (item->mode != None)
        {
            if (collision(xPos, yPos, width, height, item->X + 20, item->Y - 20, 40, 40))
            {
                if (item->mode == Health)
                {
                    ChangeHealth(HEAlTH_REC);
                    im = Health;
                }
                else if (item->mode == Ink)
                {
                    ChangeInk(INK_REC);
                    im = Ink;
                }
                else if (item->mode == Weapon_attack)
                {
                    im = Weapon_attack;
                }
                else if (item->mode == Weapon_painting)
                {
                    im = Weapon_painting;
                }
                item->mode = None;
            }
        }
        else
        {
            im = None;
        }
    }

    //
    // printf("%f, %f\n", xPos, yPos);
}

void Character::UpdateMove(double xPosNew, double yPosNew, Character &player2, std::vector<Obstacle *> obstacles, const GLubyte color_map[], std::vector<Enhancement *> items, Item_mode &im)
{
    bool is_update_loc = true;

    // TODO: avoid obstacle
    for (auto obstacle : obstacles)
    {
        if (!(obstacle->is_exist))
            continue;
        double bx = obstacle->X + obstacle->Dx / 2.0;
        double by = obstacle->Y - obstacle->Dy / 2.0;
        if (collision(xPosNew, yPosNew, width, height, bx, by, obstacle->Dx, obstacle->Dy))
        {
            is_update_loc = false;
        }
    }

    // check outside box
    if (OutOfBox(xPosNew, yPosNew))
    {
        is_update_loc = false;
    }

    // check collision with player
    bool collisionOld = collision(xPos, yPos, width, height, player2.xPos, player2.yPos, player2.width, player2.height);
    bool collisionNew = collision(xPosNew, yPosNew, width, height, player2.xPos, player2.yPos, player2.width, player2.height);

    if (player2.isAlive && !collisionOld && collisionNew)
    {

        is_update_loc = false;
    }

    // check in link when swimming
    if (isSwim && !CanSwim(xPosNew, yPosNew, color_map))
    {
        is_update_loc = false;
    }

    // update position
    if (is_update_loc)
    {
        xPos = xPosNew;
        yPos = yPosNew;
    }

    //
    // printf("%f, %f\n", xPos, yPos);
}

bool Character::OutOfBox(double x, double y)
{
    return x <= 0 + width / 2 || x >= 800 - width / 2 || y <= 200 + height / 2 || y >= 800 - height / 2;
}

void Character::Rotate()
{
    int pressRotate, pressRotateCounter;
    pressRotate = FsGetKeyState(keyRotate);
    pressRotateCounter = FsGetKeyState(keyRotateCounter);
    if (pressRotate == 1 && pressRotateCounter == 0)
    {
        // rotate fire direction clockwise
        theta += rotateSpeed;
    }
    else if (pressRotateCounter == 1 && pressRotate == 0)
    {
        // rotate fire direction counterclockwise
        theta -= rotateSpeed;
    }
}

void Character::Swim(const GLubyte color_map[])
{
    // TODO: Get the value of can swim from the map
    bool canSwim = CanSwim(xPos, yPos, color_map);

    if (!canSwim)
    {
        isSwim = false;
    }

    int pressSwim = FsGetKeyState(keySwim);

    // change the swim state
    if (pressSwim == 1 && !isSwim && canSwim && swimCoolTime <= 0)
    {
        isSwim = true;
        swimCoolTime = totalFireCoolTime;
    }
    else if (pressSwim == 1 && isSwim && swimCoolTime <= 0)
    {
        isSwim = false;
        swimCoolTime = totalFireCoolTime;
    }
    else if (swimCoolTime > 0)
    {
        --swimCoolTime;
    }

    // refill ink while swim
    if (isSwim)
    {
        ChangeInk(inkRecoverSpeed);
    }
}

// Trigger the fire function of the character weapon
bool Character::Fire()
{
    bool isFire = false;
    // TODO: get require ink mount for each fire from the weapon
    int pressFire = FsGetKeyState(keyFire);
    if (pressFire == 1 && fireCoolTime <= 0 && inkMount > 0 && !isSwim)
    {
        // TODO: fire at a certain angle
        isFire = true;
        fireCoolTime = totalFireCoolTime;
        ChangeInk(-fireReqInk);
    }
    else if (fireCoolTime > 0)
    {
        --fireCoolTime;
    }
    return isFire;
};

// Reborn the player
void Character::Reborn()
{
    xPos = xPosInit;
    yPos = yPosInit;
    isAlive = true;
    isSwim = false;
    health = 100.0;
    inkMount = 100.0;
};

// Change the player health
void Character::ChangeHealth(double x)
{
    if (!isAlive)
    {
        return;
    }

    double oldHealth = health;

    health += x;
    if (health > 100.0)
    {
        health = 100.0;
    }
    else if (health < 0)
    {
        deadPlayer.Stop(deadWav);
        deadPlayer.PlayOneShot(deadWav);
        deathNum++;
        health = 0.0;
        inkMount = 0.0;
        isAlive = false;
        rebornTime = totalRebornTime;
    };

    // compute
    if (health - oldHealth < 0)
    {
        takeDamage += (oldHealth - health);
    }
}

// Called when character get enhancement on the map.
void Character::Enhance(int enhanceType, double value)
{
    if (!isAlive)
    {
        return;
    }

    switch (enhanceType)
    {
        // TODO: change character state according to different enhancement.
    }
}

// Called when character get enhancement on the map.
void Character::SetColor(int r, int g, int b)
{
    colorR = r;
    colorG = g;
    colorB = b;
}

bool Character::CanSwim(double x, double y, const GLubyte color_map[])
{

    int idx = int(x) + 800 * (800 - int(y));
    int r = color_map[3 * idx];
    int g = color_map[3 * idx + 1];
    int b = color_map[3 * idx + 2];
    // printf("%d, %d, %d - %d, %d, %d\n", colorR, colorG, colorB, r, g, b);
    return int(r) == colorR && int(g) == colorG && int(b) == colorB;
};

void Character::ChangeInk(double x)
{
    inkMount += x;
    if (inkMount > 100.0)
    {
        inkMount = 100.0;
    }
    else if (inkMount < 0)
    {
        inkMount = 0;
    }
}

// void CharacterInit(int x, int y, int color)
// {
//     Character player1 = Character();
//     Character player2 = Character();
//     // set key for each player
//     const int keys1[] = {FSKEY_W, FSKEY_A, FSKEY_S, FSKEY_D, FSKEY_E, FSKEY_Q, FSKEY_R, FSKEY_F};
//     const int keys2[] = {FSKEY_I, FSKEY_J, FSKEY_K, FSKEY_L, FSKEY_O, FSKEY_U, FSKEY_P, FSKEY_SEMICOLON};
//     player1.SetKey(keys1);
//     player2.SetKey(keys2);
//     // set players initial positions
//     player1.SetPos(100, 500);
//     player2.SetPos(600, 500);
//     // play
//     while (true)
//     {
//         FsPollDevice();
//         if (FsInkey() == FSKEY_ESC)
//         {
//             return;
//         }

//         player1.Step();
//         player2.Step();

//         // Draw objects
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         player1.Draw();
//         player2.Draw();

//         glFlush();
//         FsSwapBuffers();
//         FsSleep(25);
//     }
// }