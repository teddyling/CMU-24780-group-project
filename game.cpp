#include "game.hpp"
#include "map.hpp"
#include "UI.h"
#include "character.h"
#include "fssimplewindow.h"
#include "character.h"
#include "map.hpp"
#include "weapon.h"
#include "utils.hpp"

// TODO : Pregame
Pregame_msg pregame()
{
    StartingPage startpage = StartingPage();
    PreGameUI pregameui = PreGameUI();
    Pregame_msg pregamemsg;

    int lb;
    int mb;
    int rb;
    int mx;
    int my;
    int state = 0;
    while (true)
    {
        FsPollDevice();
        if (FsInkey() == FSKEY_ESC)
        {
            break;
        }
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        int mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
        // In start page
        if (state == 0)
        {
            startpage.drawBackground();
            startpage.drawTitle();
            startpage.drawAuthor();
            startpage.drawButton();
            if (startpage.startButton->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
            {
                state = 1;
            }
            if (startpage.endButton->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
            {
                break;
            }
        }
        // In pregame UI
        if (state == 1)
        {
            pregameui.drawBackGround();
            pregameui.drawFrame();
            pregameui.drawBlock();
            pregameui.drawButton();
            pregameui.drawButtonSymbol();
            pregameui.drawChoice();
            pregameui.checkButtonClick(lb, mb, rb, mx, my, mouseEvent);
            if (pregameui.checkProceed(lb, mb, rb, mx, my, mouseEvent))
            {

                pregamemsg.color1 = (ColorType)pregameui.colorChose1p;
                pregamemsg.color2 = (ColorType)pregameui.colorChose2p;
                pregamemsg.weapon1 = (WeaponType)pregameui.weaponChose1p;
                pregamemsg.weapon2 = (WeaponType)pregameui.weaponChose2p;
                pregamemsg.map_no = pregameui.mapChose;
                return pregamemsg;
            }
        }
        FsSwapBuffers();
        FsSleep(20);
    }
}

Ingame_msg ingame(Pregame_msg msg)
{
    time_t startTime = time(NULL);

    int colorR1, colorG1, colorB1;
    int colorR2, colorG2, colorB2;
    SetColor(msg.color1, colorR1, colorG1, colorB1);
    SetColor(msg.color2, colorR2, colorG2, colorB2);
    InGameUI ingameui;

    Ingame_msg ingame_msg;
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
    player1.SetWeapon(1, msg.weapon1);
    player2.SetWeapon(2, msg.weapon2);
    // set player color
    player1.SetColor(colorR1, colorG1, colorB1);
    player2.SetColor(colorR2, colorG2, colorB2);
    // set player weapon
    std::vector<Weapon *> weapon_list1;
    weapon_list1.push_back(new Weapon_Shotgun);
    weapon_list1.push_back(new Weapon_Sniper);
    weapon_list1.push_back(new Weapon_Grenade);
    std::vector<Weapon *> weapon_list2;
    weapon_list2.push_back(new Weapon_Shotgun);
    weapon_list2.push_back(new Weapon_Sniper);
    weapon_list2.push_back(new Weapon_Grenade);
    auto weapon1 = weapon_list1[msg.weapon1];
    auto weapon2 = weapon_list2[msg.weapon2];

    weapon1->SetColor(colorR1, colorG1, colorB1);
    weapon2->SetColor(colorR2, colorG2, colorB2);

    // switch(msg.weapon1)
    // {
    //     case SHOTGUN:
    //     auto tmp = new Weapon_Shotgun;
    //     weapon1 = dynamic_cast<Weapon_Shotgun*>(weapon1);
    //     // Weapon_Shotgun weapon1;
    //     break;
    //     case SNIPER:
    //     // Weapon_Sniper weapon1;
    //     break;
    //     default:
    //     // Weapon_Grenade weapon1;
    //     break;
    // }

    // Weapon_Shotgun weapon1;
    // Weapon_Sniper weapon2;
    // Weapon_Grenade weapon3;
    // set players initial positions
    player1.SetPos(100, 500);
    player2.SetPos(600, 500);

    player1.SetFireInterval(SetFireInterval(msg.weapon1));
    player2.SetFireInterval(SetFireInterval(msg.weapon2));

    // play
    const int tmp = 800 * 600 * 3;
    int pixels[tmp];
    bool isBuffer = false;
    //GLubyte color[3 * 800 * 800];

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
            return ingame_msg;
        }

        bool isFire1 = player1.Step(player2, map, im1);
        bool isFire2 = player2.Step(player1, map, im2);
        weapon1->update(im1);
        weapon2->update(im2);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        map.draw_floor();

        if (isFire1)
        {
            printf("player 1 fire.\n");
            weapon1->Fire(player1, map.Obstacles, player2);
            // weapon1.CheckHit(player2);
        }

        if (isFire2)
        {
            printf("player 2 fire.\n");
            weapon2->Fire(player2, map.Obstacles, player1);
        }
        ingameui.player1HP = player1.health;
        ingameui.player2HP = player2.health;
        ingameui.player1Ink = player1.inkMount;
        ingameui.player2Ink = player2.inkMount;

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
        auto ratio = map.game_summary({colorR1, colorG1, colorB1}, {colorR2, colorG2, colorB2});
        printf("color1 : %f, color2 : %f\n", ratio.first, ratio.second);

        map.draw();
        player1.Draw();
        player2.Draw();

        weapon1->firePlayer.KeepPlaying();
        weapon2->firePlayer.KeepPlaying();
        player1.deadPlayer.KeepPlaying();
        player2.deadPlayer.KeepPlaying();

        ingameui.drawBarFrame();
        ingameui.drawHealthandInk();
        ingameui.drawTimer(startTime);
        if (ingameui.checkTime())
        {
            ingame_msg.color1_ratio = ratio.first;
            ingame_msg.color2_ratio = ratio.second;
            ingame_msg.death1 = player1.deathNum;
            ingame_msg.death2 = player2.deathNum;
            ingame_msg.damage1 = player2.takeDamage;
            ingame_msg.damage2 = player1.takeDamage;
            break;
        }

        glFlush();
        FsSwapBuffers();
        FsSleep(25);
    }

    return ingame_msg;
}
void postgame(Ingame_msg ingame_msg)
{
    PostGameUI postui = PostGameUI(ingame_msg.color1_ratio, ingame_msg.color2_ratio, (int)ingame_msg.damage1, (int)ingame_msg.damage2, ingame_msg.death1, ingame_msg.death2);
    while (true) {
        FsPollDevice();
        if (FsInkey() == FSKEY_ESC)
        {
            return;
        }
        postui.drawWinner();
        postui.drawStats();
    }
}
// Ingame_msg ingame(Pregame_msg msg)
// {

