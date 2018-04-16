#include <stdio.h>
#include <termios.h>
//#include <curses.h>
#include <sys/ioctl.h>
#include "myTerm.h"
#define c 112
#define r 35

int printA()
{
	mt_gotoXY(1, 7);
	printf("%c", c);
	mt_gotoXY(2, 5);
	printf("%c   %c", c, c);
	mt_gotoXY(3, 3);
	printf("%c  %c%c%c  %c", c, c, c, c, c);
	mt_gotoXY(4, 1);
	printf("%c           %c", c, c);
	

}

int bc_box(int x1, int y1, int x2, int y2)
{
int i;
	//mt_clrscr();
	mt_gotoXY(y1, x1);
	for (i = x1; i < x2; i++){
		printf("%c", r);
	}
	for (i = y1; i < y2; i++){
		mt_gotoXY(i, x1);
		printf("%c", r);
		mt_gotoXY(i, x2);
		printf("%c", r);
	}
	mt_gotoXY(y2, x1);
	for (i = x1; i <= x2; i++){
		printf("%c", r);
	}
	printf("\n");
	
}

int bc_printA(char *str)
{
	printA();
}

int bc_printbigchar(int symbol[2], int x, int y, int color1, int color2)
{
int i = 0, j;

	mt_setbgcolor(4);
	mt_setfgcolor(3);
	for (i = 0; i < 4; i++){
		for (j = 8; j >= 1; j--){
			if ((symbol[0] >> (i*7 + j - 1)&0x1) == 1){
				printf("%c", r);
			}
			else
				printf(".");
			
		}
		printf("\n");
	}
	for (i = 0; i < 4; i++){
		for (j = 8; j >= 1; j--){
			if ((symbol[1] >> (i*7 + j - 1)&123) == 1){
				printf("%c", r);
			}
			else
				printf(".");
			
		}
		printf("\n");
	}
	mt_setbgcolor(9);
	mt_setfgcolor(7);
}

int bc_setbigcharos(int *big, int x, int y, int value)  //*big
{	
	if (value == 1){
		if (y < 4){
			big[0] = big[0] | (1 << ((7 - x) + y * 7));
		}else {
			big[1] = big[1] | (1 << ((7 - x) + (y - 4) * 7));
		}
		
	}
	else if (value == 0){
		if (y < 4){
			big[0] = big[0] & (~(1 << ((7 - x) + y * 7)));
		}else {
			big[1] = big[1] & (~(1 << ((7 - x) + y * 7)));
		}
	}
} 

int bc_getbigcharpos(int * big, int x, int y, int *value)
{
	if (y < 4){
		*value = ((big[0] >> (y * 7) + (7 - x)) & 0x1);
	}else{
		*value = (big[1] >> ((y - 4) * 7 + x - 1) & 0x1);
	}
	return 0;
}

int bc_bigcharwrite (int fd, int * big, int count)
{
FILE *file = fopen("text.txt", "w");
int i, j, k;
	for (k = 0; k < count; k = k + 2){
	for (j = 0; j < 4; j++){
		for (i = 8; i >= 1; i--){
			if ((big[k] >> (j*7 + i - 1)&0x1) == 1)
				fputc(r, file);
			else fputc((int)'.', file);
		}
		fputc('\n', file);
	}
	for (j = 0; j < 4; j++){
		for (i = 8; i >= 1; i--){
			if ((big[k + 1] >> (j*7 + i - 1)&0x1) == 1)
				fputc(r, file);
			else fputc((int)'.', file);
		}
		fputc('\n', file);
	}
	fputc('\n',file);
	fputc('\n', file); 
	}
		
	
	
fclose(file);
}

int bc_bigcharread (int fd, int * big, int need_count, int * count)
{
FILE *file = fopen("text.txt", "r");
char str[10], str2[10];
int i, j,  k, l;

	for (k = 0; k < 1; k++){
		for (i = 0; i < 8; i++){
			for (l = 0; l < 8; l++)
				str[l] = 0;
			fscanf(file, "%s", str);
			for (j = 0; j < 8; j++){

				if (str[j] == '.'){
					bc_setbigcharos(big, j, i, 0);
					printf(".");
				}else if (str[j] == r){ 
					bc_setbigcharos(big, j, i, 1);
					printf("+");
				}
			}
			printf("\n");
		}
	}
	/*for (k = 1; k < 2; k++){
	printf("k = 1\n");
		for (i = 0; i < 4; i++){
			printf("i = %d\n", i);
			for (j = 0; j < 8; j++){
			printf("j = %d ", j);
				s = fgetc(file);
				if (s == '.'){
					bc_setbigcharos(&big[k], i, j, 0);
					printf(".");
				}else if (s == r){
					bc_setbigcharos(&big[k], i, j, 1);
					printf("+");
				}
			}
			printf("\n");
		}
	}*/
fclose(file);
}

int main()
{
	mt_clrscr();
	char a[1] = {'a'};
	int k[4] = {20, 4, 2, 5};
	int b[4] = {17, 2, 1, 3}, n[4] = {0};
	int enter[2];
	
	//bc_printA(a);
	//scanf("%d", &enter[0]);
	//mt_clrscr();
	
	//bc_box(10, 7, 25, 14);
	//scanf("%d", &a);
	//mt_clrscr();
	
	bc_printbigchar(k, 10, 10, 1, 1);
	bc_bigcharwrite(2, b, 4);
	bc_bigcharread(1, k , 2, b);
	//bc_setbigcharos(k, 1, 2, 1);
	printf("\n");
	bc_printbigchar(k, 10, 10, 1, 1);
	
	//bc_getbigcharpos(k, 1, 2, &k[0]);
	printf("k[0] = %d\n", k[1]);
	
	//bc_bigcharwrite(2, k, 4);
	//bc_bigcharread(1, b, 3, &k[0]); 
	//bc_printbigchar(b, 10, 10, 1, 1);
	printf("b = %d \n", b[0]);
	

	return 0;
}
