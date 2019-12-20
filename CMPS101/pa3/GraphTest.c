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

    for(i = 1; i <=getOrder(G); i++){
        if(i < getOrder(G)) addEdge(G, i, i + 1);
        else addEdge(G, getOrder(G), 1);
        if(i % 3 == 1) addArc(G, i, getOrder(G));
        else if(i%3 == 2) addArc(G, getOrder(G)/3 , i);
    }
    BFS(G, 1);
    printGraph(stdout, G);
    List L = newList();
    getPath(L, G, 6);
    printf("The shortest path from 1 to 6 is:");
    printList(stdout, L);
    printf("size of G: %d\n", getSize(G));
    printf("parent of 2: %d\n", getParent(G, 2));
    printf("distance from source to 3: %d\n", getDist(G, 3));
    makeNull(G);
    printGraph(G);

    freeList(L);
    freeGraph(G);

    return 0;
}