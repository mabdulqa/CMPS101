//-----------------------------------------------------------------
//  CMPS101 PA2
//  Mohammad Abdulqder (mabdulqa)
//  
//  Matrix.c
//  Matrix ADT file with its public and private functions.
//-----------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Matrix.h"


// Entry and Matrix Structs --------------------------------------

typedef struct EntryObj{
    int column;
    double data;
} EntryObj;

typedef EntryObj* Entry;

typedef struct MatrixObj{
    List* row;
    int size;
    int NNZ;
} MatrixObj;

// Constructors and Deconstructors -------------------------------

Entry newEntry(int j, double data){
    Entry E;
    E = malloc(sizeof(EntryObj));
    E->column = j;
    E->data = data;
    return E;
}

void freeEntry(Entry* pE){
    if(pE!=NULL && *pE!=NULL){ 
        free(*pE);
        *pE = NULL;
    }
}

Matrix newMatrix(int n){
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->row = calloc(n+1, sizeof(List));
    for(int i = 1; i<= M->size; i++){
        M->row[i] = newList();
    }
    M->NNZ = 0;
    return M;
}

void freeMatrix(Matrix* pM){
    if(pM!=NULL && *pM!=NULL){ 
        makeZero(*pM);
        free(*pM);
        *pM = NULL;
    }
}

// Basic Matrix ---------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if(M == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if(M == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if(A == NULL && B == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    if(A->size != B->size) return 0;
    else if(A->NNZ != B->NNZ) return 0;
    else{
        for(int i = 1; i<= A->size; i++){
            if(length(A->row[i]) != length(B->row[i])) return 0;
            else if(length(A->row[i]) > 0 && length(B->row[i]) > 0){
                moveFront(A->row[i]);
                moveFront(B->row[i]);
                while(index(A->row[i]) != -1){
                    Entry a = (Entry) get(A->row[i]);
                    Entry b = (Entry) get(B->row[i]);
                    if(a->column != b->column) return 0;
                    else if(a->data != b->data) return 0;
                    else{
                        moveNext(A->row[i]);
                        moveNext(B->row[i]);
                    }
                }
            }
        }
        return 1;
    }
}

