#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <mmsystem.h>
/*
  For sound effect:
  Dev C++: In [Project Options]->[Parameters]->[Linker] add the parameter -lwinmm
  Code::Blocks: In [Project]->[Build options]->[Linker settings] add the parameter -lwinmm at [other linker options]
*/

#include "console_draw.h"

#define WIDTH     17
#define HEIGHT    15
#define OFFSET_X  5
#define OFFSET_Y  1
void delay(float sec);
void putString(int x, int y, char *p, int fg_color);
void sound(int select);

#define N_PL 3
#define N_MST 10
#define N_ENG 10
#define N_SCK 10
#define INIT_VITAL 5
#define INIT_CHI 5

/* global �}�C    �ΨӰO���a�Ϫ����e */

typedef enum _action {MOVE_FORWARD, MOVE_BACKWORD, TURN_RIGHT, TURN_LEFT, SHOOT, RECHARGE, PICK, IDLE} Action;

typedef struct _player {
    int row;
    int col;
    int direction;
    int vital;
    int chi;
    char fov[3][3];
    Action act;
} Player;


typedef struct _monster {
    int row;
    int col;
    int direction;
    int vital;
    int chi;
    char fov[3][3];
    Action act;
} Monster;

typedef struct _energy {
    int row;
    int col;
    int amount;
} Energy;

typedef struct _shock {
    int row;
    int col;
} Shock;


Action player0(Player pl);
Action player1(Player pl);
Action player2(Player pl);


void update(char ori_a[][WIDTH], char a[][WIDTH], Player *pl, int L, Monster *mst, int M, Energy *eng, int E, Shock *sck, int K);
void apply(char ori_a[][WIDTH], char a[][WIDTH], Player *pl, int L, Monster *mst, int M, Energy *eng, int E, Shock *sck, int K);

