#include <math.h>
#include <iostream>
#include "yssimplesound.h"
#include "fssimplewindow.h"
#include "character.h"
#include "map.hpp"

class Weapon
{
public:
	double current_time;
	int weapon_x, weapon_y;
	int rival_x, rival_y;
	int oriental_angle;
	int ink_num;
	int obstacle_pos;
	int fire_flag;

	int attack_speed;
	int shooting_range;
	int ink_consumption;

	YsSoundPlayer firePlayer;
	YsSoundPlayer::SoundData wav;

	virtual void Fire(Character &player1, std::vector<Obstacle *> &obstacle, Character &enemy){};
	virtual void SetColor(int r, int g, int b){};
	virtual void update(Item_mode im){};

	// virtual void Hit(Character &player, vector<Obstacle *> &obs);

	Weapon(){};
	~Weapon(){};
};

class Weapon_Shotgun : public Weapon
{
public:
	double radius = 100;
	double range = 120;
	double attack_power = 30.0;
	int shotgun_color[3];
	void Fire(Character &player1, std::vector<Obstacle *> &obstacle, Character &enemy);
	void Hit(Character &player, vector<Obstacle *> &obstacle, Character &enemy);
	void update(Item_mode im);
	void SetColor(int r, int g, int b);

	void Draw_Weapon(int weapon_x, int weapon_y, int oriental_angle);
	void Draw_Fire_Line(int weapon_x, int weapon_y, int oriental_angle);
	int Check_Hit(int weapon_x, int weapon_y, int oriental_angle, int rival_x, int rival_y);
	void Paint_Board(int weapon_x, int weapon_y, int oriental_angle);
	
	
	Weapon_Shotgun()
	{
		firePlayer.MakeCurrent();
		firePlayer.Start();
		if (YSOK != wav.LoadWav("music/shotgun_fire.wav"))
		{
			printf("Can not find shotgun_fire.wav\n");
		}
	};
	~Weapon_Shotgun(){};
};

class Weapon_Sniper : public Weapon
{
public:
	double attack_power = 75.0;
	double sniper_x;
	double sniper_y;
	double sniper_paint_width = 10.0;
	double sniper_radius = 40.0;
	int sniper_color[3];
	void Fire(Character &player1, std::vector<Obstacle *> &obstacle, Character &enemy);
	void Hit(Character &player, vector<Obstacle *> &obs, Character &enemy);
	void update(Item_mode im);
	void SetColor(int r, int g, int b);

	void Draw_Weapon(int weapon_x, int weapon_y, int oriental_angle);
	void Draw_Fire_Line(int weapon_x, int weapon_y, int oriental_angle);
	int Check_Hit(int weapon_x, int weapon_y, int oriental_angle, int rival_x, int rival_y);
	void Paint_Board(int weapon_x, int weapon_y, int oriental_angle);

	Weapon_Sniper(){
		firePlayer.MakeCurrent();
		firePlayer.Start();
		if (YSOK != wav.LoadWav("music/sniper_fire.wav"))
		{
			printf("Can not find sniper_fire.wav\n");
		}
	};
	~Weapon_Sniper(){};
};

class Weapon_Grenade : public Weapon
{
public:
	double explosion_radius = 100.0;
	double grenade_maximum_distance = 200.0;
	double attack_power = 30.0;
	double grenade_x;
	double grenade_y;
	int grenade_color[3];
	void Fire(Character &player1, std::vector<Obstacle *> &obstacle, Character &enemy);
	void Hit(Character &player, vector<Obstacle *> &obs, Character &enemy);
	void update(Item_mode im);
	void SetColor(int r, int g, int b);

	void Draw_Weapon(int weapon_x, int weapon_y, int oriental_angle);
	void Draw_Fire_Line(int weapon_x, int weapon_y, int oriental_angle);
	int Check_Hit(int weapon_x, int weapon_y, int oriental_angle, int rival_x, int rival_y);
	void Paint_Board(int weapon_x, int weapon_y, int oriental_angle);

	Weapon_Grenade(){
		firePlayer.MakeCurrent();
		firePlayer.Start();
		if (YSOK != wav.LoadWav("music/grenade_fire.wav"))
		{
			printf("Can not find grenade_fire.wav\n");
		}
	};
	~Weapon_Grenade(){};
};

class Weapon_SMG : public Weapon
{
public:
	void Draw_Weapon(int weapon_x, int weapon_y, int oriental_angle);
	void Draw_Fire_Line(int weapon_x, int weapon_y, int oriental_angle);
	int Check_Hit(int weapon_x, int weapon_y, int oriental_angle, int rival_x, int rival_y);
	void Paint_Board(int weapon_x, int weapon_y, int oriental_angle);

	Weapon_SMG(){};
	~Weapon_SMG(){};
};

bool is_in_semi_sphere(double center_x, double center_y, double radius, double orientation, double scale, double tar_x, double tar_y);
bool is_within_line(double center_x, double center_y, double orientation, double tar_x, double tar_y, double th);
float get_angle(pair<double, double> v1, pair<double, double> v2);