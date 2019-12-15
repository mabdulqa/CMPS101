//-----------------------------------------------------------------
//  CMPS101 PA3
//  Mohammad Abdulqder (mabdulqa)
//  
//  List.c
//  List ADT file with its public and private functions.
//-----------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int index;
    int numitems;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next, prev, and data fields.
// Private.
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->numitems = 0;
    L->index = -1;
    return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
    if(pL!=NULL && *pL!=NULL) { 
        Node temp = (*pL)->front;
        while(temp != NULL) {
            Node current = temp;
            temp = temp->next;
            free(current);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access Functions -----------------------------------------------------------

// length()
// returns the size of the List linked list.
int length(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    return L->numitems;
}

// index()
// returns index of cursor element, else returns -1.
int index(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    return L->index;
}

// front()
// returns front element of L.
int front(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(length(L) == 0){
        fprintf(stderr, "List error: Calling front() on an empty List.");
        exit(1);
    }
    return L->front->data;
}

// back()
// returns back element of L.
int back(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(length(L) <= 0){
        fprintf(stderr, "List error: Calling back() on an empty List.");
        exit(1);
    }
    return L->back->data;
}

// get()
// returns cursor element of L.
int get(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(length(L) == 0){
        fprintf(stderr, "List error: Calling get() on an empty List.");
        exit(1);
    }if(index(L) < 0){
        fprintf(stderr, "List error: Calling get() on an undefined index.");
        exit(1);
    }
    return L->cursor->data;
}

// equals()
// returns true iff both lists are exactly the same.
int equals(List L, List M){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(L->numitems != M->numitems) return 0;
    else{
        Node test = L->front;
        Node test2 = M->front;

        while(test != NULL){
            if(test-> data != test2->data) return 0;
            else{
                test = test->next;
                test2 = test2->next;
            }
        }
        return 1;
    }
}

// Manipulation procedures ----------------------------------------------------

// clear()
// resets L to its original empty state.
void clear(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    Node N = L->front;
    while(N != NULL){
        Node target = N;
        N = N->next;
        freeNode(&target);
    }
    L->index = -1;
    L->front = L->back = L->cursor = NULL;
    L->numitems = 0;

}

// moveFront()
// if L is non-empty, sets cursor under front.
void moveFront(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(L->numitems > 0){ 
        L->cursor = L->front;
        L->index = 0;
    }
}

// moveBack()
// if L is non-empty, sets cursor under back.
void moveBack(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(L->numitems > 0){
        L->cursor = L->back;
        L->index = L->numitems - 1;
    }
}

// movePrev()
// if cursor is not at front, moves back by one.
void movePrev(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if( L->cursor != NULL && L->index == 0){
        L->cursor = NULL;
        L->index = -1;
    }else if(L->cursor != NULL){
        L->cursor = L->cursor->prev;
        L->index = L->index - 1;
    }
}

// moveNext()
// if cursor is not at back, moves up by one.
void moveNext(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(L->cursor != NULL && L->index == L->numitems - 1){
        L->cursor = NULL;
        L->index = -1;
    }else if(L->cursor != NULL){
        L->cursor = L->cursor->next;
        L->index = L->index + 1;
    }
}

// prepend()
// Inserts new element to the front of L.
void prepend(List L, int data){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    Node newData = newNode(data);
    if(L->numitems == 0){
        L->front = newData;
        L->back = newData;
        L->numitems++;
    }else{
        newData->next = L->front;
        L->front->prev = newData;
        L->front = newData;
        L->numitems++;
    }
    if(L->index != -1){
        L->index++;
    }
}

// append()
// Inserts new element into back of L.
void append(List L, int data){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    Node newData = newNode(data);
    if(L->numitems == 0){
        L->front = newData;
        L->back = newData;
        L->numitems++;
    }else{
        newData->prev = L->back;
        L->back->next = newData;
        L->back = newData;
        L->numitems++;
    }
}

// insertBefore()
// adds new element before the cursor.
void insertBefore(List L, int data){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(L->numitems == 0){
        printf( "List error: Calling insertBefore() on an empty List.");
        exit(1);
    }if(L->index == -1 && L->cursor == NULL){
        printf( "List error: Calling insertBefore() with an undefined cursor.");
        exit(1);
    }if(L->index == 0){
        prepend(L, data);
    }else{
        Node newData = newNode(data);
        Node nodeBefore = L->cursor->prev;
        L->cursor->prev = newData;
        newData->prev = nodeBefore;
        newData->next = L->cursor;
        nodeBefore->next = newData;
        L->numitems++;
        L->index++;
    }
}

// insertAfter()
// adds new element after the cursor.
void insertAfter(List L, int data){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(L->numitems == 0){
        fprintf(stderr, "List error: Calling insertAfter() on an empty List.");
        exit(1);
    }if(L->index == -1 && L->cursor == NULL){
        fprintf(stderr, "List error: Calling insertAfter() with an undefined cursor.");
        exit(1);
    }
    if(L->index == length(L) - 1){
        append(L, data);
    }else{
        Node newData = newNode(data);
        Node nodeAfter = L->cursor->next;
        newData->prev = L->cursor;
        nodeAfter->prev = newData;
        L->cursor->next = newData;
        newData->next = nodeAfter;
        L->numitems++;
    }
}

// deleteFront()
// deletes front element.
void deleteFront(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(L->numitems == 0){
        fprintf(stderr, "List error: Calling deleteFront() on empty List.");
        exit(1);
    }
    // first block addresses the index changes if any happen.
    if(L->index == 0){
        L->cursor = NULL;
        L->index = -1;
    }else if(L->index > 0){
        L->index--;
    }
    // second block actually addresses removing the front node.
    if(L->numitems == 1){
        Node frontNode = L->front;
        L->front = NULL;
        L->back = NULL;
        freeNode(&frontNode);
        L->numitems--;
    }else{ // L->numitems > 1
        Node frontNode = L->front;
        L->front = L->front->next;
        L->front->prev = NULL;
        frontNode->next = NULL;
        freeNode(&frontNode);
        L->numitems--;
    }
}

// deleteBack()
// deletes back element.
void deleteBack(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(L->numitems == 0){
        fprintf(stderr, "List error: Calling deleteBack() on empty List.");
        exit(1);
    }
    // first block addresses if the back node is the cursor.
    if(L->index == length(L) - 1){
        L->index = -1;
        L->cursor = NULL;
    }
    // second block adresses removing the node.
    if(L->numitems == 1){
        Node backNode = L->front;
        L->front = NULL;
        L->back = NULL;
        freeNode(&backNode);
        L->numitems--;
    }else{ // L->numitems > 1
        Node backNode = L->back;
        L->back = L->back->prev;
        L->back->next = NULL;
        backNode->prev = NULL;
        freeNode(&backNode);
        L->numitems--;
    }
}

// delete()
// deletes cursor element, cursor becomes undefined.
void delete(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    if(L->numitems == 0){
        fprintf(stderr, "List error: Calling delete() on empty List.");
        exit(1);
    }
    if(L->index == -1){
        fprintf(stderr, "List error: Calling delete() on List with no cursor.");
        exit(1);
    }
    if(L->index == 0) deleteFront(L);
    else if(L->index == length(L) - 1) deleteBack(L);
    else{ // cursor is not L->front or L->back
        Node cursor = L->cursor;
        Node after = L->cursor->next;
        Node before = L->cursor->prev;
        L->cursor = NULL;
        L->index = -1;
        cursor->next = NULL;
        before->next = after;
        cursor->prev = NULL;
        after->prev = before;
        freeNode(&cursor);
        L->numitems--;
    }
}

// other operations -----------------------------------------------------------

// printList()
// prints to file pointed to by out, will be printed as int int int.
void printList(FILE* out, List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    Node G = L->front;
    while (G != NULL){
        fprintf(out, "%d ", G->data);
        G = G->next;
    }
}

// copyList()
// returns a new list which is an exact copy of L, its cursor in undefined.
List copyList(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    List M = newList();
    Node K = L->front;
    while (K != NULL){
        append(M, K->data);
        K = K->next;
    }
    return M;
    
}

// concatList()
// returns new list which is a contactination of the two given lists L and M.
List concatList(List L, List M){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    List N = newList();
    Node K = L->front;
    Node O = M->front;
    while(K != NULL){
        append(N, K->data);
        K = K->next;
    } while (O != NULL){
        append(N, O->data);
        O = O->next;
    }
    return N;
}

// isEmpty()
// returns true iff L->numitems is 0.
int isEmpty(List L){
    if(L == NULL){
        fprintf(stderr, "List error: NULL List reference called");
        exit(1);
    }
    return(L->numitems == 0);
}

// end of ADT operations ------------------------------------------------------