int main(void)
{
	FILE *fp;
	int i, j, L, K, M, N, E;
	char *pl_icon = ">V<^";


    char a[HEIGHT][WIDTH], ori_a[HEIGHT][WIDTH];
    Player pl[N_PL];
    Monster mst[N_MST];
    Energy eng[N_ENG];
    Shock sck[N_SCK];

    int round = 0;
    char str[100];

    int done = 0;

	int d, r, c, front;
    int rowf[] = {0, 1, 0, -1};
    int colf[] = {1, 0, -1, 0};


	/* �յ۶}�ҥؿ��U�� map.txt �� */
	fp = fopen("map.txt", "r");
   /* ���p�ɮצs�b �NŪ���ɮפ��e ��}�C�������̷Ӧ�m�@�Ӥ@�ӳ]�w�n */
   	if (fp != NULL) {
        L = K = N = M = E = 0;
      	for (i = 0; i < HEIGHT; i++) {      /* �ѩ�a�Ϫ����e�O�T�w��  �ҥH�N�����Ψ�Ӱj���Ū�� */
         	for (j = 0; j < WIDTH; j++) {
            	fscanf(fp, "%c", &a[i][j]);
            	if (a[i][j]=='V') {
            		pl[L].row = i;
            		pl[L].col = j;
            		pl[L].direction = rand()%4;
            		pl[L].vital = INIT_VITAL;
            		pl[L].chi = INIT_CHI;
                    a[i][j] = ' ';
            		L++;
				} else if (a[i][j]=='W') {
            		mst[M].row = i;
            		mst[M].col = j;
            		mst[M].direction = rand()%4;
            		mst[M].vital = INIT_VITAL;
            		mst[M].chi = INIT_CHI*1000;
            		a[i][j] = ' ';
            		M++;
				} else if (isdigit(a[i][j])) {
                    eng[E].row = i;
            		eng[E].col = j;
            		eng[E].amount = a[i][j]-'0';
            		a[i][j] = ' ';
            		E++;
				} else if (a[i][j]=='@') {
            		sck[K].row = i;
            		sck[K].col = j;
            		a[i][j] = ' ';
            		K++;
				}
         	}
         	fscanf(fp, "%*c");  /* �o�@�B�O���F��C�@�浲����  '\n' �Y��   "%*c" ���N��OŪ���@�Ӧr���åB�ᱼ */
      	}
      	fclose(fp);
   	} else {
		return -1;
   	}

   	for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            ori_a[i][j] = a[i][j];
        }
   	}
    apply(ori_a, a, pl, L, mst, M, eng, E, sck, K);

	/* �L�a�j��  �̭��]�t�F�o�ӵ{�����D�n�u�@
   	�ӥB�C���j��|���_��̷s���e����ܨ�ù��W  ���O���ʵe�@�� �C���j���s�@���e�� */
   	while (!done) {

        for (i=0; i<L; i++) {
            if (pl[i].vital<=0) {
                done = 1;
                break;
            }
        }

      	/* �� putASCII() ��a�ϵe�X��   */
      	for (i = 0; i < HEIGHT; i++) {
         	for (j = 0; j < WIDTH; j++) {
            	putASCII(j + OFFSET_X, i + OFFSET_Y, a[i][j] , 3);
         	}
      	}
      	for (i=0; i<L; i++) {
            putASCII(pl[i].col + OFFSET_X, pl[i].row + OFFSET_Y, pl_icon[pl[i].direction], i%4);
      	}
      	/* current location */


        sprintf(str, "Round: %05d", round++);
        putString(2, 16, str, 0);
        for (i=0; i<L; i++) {
            sprintf(str, "Vital: %03d, Chi: %03d", pl[i].vital, pl[i].chi);
            putString(2, 17+i, str, i%4);
        }


      	/* ���F�n���@�s�� putASCII() ���ʧ@���ͮĪG
         �����n�I�s�@�� drawCmdWindow() �⤧�e�e���������e�@����ܨ�ù��W */
      	drawCmdWindow();

        for (i=0; i<L; i++) {
            pl[i].act = IDLE;
        }
        for (i=0; i<L; i++) {
            switch (i) {
            case 0:
                pl[0].act = player0(pl[0]);
                break;
            case 1:
                pl[1].act = player1(pl[1]);
                break;
            case 2:
                pl[2].act = player2(pl[2]);
                break;
            }
            apply(ori_a, a, pl, L, mst, M, eng, E, sck, K);
        }

        for (i=0; i<M; i++) {
            mst[i].act = rand()%IDLE;

            r = mst[i].row;
            c = mst[i].col;
            d = mst[i].direction;

            front = a[r+rowf[d]][c+colf[d]];

            if (front=='>' || front=='V' || front=='<' || front=='^') {
                mst[i].act = SHOOT;
            }

            apply(ori_a, a, pl, L, mst, M, eng, E, sck, K);
        }



		delay(0.5);

   	} /* while (1) */

	sound(3);
   	return 0;
}


Action player0(Player pl)
{
  //  static char my_map[HEIGHT][WIDTH];
    int rowf[] = {0, 1, 0, -1};
    int colf[] = {1, 0, -1, 0};
    int d;
    char front;

    Action move[4] = {MOVE_FORWARD, MOVE_BACKWORD, TURN_RIGHT, TURN_LEFT};

    d = pl.direction;
    front = pl.fov[1+rowf[d]][1+colf[d]];
    if (pl.chi==0) {
        return RECHARGE;
    }
    if (front=='>' || front=='V' || front=='<' || front=='^') {
        return SHOOT;
    }
    if (front=='B' || front=='W' || front=='E' || front=='M') {
        return SHOOT;
    }
    if (isdigit(front) && front!='0') {
        return PICK;
    }
    if (front == '@') {
        return MOVE_BACKWORD;
    }
    return move[rand()%4];
}
Action player1(Player pl)
{
  //  static char my_map[HEIGHT][WIDTH];
    int rowf[] = {0, 1, 0, -1};
    int colf[] = {1, 0, -1, 0};
    int d;
    char front;

    Action move[4] = {MOVE_FORWARD, MOVE_BACKWORD, TURN_RIGHT, TURN_LEFT};

    d = pl.direction;
    front = pl.fov[1+rowf[d]][1+colf[d]];
    if (front=='>' || front=='V' || front=='<' || front=='^') {
        return SHOOT;
    }
    if (front=='B' || front=='W' || front=='E' || front=='M') {
        return SHOOT;
    }
    if (isdigit(front) && front!='0') {
        return PICK;
    }
    if (front == '@') {
        return MOVE_BACKWORD;
    }
    return move[rand()%4];
}
Action player2(Player pl)
{
    return 0;
}

