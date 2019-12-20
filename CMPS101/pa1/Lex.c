//-----------------------------------------------------------------
//  CMPS101 PA1
//  Mohammad Abdulqder (mabdulqa)
//  
//  Lex.c
//  Main program for List ADT.
//-----------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 255

int main(int argc, char * argv[]){
    if (argc != 3){ // makes sure in and out are specified.
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    FILE *in;
    in = fopen(argv[1], "r");
    FILE *out;
    out = fopen(argv[2], "w");

    // checks if in and out files are able to be opened.
    if( in==NULL ){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if( out==NULL ){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int countLine = 0;
    char newLine[MAX_LEN];
    // sees how many lines are in input file.
    while(fgets(newLine, MAX_LEN, in) != NULL) countLine++;
    // rewinds to begining.
    rewind(in);
    char infileData[countLine][MAX_LEN]; //creates the 2D array 
    
    int lineNum = 0;
    while(fgets(newLine, MAX_LEN, in) != NULL){ 
        strcpy(infileData[lineNum], newLine);
        lineNum++;
    }
    List L = newList();
    append(L, 0);


    int j;
    for(int i = 1 ; i<lineNum; i++){
        char* currentline = infileData[i];
        j = i - 1;
        moveBack(L);
        while(j >= 0 && strcmp(currentline, infileData[get(L)])< 0){
            movePrev(L);
            j--;
        }
        if(index(L) >= 0) insertAfter(L, i);
        else prepend(L, i);
    }

    moveFront(L);
    int printLine = 0;
    while(printLine < lineNum){
        if(printLine == lineNum - 1){
            fprintf(out, "%s", infileData[get(L)]);
        }
        else{
            fprintf(out, "%s\n", infileData[get(L)]);
        }
        moveNext(L);
        printLine++;
    }

    fclose(in);
    fclose(out);
    freeList(&L);

    return 0;
}