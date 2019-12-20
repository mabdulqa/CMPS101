//-----------------------------------------------------------------
//  CMPS101 PA1
//  Mohammad Abdulqder (mabdulqa)
//  
//  ListTest.c
//  Tests the List ADT.
//-----------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

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
    printf(get(A));
    printf(index(A));
    printf(front(A));
    printf(back(B));
    delete(A);
    delete(B);
    deleteFront(A);
    deleteBack(A);

    clear(C);
    freeList(&C);
    C = copyList(A);
    freeList(&B);
    if(equals(A, C) == 1){
        printf("True");
    }else{
        printf("False");
    }

    freeList(&A);
    freeList(&C);
}