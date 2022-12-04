#include "character.h"
#include "weapon.h"
#include "fssimplewindow.h"
#include <math.h>

const double PI = 3.1415927;
double angle = 0.0;
int i;

double abso(double origin)
{
    if (origin >= 0)
    {
        return origin;
    }
    else
    {
        return -origin;
    }
}

float get_angle(pair<double, double> v1, pair<double, double> v2)
{
    return abso(atan2(v2.second, v2.first) - atan2(v1.second, v1.first));
}

double point_to_point_distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

int calculate_quadrant(double x1, double y1, double x2, double y2)
{
    if (x2 >= x1 && y2 >= y1)
    {
        return 1;
    }
    if (x2 < x1 && y2 >= y1)
    {
        return 2;
    }
    if (x2 < x1 && y2 < y1)
    {
        return 3;
    }
    if (x2 >= x1 && y2 < y1)
    {
        return 4;
    }
    return 0;
}

void Weapon_Shotgun::SetColor(int r, int g, int b)
{
    shotgun_color[0] = r;
    shotgun_color[1] = g;
    shotgun_color[2] = b;
}

void Weapon_Sniper::SetColor(int r, int g, int b)
{
    sniper_color[0] = r;
    sniper_color[1] = g;
    sniper_color[2] = b;
}

void Weapon_Grenade::SetColor(int r, int g, int b)
{
    grenade_color[0] = r;
    grenade_color[1] = g;
    grenade_color[2] = b;
}

void Weapon_Sniper::Fire(Character &Player1, std::vector<Obstacle *> &obstacles, Character &enemy)
{
    firePlayer.Stop(wav);
    firePlayer.PlayOneShot(wav);
    printf("sniper get fire call\n");
    Hit(Player1, obstacles, enemy);
    glColor3ub(sniper_color[0], sniper_color[1], sniper_color[2]);
    glLineWidth(sniper_paint_width);
    glBegin(GL_LINES);
    glVertex2d(Player1.xPos, Player1.yPos);
    glVertex2d(sniper_x, sniper_y);
    glEnd();
    glBegin(GL_POLYGON);
    for (i = 0; i < 36; i++)
    {
        glVertex2d(Player1.xPos + sniper_radius * cos(i * PI / 18), Player1.yPos + sniper_radius * sin(i * PI / 18));
    }
    glEnd();
}

void Weapon_Sniper::update(Item_mode im)
{
    if (im == Weapon_attack)
    {
        attack_power *= 1.5;
    }
    if (im == Weapon_painting)
    {
        sniper_radius *= 1.5;
    }
}

void Weapon_Shotgun::Fire(Character &Player1, std::vector<Obstacle *> &obstacle, Character &enemy)
{
    firePlayer.Stop(wav);
    firePlayer.PlayOneShot(wav);
    printf("shotgun get fire call\n");
    Hit(Player1, obstacle, enemy);
    double shotgun_angle = 120.0 * PI / 180.0;
    double shotgun_radius = 100.0;
    double shotgun_start_angle = Player1.theta * PI / 180.0 - shotgun_angle / 2.0;
    glColor3ub(shotgun_color[0], shotgun_color[1], shotgun_color[2]);
    glBegin(GL_POLYGON);
    glVertex2d(Player1.xPos, Player1.yPos);
    for (i = 0; i < 20; i++)
    {
        glVertex2d(Player1.xPos + shotgun_radius * cos(shotgun_start_angle + i * shotgun_angle / 20.0), Player1.yPos + shotgun_radius * sin(shotgun_start_angle + i * shotgun_angle / 20.0));
    }
    glEnd();
}

void Weapon_Shotgun::update(Item_mode im)
{
    if (im == Weapon_attack)
    {
        attack_power *= 1.5;
    }
    if (im == Weapon_painting)
    {
        radius *= 1.5;
    }
}

void Weapon_Grenade::Fire(Character &Player1, std::vector<Obstacle *> &obstacle, Character &enemy)
{
    firePlayer.Stop(wav);
    firePlayer.PlayOneShot(wav);
    printf("grenade get fire call\n");

    Hit(Player1, obstacle, enemy);
    angle = (Player1.theta * PI) / 180.0;
    glColor3ub(grenade_color[0], grenade_color[1], grenade_color[2]);
    glBegin(GL_POLYGON);
    for (i = 0; i < 36; i++)
    {
        glVertex2d(grenade_x + explosion_radius * cos(i * PI / 18), grenade_y + explosion_radius * sin(i * PI / 18));
    }
    glEnd();
}

