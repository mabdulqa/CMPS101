//-----------------------------------------------------------------
//  CMPS101 PA3
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
    int source;
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
    G->source = NIL;
    G->vertex = n;
    G->edges = 0;

    for(int i = 1; i<= n; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->P[i] = NIL;
        G->D[i] = INF;
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

// getSource()
// returns the previous source used by BFS.
int getSource(Graph G){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    return G->source;
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

// getDistance()
// returns the distance from most recent BFS source.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph error: getDist() called with invalid vertex.");
        exit(1);
    }
    return G->D[u];
}

// getPath();
// find the shortest path from source to u.
// pre: getSource(G)!= NIL and 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph error: getPath() called with invalid vertex.");
        exit(1);
    }
    if(getSource(G) == NIL){
        fprintf(stderr, "Graph error: getPath() called before BFS was called.");
        exit(1);
    }
    if(u == getSource(G)){
        append(L, u);
    }else if(getParent(G, u) == NIL){
        prepend(L, NIL);
    }else{
        getPath(L, G, G->P[u]);
        append(L, u);
    }
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

// BFS()
// the classic BFS algorithm.
// Pre: source is 1 <= s <= getOrder(G)
void BFS(Graph G, int s){
    if(G == NULL){
        fprintf(stderr, "Graph error: NULL Graph reference called");
        exit(1);
    }
    if(s < 1 || s > getOrder(G)){
        fprintf(stderr, "Graph error: BFS() called with an invalid source.");
        exit(1);
    }
    for(int i = 1; i <= getOrder(G); i++){
        if(s != i){
            G->color[i] = WHITE;
            G->D[i] = INF;
            G->P[i] = NIL;
        }
    }
    G->color[s] = GRAY;
    G->D[s] = 0;
    G->P[s] = NIL;

    List Q = newList();
    int x;
    int y;
    append(Q, s);

    while(length(Q) > 0){
        x = front(Q);
        deleteFront(Q);

        moveFront(G->adj[x]);
        while(index(G->adj[x]) != -1){
            y = get(G->adj[x]);
            if (G->color[y] == WHITE){
                G->color[y] = GRAY;
                G->D[y] = G->D[x] + 1;
                G->P[y] = x;
                append(Q, y);
            }
            moveNext(G->adj[x]);
        }
        G->color[x] = BLACK;
    }
    freeList(&Q);
    G->source = s;
}

// Other operations ------------------------------------------------------------

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

// end of ADT operations -------------------------------------------------------
