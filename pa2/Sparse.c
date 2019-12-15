//-----------------------------------------------------------------
//  CMPS101 PA2
//  Mohammad Abdulqder (mabdulqa)
//  
//  Sparse.c
//  Main program for the Matrix and List ADTs.
//-----------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Matrix.h"

#define MAX_LEN 12

int main(int argc, char* argv[]){
    FILE* in;
    FILE* out;
    if (argc != 3){
        fprintf(stderr, "Usage: Sparse <infile> <outfile>");
        exit(1);
    }
    in = fopen(argv[1], "r");
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

    int linecount = 0;

    char size[MAX_LEN];
    char Annz[MAX_LEN];
    char Bnnz[MAX_LEN];
    int intSize;
    int ANNZ;
    int BNNZ;
    for(linecount = 0; linecount< 1; linecount++){
        fscanf(in, "%s %s %s", size, Annz, Bnnz);
        intSize = atoi(size);
        ANNZ = atoi(Annz);
        BNNZ = atoi(Bnnz);
    }

    Matrix A = newMatrix(intSize);
    Matrix B = newMatrix(intSize);


    char newLine1[MAX_LEN];
    char newLine2[MAX_LEN];
    char newLine3[MAX_LEN];
    // sees how many lines are in input file.
    while(fscanf(in, "%s %s %s", newLine1, newLine2, newLine3) != EOF){ 
        int i = atoi(newLine1);
	    int j = atoi(newLine2);
	    double data = atoi(newLine3);
        if(linecount <= ANNZ){
            changeEntry(A, i, j, data);
        }else{
            changeEntry(B, i, j, data);
        }
        linecount++;
    }

    fprintf(out, "A has %d non-zero entries:\n", ANNZ);
    printMatrix(out, A);
    fprintf(out, "\n");
    fprintf(out, "B has %d non-zero entries:\n", BNNZ);
    printMatrix(out, B);
    fprintf(out, "\n");

    Matrix C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");

    Matrix D = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, D);
    fprintf(out, "\n");

    Matrix E = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, E);
    fprintf(out, "\n");

    Matrix F = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, F);
    fprintf(out, "\n");

    Matrix G = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, G);
    fprintf(out, "\n");

    Matrix H = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, H);
    fprintf(out, "\n");

    Matrix I = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, I);
    fprintf(out, "\n");

    Matrix J = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, J);
    fprintf(out, "\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);

    fclose(in);
    fclose(out);

    return 0;
}