//     // // Initialize
//     // InGameUI ingameui = InGameUI();
//     // Map map(w, h, msg.map_no);
//     // loc1, loc2 = map.give_born_location();
//     // Character player1 = Character(msg.color1, loc1);
//     // Character player2 = Character(msg.color2, loc2);
//     // Weapon weapon1 = Weapon(msg.weapon1, loc1, weapon_select1);
//     // Weapon weapon2 = Weapon(msg.weapon2, loc2, weapon_select2);

//     // while (true)
//     // {
//     //     // take keyboard input
//     //     FsPollDevice();
//     //     if (FsInkey() == FSKEY_ESC)
//     //     {
//     //         break;
//     //     }

//     //     // step1 : draw floor & update floor
//     //     map.draw_painting();
//     //     // 1. based on bit map draw previous painting distribution
//     //     // 2. based on new paintings, draw new bullet painting

//     //     // Frame update routine
//     //     color1 = map.get_color(player1.loc);
//     //     color2 = map.get_color(player2.loc);

//     //     // player take action
//     //     isfire1 = player1.Step(player2.loc, color1, map.Obstacles, map.items)
//     //     isfire2 = player2.Step(player1.loc, color2, map.Obstacles, map.items)

//     //     if (isfire1) {
//     //         // draw painting
//     //         //modify element
//     //         weapon1.fire(player1);
//     //         bullet_line1 = weapon1.check_hit(player2, map.Obstacles);
//     //         map.update_painting(bullet_line1);
//     //     }

//     //     if (isfire2) {
//     //         weapon2.fire(player2);
//     //         bullet_line2 = weapon2.check_hit(player2, map.Obstacles);
//     //         map.update_painting(bullet_line2);
//     //     }
//     //     //需要一个血量和墨量的传参

//     //     // draw
//     //     map.draw();
//     //     character1.draw();
//     //     character2.draw();
//     //     ingameui.drawBarFrame();
//     //     ingameui.drawTimer();
//     //     ingameui.drawHealthandInk();
//     //     if (ingameui.checkTime()) {
//     //         // go to postgame;
//     //     }

//     //     //Frame update routine end

//     // }
// }