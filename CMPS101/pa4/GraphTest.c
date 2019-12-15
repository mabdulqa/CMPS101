//-----------------------------------------------------------------
//  CMPS101 PA3
//  Mohammad Abdulqder (mabdulqa)
//  
//  GraphTest.c
//  Main file to test the Graph ADT with its public functions.
//-----------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

int main(void){
    int i;

    Graph G = newGraph(6);

    addArc(G, 1, 2);
    addArc(G, 1, 6);
    addArc(G, 2, 2);
    addArc(G, 2, 3);
    addArc(G, 2, 4);
    addArc(G, 3, 4);
    addArc(G, 4, 5);
    addArc(G, 5, 1);
    addArc(G, 5, 2);
    addArc(G, 6, 5);

    printf("This is Graph G:\n");
    printGraph(stdout, G);
    printf("\n");

    Graph H = transpose(G);
    Graph I = copyGraph(G);

    printf("This is transpose of G:\n");
    printGraph(stdout, H);
    printf("\n");

    printf("This is Graph I, a copy of G:\n");
    printGraph(stdout, G);
    printf("\n");


    List L = newList();
    for(i = 1; i<= getOrder(G); i++){
        append(L, i);
    }

    printf("List L before first DFS\n");
    printList(stdout, L);
    DFS(G, L);
    printf("\n");

    printf("List L after first DFS\n");
    printList(stdout, L);
    printf("\n");
    printf("The Discover and Finsh time of each vertex.\n");
    for(i = 1; i<= getOrder(G); i++){
        printf("%d: %d  %d\n", i, getDiscover(G, i), getFinish(G, i));
    }
    printf("\n");
    DFS(H, L);

    printf("List L after second DFS\n");
    printList(stdout, L);
    printf("\n");
    for(i = 1; i<= getOrder(H); i++){
        printf("%d: %d  %d\n", i, getDiscover(H, i), getFinish(H, i));
    }
    printf("\n");


    freeList(L);
    freeGraph(G);
    freeGraph(H);
    freeGraph(I);

    return 0;
}