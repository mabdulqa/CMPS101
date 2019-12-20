//-----------------------------------------------------------------
//  CMPS101 PA4
//  Mohammad Abdulqder (mabdulqa)
//  
//  Graph.c
//  Graph ADT file with its public and private functions.
//-----------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

// Defn -----------------------------------------------------------------------

#define WHITE -1
#define GRAY -2
#define BLACK -3

// structs --------------------------------------------------------------------

// Graph type
typedef struct GraphObj{
    List* adj;
    int* color;
    int* P;
    int* D;
    int* F;
    int time;
    int vertex;
    int edges;
}GraphObj;


// Constructors-Destructors ----------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object.
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adj = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->P = calloc(n+1, sizeof(int));
    G->D = calloc(n+1, sizeof(int));
    G->F = calloc(n+1,sizeof(int));
    G->time = NIL;
    G->vertex = n;
    G->edges = 0;

    for(int i = 1; i<= n; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->P[i] = NIL;
        G->D[i] = UNDEF;
        G->F[i] = UNDEF;
    }
    return G;
}


// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG){
    if(pG!=NULL && *pG!=NULL) {
        Graph G = *pG; 
        for(int i = 1; i <= G->vertex; i++){
            freeList(&(G->adj[i]));
        }
        free(G->adj);
        free(G->color);
        free(G->P);
        free(G->D);
        free(G->F);
        free(*pG);
        *pG = NULL;
    }
}

// Acess Functions -------------------------------------------------------------

// getOrder()
// returns the number of vertices in Graph G.
int getOrder(Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    return G->vertex;
}

// getSize()
// returns the number of edges in Graph G.
int getSize(Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    return G->edges;
}

// getParent()
// returns the parent of the given vertex.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph error: getParent() called with invalid vertex.");
        exit(1);
    }
    return G->P[u];
}

// getDiscover()
// returns the discovery time of said vertex.
// Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph error: getDiscover() called with invalid vertex.");
        exit(1);
    }
    return G->D[u];
}

// getFinish()
// returns the finish time of said vertex.
// Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph error: getFinish() called with invalid vertex.");
        exit(1);
    }
    return G->F[u];
}

// Manipulaton procedures ------------------------------------------------------

// makeNull()
// deletes all edges in G, making it a null graph.
void makeNull(Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    for(int i = 1; i<= getOrder(G); i++){
        clear(G->adj[i]);
    }
    G->edges = 0;
}

// addEdge()
// adds a new edge to the graph G in adj[u] and adj[v].
// pre: 1 <= u <= getOrder(G) and 1 <= u <= getOrder(G).
void addEdge(Graph G, int u, int v){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph error: addEdge() called with an invalid start vertex.");
        exit(1);
    }
    if(v < 1 || v > getOrder(G)){
        fprintf(stderr, "Graph error: addEdge() called with an invalid end vertex.");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->edges--; //becausce getArc added twice.
}

// addArc()
// adds a new edge to graph G into adj[u] but not adj[v]
// pre: 1 <= u <= getOrder(G) and 1 <= u <= getOrder(G).
void addArc(Graph G, int u, int v){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph error: addArc() called with an invalid start vertex.");
        exit(1);
    }
    if(v < 1 || v > getOrder(G)){
        fprintf(stderr, "Graph error: addArc() called with an invalid end vertex.");
        exit(1);
    }
    moveFront(G->adj[u]);
    while(index(G->adj[u]) != -1 && get(G->adj[u]) < v) moveNext(G->adj[u]);
    if(index(G->adj[u]) == -1) append(G->adj[u], v);
    else insertBefore(G->adj[u], v);
    G->edges++;
}

// DFS()
// the classic DFS algorithm.
void DFS(Graph G, List S){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    int x;
    List copy = copyList(S);
    clear(S);
    for (int i = 1; i<= getOrder(G); i++){
        G->color[i] = WHITE;
        G->P[i] = NIL;
        G->D[i] = UNDEF;
        G->F[i] = UNDEF;
    }
    G->time = 0;
    moveFront(copy);
    while(index(copy) != -1){
        x = get(copy);
        if(G->color[x] == WHITE){
            Visit(G, x, S);
        }
        moveNext(copy);
    }
    freeList(&copy);
}

// Other operations ------------------------------------------------------------

// transpose()
// returns the transpose of graph G.
Graph transpose(Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    int i;
    int j;
    Graph H = newGraph(getOrder(G));
    for(i = 1; i <= getOrder(G); i++){
        moveFront(G->adj[i]);
        while(index(G->adj[i]) != -1){
            j = get(G->adj[i]);
            append(H->adj[j], i);
            moveNext(G->adj[i]);
        }
    }
    H->edges = getSize(G);
    return H;
}

// copyGraph()
// copies graph G and returns the copied graph.
Graph copyGraph(Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    int i;
    int j;
    Graph H = newGraph(getOrder(G));
    for(i = 1; i<= getOrder(G); i++){
        moveFront(G->adj[i]);
        while(index(G->adj[i]) != -1){
            j = get(G->adj[i]);
            append(H->adj[i], j);
            moveNext(G->adj[i]);
        }
    }
    H->edges = getSize(G);
    return H;
}

// printGraph()
// prints adjacency list of Graph G to out.
void printGraph(FILE* out, Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    if(out == NULL){
        fprintf(stderr, "Graph error: printGraph() called on NULL FILE reference");
        exit(1);
    }
    for(int i = 1; i<=getOrder(G); i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}

// Helper functions ------------------------------------------------------------

// Visit()
// helper function for DFS.
void Visit(Graph G, int x, List S){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    int y;
    G->D[x] = (++G->time);
    G->color[x] = GRAY;
    moveFront(G->adj[x]);
    while(index(G->adj[x]) != -1){
        y = get(G->adj[x]);
        if(G->color[y] == WHITE){
            G->P[y] = x;
            Visit(G, y, S);
        }
        moveNext(G->adj[x]);
    }
    G->color[x] = BLACK;
    G->F[x] = (++G->time);
    prepend(S, x);
}

// end of ADT operations -------------------------------------------------------
