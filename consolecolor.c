#include <stdio.h>

#define RESET		0
#define BRIGHT 		1
#define DIM		2
#define UNDERLINE 	3
#define BLINK		4
#define REVERSE		7
#define HIDDEN		8

#define BLACK 		0
#define RED		1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7

void textcolor(int attr, int fg, int bg);

int main(int argc, char **argv)
{
	textcolor(BRIGHT, WHITE, BLACK);
	printf("Initialization        ");
    textcolor(BRIGHT, RED, BLACK);
	printf("[Failed]\n");
	textcolor(BRIGHT, WHITE, BLACK);
	printf("Module Loader        ");
	textcolor(DIM, GREEN, BLACK);
	printf("[OK]\n");
    textcolor(BRIGHT, WHITE, BLACK);
	/*printf("%c[9;32mHello ",27);  Prints "Hello\n" in RED (ANSI) */
	/*printf("%c[0;0mWorld\n",27); Prints "Hello\n" in RED (ANSI) */
	return 0;

}


void textcolor(int attr, int fg, int bg)
{	
	char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	

	printf("%s", command);
}