void update(char ori_a[][WIDTH], char a[][WIDTH], Player *pl, int L, Monster *mst, int M, Energy *eng, int E, Shock *sck, int K)
{
    char *pl_icon = ">V<^";
    char *mst_icon = "BWEM";

    int r, c, d;
    int i, j, k;
   	for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            a[i][j] = ori_a[i][j];
        }
   	}
    for (i=0; i<L; i++) {
        a[pl[i].row][pl[i].col] = pl_icon[pl[i].direction];
    }
    for (i=0; i<M; i++) {
        a[mst[i].row][mst[i].col] = mst_icon[mst[i].direction];
    }
    for (i=0; i<E; i++) {
        a[eng[i].row][eng[i].col] = eng[i].amount + '0';
    }
    for (i=0; i<K; i++) {
        a[sck[i].row][sck[i].col] = '@';
    }

    for (i=0; i<L; i++) {
        r = pl[i].row;
        c = pl[i].col;
        d = pl[i].direction;
        for (j=0; j<3; j++) {
            for (k=0; k<3; k++) {
                pl[i].fov[j][k] = a[r-1+j][c-1+k];
            }
        }
        switch (d) {
            case 0:
            pl[i].fov[0][0] = '?';
            pl[i].fov[1][0] = '?';
            pl[i].fov[2][0] = '?';
            break;
            case 1:
            pl[i].fov[0][0] = '?';
            pl[i].fov[0][1] = '?';
            pl[i].fov[0][2] = '?';
            break;
            case 2:
            pl[i].fov[0][2] = '?';
            pl[i].fov[1][2] = '?';
            pl[i].fov[2][2] = '?';
            break;
            case 3:
            pl[i].fov[2][0] = '?';
            pl[i].fov[2][1] = '?';
            pl[i].fov[2][2] = '?';
            break;
        }
    }
}


void apply(char ori_a[][WIDTH], char a[][WIDTH], Player *pl, int L, Monster *mst, int M, Energy *eng, int E, Shock *sck, int K)
{
    int i, j, actor;
    //char str[100];
    int rowf[] = {0, 1, 0, -1};
    int colf[] = {1, 0, -1, 0};
    int r, c, d;

    update(ori_a, a, pl, L, mst, M, eng, E, sck, K);

    actor = -1;
    for (i=0; i<L; i++) {
        if (pl[i].act != IDLE) {
            actor = i;
            break;
        }
    }
    if (actor!=-1) {
        r = pl[actor].row;
        c = pl[actor].col;
        d = pl[actor].direction;
        switch (pl[actor].act) {
        case MOVE_FORWARD:
            if (a[r+rowf[d]][c+colf[d]] == ' ') {
                pl[actor].row = r+rowf[d];
                pl[actor].col = c+colf[d];
            }
            break;
        case MOVE_BACKWORD:
            if (a[r-rowf[d]][c-colf[d]] == ' ') {
                pl[actor].row = r-rowf[d];
                pl[actor].col = c-colf[d];
            }
            break;
        case TURN_RIGHT:
            pl[actor].direction = (d+1)%4;
            break;
        case TURN_LEFT:
            pl[actor].direction = (d+3)%4;
            break;
        case SHOOT:
            if (pl[actor].chi>0) {
                for (i=0; i<L && i!=actor; i++) {
                    if (pl[i].row==(r+rowf[d]) && pl[i].col==(c+colf[d])) {
                        if (pl[i].vital>0) {
                            pl[i].vital--;
                        }
                        break;
                    }
                }

                pl[actor].chi--;
            }
            break;
        case RECHARGE:
            if (pl[actor].vital>1) {
                pl[actor].vital--;
                pl[actor].chi += INIT_CHI;
            }
            break;
        case PICK:
            for (i=0; i<E; i++) {
                if (eng[i].row==(r+rowf[d]) && eng[i].col==(c+colf[d])) {
                    if (eng[i].amount>0) {
                        eng[i].amount--;
                        pl[actor].vital += INIT_VITAL;
                        break;
                    }
                }
            }
            break;
        case IDLE:
            break;
        }
        pl[actor].act = IDLE;
    } else {
        actor = -1;
        for (i=0; i<M; i++) {
            if (mst[i].act != IDLE) {
                actor = i;
                break;
            }
        }
        if (actor!=-1) {
            r = mst[actor].row;
            c = mst[actor].col;
            d = mst[actor].direction;
            switch (mst[actor].act) {
            case MOVE_FORWARD:
                if (a[r+rowf[d]][c+colf[d]] == ' ') {
                    mst[actor].row = r+rowf[d];
                    mst[actor].col = c+colf[d];
                }
                break;
            case MOVE_BACKWORD:
                if (a[r-rowf[d]][c-colf[d]] == ' ') {
                    mst[actor].row = r-rowf[d];
                    mst[actor].col = c-colf[d];
                }
                break;
            case TURN_RIGHT:
                mst[actor].direction = (d+1)%4;
                break;
            case TURN_LEFT:
                mst[actor].direction = (d+3)%4;
                break;
            case SHOOT:
                for (i=0; i<L; i++) {
                    if (pl[i].row==(r+rowf[d]) && pl[i].col==(c+colf[d])) {
                        if (pl[i].vital>0) {
                            pl[i].vital-=2;
                        }
                        break;
                    }
                }
                break;
            case RECHARGE:
            case PICK:
            case IDLE:
                break;
            }
            mst[actor].act = IDLE;
        }

    }

    for (i=0; i<K; i++) {
        r = sck[i].row;
        c = sck[i].col;
        for (j=0; j<L; j++) {
            if ((pl[j].col==c && pl[j].row==r+1) ||
                (pl[j].col==c && pl[j].row==r-1) ||
                (pl[j].col==c+1 && pl[j].row==r) ||
                (pl[j].col==c-1 && pl[j].row==r) ) {
                    if (pl[j].vital>0)
                        pl[j].vital--;
                }
        }
    }
    update(ori_a, a, pl, L, mst, M, eng, E, sck, K);
}