// Manipulation procedures --------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M){
    if(M == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    for(int i = 1; i<= M->size; i++){
        List info = M->row[i];
        if(length(info) > 0){
            while(length(info) > 0){
                moveFront(info);
                Entry E = (Entry) get(info);
                freeEntry(&E);
                deleteFront(info);
            }
        }
    }
    M->NNZ = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if(M == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    if( 1 > i || i > M->size || j < 1 || j > M->size){
        fprintf(stderr, "Matrix Error: changeEntry() called with an invalid i and j.");
        exit(1);
    }

    int foundEntry = 0;
    moveFront(M->row[i]);
    while(index(M->row[i]) != -1){
        Entry E = (Entry) get(M->row[i]);
        if (j == E->column){
            foundEntry = 1;
            break;
        } 
        if(j < E->column) break; // if Entry was passed
        moveNext(M->row[i]);
    }

    if(foundEntry == 0 && x != 0.0){
        Entry E = newEntry(j, x);
        if(index(M->row[i]) == -1) append(M->row[i], E);
        else insertBefore(M->row[i], E);
        M->NNZ++;
    } else if(foundEntry == 0 && x == 0.0){
    } else if(foundEntry == 1 && x != 0.0){
        Entry E = (Entry) get(M->row[i]);
        E->data = x;
    } else if(foundEntry == 1 && x == 0.0){
        Entry E = (Entry) get(M->row[i]);
        freeEntry(&E);
        delete(M->row[i]);
        M->NNZ--;
    }
}

// Matrix Arithmetic operations ---------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if(A == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    Matrix M = newMatrix(A->size);
    for(int i = 1; i <= M->size; i++){
        List iA = A->row[i];
        List iM = M->row[i];
        moveFront(iA);
        while(index(iA) != -1){
            Entry E = (Entry) get(iA);
            Entry F = newEntry(E->column, E->data);
            append(iM, F);
            moveNext(iA);
        }
    }
    M->NNZ = NNZ(A);
    return M;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    if(A == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    Matrix B = newMatrix(size(A));
    for(int i = 1; i <= size(A); i++){
        moveFront(A->row[i]);
        while(index(A->row[i]) != -1){
            Entry E = (Entry) get(A->row[i]);
            Entry F = newEntry(i, E->data);
            append(B->row[E->column], F);
            moveNext(A->row[i]);
        }
    }
    B->NNZ = NNZ(A);
    return B;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if(A == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    Matrix B = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++){
        moveFront(A->row[i]);
        while(index(A->row[i]) != -1){
            Entry E = (Entry) get(A->row[i]);
            Entry F = newEntry(E->column, x * E->data);
            append(B->row[i], F);
            moveNext(A->row[i]);
        }
    }
    B->NNZ = NNZ(A);
    return B;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    if(size(A) != size(B)){
        fprintf(stderr, "Matrix error: sum() called on different sized matrecies.");
        exit(1);
    }

    if(equals(A, B) == 1){
        Matrix C = scalarMult(2.0, A);
        return C;
    }
    Matrix C = newMatrix(size(A));
    for(int i = 1; i<= size(A); i++){
        vectorAdd(A->row[i], B->row[i], C->row[i], 0);
        C->NNZ = C->NNZ + length(C->row[i]);
    }
    return C;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    if(size(A) != size(B)){
        fprintf(stderr, "Matrix error: diff() called on different sized matrecies.");
        exit(1);
    }
    Matrix C = newMatrix(size(A));
    for(int i = 1; i<= size(A); i++){
        vectorAdd(A->row[i], B->row[i], C->row[i], 1);
        C->NNZ = C->NNZ + length(C->row[i]);
    }
    return C;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    if(size(A) != size(B)){
        fprintf(stderr, "Matrix error: product() called on different sized matrecies.");
        exit(1);
    }
    Matrix BT = transpose(B);
    Matrix Prod = newMatrix(size(A));
    for(int i = 1; i <= size(A); i++){
        if(length(A->row[i]) > 0){ // if the row is empty then all the values will be zero.
            for( int j = 1; j<= size(BT); j++){
                double product = 0.0;
                if(length(BT->row[j]) > 0){ // the row needs to have something.
                    product = vectorDot(A->row[i], BT->row[j]);
                }
                if(product != 0.0){
                    changeEntry(Prod, i, j, product);
                }
            }

        }
    }
    freeMatrix(&BT);
    return Prod;
}

// Other Matrix operations ------------------------------------------------

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    if(M == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    for (int i = 1; i <= size(M); i++){
        List Output = M->row[i];
        if(length(Output) > 0){
            fprintf(out, "%d: ", i);
            moveFront(Output);
            while(index(Output) < length(Output) - 1){
                Entry E = (Entry) get(Output);
                fprintf(out, "(%d, %0.1f) ", E->column, E->data);
                moveNext(Output);
            }
            if(index(Output) == length(Output) - 1){
                Entry F = (Entry) get(Output);
                fprintf(out, "(%d, %0.1f)\n", F->column, F->data);
            }
        }
    }
}

// Helper functions -------------------------------------------------------

// vectorDot()
// Helper function that performs dot products.
double vectorDot(List P, List Q){
    if(P == NULL || Q == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    double product = 0.0;
    moveFront(P);
    moveFront(Q);
    while(index(P) != -1 && index(Q) != -1){
        Entry E = (Entry) get(P);
        Entry F = (Entry) get(Q);
        if(E->column < F->column) moveNext(P);
        else if(E->column > F->column) moveNext(Q);
        else if (E->column == F->column){
            product += (E->data * F->data);
            moveNext(P);
            moveNext(Q);
        }
    }
    return product;
}

// vectorAdd()
// Helper function that produces vector addition and substitution.
void vectorAdd(List A, List B, List C, int op){
    if(A == NULL || B == NULL || C == NULL){
        fprintf(stderr, "Matrix error: NULL Matrix reference called");
        exit(1);
    }
    int unit;
    if(op == 1) unit = -1;
    else if (op == 0) unit = 1;
    moveFront(A);
    moveFront(B);

    while(index(A) >= 0 || index(B) >= 0) {
        if(index(A) >= 0 && index(B) >= 0) {
            Entry a = (Entry) get(A);
            Entry b = (Entry) get(B);
            if(a->column > b->column) {
                Entry c = newEntry(b->column, (unit) * b->data);
            	append(C, c);
                moveNext(B);
            } else if(a->column < b->column) {
            	Entry c = newEntry(a->column, a->data);
            	append(C, c);
                moveNext(A);
            } else if(a->column == b->column) {
                double newData = a->data + (unit * b->data);
                if(newData != 0.0){
                    Entry z = newEntry(a->column, newData);
                    append(C, z);
                }
                moveNext(A);
                moveNext(B);
            }
        } else if(index(A) >= 0) {
            Entry a = (Entry) get(A);
            Entry H = newEntry(a->column, a->data);
            append(C, H);
            moveNext(A);
        } else {
            Entry b = (Entry) get(B);
            Entry I = newEntry(b->column, unit * b->data);
            append(C, I);
            moveNext(B);
        }
    }

}

// end of ADT operations ------------------------------------------------------



