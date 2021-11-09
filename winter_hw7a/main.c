#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define ONLINE_JUDGE

/*
struct for product items
*/
typedef struct _Product {
    char name[51];
    float price;
    float review;
    int  num_reviews;
} Product;


int compare(const void *a, const void *b)
{
	Product *ia, *ib;
	ia = *(Product **)a;
	ib = *(Product **)b;
	if( (ia->review) > (ib->review) ){
        return 1;
	}else if( (ia->review) < (ib->review) ){
        return -1;
	}else if( (ia->price) > (ib->price) ) {
        return -1;
	}else if( (ia->price) < (ib->price) ) {
        return 1;
	}else{
        return 0;
	}
}


void show_product(Product *item)
{
    printf("%s, ", item->name);
    printf("$%.2f, ", item->price);
    printf("%.1f\n", item->review);
}

int main(void)
{
    Product **items;
    int i, j,len;
    int ndata, nqueries;
    char query[51]={'/0'};


    scanf("%d", &ndata);
    items = (Product**) malloc(sizeof(Product*) * ndata);

    for (i=0; i<ndata; i++) {
        items[i] = (Product*) malloc(sizeof(Product));
        gets(items[i]->name);
        items[i]->name[strlen(items[i]->name)-1] = 0;
        scanf("%f", &items[i]->price);
        scanf("%f", &items[i]->review);
        scanf("%d", &items[i]->num_reviews);
        while (getchar() !='\n');

        show_product(items[j]);
    }

    /*qsort(items, ndata, sizeof(Product *), compare);

    scanf("%d", &nqueries);

    for (i=0; i<nqueries; i++) {
        scanf("%s",query);
        len = strlen(query);
        printf("%s\n",query);

        for(j=0;j<ndata;j++){
            if(strncmp(query,items[j]->name,len)==0){
                show_product(items[j]);
            }
        }
    }*/

    for (i=0; i<ndata; i++) {
        free(items[i]);
    }
    free(items);
    return 0;
}
