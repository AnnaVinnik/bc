#ifndef MYTERM
#define MYTERM

#define red 1
#define green 2
#define yellow 3
#define blue 4
#define white 7
#define black 0

int mt_clrscr();
int mt_gotoXY(int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(int colors);
int mt_setbgcolor(int colors);

#endif
