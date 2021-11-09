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
#define MAX_NUM_TANKS 30
#define REFRESH_RATE 20


int plate[HEIGHT][WIDTH] = {0};

/* �۩w�� struct   �ΨӴy�z������U���ݩ� */ 
struct t_Tank {
   int x;
   int y;
   int direction;
   int color;
   int duration;
   int last_tick;
   int shape[3][3];
};
typedef struct t_Tank Tank;


int TANK_SHAPE[4][9] = {
      {0, 1 ,0, 
       3, 2, 3, 
       3, 3, 3},
      {3, 3 ,0, 
       3, 2, 1, 
       3, 3, 0},
      {3, 3 ,3, 
       3, 2, 3, 
       0, 1, 0},
      {0, 3 ,3, 
       1, 2, 3, 
       0, 3, 3}};

void delay(float sec); 
void putString(int x, int y, char *p, int fg_color, int bg_color);

void genTanks(Tank *tank_p, int num);
void showTanks(Tank *tank_p, int num);
int moveTanks(Tank *tank_p, int num, int tick);


int main(void) 
{    
   int IsEnding = 0;
   char logo[] = "SAMPLE PROGRAM PROVIDED BY I2P";
   int i, j, k;

   Tank tanks[MAX_NUM_TANKS];
   int num_tanks = 5;
   
   clock_t startc;    
   int tick = 0;
   int frame_update = 0;

   int key_down[NUM_KEYS] = {0};
   int key_val[NUM_KEYS] = {VK_A, VK_S, VK_D, VK_F, VK_G, VK_ESCAPE, VK_Q};

   char str[40] = {'\0'};
   int vk;
   
   /* �ΨӰO�����Ī� struct �}�C */ 
   Audio audio[6];
   
   /* Ū�J���ӭ����� */ 
   openAudioFile("DR220A_CH.wav", &audio[0]);
	openAudioFile("DR220A_SD.wav", &audio[1]);
	openAudioFile("DR220A_HT.wav", &audio[2]);
	openAudioFile("DR220A_CCY.wav", &audio[3]);
	openAudioFile("DR220A_BD.wav", &audio[4]);
	 
   openAudioFile("liberty.wav", &audio[5]);  	/* �I������ */
   audio[5].loop = 1;	/* ���Ƽ��� */

   /* �}�l����I������  */
   playAudio(&audio[5]);   
   
   
   
   
   /* �Q�W���䪺����M�̩��U���a�O�@*/ 
   for (i = 0; i < HEIGHT; i++) {
      plate[i][0] = 1;
      plate[i][WIDTH-1] = 1;
   }
   for (j = 0; j < WIDTH; j++) {
      plate[0][j] = 1;
      plate[HEIGHT-1][j] = 1;
   }

   /* ���Ͷü� seed    ���᭱�I�s rand() �i�H�o�줣�P���üƧǦC  */ 
   srand(time(NULL));   

   /* �Ψӭp�� */ 
   startc = clock();

   /* �Ұ���L���� */ 
   initializeKeyInput(); 
   
   /* ���ͩZ�J */ 
   genTanks(tanks, num_tanks);

   


	/* �L�a�j��  �̭��]�t�F�o�ӵ{�����D�n�u�@   
   �ӥB�C���j��|���_��̷s���e����ܨ�ù��W  ���O���ʵe�@�� �C���j���s�@���e�� */
   while (!IsEnding) { 

      /* �ۤv�]�w���ɶ���� tick  �C 0.05 ����@�� tick   �᭱�|�Q�� tick �ƨӨM�w������ʳt�� */ 
      if ((double)(clock()-startc) > 0.005*CLOCKS_PER_SEC) {
         tick++;
         frame_update = 0;
         startc = clock();
      }

      
      /* ��ثe�C�����p �� putASCII2() ��ܥX��  
         �C�g�L REFRESH_RATE �� ticks �~�|��s�@���e�� */  
      if (tick % REFRESH_RATE == 0 && !frame_update) {
         frame_update = 1;
         for (i = 0; i < HEIGHT; i++) {
            for (j = 0; j < WIDTH; j++) {
               if (plate[i][j] == 1) {
                  putASCII2(j*2 + OFFSET_X, i + OFFSET_Y, 0xA1, 8, 0);  /* fg_color=8 �N��e�����C��O�Ǧ� */ 
                  putASCII2(j*2+1 + OFFSET_X, i + OFFSET_Y, 0xBD, 8, 0);
               } else {
                  putASCII2(j*2 + OFFSET_X, i + OFFSET_Y, ' ', 0, 0);
                  putASCII2(j*2+1 + OFFSET_X, i + OFFSET_Y, ' ', 0, 0);
               }
            }
         } 

         /* ��Z�J�e�X�� */      
         showTanks(tanks, num_tanks); 
      
           
      /*  �� logo �� putString() ��ܥX�� 
         putString() �O�۩w�� function    ����b�S�w��m��ܦr�� 
         �o�� function ���{���X�]��b�o���ɮ׸�  �b main() ���� 
         �{���X����²�u  �u�O�b�j��̩I�s putASCII2() �Ӥw       */ 
         putString(OFFSET_X, OFFSET_Y-2, logo, 14, 3);

         putString(OFFSET_X, OFFSET_Y-1, str, 14, 1);


      /* ���F�n���@�s�� putASCII2() ���ʧ@���ͮĪG  
         �����n�I�s�@�� drawCmdWindow() �⤧�e�e���������e�@����ܨ�ù��W */ 
         drawCmdWindow();      

      } 
      /* end of if (tick%REFRESH_RATE) */ 



      /* ��L���� �B�z���ۤ��񪺪��p */ 
      for (k=0; k<NUM_KEYS; k++) {
         /* ����B�b�Q���U�����A  ��o�Өƥ�O���b key_down[k] */ 
         if(KEY_DOWN(key_val[k]) && !key_down[k]) {
            key_down[k] = 1;

            /* �̷ӧA�Q�n���ʧ@�ӳB�z���� */
            /* �b�o�ӨҤl�� ���U A, S, D, F, G 
            �i�H���O���� ���x�Z�J���C��  �o�X���ؤ��P���� 
            ���O�Y���ۤ��� �h�u�|�o�ͤ@���@��
            �P�ɫܦh��@�_���� ���|���ۤz�Z */ 
            switch (key_val[k]) {            
               case VK_A:            
                  tanks[0].color=(tanks[0].color+1)%15 + 1;
                  /* ������������� */ 
                  playAudio(&audio[0]);
                  break;
               case VK_S:            
                  tanks[1].color=(tanks[1].color+1)%15 + 1;
                  /* ������������� */ 
                  playAudio(&audio[1]);
                  break;
               case VK_D:            
                  tanks[2].color=(tanks[2].color+1)%15 + 1;
                  /* ������������� */ 
                  playAudio(&audio[2]);
                  break;
               case VK_F:            
                  tanks[3].color=(tanks[3].color+1)%15 + 1;
                  /* ������������� */ 
                  playAudio(&audio[3]);
                  break;
               case VK_G:            
                  tanks[4].color=(tanks[4].color+1)%15 + 1;
                  /* ������������� */ 
                  playAudio(&audio[4]);
                  break;
               case VK_ESCAPE:            
                  
                  /* �Ȱ��I������ */
                  pauseAudio(&audio[5]);
                  
                  /* �Ȯɶi�J�@���J�Ҧ� */ 
                  SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), (COORD){30, 20} );
                  SetConsoleMode (GetStdHandle (STD_INPUT_HANDLE), ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT|ENABLE_PROCESSED_INPUT);                   
                  scanf("%39s", str);
                  SetConsoleMode (GetStdHandle (STD_INPUT_HANDLE), ENABLE_LINE_INPUT); 
                  
                  /* �~�򼽩�쥻������ */ 
                  restartAudio(&audio[5]);
                  break;
               case VK_Q:          
                  IsEnding = 1;
                  break;
                  
            }
            
         }
         
         /* ����q�쥻�Q���U�����A �ܦ���}�����A  �o�O���F�B�z���ۤ��񪺱��p */ 
         if(KEY_UP(key_val[k]) && key_down[k]) {
            key_down[k] = 0;    
         }
                
      }


      /* ���ʩZ�J */ 
      moveTanks(tanks, num_tanks, tick);
             

                                   
   } /* while (IsEnding) */      
 

   /* �C�������e �Ȱ� 0.5 ��*/ 
   
   delay(0.5);   
   return 0; 
} 




