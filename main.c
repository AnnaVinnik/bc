#include <stdio.h>
#include <termios.h>
//#include <curses.h>
#include <sys/ioctl.h>
#include "myTerm.h"
#define c 35 
#define r 35
#define t1 16843134
#define t2 260079876
// s -; l  , k
int printA()
{
	//printf("\E(0%s\E(B", "r");
	//printf("\E[4%dm", 2);
	mt_setbgcolor(3);
	printf("%c", r);
	//printf("\E[4%dm", 0);
	
}

int bc_box(int x1, int y1, int x2, int y2)
{
int i;
	mt_clrscr();
	mt_gotoXY(y1, x1);
	printf("\E(0%s\E(B", "l");
	for (i = x1 + 1; i < x2 - 1; i++){
		printf("\E(0%s\E(B", "q");
	}
	printf("\E(0%s\E(B", "k");
	for (i = y1 + 2; i < y2; i++){
		mt_gotoXY(i, x1 );
		printf("\E(0%s\E(B", "x");
		mt_gotoXY(i, x2);
		printf("\E(0%s\E(B", "x");
	}
	mt_gotoXY(y2, x1 + 1);
	printf("\E(0%s\E(B", "m");
	for (i = x1; i < x2 - 2; i++){
		printf("\E(0%s\E(B", "q");
	}
	printf("\E(0%s\E(B", "j");
	printf("\n");
	
}

int bc_printA(char *str)
{
	printA();
}

int bc_printbigchar(int symbol[2], int x, int y, int color1, int color2)
{
int i = 0, j;

	mt_setbgcolor(7);
	mt_setfgcolor(4);
	
	
	
	
	for (i = 0; i < 4; i++){
		for (j = 8; j >= 1; j--){
			if ((symbol[0] >> (i*7 + j - 1)&0x1) == 1){
				printf("\E(0%s\E(B", "a");
			}
			else
				printf(" ");
			
		}
		printf("\n");
	}
	for (i = 0; i < 4; i++){
		for (j = 8; j >= 1; j--){
			if ((symbol[1] >> (i*7 + j - 1)&0x1) == 1){
				printf("\E(0%s\E(B", "a");
			}
			else
				printf(" ");
			
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
		*value = (big[0] >> ((y - 4) * 7 + x - 1) & 0x1);
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
	//fputc('\n', file); 
	}
		
	
	
fclose(file);
}

int bc_bigcharread (int fd, int * big, int need_count, int * count)
{
FILE *file = fopen("text.txt", "r");
char str[10], str2[10];
int i, j,  k, l;

	for (k = 0; k < need_count; k++){
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
		//fscanf(file, "%s", str);
		//printf("\n");
	}

fclose(file);
}

int main()
{
	mt_clrscr();
	char a[1] = {'a'};
	int k[4] = {20, 4, 3, 5};
	int b[4] = {4, 2, 1, 10}, n[4] = {0};
	int enter[2];
	
	
	//scanf("%d", &enter[0]);
	//mt_clrscr();
	//scanf("%d", &enter[0]);
	//mt_clrscr();
	//bc_printA(a);
	//bc_box(0, 0, 8, 9);
	
	
	bc_bigcharread(1, k , 1, b);
	printf("bigcharread in k[] = %d \n", k[1]);
	
	bc_printbigchar(k, 10, 10, 1, 1);
	printf("\n");
	/*scanf("%d", &enter[1]);
	mt_clrscr();
	printf("\n");
	bc_printbigchar(k, 10, 10, 1, 1);
	
	bc_bigcharwrite(2, b, 2);
	printf("k[0] = %d\n", k[0]);
	printf("bigcharwrite b[]\n");
	bc_bigcharread(1, k , 1, b);
	printf("bigcharread in k[]: \n");
	printf("k[0] = %d\n", k[0]);
	printf("setbigchar x = 1, y = 2, value = 1\n");
	bc_setbigcharos(k, 1, 2, 1);
	printf("\n");
	bc_printbigchar(k, 10, 10, 1, 1);
	//bc_printbigchar(k, 10, 10, 1, 1);
	printf("getbigchar x = 1, y = 2: ");
	bc_getbigcharpos(k, 1, 2, &k[0]);
	printf(" %d\n", k[0]);
	
	
	
	//bc_bigcharwrite(2, k, 4);
	//bc_bigcharread(1, b, 3, &k[0]); 
	//bc_printbigchar(b, 10, 10, 1, 1);
	//printf("b = %d \n", b[0]);
	*/

	return 0;
}
