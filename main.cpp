#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "game.hpp"

int main(void) {
	// Set random seed
    srand(time(NULL));
    FsOpenWindow(16, 16, 800, 800, 1);
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);



	auto pregame_message = pregame();
	auto ingame_message = ingame(pregame_message);
	postgame(ingame_message);

	



	// int state = 0;
	// FsOpenWindow(0, 0, 800, 800, 1);
	// int terminate = 0;
	// StartingPage startpage = StartingPage();
	// PreGameUI pregame = PreGameUI();
	// InGameUI ingame = InGameUI();
	// PostGameUI postgame = PostGameUI(47.32, 52.68, 2444, 2444);
	// int lb;
	// int mb;
	// int rb;
	// int mx;
	// int my;
	// time_t startTime;
	// while (terminate == 0) {
	// 	FsPollDevice();
	// 	auto key = FsInkey();
	// 	if (key == FSKEY_ESC) {
	// 		terminate = 1;
	// 	}
	// 	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	// 	int mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
	// 	if (state == 0) {
	// 		startpage.drawBackground();
	// 		startpage.drawTitle();
	// 		startpage.drawAuthor();
	// 		startpage.drawButton();
	// 		if (startpage.startButton->checkButtonClick(lb, mb, rb, mx, my, mouseEvent)) {
	// 			state = 1;
	// 		}
	// 		if (startpage.endButton->checkButtonClick(lb, mb, rb, mx, my, mouseEvent)) {
	// 			break;
	// 		}
	// 	}
	// 	if (state == 1) {
	// 		pregame.drawBackGround();
	// 		pregame.drawFrame();
	// 		pregame.drawBlock();
	// 		pregame.drawButton();
	// 		pregame.drawButtonSymbol();
	// 		pregame.drawChoice();
	// 		pregame.checkButtonClick(lb, mb, rb, mx, my, mouseEvent);
	// 		if (pregame.checkProceed(lb, mb, rb, mx, my, mouseEvent)) {
	// 			startTime = time(NULL);
	// 			state = 2;
	// 		}
	// 	}
	// 	if (state == 2) {
	// 		ingame.drawBarFrame();
	// 		ingame.drawHealthandInk();
	// 		ingame.drawTimer(startTime);
	// 		if (ingame.checkTime()) {
	// 			state = 3;
	// 		}
	// 	}
	// 	if (state == 3) {
	// 		postgame.drawWinner();
	// 		postgame.drawStats();
	// 	}
	// 	FsSwapBuffers();
	// 	FsSleep(20);
	// }
}