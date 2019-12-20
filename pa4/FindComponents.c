//-----------------------------------------------------------------
//  CMPS101 PA4
//  Mohammad Abdulqder (mabdulqa)
//  
//  FindComponents.c
//  Main program implementing the Graph ADT.
//-----------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 100

int main(int argc, char* argv[]){
    FILE* in;
    FILE* out;
    if (argc != 3){
        fprintf(stderr, "Usage: FindComponents <infile> <outfile>");
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

    int vertex;
    char line[MAX_LEN];
    int x, y;
    int i, j;
    int indicy;
    int components = 0;
    List L = newList();
    List* Comp;

    fgets(line, MAX_LEN, in);
    sscanf(line, "%d", &vertex);

    Graph G = newGraph(vertex);

    while(fgets(line, MAX_LEN, in) != NULL){
        sscanf(line, "%d %d", &x, &y);
        if(x == 0 && y == 0) break;
        addArc(G, x, y);
    }

    for(i = 1; i <= vertex; i++){
        append(L, i);
    }

    Graph H = transpose(G);

    DFS(G, L);
    DFS(H, L);

    moveFront(L);
    while(index(L) != -1){
        j = get(L);
        if(getParent(H, j) == NIL) components++;
        moveNext(L);
    }

    Comp = calloc(components + 1, sizeof(List));
    for(i = 1; i <= components; i++){
        Comp[i] = newList();
    }

    moveFront(L);
    indicy = components + 1;
    while(index(L) != -1){
        if(getParent(H, get(L)) == NIL) indicy--;
        append(Comp[indicy], get(L));
        moveNext(L);
    }

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    fprintf(out, "G contains %d strongly connected components:\n", components);
    for(i = 1; i<=components; i++){
        fprintf(out, "Component %d: ", i);
        printList(out, Comp[i]);
        fprintf(out, "\n");
    }

    freeGraph(&G);
    freeGraph(&H);
    freeList(&L);
    for(i = 1; i <= components; i++){
        freeList(&Comp[i]);
    }
    free(Comp);
    fclose(in);
    fclose(out);
    return 0;
}