/***********************
���U�O�۩w�� functions
�]�t dalay(), putString(), sound()
***********************/

/* ���{���Ȱ� sec �� */
void delay(float sec)
{
   	clock_t startc;
   	startc = clock();
   	for ( ; ; ) {
		if ((float)(clock()-startc)/CLOCKS_PER_SEC > sec) break;
  	}
}
/* �b (x, y) �y�Ъ���m��ܦr�� p �����e  fg_color �O�C��
   �ǤJ���r�� p �O�Ϋ��Ъ��覡��r���}�C���}�Y��}�ǤJ
   �ѩ�ΨӪ�ܦr�ꪺ�r���}�C  �|�O�� '\0' �@������
   �]���i�H�ϥ� strlen() �ӧP�_�r�����?
*/
void putString(int x, int y, char *p, int fg_color)
{
   	int i;
   	for(i=0; i<strlen(p); i++) {
      	putASCII(x+i, y, p[i], fg_color);
   	}
}

void sound(int select)
{

   if (select == 0) {
   /*
      �� PlaySound() ���� wav �ɮ�
      ���] "recycle.wav" �n���ɩM�{���X��b�ۦP�ؿ�
      PlaySound("recycle.wav", NULL, SND_ASYNC|SND_FILENAME);
      �|�b�I���}�Ҩü��� recycle.wav (����� ��L��L�ʧ@���i�H�~��)

      �n�ϥ� PlaySound() �o�� function
      �����n���� [Project] -> [Project Options] �]�w (�b Dev-C++ �̭����U  Alt+P)
      ��� Parameters ���@��  �M��b Linker �̭��[�J�@��
       -lwinmm
 	  �p�G�O Code::Blocks �h�n��   [Project]->[Build options]->[Linker settings] [other linker options]
	  �[�J�Ѽ� -lwinmm

      �A compile �N�i�H���Ͱ�����
   */
      PlaySound(TEXT("metalplate.wav"), NULL, SND_ASYNC|SND_FILENAME);
   }
   else if (select == 1) {
      PlaySound(TEXT("applause.wav"), NULL, SND_ASYNC|SND_FILENAME);
      Sleep(4000);
   }
   else if (select == 2) {
      PlaySound(TEXT("metal.wav"), NULL, SND_ASYNC|SND_FILENAME);
      Sleep(2000);
   }
   else if (select == 3) {
      PlaySound(TEXT("recycle.wav"), NULL, SND_ASYNC|SND_FILENAME);
      Sleep(1000);
   }

}