void Weapon_Grenade::update(Item_mode im)
{
    if (im == Weapon_attack)
    {
        attack_power *= 1.5;
    }
    if (im == Weapon_painting)
    {
        explosion_radius *= 1.5;
    }
}

void Weapon_Shotgun::Hit(Character &player, vector<Obstacle *> &obs, Character &enemy)
{
    // hit Obstacle check
    int hit_num = 0;
    for (Obstacle *b : obs)
    {

        if (b->is_exist == false)
            continue;
        if (is_in_semi_sphere(player.xPos, player.yPos, radius, player.theta, range, b->X + 0.5 * b->Dx, b->Y - 0.5 * b->Dy))
        {
            hit_num++;
            if (b->endurance != -1)
            {
                b->endurance--;
                if (b->endurance == 0)
                {
                    b->is_exist = false;
                }
            }
        }
    }
    // hit enemy check
    if (is_in_semi_sphere(player.xPos, player.yPos, radius + player.width, player.theta, range, enemy.xPos, enemy.yPos))
    {
        printf("hit enemy\n");
        enemy.ChangeHealth(-attack_power);
    }
}

void Weapon_Sniper::Hit(Character &player, vector<Obstacle *> &multi_obs, Character &enemy)
{
    double min_dist = 10000;
    Obstacle *closest_box = nullptr;
    for (Obstacle *box : multi_obs)
    {
        if (box->is_exist == false)
            continue;
        if (is_within_line(player.xPos, player.yPos, player.theta, box->X + box->Dx / 2., box->Y - box->Dy / 2., 25.0))
        {
            double dist = point_to_point_distance(player.xPos, player.yPos, box->X, box->Y);
            if (dist < min_dist)
            {
                closest_box = box;
                min_dist = dist;
            }
        }
    }
    if (is_within_line(player.xPos, player.yPos, player.theta, enemy.xPos, enemy.yPos, 15))
    {
        double ch_dist = point_to_point_distance(player.xPos, player.yPos, enemy.xPos, enemy.yPos);
        if (ch_dist < min_dist)
        {
            closest_box = nullptr;
            sniper_x = enemy.xPos;
            sniper_y = enemy.yPos;
            printf("hit enemy\n");
            // TODO: enemy get life loss
            enemy.ChangeHealth(-attack_power);
        }
    }

    if (closest_box != nullptr)
    {
        sniper_x = closest_box->X + closest_box->Dx / 2.;
        sniper_y = closest_box->Y - closest_box->Dy / 2.;
        if (closest_box->endurance != -1)
        {
            (closest_box->endurance)--;
            if (closest_box->endurance == 0)
            {
                closest_box->is_exist = false;
            }
        }
    }
    else
    {
        double angle = (player.theta * PI) / 180.0;
        sniper_x = player.xPos + 2000 * cos(angle);
        sniper_y = player.yPos + 2000 * sin(angle);
    }
}

