#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "winmm.lib")
#include "graphics.h"
#include <dos.h>
#include <stdio.h>
#include <Windows.h>
#include <ctype.h>
#include <time.h>
using namespace std;
char msg[128];
char msg2[128];
const char *plane = "plane.bmp";
const char *explo = "explo.bmp";
const char *explod = "explod.jpg";
const char *ph0 = "h0.jpg";
const char *ph1 = "h1.bmp";
const char *ph2 = "h2.bmp";
const char *ph3 = "h3.bmp";
const char *dgo = "dgo.bmp";
const char *barimg = "bar.jpg";
const char *jp = "jp.bmp";
static int i = 0, a, b,high=0;
int score=0,endg=1;
static int maxx, maxy, midx, midy;
void hurdles(static int *, static int *,int);
void h0(static int *, static int *);
void h1(static int *, static int *);
void h2(static int *, static int *);
void h3(static int *, static int *);
void h4(static int *, static int *);
void mainmenu()
{
	readimagefile(jp,0 ,0 ,1050 ,550 );
	outtextxy(midx-40,10 ,"Press any key to start...." );
	outtextxy(midx - 40, 30, "Press ESC key to Quit....");
	sprintf(msg2, "High score=%d", high);
	outtextxy(midx - 40, 50, msg2);
	PlaySound("d1.wav", NULL, SND_ASYNC);
	delay(2000);
	PlaySound("d2.wav", NULL, SND_ASYNC);
	delay(2000);
	PlaySound("d3.wav", NULL, SND_ASYNC);
	if (GetAsyncKeyState(VK_ESCAPE))
		exit(0);
	getch();
}
void sscore()
{
	sprintf(msg, "Score=%d", score);
	outtextxy(900, 10, msg);
}
void go()
{
	if (score > high)
		high = score;
	cleardevice();
	readimagefile(dgo, midx - 120, midy - 70, midx + 120, midy);
	PlaySound("dgo.wav", NULL, SND_ASYNC);
	sprintf(msg, "Score=%d", score);
	outtextxy(midx - 40, 280, msg);
	delay(1500);
	getch();
	getch();
	endg = 0;
}
void planef()
{
	a = 70 + i, b = 150 + i;
	readimagefile(plane, 50, a, 140, b);
	delay(30);
	if (GetAsyncKeyState(VK_UP))
		i -= 20;
	if (GetAsyncKeyState(VK_DOWN))
		i += 15;
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		int resume = 0;
		mciSendString("PAUSE MY_SND", NULL, 0, NULL);
		for (;resume!=1;){
			outtextxy(midx - 120, midy, "Game Paused! Press ENTER key to continue");
			if (GetAsyncKeyState(VK_RETURN))
				resume = 1;
		}
		cleardevice();
		mciSendString("RESUME MY_SND", NULL, 0, NULL);
	}
	cleardevice();
	if (b == 490 || b == 495 || b == 500 || b == 505 || b == 510)
	{
		readimagefile(explod, 70, a, 140, b);
		mciSendString("PAUSE MY_SND", NULL, 0, NULL);
		PlaySound("ex.wav", NULL, SND_ASYNC);
		delay(1500);
		getch();
		go();
	}
	if (a == 0 || a == -5 || a == -10 || a == -15 || a == -20)
	{
		readimagefile(explo, 70, a, 140, b);
		mciSendString("PAUSE MY_SND", NULL, 0, NULL);
		PlaySound("ex.wav", NULL, SND_ASYNC);
		delay(1500);
		getch();
		go();
	}
	i += 10;
}
int main()
{
	for (;;)
	{
		endg = 1;
		i = 0;
		score = 0;
		srand(time(NULL));
		int l;
		initwindow(1050, 510);
		cleardevice();
		maxx = 1050, maxy = 550, midx = maxx / 2, midy = maxy / 2;
		mainmenu();
		cleardevice();
		mciSendString("open bgm.wav alias MY_SND", NULL, 0, NULL);
		mciSendString("play MY_SND", NULL, 0, NULL);
		for(;;){
			if (endg == 0)
				break;
			planef();
			l = rand() % 4;
			hurdles(&a, &b, l);
			score += 5;
			sscore();
		}
		getch();
		getch();
	}
	closegraph();
	return 0;
}
void hurdles(int *a, int *b, int l)
{
	switch (l){
	case 0:
		h0(a, b);
		break;
	case 1:
		h1(a, b);
		break;
	case 2:
		h2(a, b);
		break;
	case 3:
		h3(a, b);
		break;
	case 4:
		h4(a, b);
		break;
	}
}
void h0(static int *a, static int *b){
	int au1 = 0;
	int inc = 0;
	int end2 = 1, end1, top, bot;
	bool flag = 0;
	PlaySound("d3.wav", NULL, SND_ASYNC);
	for (; end2 >= 0;)
	{
		if (endg == 0)
			break;
		end2 = 1250 - inc;
		end1 = 1050 - inc;
		top = 370 - au1;
		bot = 500 - au1;
		planef();
		sscore();
		readimagefile(ph1, end1, top, end2, bot);
		inc += 30;
		if (flag == 0)
		{
			au1 += 20;
			if (au1 == 300)
				flag = 1;
		}
		if (flag == 1)
		{
			au1 -= 20;
			if (au1 == 0)
				flag = 0;
		}
		if ((*a >= top&&*a <= bot) && ((end1 <= 140 && end1 >= 50) || (end2 <= 140 && end2 >= 50)))
		{
			{
				readimagefile(explod, 70, *a, 140, *b);
				mciSendString("PAUSE MY_SND", NULL, 0, NULL);
				PlaySound("ex.wav", NULL, SND_ASYNC);
				delay(1500);
				getch();
				go();
			}
		}
	}
}
void h1(static int *a, static int *b){
	int au1 = 0;
	int inc2 = 0;
	int end2 = 1, end1, top, bot;
	bool flag = 0;
	PlaySound("d1.wav", NULL, SND_ASYNC);
	for (; end2 >= 0;)
	{
		if (endg == 0)
			break;
		planef();
		sscore();
		end2 = 1550 - inc2;
		end1 = 1150 - inc2;
		int endm = end1 + end2 / 2;
		top = 250 - au1;
		bot = 500 - au1;
		readimagefile(ph0, end1, top, end2, bot);
		if (*a >= (top + 10) && ((end1 <= 140 && end1 >= 50) || (endm <= 140 && endm >= 50)))
		{
			{
				readimagefile(explod, 70, *a, 140, *b);
				mciSendString("PAUSE MY_SND", NULL, 0, NULL);
				PlaySound("ex.wav", NULL, SND_ASYNC);
				delay(1500);
				getch();
				go();
			}
		}
		if (*a >= (top + 70) && ((endm <= 140 && endm >= 50) || (end2 <= 140 && end2 >= 50)))
		{
			{
				readimagefile(explod, 70, *a, 140, *b);
				mciSendString("PAUSE MY_SND", NULL, 0, NULL);
				PlaySound("ex.wav", NULL, SND_ASYNC);
				delay(1500);
				getch();
				go();
			}
		}
		inc2 += 30;
	}
}
void h2(static int *a, static int *b){
	int au1 = 0;
	int inc = 0;
	int end2 = 1, end1, top, bot;
	bool flag = 0;
	PlaySound("d2.wav", NULL, SND_ASYNC);
	for (; end2 >= 0;)
	{
		if (endg == 0)
			break;
		end2 = 1450 - inc;
		end1 = 1050 - inc;
		top = 100 - au1;
		bot = 400 - au1;
		planef();
		sscore();
		readimagefile(ph2, end1, top, end2, bot);
		inc += 30;
		if (flag == 0)
		{
			au1 += 20;
			if (au1 == 300)
				flag = 1;
		}
		if (flag == 1)
		{
			au1 -= 20;
			if (au1 == 0)
				flag = 0;
		}
		if ((*a >= top&&*a <= (bot - 40)) && (((end1 + 20) <= 140 && (end1 + 20) >= 50) || (end2 <= 140 && end2 >= 50)))
		{
			{
				readimagefile(explod, 70, *a, 140, *b);
				mciSendString("PAUSE MY_SND", NULL, 0, NULL);
				PlaySound("ex.wav", NULL, SND_ASYNC);
				delay(1500);
				getch();
				go();
			}
		}
	}
}
void h3(static int *a, static int *b){
	int au1 = 0;
	int inc = 0;
	int end2 = 1, end1, top, bot;
	PlaySound("d2.wav", NULL, SND_ASYNC);
	for (; end2 >= 0;)
	{
		if (endg == 0)
			break;
		end2 = 1450 - inc;
		end1 = 1050 - inc;
		top = 200 - au1;
		bot = 500 - au1;
		planef();
		sscore();
		readimagefile(ph3, end1, top, end2, bot);
		inc += 30;
		au1 += 5;

		if ((*a >= top&&*a <= (bot - 40)) && (((end1 + 20) <= 140 && (end1 + 20) >= 50) || (end2 <= 140 && end2 >= 50)))
		{
			{
				readimagefile(explod, 70, *a, 140, *b);
				mciSendString("PAUSE MY_SND", NULL, 0, NULL);
				PlaySound("ex.wav", NULL, SND_ASYNC);
				delay(1500);
				getch();
				go();
			}
		}
	}
}
void h4(static int *a, static int *b){
	int au1 = 0;
	int inc = 0;
	int end2 = 1, end1, top, bot;
	PlaySound("d2.wav", NULL, SND_ASYNC);
	for (; end2 >= 0;)
	{
		if (endg == 0)
			break;
		end2 = 1450 - inc;
		end1 = 1050 - inc;
		top = 100 + au1;
		bot = 300 + au1;
		planef();
		sscore();
		readimagefile(ph3, end1, top, end2, bot);
		inc += 30;
		au1 += 5;

		if ((*a >= top&&*a <= (bot - 40)) && (((end1 + 20) <= 140 && (end1 + 20) >= 50) || (end2 <= 140 && end2 >= 50)))
		{
			{
				readimagefile(explod, 70, *a, 140, *b);
				mciSendString("PAUSE MY_SND", NULL, 0, NULL);
				PlaySound("ex.wav", NULL, SND_ASYNC);
				delay(1500);
				getch();
				go();
			}
		}
	}
}