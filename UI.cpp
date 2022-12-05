#include <stdio.h>
#include <math.h>
#include <string>
#include <time.h>
#include <iomanip>
#include <sstream>
using namespace std;
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "UI.h"

/// Button class //////////////////////
Button::Button(int x, int y, int sizeX, int sizeY)
{
	this->x = x;
	this->y = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
};
void Button::draw(int r, int g, int b)
{
	glColor3ub(r, g, b);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + sizeX, y);
	glVertex2i(x + sizeX, y + sizeY);
	glVertex2i(x, y + sizeY);
	glEnd();
	glColor3ub(0, 0, 0);
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x, y);
	glVertex2i(x + sizeX, y);
	glVertex2i(x + sizeX, y + sizeY);
	glVertex2i(x, y + sizeY);
	glEnd();
	glLineWidth(1.0f);
}
int Button::checkButtonClick(int lb, int mb, int rb, int mx, int my, int mouseEvent)
{
	if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN && mx >= this->x && mx <= this->x + this->sizeX && my >= this->y && my <= this->y + this->sizeY)
	{
		return 1;
	}
	return 0;
}

//////////Starting Page /////////////////////////////////////
void StartingPage::drawButton()
{
	startButton->draw(255, 0, 0);
	glColor3ub(0, 0, 0);
	glRasterPos2d(150, 730);
	YsGlDrawFontBitmap32x48("START");
	endButton->draw(255, 0, 0);
	glRasterPos2d(510, 730);
	YsGlDrawFontBitmap32x48("QUIT");
}
void StartingPage::drawTitle()
{
	glColor3ub(0, 0, 255);
	glRasterPos2d(310, 100);
	YsGlDrawFontBitmap32x48("PAINT");
	glRasterPos2d(350, 200);
	YsGlDrawFontBitmap32x48("OR");
	glRasterPos2d(340, 300);
	YsGlDrawFontBitmap32x48("DIE");
}
void StartingPage::drawAuthor()
{
	glColor3ub(0, 0, 0);
	glRasterPos2d(60, 500);
	YsGlDrawFontBitmap24x40("Presented By Team WHATEVER");
}
void StartingPage::drawBackground()
{
	glColor3ub(229, 255, 204);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(800, 0);
	glVertex2i(800, 267);
	glVertex2i(0, 267);
	glEnd();
	glColor3ub(204, 255, 204);
	glBegin(GL_QUADS);
	glVertex2i(0, 267);
	glVertex2i(800, 267);
	glVertex2i(800, 267 * 2);
	glVertex2i(0, 267 * 2);
	glEnd();
	glColor3ub(204, 255, 229);
	glBegin(GL_QUADS);
	glVertex2i(0, 267 * 2);
	glVertex2i(800, 267 * 2);
	glVertex2i(800, 800);
	glVertex2i(0, 800);
	glEnd();
}

