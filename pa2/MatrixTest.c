//-----------------------------------------------------------------
//  CMPS101 PA2
//  Mohammad Abdulqder (mabdulqa)
//  
//  MatrixTest.c
//  Test file for Matrix ADT.
//-----------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "List.h"
#include "Matrix.h"

int main(void){
    Matrix M = newMatrix(4);
    Matrix N = newMatrix(4);
    double number = 0.0;

    for(int i = 1; i <=size(M); i++){
        number = number + (double) (i * i);
        number = (number/(double) i * i);
        for(int j = 1; j <=size(M); j++){
            if(number/2.0 > 0.99){
                changeEntry(N, i, j, number);
            }
            else if(number/2.0 <= 0.99){
                changeEntry(M, i, j, number);
            }
        }
    }
    // M and N
    printf("M\n");
    printMatrix(stdout, M);
    printf("\n");
    printf("N\n");
    printMatrix(stdout, N);
    printf("\n");

    // scalarMult and transpose test
    Matrix O = transpose(N);
    Matrix A = scalarMult(0.5, M);
    Matrix B = scalarMult(0.5, N);

    printf("A the scalarMult of M by 0.5\n");
    printMatrix(stdout, A);
    printf("\n");
    printf("B the scalarMult of N by 0.5\n");
    printMatrix(stdout, B);
    printf("\n");
    printf("Transpose of N");
    printMatrix(stdout, O);
    printf("\n");

    freeMatrix(&M);
    freeMatrix(&N);
    freeMatrix(&O);

    // sum diff and product test
    Matrix C = sum(A, B);
    Matrix D = diff(A, B);
    Matrix E = product(A, B);

    printf("sum of A and B\n");
    printMatrix(stdout, C);
    printf("\n");
    printf("diff of A and B\n");
    printMatrix(stdout, D);
    printf("\n");
    printf("product of A and B");
    printMatrix(stdout, E);
    printf("\n");

    //copy and makeZero test
    Matrix F = copy(A);

    printf("F, the copy of A\n");
    printMatrix(stdout, F);
    printf("\n");
    if(equals(F, A) == 1){
        printf("True, A and F are equal.\n");
    }else{
        printf("False, A and F are not equal.\n");
    }
    makeZero(A);
    makeZero(F);
    printf("F, the copy of A\n");
    printMatrix(stdout, F);
    printf("\n");
    
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);

    printf("Test passed my boi.");

    return 0;
}