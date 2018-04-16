#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "myTerm.h"

int mt_clrscr() //Очищает экран
{
	printf("\E[H\E[J");
	return 0;
}

int mt_gotoXY(int x, int y) //Перемещает курсор
{
	printf("\E[%d;%dH", x, y);
	return 0;
}

int mt_getscreensize(int *rows, int *cols) //Размер терминала
{
struct winsize ws;

	if (!ioctl(1, TIOCGWINSZ, &ws)){
		*rows = ws.ws_row;
		*cols = ws.ws_col;
	}else
		return -1;
	return 0;

}

int mt_setfgcolor(int colors) //Цвет символов
{
	printf("\E[3%dm", colors);
}

int mt_setbgcolor(int colors) //Цвет фона
{
	printf("\E[4%dm", colors);
}

