//-----------------------------------------------------------------
//  CMPS101 PA3
//  Mohammad Abdulqder (mabdulqa)
//  
//  FindPath.c
//  Graph ADT file with its public and private functions.
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
        fprintf(stderr, "Usage: FindPath <infile> <outfile>");
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
    int source, destination;
    int distance;
    List L = newList();

    fgets(line, MAX_LEN, in);
    sscanf(line, "%d", &vertex);

    Graph G = newGraph(vertex);

    while(fgets(line, MAX_LEN, in) != NULL){
        sscanf(line, "%d %d", &x, &y);
        if(x == 0 && y == 0) break;
        addEdge(G, x, y);
    }
    
    //prints adj list.
    printGraph(out, G);
    fprintf(out, "\n");

    // finds distance of source to 
    while(fgets(line, MAX_LEN, in) != NULL){
        sscanf(line, "%d %d", &source, &destination);
        if(source == 0 && destination == 0) break;
        BFS(G, source);
        getPath(L, G, destination);
        distance = getDist(G, destination);
        if(distance == INF){
            fprintf(out, "The distance from %d to %d is infinity\n", source, destination);
        }else{
            fprintf(out, "The distance from %d to %d is %d\n", source, destination, distance);
        }
        moveFront(L);
        if(get(L) == NIL){
            fprintf(out, "No %d to %d path exists\n", source, destination);
        }else{
            fprintf(out, "A shortest %d-%d path is: ", source, destination);
            printList(out, L);
            fprintf(out, "\n");
        }
        fprintf(out, "\n");
        clear(L);
    }

    freeList(&L);
    freeGraph(&G);
    fclose(in);
    fclose(out);

    return 0;
}