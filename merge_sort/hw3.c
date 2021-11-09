#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>

//GLOBAL var
int *result;

void merge_sort(int* raw, const int len){
    int a_len = (int)len/2, b_len = len-a_len;
    int *tmp = (int*) malloc(sizeof(int)*len);
    int i=0, j=0;

    if(len<=1){
        free(tmp);
        return;
    }
    //copy the input array
    memcpy(tmp, raw, sizeof(int)*len);
    //divde array and run mergesort to both subarrays
    merge_sort(tmp, a_len);
    merge_sort(&tmp[a_len], b_len);

    //run mergesort on both sorted subarrays
    i=0; j=a_len;
    while(i<a_len || j<len){
        if( i < a_len && ( j>=len || tmp[i] <= tmp[j]) ){
            raw[i+j-a_len] = tmp[i];
            i++;
        }else{
            raw[i+j-a_len] = tmp[j];
            j++;
        }
    }
    //free dynamic allocated memory
    free(tmp);
}


void* sort_thread(void* in){
    int i=0, *t = (int*)in;
    //get the length of input array
    while(t[i]!=INT_MAX)
        i++;

    merge_sort(t, i);
    return NULL;
}


void* merge_thread(void* in){
    int *a = ((int**)in)[0];
    int *b = ((int**)in)[1];
    int a_len=0, b_len=0;
    int i=0, j=0;

    //get the length of input arrays
    while(a[a_len]!=INT_MAX)
        a_len++;

    while(b[b_len]!=INT_MAX)
        b_len++;
    
    //run mergesort on input arrays, safe the result on global var
    result = (int*) malloc(sizeof(int)*(a_len+b_len));
    while(i<a_len || j<b_len){
        if( i < a_len && ( j>=b_len || a[i] <= b[j]) ){
            result[i+j] = a[i];
            i++;
        }else{
            result[i+j] = b[j];
            j++;
        }
    }

    return NULL;
}

int main(int argc, char* argv[]){
    FILE *input, *output;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int testcase[10000];
    int i, j, count=0;
    char *tmp;

    pthread_t t1, t2, t_merge;
    int *args[2];

    clock_t begin, end;

    if(argc<3){ //avoid invalid input
        printf("%s\n", "to execute: ./hw2.o testcase.txt output.txt");
        return -1;
    }

    input = fopen(argv[1],"r");  //open input file
    output = fopen(argv[2],"w"); //open output file
    if (input==NULL){ //avoid invalid input
        printf("%s\n", "file not exist!");
        return -1;   
    }
    //read testcase file line by line
    while ((read = getline(&line, &len, input)) != -1) {
        //get current time for time computation
        begin = clock();
        count++;

        i = 0;
        tmp = strtok(line," "); //split the line by space, transfer each token to integer
        while(tmp!=0){
            testcase[i] = atoi(tmp);
            i ++;
            tmp = strtok (NULL," ");
        }
        testcase[i] = INT_MAX; //add INT_MAX to note the end of the array

        //copy and divide the inpute testcase into two subarrays
        args[0] = (int*) malloc(sizeof(int)*(i/2+1));
        args[1] = (int*) malloc(sizeof(int)*(i+1-i/2));
        memcpy(args[0], testcase, sizeof(int)*i/2);
        memcpy(args[1], &testcase[i/2], sizeof(int)*(i+1-i/2));
        args[0][i/2] = INT_MAX; //add INT_MAX to note the end of the array

        //start 2 sorting threads
        pthread_create(&t1, NULL, sort_thread, args[0]); 
        pthread_create(&t2, NULL, sort_thread, args[1]);
        
        //wait for both sorting threads to finish
        pthread_join(t1, NULL);
        pthread_join(t1, NULL);
        
        //start the marging thread
        pthread_create(&t_merge, NULL, merge_thread, args); 
        pthread_join(t_merge, NULL);

        //output to output file
        for(j=0; j<i-1; j++){
            fprintf(output, "%d ", result[j]);
        }
        fprintf(output, "%d\n", result[j]);

        //free dynamic allocated memories
        free(args[0]);
        free(args[1]);
        free(result);

        //get current time, compute execution time of this testcase
        end = clock();
        printf("testcase %d: %f sec\n", count, (double)(end - begin) / CLOCKS_PER_SEC);
    }

    //close the files
    fclose(input);
    fclose(output);
    return 0;
}