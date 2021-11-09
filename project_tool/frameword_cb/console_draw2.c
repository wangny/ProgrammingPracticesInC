#include "console_draw2.h"

COORD dwBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
COORD dwBufferCoord = { 0, 0 };
SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1 };
CHAR_INFO screen_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
HANDLE hOutput;
int Touched_Global = 0;

void putASCII2( int x, int y, int ch, int fgcolor, int bgcolor )
{
    if ( Touched_Global == 0) {
        hOutput = (HANDLE) GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleScreenBufferSize(hOutput, dwBufferSize);

        Touched_Global = 1;
    }

    if (x<SCREEN_WIDTH && x>=0 && y<SCREEN_HEIGHT && y>=0) {
        screen_buffer[y][x].Char.AsciiChar = ch;
        screen_buffer[y][x].Attributes = fgcolor | bgcolor<<4;
    }
}

void drawCmdWindow()
{
    if (Touched_Global) {

        WriteConsoleOutput( hOutput, (CHAR_INFO *)screen_buffer, dwBufferSize,
                dwBufferCoord, &rcRegion );
        SetConsoleActiveScreenBuffer(hOutput);
        SetConsoleCursorPosition( hOutput, dwBufferSize );
    }
}

void clearScreen(void)
{

    int i, j;
    for (i=0; i<SCREEN_HEIGHT; i++) {
        for (j=0; j<SCREEN_WIDTH; j++) {
            screen_buffer[i][j].Char.AsciiChar = ' ';
            screen_buffer[i][j].Attributes = 0;
        }
    }


}
