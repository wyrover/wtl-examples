#include"game.h"
#include"costant.h"
#include<graphics.h>
#include<conio.h>
#include"Arr.h"
#pragma comment (lib,"MSIMG32.lib")

IMAGE GraphBuffer(BOUND_X, BOUND_Y),Background,Fighter, Ufo1,Ufo2,Ufo3,gBullet;

void putpicture(int x, int y, IMAGE*img)
{
	HDC dstDC = GetImageHDC(&GraphBuffer);
	HDC srcDC = GetImageHDC(img);
	TransparentBlt(dstDC, x, y, img->getwidth(), img->getheight(), srcDC, 0, 0, img->getwidth(), img->getheight(), RGB(255, 255, 255));
}

void loader()
{
	loadimage(&Background,_T("bk.bmp"));
	loadimage(&gBullet,_T("bomb.bmp"));
	loadimage(&Fighter, _T("playerplane.bmp"));
	loadimage(&Ufo1, _T("ufoBlue.bmp"));
}

Game theGame;

int main()
{
	loader();
	initgraph(BOUND_X, BOUND_Y);

//	setbkmode(TRANSPARENT);
	Player GXS("gxs");
	theGame.addPlayer(&GXS);
	theGame.play();

	return 0;
}