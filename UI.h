#include <stdio.h>
#include <math.h>
#include <string>
#include <time.h>
#include <iomanip>
#include <sstream>

using namespace std;

#include "fssimplewindow.h"
#include "ysglfontdata.h"

class Button {
public:
	int x;
	int y;
	int sizeX;
	int sizeY;
	Button(int x, int y, int sizeX, int sizeY);
	void draw(int r, int g, int b);
	int checkButtonClick(int lb, int mb, int rb, int mx, int my, int mouseEvent);
};

class StartingPage {
public:
	Button* startButton = new Button(100, 650, 250, 100);
	Button* endButton = new Button(450, 650, 250, 100);
	StartingPage() {};
	void drawButton();
	void drawTitle();
	void drawAuthor();
	void drawBackground();
};

class PreGameUI {
public:
	int colorChose1p = 0;
	int colorChose2p = 0;
	int weaponChose1p = 0;
	int weaponChose2p = 0;
	int mapChose = 0;
	Button* weaponLeft1p = new Button(50, 180, 40, 60);
	Button* weaponRight1p = new Button(290, 180, 40, 60);
	Button* weaponLeft2p = new Button(450, 180, 40, 60);
	Button* weaponRight2p = new Button(690, 180, 40, 60);
	Button* colorLeft1p = new Button(50, 330, 40, 60);
	Button* colorRight1p = new Button(290, 330, 40, 60);
	Button* colorLeft2p = new Button(450, 330, 40, 60);
	Button* colorRight2p = new Button(690, 330, 40, 60);
	Button* mapLeft = new Button(270, 570, 40, 60);
	Button* mapRight = new Button(510, 570, 40, 60);
	Button* fight = new Button(290, 700, 240, 70);
	string weaponChoices[4] = { "Shotgun", "Sniper", "Grenade"};
	string colorChoices[6] = { "Red", "Orange", "Yellow","Green", "Blue", "Purple" };
	string mapChoices[4] = { "1", "2", "3" };
	PreGameUI() {};
	void drawBackGround();
	void drawFrame();
	void drawButton();
	void drawBlock();
	void drawChoice();
	void drawButtonSymbol();
	void checkButtonClick(int lb, int mb, int rb, int mx, int my, int mouseEvent);
	int checkProceed(int lb, int mb, int rb, int mx, int my, int mouseEvent);
};

class InGameUI {
public:
	int player1HP = 100;
	int player1Ink = 100;
	int player2HP = 100;
	int player2Ink = 100;
	int gameTime = 20;
	int timeLeft;
	InGameUI() {};
	void drawBarFrame();
	void drawTimer(int startTime);
	void drawHealthandInk();
	int checkTime();
};

class PostGameUI {
public:
	double p1Ratio;
	double p2Ratio;
	int p1Demage;
	int p2Demage;
	PostGameUI(double p1r, double p2r, int p1d, int p2d);

	void drawWinner();
	void drawStats();
};
