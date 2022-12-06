// Author: Shiqi Liu
#ifndef character_hpp
#define character_hpp

#include <vector>
#include "map.hpp"
#include "utils.hpp"
#include "yssimplesound.h"

class Character
{
protected:
    YsRawPngDecoder playerPng;
    GLuint playerTexture;
    YsRawPngDecoder playerSwimPng;
    GLuint playerSwimTexture;
    int colorR, colorG, colorB;
    int orientation;
    double speed;
    double rotateSpeed;
    double fireReqInk;
    double inkRecoverSpeed;
    double drawCharacterSize, drawSplashSize;
    int keyUp, keyDown, keyLeft, keyRight, keyFire, keySwim, keyRotate, keyRotateCounter;

    int rebornTime;
    int totalRebornTime;
    int fireCoolTime;
    int totalFireCoolTime;
    int swimCoolTime;
    int totalSwimCoolTime;

    void Move(Character &player2, std::vector<Obstacle *> obstacle, const GLubyte[], std::vector<Enhancement *> &items, Item_mode &im);
    void UpdateMove(double xNew, double yNew, Character &player2, std::vector<Obstacle *> obstacle, const GLubyte[], std::vector<Enhancement *> items, Item_mode &im);
    void Rotate();
    bool Fire();
    void Swim(const GLubyte color_map[]);
    void Reborn();
    bool OutOfBox(double x, double y);
    bool CanSwim(double x, double y, const GLubyte[]);
    void ChangeInk(double x);
    void SetSplash();

public:
    double xPos, yPos;
    double xPosInit, yPosInit;
    double theta;
    double width, height;
    bool isAlive, isSwim;
    double inkMount;
    double health;
    double takeDamage;
    int deathNum;
    YsSoundPlayer deadPlayer;
    YsSoundPlayer::SoundData deadWav;
    Character();
    bool Step(Character &player2, Map &map, Item_mode &im);
    bool Step(Character &player2, Map &map);
    void Draw();
    void SetKey(const int[]);
    void SetPos(double x, double y, double t);
    void SetColor(int r, int g, int b);
    void ChangeHealth(double x);
    void Enhance(int type, double value);
    void SetWeapon(int playerId, WeaponType weaponType);
    void SetFireInterval(int x);
};

#endif

// void CharacterInit(int color, int xInitPos, int yInitPos)
// {

// }