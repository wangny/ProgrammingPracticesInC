#include <windows.h>
#ifndef CONSOLE_DRAW_
#define CONSOLE_DRAW_
#define SCREEN_WIDTH 80 
#define SCREEN_HEIGHT 25 
enum some_color { COLOR_BLUE = 0x09, COLOR_GREEN = 0x0A, COLOR_MAGENTA = 0x0D, COLOR_YELLOW = 0x0E };
extern void putASCII( int x, int y, int ch, int color );
extern void drawCmdWindow();
#endif