///////////// PreGame UI ///////////////////////////
void PreGameUI::drawBackGround()
{
	glColor3ub(229, 255, 204);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(800, 0);
	glVertex2i(800, 267);
	glVertex2i(0, 267);
	glEnd();
	glColor3ub(204, 255, 204);
	glBegin(GL_QUADS);
	glVertex2i(0, 267);
	glVertex2i(800, 267);
	glVertex2i(800, 267 * 2);
	glVertex2i(0, 267 * 2);
	glEnd();
	glColor3ub(204, 255, 229);
	glBegin(GL_QUADS);
	glVertex2i(0, 267 * 2);
	glVertex2i(800, 267 * 2);
	glVertex2i(800, 800);
	glVertex2i(0, 800);
	glEnd();
}
void PreGameUI::drawFrame()
{
	glColor3ub(0, 0, 0);
	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2i(400, 0);
	glVertex2i(400, 440);
	glVertex2i(0, 440);
	glVertex2i(800, 440);
	glEnd();
	glLineWidth(1.0f);
	glColor3ub(0, 0, 255);
	glRasterPos2d(150, 60);
	YsGlDrawFontBitmap32x48("1P");
	glColor3ub(255, 0, 0);
	glRasterPos2d(550, 60);
	YsGlDrawFontBitmap32x48("2P");
	glColor3ub(102, 51, 0);
	glRasterPos2d(130, 160);
	YsGlDrawFontBitmap20x28("Weapon");
	glColor3ub(102, 51, 0);
	glRasterPos2d(530, 160);
	YsGlDrawFontBitmap20x28("Weapon");
	glColor3ub(102, 0, 204);
	glRasterPos2d(540, 300);
	YsGlDrawFontBitmap20x28("Color");
	glRasterPos2d(140, 300);
	YsGlDrawFontBitmap20x28("Color");
	glColor3ub(0, 0, 0);
	glColor3ub(0, 0, 0);
	glRasterPos2d(370, 550);
	YsGlDrawFontBitmap28x44("MAP");
}
void PreGameUI::drawButton()
{
	weaponLeft1p->draw(224, 224, 224);
	weaponRight1p->draw(224, 224, 224);
	weaponLeft2p->draw(224, 224, 224);
	weaponRight2p->draw(224, 224, 224);
	colorLeft1p->draw(224, 224, 224);
	colorRight1p->draw(224, 224, 224);
	colorLeft2p->draw(224, 224, 224);
	colorRight2p->draw(224, 224, 224);
	mapLeft->draw(224, 224, 224);
	mapRight->draw(224, 224, 224);
	fight->draw(255, 128, 0);
}
void PreGameUI::drawBlock()
{
	glColor3ub(0, 0, 0);
	// 1P Weapon
	glBegin(GL_LINE_LOOP);
	glVertex2i(100, 180);
	glVertex2i(280, 180);
	glVertex2i(280, 240);
	glVertex2i(100, 240);
	glEnd();
	// 1P Color
	glBegin(GL_LINE_LOOP);
	glVertex2i(100, 330);
	glVertex2i(280, 330);
	glVertex2i(280, 390);
	glVertex2i(100, 390);
	glEnd();
	// 2P Weapon
	glBegin(GL_LINE_LOOP);
	glVertex2i(500, 180);
	glVertex2i(680, 180);
	glVertex2i(680, 240);
	glVertex2i(500, 240);
	glEnd();
	// 2P Color
	glBegin(GL_LINE_LOOP);
	glVertex2i(500, 330);
	glVertex2i(680, 330);
	glVertex2i(680, 390);
	glVertex2i(500, 390);
	glEnd();
	// Map Choice
	glBegin(GL_LINE_LOOP);
	glVertex2i(320, 570);
	glVertex2i(500, 570);
	glVertex2i(500, 630);
	glVertex2i(320, 630);
	glEnd();
}
void PreGameUI::drawChoice()
{
	const char *weapon1p = weaponChoices[weaponChose1p].c_str();
	glColor3ub(0, 0, 0);
	glRasterPos2d(110, 235);
	YsGlDrawFontBitmap24x40(weapon1p);
	const char *weapon2p = weaponChoices[weaponChose2p].c_str();
	glColor3ub(0, 0, 0);
	glRasterPos2d(510, 235);
	YsGlDrawFontBitmap24x40(weapon2p);
	const char *color1p = colorChoices[colorChose1p].c_str();
	glColor3ub(0, 0, 0);
	glRasterPos2d(115, 385);
	YsGlDrawFontBitmap24x40(color1p);
	const char *color2p = colorChoices[colorChose2p].c_str();
	glColor3ub(0, 0, 0);
	glRasterPos2d(515, 385);
	YsGlDrawFontBitmap24x40(color2p);
	const char *map = mapChoices[mapChose].c_str();
	glColor3ub(0, 0, 0);
	glRasterPos2d(400, 625);
	YsGlDrawFontBitmap24x40(map);
}
void PreGameUI::drawButtonSymbol()
{
	glColor3ub(0, 0, 0);
	glRasterPos2d(58, 235);
	YsGlDrawFontBitmap32x48("<");
	glRasterPos2d(298, 235);
	YsGlDrawFontBitmap32x48(">");
	glRasterPos2d(458, 235);
	YsGlDrawFontBitmap32x48("<");
	glRasterPos2d(698, 235);
	YsGlDrawFontBitmap32x48(">");
	glRasterPos2d(58, 385);
	YsGlDrawFontBitmap32x48("<");
	glRasterPos2d(298, 385);
	YsGlDrawFontBitmap32x48(">");
	glRasterPos2d(458, 385);
	YsGlDrawFontBitmap32x48("<");
	glRasterPos2d(698, 385);
	YsGlDrawFontBitmap32x48(">");
	glRasterPos2d(278, 625);
	YsGlDrawFontBitmap32x48("<");
	glRasterPos2d(518, 625);
	YsGlDrawFontBitmap32x48(">");
	glRasterPos2d(302, 760);
	YsGlDrawFontBitmap32x48("FIGHT!!");
}
void PreGameUI::checkButtonClick(int lb, int mb, int rb, int mx, int my, int mouseEvent)
{
	if (weaponLeft1p->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
	{
		if (weaponChose1p == 0)
		{
			weaponChose1p = 2;
		}
		else
		{
			weaponChose1p--;
		}
	}
	else if (weaponRight1p->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
	{
		weaponChose1p++;
		weaponChose1p %= 3;
	}
	else if (weaponLeft2p->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
	{
		if (weaponChose2p == 0)
		{
			weaponChose2p = 2;
		}
		else
		{
			weaponChose2p--;
		}
	}
	else if (weaponRight2p->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
	{
		weaponChose2p++;
		weaponChose2p %= 3;
	}
	else if (colorLeft1p->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
	{
		if (colorChose1p == 0)
		{
			colorChose1p = 5;
		}
		else
		{
			colorChose1p--;
		}
	}
	else if (colorRight1p->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
	{
		colorChose1p++;
		colorChose1p %= 6;
	}
	else if (colorLeft2p->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
	{
		if (colorChose2p == 0)
		{
			colorChose2p = 5;
		}
		else
		{
			colorChose2p--;
		}
	}
	else if (colorRight2p->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
	{
		colorChose2p++;
		colorChose2p %= 6;
	}
	else if (mapLeft->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
	{
		if (mapChose == 0)
		{
			mapChose = 2;
		}
		else
		{
			mapChose--;
		}
	}
	else if (mapRight->checkButtonClick(lb, mb, rb, mx, my, mouseEvent))
	{
		mapChose++;
		mapChose %= 3;
	}
}
int PreGameUI::checkProceed(int lb, int mb, int rb, int mx, int my, int mouseEvent)
{
	if (colorChose1p == colorChose2p) {
		isSameColor = true;
	}
	if (fight->checkButtonClick(lb, mb, rb, mx, my, mouseEvent) && !isSameColor)
	{
		return 1;
	}
	return 0;
}

////////////// InGame UI ///////////////////////////////////
void InGameUI::drawBarFrame()
{
	// 1p HP
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(60, 25);
	glVertex2i(310, 25);
	glVertex2i(310, 55);
	glVertex2i(60, 55);
	glEnd();
	// 1p Ink
	glBegin(GL_LINE_LOOP);
	glVertex2i(60, 75);
	glVertex2i(310, 75);
	glVertex2i(310, 105);
	glVertex2i(60, 105);
	glEnd();
	// 2p HP
	glBegin(GL_LINE_LOOP);
	glVertex2i(490, 25);
	glVertex2i(740, 25);
	glVertex2i(740, 55);
	glVertex2i(490, 55);
	glEnd();
	// 2p Ink
	glBegin(GL_LINE_LOOP);
	glVertex2i(490, 75);
	glVertex2i(740, 75);
	glVertex2i(740, 105);
	glVertex2i(490, 105);
	glEnd();
	glColor3ub(204, 0, 0);
	glRasterPos2d(10, 55);
	YsGlDrawFontBitmap20x28("HP");
	glColor3ub(0, 0, 204);
	glRasterPos2d(5, 100);
	YsGlDrawFontBitmap16x24("INK");
	glColor3ub(204, 0, 0);
	glRasterPos2d(750, 55);
	YsGlDrawFontBitmap20x28("HP");
	glColor3ub(0, 0, 204);
	glRasterPos2d(745, 100);
	YsGlDrawFontBitmap16x24("INK");
}
void InGameUI::drawTimer(int startTime)
{
	time_t currTime = time(NULL);

	timeLeft = gameTime - (currTime - startTime);
	auto s = std::to_string(timeLeft);
	// const char* timeInChar = s.c_str();
	const char *timeInChar;
	if (timeLeft == 0)
	{
		glColor3ub(0, 0, 0);
		glRasterPos2d(250, 300);
		timeInChar = "Time's up";
	}
	else
	{
		glColor3ub(0, 0, 0);
		glRasterPos2d(375, 80);
		timeInChar = s.c_str();
	}
	YsGlDrawFontBitmap32x48(timeInChar);
}
void InGameUI::drawHealthandInk()
{
	double player1HPConv = ((double)player1HP / 100.0) * 250;
	double player2HPConv = ((double)player2HP / 100.0) * 250;
	double play1InkConv = ((double)player1Ink / 100.0) * 250;
	double play2InkConv = ((double)player2Ink / 100.0) * 250;
	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(60.0, 25.0);
	glVertex2d(60.0 + player1HPConv, 25.0);
	glVertex2d(60.0 + player1HPConv, 55.0);
	glVertex2d(60.0, 55.0);
	glEnd();
	glColor3ub(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2d(60.0, 75.0);
	glVertex2d(60.0 + play1InkConv, 75.0);
	glVertex2d(60.0 + play1InkConv, 105.0);
	glVertex2d(60.0, 105.0);
	glEnd();
	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(490.0, 25.0);
	glVertex2d(490 + player2HPConv, 25.0);
	glVertex2d(490 + player2HPConv, 55.0);
	glVertex2d(490.0, 55.0);
	glEnd();
	glColor3ub(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2d(490.0, 75.0);
	glVertex2d(490.0 + play2InkConv, 75.0);
	glVertex2d(490.0 + play2InkConv, 105.0);
	glVertex2d(490.0, 105.0);
	glEnd();
}
int InGameUI::checkTime()
{
	if (timeLeft == -1)
	{
		glColor3ub(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(0, 400);
		glVertex2i(400, 400);
		glVertex2i(400, 0);
		FsSleep(5000);
		return 1;
	}
	return 0;
}

/////////////// PostGameUI /////////////
PostGameUI::PostGameUI(double p1r, double p2r, int p1d, int p2d)
{
	p1Ratio = p1r;
	p2Ratio = p2r;
	p1Demage = p1d;
	p2Demage = p2d;
}
void PostGameUI::drawWinner()
{
	glColor3ub(0, 0, 0);
	glRasterPos2d(150, 70);
	YsGlDrawFontBitmap32x48("The WINNER Is:");
	if (p1Ratio >= p2Ratio)
	{
		glColor3ub(0, 0, 255);
		glRasterPos2d(360, 150);
		YsGlDrawFontBitmap32x48("1P !!");
	}
	else
	{
		glColor3ub(255, 0, 0);
		glRasterPos2d(360, 150);
		YsGlDrawFontBitmap32x48("2P !!");
	}
}
void PostGameUI::drawStats()
{
	glColor3ub(0, 0, 0);
	glRasterPos2d(240, 250);
	YsGlDrawFontBitmap20x28("Game Statistics");
	// YSGLDRAW
	glColor3ub(0, 0, 0);
	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2i(50, 300);
	glVertex2i(750, 300);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(50, 300);
	glVertex2i(50, 600);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(750, 300);
	glVertex2i(750, 600);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(50, 600);
	glVertex2i(750, 600);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(50, 400);
	glVertex2i(750, 400);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(50, 500);
	glVertex2i(750, 500);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(250, 300);
	glVertex2i(250, 600);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2i(500, 300);
	glVertex2i(500, 600);
	glEnd();
	glLineWidth(1.0f);
	glColor3ub(0, 0, 255);
	glRasterPos2d(350, 375);
	YsGlDrawFontBitmap32x48("1P");
	glColor3ub(255, 0, 0);
	glRasterPos2d(600, 375);
	YsGlDrawFontBitmap32x48("2P");
	glColor3ub(0, 0, 0);
	glRasterPos2d(90, 470);
	YsGlDrawFontBitmap32x48("Area");
	glColor3ub(0, 0, 0);
	glRasterPos2d(58, 570);
	YsGlDrawFontBitmap32x48("Damage");
	std::stringstream stream1;
	std::stringstream stream2;
	stream1 << std::fixed << std::setprecision(1) << p1Ratio;
	stream2 << std::fixed << std::setprecision(1) << p2Ratio;
	string p1AreaString = stream1.str();
	p1AreaString += "%";
	string p2AreaString = stream2.str();
	p2AreaString += "%";
	const char *p1AreaChar = p1AreaString.c_str();
	const char *p2AreaChar = p2AreaString.c_str();
	glColor3ub(0, 0, 255);
	glRasterPos2d(300, 475);
	YsGlDrawFontBitmap32x48(p1AreaChar);
	glColor3ub(255, 0, 0);
	glRasterPos2d(550, 475);
	YsGlDrawFontBitmap32x48(p2AreaChar);
}