/* ���{���Ȱ� sec �� */ 
void delay(float sec)
{
   clock_t startc;    
   startc = clock();
   for ( ; ; ) {	
	  if ((float)(clock()-startc)/CLOCKS_PER_SEC > sec) break;
   } 	 
} 
/* �b (x, y) �y�Ъ���m��ܦr�� p �����e  fg_color �O�e�����C��  bg_color �h�O�I�����C�� */ 
void putString(int x, int y, char *p, int fg_color, int bg_color)
{
   int i;
   for(i=0; i<strlen(p); i++) {
      putASCII2(x+i, y, p[i], fg_color, bg_color);
   }
}


/****************************************************************************************************/


void genTanks(Tank *tank_p, int num)
{
   int i, j, k;

   for (k=0; k<num; k++) {
      tank_p[k].x = rand()%(WIDTH-4) + 1;
      tank_p[k].y = rand()%(HEIGHT-4) + 1;
      tank_p[k].color = rand()%15 + 1;

      tank_p[k].duration = 30 + rand()%20;
      tank_p[k].last_tick = 0;

      tank_p[k].direction = rand()%3;
      
      for (i=0; i<3; i++) {
         for (j=0; j<3; j++) {
            tank_p[k].shape[i][j] 
            = TANK_SHAPE[tank_p[k].direction][i*3+j];
         }
      }
                
   }   
   
}

