#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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

#define WIDTH     30
#define HEIGHT    20
#define OFFSET_X  2
#define OFFSET_Y  2

#define NUM_KEYS 7
#define MAX_NUM_KEYS 30
#define REFRESH_RATE 2

struct t_Keyboard {
   int x;
   int y;
   int color;
   int keydown;
   int keyval;
   int pitch;
   int drum;
   int volume;
   int shape[3][1];
};
typedef struct t_Keyboard Keyboard;


void delay(float sec);
void putString(int x, int y, char *p, int fg_color, int bg_color);

void genKeyboard(Keyboard *key_p, int num);
void showKeyboard(Keyboard *key_p, int num);

int key_const[] =
{VK_1, VK_2, VK_3, VK_4, VK_5, VK_6, VK_7, VK_8, VK_9, VK_0,
VK_Q, VK_W, VK_E, VK_R, VK_T, VK_Y, VK_U, VK_I, VK_O, VK_P};

int pitch_const[] =
{60, 62, 64, 65, 67, 69, 71, 72, 74, 76,
77, 79, 81, 83, 84, 86, 88, 89, 91, 93};

int drum_const[] =
{55, 56, 57, 58, 59, 60, 61, 62, 63, 64
,65, 66, 67, 68, 69, 70, 71, 72, 73, 74};

int pitch_or_drum = 1;

int main(void)
{
   int IsEnding = 0;
   char logo[] = "SAMPLE PROGRAM PROVIDED BY I2P";
   int k;

   Keyboard keys[MAX_NUM_KEYS];
   int num_keys = 20;

   clock_t startc;
   int tick = 0;
   int frame_update = 0;

   char str[40] = {'\0'};


   openMidi();


   startc = clock();

   initializeKeyInput();


   genKeyboard(keys, num_keys);

   while (!IsEnding) {

      if ((double)(clock()-startc) > 0.005*CLOCKS_PER_SEC) {
         tick++;
         frame_update = 0;
         startc = clock();
      }


      if (tick % REFRESH_RATE == 0 && !frame_update) {

         frame_update = 1;

         showKeyboard(keys, num_keys);

         putString(OFFSET_X, OFFSET_Y-2, logo, 14, 3);

         /* sprintf(str, "%10ld", getPosition(&audio[0])); */
         putString(OFFSET_X, OFFSET_Y-1, str, 14, 1);


         drawCmdWindow();

      }

      for (k=0; k<num_keys; k++) {
         if(KEY_DOWN(keys[k].keyval) && !keys[k].keydown) {
            keys[k].keydown = 1;

            if (pitch_or_drum)
               playMidi(0, keys[k].pitch, keys[k].volume);
            else
               playMidi(1, keys[k].drum, keys[k].volume);

         }

         if(KEY_UP(keys[k].keyval) && keys[k].keydown) {
            keys[k].keydown = 0;
         }

      }

      if (KEY_DOWN(VK_X)) {
      	pitch_or_drum = !pitch_or_drum;
      }


   } /* while (IsEnding) */

   closeMidi();

   delay(0.5);
   return 0;
}




void delay(float sec)
{
   clock_t startc;
   startc = clock();
   for ( ; ; ) {
	  if ((float)(clock()-startc)/CLOCKS_PER_SEC > sec) break;
   }
}

void putString(int x, int y, char *p, int fg_color, int bg_color)
{
   int i;
   for(i=0; i<strlen(p); i++) {
      putASCII2(x+i, y, p[i], fg_color, bg_color);
   }
}


/****************************************************************************************************/


void genKeyboard(Keyboard *key_p, int num)
{
   int i, k;

   for (k=0; k<num; k++) {
      key_p[k].x = 5 + k;
      key_p[k].y = 10;
      key_p[k].color = 10;

      key_p[k].keydown = 0;
      key_p[k].keyval = key_const[k];
      key_p[k].pitch = pitch_const[k];
      key_p[k].drum = drum_const[k];
      key_p[k].volume = 100;

      for (i=0; i<3; i++) {
         key_p[k].shape[i][0] = 1;
      }

   }

}

void showKeyboard(Keyboard *key_p, int num)
{
   int i, k;

   for (k=0; k<num; k++) {
      for (i=0; i<3; i++) {
         if (key_p[k].keydown) {
           if (key_p[k].shape[i][0]) {
               putASCII2((key_p[k].x)*2  + OFFSET_X,
               key_p[k].y + i + OFFSET_Y, 0xA1, key_p[k].color, 0);
               putASCII2((key_p[k].x)*2+1  + OFFSET_X,
               key_p[k].y + i +  OFFSET_Y, 0xBD, key_p[k].color, 0);
            }
         }
         else {
           if (key_p[k].shape[i][0]) {
               putASCII2((key_p[k].x)*2  + OFFSET_X,
               key_p[k].y + i + OFFSET_Y, 0xA1, 5, 0);
               putASCII2((key_p[k].x)*2+1  + OFFSET_X,
               key_p[k].y + i +  OFFSET_Y, 0xBD, 5, 0);
            }
         }
      }
   }

}


