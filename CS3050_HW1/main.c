/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Matthew Carroll
 *
 * Created on August 25, 2017, 2:05 PM
 */

//Libraries
#include "input_error.h"
#include "vector.h"
#include <ctype.h>
#include <limits.h>

//Prototypes
void read(char* file, Vector* vec);
void print(Vector* vec);
void msort(int* data, int low, int size);
void merge(int* data, int low, int mid, int size);
void empty(Vector* vec);
Vector combine(Vector* vec);
void Fmsort(Vector* vec, int low, int size);
void Fmerge(Vector* vec, int low, int mid, int size);
void write(Vector* vec, char* ofile);

//Begin Main
int main(int argc, char *argv[]) {

    //checks for correct number of arguments
    if(argc != 3){
        exit(1);
    }
    Vector vec;
    init_vector(&vec);
    read(argv[1], &vec);
    //print(&vec);
    //printf("\n\n\n******BREAK BETWEEN FIRST PRINT AND SORT******\n\n\n");
    msort(vec.data, 0, vec.size - 1);
    //print(&vec);
    //printf("\n\n\n******BREAK BETWEEN SECOND PRINT AND COMBINE******\n\n\n");
    vec = combine(&vec);
    //print(&vec);
    Fmsort(&vec, 0, vec.size - 1);
    //printf("\n\n\n******BREAK BETWEEN THIRD PRINT AND REORDER******\n\n\n");
    //print(&vec);
    write(&vec, argv[2]);
    empty(&vec);


    return 1;
}

//Begin Read Function
void read(char* file, Vector* vec){

    int temp;
    FILE* fp = fopen(file, "r");
    if(!fp){
        exit(2);
    }

    //error check
    if(feof(fp)){
        exit(7);
    }
    while(!feof(fp)){
        //reads in looking for int variable, if its not an int then it sends back something other than 1
        if(fscanf(fp, "%d\n", &temp) != 1){
            exit(6);
        }
        //makes sure the variable is actually a number
        if(temp >= 0 && temp <= UINT_MAX){
            //calls vector function from vector.h
            insert_element_vector(vec, temp);
        }
        else{
            exit(6);
        }  
    }
    fclose(fp);
    fp = NULL;
    //error check
    if(fp != NULL){
        exit(3);
    }
}

//Begin Print Function
void print(Vector* vec){
    int i;
    for(i = 0; i < vec->size; i++){
        printf("Number: %d Count: %d\n", access_element_vector(vec, i), access_frequency_vector(vec, i));
    }
}

//Begin Msort Function will sort via element
void msort(int* data, int low, int size){

    //splits the list recursively to compare each element to each other
    if(low < size){
        int mid = (low + size)/2;
        msort(data, low, mid);
        msort(data, mid + 1, size);
        //after split, the merge will combine
        merge(data, low, mid, size);
    }
    else{
        return;
    }
}

//Begin Merge Function
void merge(int* data, int low, int mid, int size){
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = size - mid;
    int l[n1], r[n2];

    //sets data to a left subarray
    for(i = 0; i < n1; i++){
        l[i] = data[low + i];
    }
    //sets higher data to right subarray
    for(j = 0; j < n2; j++){
        r[j] = data[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = low;

    //actual combining part, compares left array to right
    while(i < n1 && j < n2){
        if(l[i] <= r[j]){
            data[k] = l[i];
            i++;
        }
        else{
            data[k] = r[j];
            j++;
        }
        k++;
    }

    //next 2 whiles fill the array with any left over data
    while(i < n1){
        data[k] = l[i];
        i++;
        k++;
    }
    while(j < n2){
        data[k] = r[j];
        j++;
        k++;
    }
}

//Begin Combine Function
Vector combine(Vector* vec){
    int i, j, k, size, temp[vec->size];
    size = vec->size;
    j = 0;
    k = 0;
    //used to make sure the array isn't too small to get stuck in the combine function
    if(size == 0 || size == 1){
        return *vec;
    }

    for(i = 0; i < size - 1; i++){
        //checks to see if elements i and i+1 are the same
        if(vec->data[i] != vec->data[i + 1]){
            //if they are not it saves the data to a temporary array
            temp[j++] = vec->data[i];
        }
        else{
            //if they are it increases the frequency
            ++vec->frequency[k];
            k--;
        }
        k++;
    }
    //caps off temp array
    temp[j] = vec->data[size - 1];
    k = 0;
    j++;
    //switches temp array back to vector
    for(i = 0; i < j; i++){
        vec->data[i] = temp[i];
        k++;
    }
    //gives the vector its new size
    vec->size = j;
    return *vec;
}

//Begin second msort Function
//same split function as before, just for frequency. See above comments
void Fmsort(Vector* vec, int low, int size){


    if(low < size){
        int mid = (low + size)/2;
        Fmsort(vec, low, mid);
        Fmsort(vec, mid + 1, size);
        Fmerge(vec, low, mid, size);
    }
    else{
        return;
    }
}

//Begin Fmerge Function
//same merge function as before, just for frequency. See above comments
void Fmerge(Vector* vec, int low, int mid, int size){
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = size - mid;
    int l[n1], r[n2], l2[n1], r2[n2];

    for(i = 0; i < n1; i++){
        l[i] = vec->data[low + i];
        l2[i] = vec->frequency[low + i];
    }
    for(j = 0; j < n2; j++){
        r[j] = vec->data[mid + 1 + j];
        r2[j] = vec->frequency[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = low;

    while(i < n1 && j < n2){
        if(l2[i] <= r2[j]){
            vec->data[k] = l[i];
            vec->frequency[k] = l2[i];
            i++;
        }
        else{
            vec->data[k] = r[j];
            vec->frequency[k] = r2[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        vec->data[k] = l[i];
        vec->frequency[k] = l2[i];
        i++;
        k++;
    }
    while(j < n2){
        vec->data[k] = r[j];
        vec->frequency[k] = r2[j];
        j++;
        k++;
    }
}

//Function used to write to output.txt file
void write(Vector* vec, char* ofile){
    FILE* fptr = fopen(ofile, "w");
    int i, size;
    size = vec->size;

    //error check
    if(fptr == NULL){
        exit(4);
    }
    for(i = 0; i < size; i++){
        fprintf(fptr, "%d\n", vec->data[i]);
    }
    fclose(fptr);
    fptr = NULL;
    if(fptr != NULL){
        exit(5);
    }
}

//Begin Empty Function
void empty(Vector* vec){
    free_vector(vec);
}