void Weapon_Grenade::Hit(Character &player, vector<Obstacle *> &multi_obs, Character &enemy)
{
    double min_dist = 10000;
    Obstacle *closest_box = nullptr;
    double ch_dist = point_to_point_distance(player.xPos, player.yPos, enemy.xPos, enemy.yPos);
    for (Obstacle *box : multi_obs)
    {
        if (box->is_exist == false)
            continue;
        if (is_within_line(player.xPos, player.yPos, player.theta, box->X + box->Dx / 2., box->Y - box->Dy / 2., 25.0))
        {
            double dist = point_to_point_distance(player.xPos, player.yPos, box->X, box->Y);
            if (dist < min_dist)
            {
                closest_box = box;
                min_dist = dist;
            }
        }
    }
    if (is_within_line(player.xPos, player.yPos, player.theta, enemy.xPos, enemy.yPos, 15))
    {

        if (ch_dist < min_dist && ch_dist <= grenade_maximum_distance)
        {
            grenade_x = enemy.xPos;
            grenade_y = enemy.yPos;
            closest_box = nullptr;
            printf("hit enemy\n");
            // TODO: enemy get life loss
            enemy.ChangeHealth(-attack_power);

            // if hit enemy: near obstacles disappear
            for (Obstacle *box : multi_obs)
            {
                if (box->is_exist == false)
                {
                    continue;
                }
                if (point_to_point_distance(enemy.xPos, enemy.yPos, box->X + box->Dx / 2., box->Y - box->Dy / 2.) < explosion_radius)
                {
                    if (box->endurance != -1)
                    {
                        box->endurance--;
                        if (box->endurance == 0)
                        {
                            box->is_exist = false;
                        }
                    }
                }
            }
        }
    }

    if (closest_box != nullptr && min_dist <= grenade_maximum_distance)
    {
        grenade_x = closest_box->X + closest_box->Dx / 2.;
        grenade_y = closest_box->Y - closest_box->Dy / 2.;
        if (closest_box->endurance != -1)
        {
            (closest_box->endurance)--;
            if (closest_box->endurance == 0)
            {
                closest_box->is_exist = false;
                // enemy and obstacles near closest box disappear of get damage
                for (Obstacle *box : multi_obs)
                {
                    if (box->is_exist == false)
                    {
                        continue;
                    }
                    if (point_to_point_distance(closest_box->X + closest_box->Dx / 2., closest_box->Y - closest_box->Dy / 2., box->X + box->Dx / 2., box->Y - box->Dy / 2.) < explosion_radius)
                    {
                        if (box->endurance != -1)
                        {
                            box->endurance--;
                            if (box->endurance == 0)
                            {
                                box->is_exist = false;
                            }
                        }
                    }
                    if (point_to_point_distance(enemy.xPos, enemy.yPos, closest_box->X + closest_box->Dx / 2., closest_box->Y - closest_box->Dy / 2.) < explosion_radius)
                    {
                        // enemy get life loss
                        printf("hit enemy\n");
                        enemy.ChangeHealth(-attack_power);
                    }
                }
            }
        }
    }
    // no enemy or obstacles within grenade maximum distance
    // if (min_dist > grenade_maximum_distance && ch_dist > grenade_maximum_distance)
    else
    {
        double angle = (player.theta * PI) / 180.0;
        grenade_x = player.xPos + grenade_maximum_distance * cos(angle);
        grenade_y = player.yPos + grenade_maximum_distance * sin(angle);
        if (grenade_x < 0)
        {
            grenade_x = 0;
        }
        if (grenade_x > 800)
        {
            grenade_x = 800;
        }
        if (grenade_y < 200)
        {
            grenade_y = 200;
        }
        if (grenade_y > 800)
        {
            grenade_y = 800;
        }

        // obstacles and enemy near maximum distance point damage/disappear
        for (Obstacle *box : multi_obs)
        {
            if (box->is_exist == false)
            {
                continue;
            }
            if (point_to_point_distance(grenade_x, grenade_y, box->X + box->Dx / 2., box->Y - box->Dy / 2.) < explosion_radius)
            {
                if (box->endurance != -1)
                {
                    box->endurance--;
                    if (box->endurance == 0)
                    {
                        box->is_exist = false;
                    }
                }
            }
        }
        if (point_to_point_distance(enemy.xPos, enemy.yPos, grenade_x, grenade_y) < explosion_radius)
        {
            // enemy get life loss
            enemy.ChangeHealth(-attack_power);
        }
    }
}

// bool is_in_semi_sphere(double center_x, double center_y, double radius, double orientation, double scale, double tar_x, double tar_y);
bool is_within_line(double center_x, double center_y, double orientation, double tar_x, double tar_y, double threshold)
{
    double angle = 0.0;
    angle = (orientation * PI) / 180.0;
    double x1 = center_x;
    double y1 = center_y;
    double x2 = center_x + 200 * cos(angle);
    double y2 = center_y + 200 * sin(angle);
    double x3 = tar_x;
    double y3 = tar_y;
    double angle_bet = get_angle({x3 - x1, y3 - y1}, {x2 - x1, y2 - y1});
    if (angle_bet > PI / 2)
    {
        return false;
    }
    double distance = 0.0;
    double A = y2 - y1;
    double B = x1 - x2;
    double C = x2 * y1 - x1 * y2;
    distance = abso(A * x3 + B * y3 + C) / point_to_point_distance(A, B, 0, 0);
    // printf("x1: %f, y1: %f, x2: %f, y2 : %f, x3 : %f, y3 : %f, %f / %f  distance : %f, threshold : %f\n", x1, y1, x2, y2, x3, y3, abso(A * x3 + B * y3 + C), point_to_point_distance(A, B, 0, 0), distance, threshold);
    if (distance < threshold)
    {
        return true;
    }
    return false;
}

bool is_in_semi_sphere(double center_x, double center_y, double radius, double orientation, double scale, double tar_x, double tar_y)
{
    if (point_to_point_distance(center_x, center_y, tar_x, tar_y) < radius)
    {
        if (abso(atan2(tar_y - center_y, tar_x - center_x) / PI * 180. - orientation) < scale / 2)
        {
            return true;
        }
    }
    return false;
}
