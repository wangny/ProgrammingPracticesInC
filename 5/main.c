#include <stdio.h>
#include <math.h>
#define MAP_SIZE 12
#define CAR_SIZE 3

int map[MAP_SIZE][MAP_SIZE];
void map_reset(void);
void map_show(void);

int blocks[MAP_SIZE][MAP_SIZE];
void blocks_read(void);
void blocks_put_on_map(void);
int jewels[MAP_SIZE][MAP_SIZE];
void jewels_read(void);
void jewels_put_on_map(void);

int car[CAR_SIZE][CAR_SIZE] = {{'@', 'O', '@'}, {'O', 'O', 'O'}, {'O', 'O', 'O'}};
int car_row = 3, car_col = 4;
int car_direction = 3;
int car_earnings = 0;
void car_rotate90(void);
void car_put_on_map(void);
void car_move(void);

int main(void)
{
    int ch,i,j;
    char dirs[] = "RDLU";

    jewels_read();
    blocks_read();


    while ((ch=getchar()) != EOF) {
        i = car_row-1;
        while(i<=car_row+1){
            j = car_col-1;
            while(j<=car_col+1){
                    if(jewels[i][j]){
                        jewels[i][j] = 0;
                        car_earnings++;
                    }
                    j++;
            }
            i++;
        }

        if (ch=='R') {
            car_rotate90();
        }
        if (ch=='F') {
            car_move();
        }

        map_reset();
        jewels_put_on_map();
        blocks_put_on_map();
        car_put_on_map();
        /* You may call map_show() to print the current state.
        Be sure to remove it before you submit the code*/
        map_show();
    }


    printf("%d\n", car_earnings);
    printf("%d %d\n", car_row, car_col);
    printf("%c\n", dirs[car_direction]);

    return 0;
}

void blocks_read(void)
{
    int n, i;
    int row, col;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d%d", &row, &col);
        blocks[row][col] = 1;
    }
}

void jewels_read(void)
{
    int n, i;
    int row, col;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d%d", &row, &col);
        jewels[row][col] = 1;
    }
}

void blocks_put_on_map(void)
{
    int i, j;
    for (i=0; i<MAP_SIZE; i++) {
        for (j=0; j<MAP_SIZE; j++) {
            if (blocks[i][j])
                map[i][j] = '#';
        }
    }
}

void jewels_put_on_map()
{
    int i, j;
    for (i=0; i<MAP_SIZE; i++) {
        for (j=0; j<MAP_SIZE; j++) {
            if (jewels[i][j])
                map[i][j] = '$';
        }
    }
}

void map_reset(void)
{
    int i, j;
    for (i=0; i<MAP_SIZE; i++) {
        for (j=0; j<MAP_SIZE; j++) {
            map[i][j] = '.';
        }
    }
    for (i=0; i<MAP_SIZE; i++) {
        map[i][0] = 'H';
        map[i][MAP_SIZE-1] = 'H';
    }
    for (j=0; j<MAP_SIZE; j++) {
        map[0][j] = 'H';
        map[MAP_SIZE-1][j] = 'H';
    }
}

void map_show(void)
{
    int i, j;
    for (i=0; i<MAP_SIZE; i++) {
        for (j=0; j<MAP_SIZE; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void car_put_on_map(void)
{
    int i, j;
    for (i=0; i<CAR_SIZE; i++) {
        for (j=0; j<CAR_SIZE; j++) {
            map[i+car_row-1][j+car_col-1] = car[i][j];
        }
    }
}

void car_rotate90(void)
{
    if (car_direction == 3){
        car_direction = 0;
    } else {
        car_direction = car_direction + 1;
    }
}

void car_move(void)
{
    int i,j,x,y,k;
    k = 0;

    i = car_row-1;
    while(i<=car_row+1){
            j = car_col-1;
            while(j<=car_col+1){
                    if(blocks[i][j]){
                        k++;
                    }
                    j++;
            }
            i++;
    }

    if(car_direction==0 && car_col != MAP_SIZE-3){
        for(y=car_row-1;y<=car_row+1;y++){
            if(blocks[y][car_col+2]){
                k++;
            }
        }
        if(k==0){
            car_col++;
        }
    }

    if(car_direction==1 && car_row != MAP_SIZE-3){
        for(x=car_col-1;x<=car_col+1;x++){
            if(blocks[car_row+2][x]){
                k++;
            }
        }
        if(k==0){
            car_row++;
        }
    }

    if (car_direction==2 && car_col != 2){
        for(y=car_row-1;y<=car_row+1;y++){
            if(blocks[y][car_col-2]){
                k++;
            }
        }
        if(k==0){
            car_col = car_col - 1;
        }
    }

    if (car_direction==3 && car_row != 2){
        for(x=car_col-1;x<=car_col+1;x++){
            if(blocks[car_row-2][x]){
                k++;
            }
        }
        if(k==0){
            car_row = car_row - 1;
        }
    }
}
