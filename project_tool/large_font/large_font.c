#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <mmsystem.h>
/* ���İO�o�n�[�J�o�� */
#include "audio.h"
/* �t�~�٦����U���]�w */
/* For sound effect: In [Project Options]->[Parameters]->[Linker] add the parameter -lwinmm */

#include "console_draw2.h"
#include "kb_input2.h"

/*
putASCII2()  �̫��ӰѼƤ��O�O�r���e���M�I�����C��
�i�H�ѦҤU�����C��ȹ�Ӫ�ӳ]�w�A�Q�n���C��
   0: ��     1: �t��   2: �t��   3: �t�C
   4: �t��   5: �t��   6: �t��   7: �L��
   8: �t��   9: �G��  10: �G��  11: �G�C
  12: �G��  13: �G��  14: �G��  15: ��
*/

#define REFRESH_DURATION 5

typedef struct _font {
    int height;
    int width;
    char *pixel;
} Font;

void putStringLarge(Font *fp, int x, int y, char *p, int fg_color, int bg_color);

Font * read_font(char *pixel_file);
char getpixel(Font *ip, int x, int y);

void show_font(Font *ip, char letter, int offx, int offy, int fg_color, int bg_color);
void destroy_font(Font *ip);


int main(void)
{
    int IsEnding = 0;


    /* �Ψӭp�� time.h */
    clock_t startc;
    int game_tick = 0;

    Font *large_font = read_font("font.txt");

	/* �Ұ���L���� */
    initializeKeyInput();

    startc = clock();
    while (!IsEnding) { /* game loop */

        if ((double)(clock()-startc) > 0.01*CLOCKS_PER_SEC) {
            game_tick++;  /* game_tick 0.01 �� */
            startc = clock();
        }


        if (game_tick > REFRESH_DURATION) {
            game_tick = 0;
            clearScreen();


            putStringLarge(large_font, 10, 10, "SAMPLE PROGRAM", 10, 0);
            putStringLarge(large_font, 10, 16, "PROVIDED BY I2P", 10, 0);

            drawCmdWindow();  /* update window immediately */

        }


        if (KEY_DOWN(VK_ESCAPE)) {
            IsEnding = 1;
        }



    } /* while (IsEnding) */


    return 0;
}



void putStringLarge(Font *fp, int x, int y, char *p, int fg_color, int bg_color)
{
    int i;
    for(i=0; i<strlen(p); i++) {
        show_font(fp,  p[i], x+i*fp->width, y, fg_color, bg_color);
    }
}


Font * read_font(char *pixel_file)
{
    FILE *fid;
    int height, width, num, i, j, k;
    Font *p;

    fid = fopen(pixel_file, "r");

    if (fid==NULL) {
        return NULL;
    } else {
        fscanf(fid, "%d%d%d", &height, &width, &num);
        p = (Font*) malloc(sizeof(Font));
        p->height = height;
        p->width = width;
        p->pixel = (char*) malloc(sizeof(char)*height*width*num);
        fscanf(fid, "%*c");
        for (k=0; k<num; k++) {
            for (i=0; i<height; i++) {
                for (j=0; j<width; j++) {
                    fscanf(fid, "%c", & (p->pixel[k*width*height+i*width+j]));
                }
                fscanf(fid, "%*c");
            }
        }
        fclose(fid);

        return p;
    }
}

char getpixel(Font *ip, int x, int y)
{
    return ip->pixel[y*ip->width + x];
}



void show_font(Font *ip, char letter, int offx, int offy, int fg_color, int bg_color)
{
    int x, y;
    char c;
    int shift;
    if (letter==' ') return;
    if (isdigit(letter)) {
        shift = ip->height*(26 + letter-'0');
    } else {
        shift = ip->height*(toupper(letter)-'A');
    }
    for (y=0; y<ip->height; y++) {
            for (x=0; x<ip->width; x++) {

            c = getpixel(ip, x, y+shift);
            if (c!=' ')
            putASCII2( x + offx,
                y + offy, '@', fg_color, bg_color);
            }
    }
}

void destroy_font(Font *ip)
{
    free(ip->pixel);
    free(ip);
}