void showTanks(Tank *tank_p, int num)
{
   int i, j, k;
   
   for (k=0; k<num; k++) {  
      for (i=0; i<3; i++) {
         for (j=0; j<3; j++) {              
            switch (tank_p[k].shape[i][j]) {
               case 1:
               putASCII2((tank_p[k].x+ j)*2  + OFFSET_X, 
               tank_p[k].y + i + OFFSET_Y, 0xA1, tank_p[k].color, 0);  
               putASCII2((tank_p[k].x+ j)*2+1  + OFFSET_X, 
               tank_p[k].y + i +  OFFSET_Y, 0xBD, tank_p[k].color, 0);               
               break;
               
               case 2:
               putASCII2((tank_p[k].x+ j)*2  + OFFSET_X, 
               tank_p[k].y + i + OFFSET_Y, 0xA1, tank_p[k].color, 0);  
               putASCII2((tank_p[k].x+ j)*2+1  + OFFSET_X, 
               tank_p[k].y + i +  OFFSET_Y, 0xB4, tank_p[k].color, 0);               
               break;
               
               case 3:
               putASCII2((tank_p[k].x+ j)*2  + OFFSET_X, 
               tank_p[k].y + i + OFFSET_Y, 0xCA, tank_p[k].color, 0);  
               putASCII2((tank_p[k].x+ j)*2+1  + OFFSET_X, 
               tank_p[k].y + i +  OFFSET_Y, 0xA8, tank_p[k].color, 0);               
               break;
               
            }
         }
      }
   }

}

int moveTanks(Tank *tank_p, int num, int tick)
{
   int i, j, k;
   
   for (k=0; k<num; k++) {
      if (tick-tank_p[k].last_tick > tank_p[k].duration) {
         switch (tank_p[k].direction) {
            case 0:
               tank_p[k].y -= 1;
               break;
            case 1: 
               tank_p[k].x += 1;
               break;
            case 2:
               tank_p[k].y += 1;
               break;
            case 3: 
               tank_p[k].x -= 1;
               break;
         }
         
         if (tank_p[k].x < 1) {
            tank_p[k].direction = rand()%4;
            tank_p[k].x += 1;
         }
         else if (tank_p[k].x > WIDTH-4) {
            tank_p[k].direction = rand()%4;
            tank_p[k].x -= 1;
         }
         else if (tank_p[k].y < 1) {
            tank_p[k].direction = rand()%4;
            tank_p[k].y += 1;
         }
         else if (tank_p[k].y > HEIGHT-4) {
            tank_p[k].direction = rand()%4;
            tank_p[k].y -= 1;
         }

         /* ���ʤ����G�Q�����v�|�A���ܤ�V */ 
         if (rand()%10 > 7) {
            tank_p[k].direction = rand()%4;
         }                        
         /* ���ʤ����G�Q�����v�|�A���ܳt�� */ 
         if (rand()%10 > 7) {
            tank_p[k].duration = 30 + rand()%20;
         }                        
         
         tank_p[k].last_tick = tick;         
      
         for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {
               tank_p[k].shape[i][j] 
               = TANK_SHAPE[tank_p[k].direction][i*3+j];
            }
         }
      }
                
   }
   
}

