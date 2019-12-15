//-----------------------------------------------------------------
//  CMPS101 PA2
//  Mohammad Abdulqder (mabdulqa)
//  
//  ListTest.c
//  Test file for List ADT.
//-----------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Matrix.h"

int main(void){

    List A = newList();
    List B = newList();
    List C = NULL;
    int i;

    for(i = 1; i<=20; i++){
        append(A, i);
        prepend(B, i);
    }

    moveFront(B);
    moveBack(A);
    for(i = 30; i> 25; i--){
        movePrev(A);
        movePrev(A);
        insertBefore(A, i);
        moveNext(B);
        moveNext(B);
        insertAfter(B, i);
    }

    C = concatList(A, B);
    printList(stdout ,C);
    printf(length(A));
    printf((int) get(A));
    printf(index(A));
    printf((int) front(A));
    printf((int)back(B));
    delete(A);
    delete(B);
    moveFront(A);
    moveFront(B);
    while(index(A) != -1){
        int data = (int) get(A);
        printf("%d ", data);
        moveNext(A);
    }
    while(index(B) != -1){
        int data2 = (int) get(B);
        printf("%d ", data2);
        moveNext(B);
    }
    deleteFront(A);
    deleteBack(A);

    clear(C);
    freeList(&C);
    freeList(&B);
    freeList(&A);

    return 0;
}