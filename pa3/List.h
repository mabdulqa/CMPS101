//-----------------------------------------------------------------
//  CMPS101 PA3
//  Mohammad Abdulqder (mabdulqa)
//  
//  List.h
//  Header file for List ADT with its public functions.
//-----------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// structs --------------------------------------------------------------------

// List type
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList(void);


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);

// Access Functions -----------------------------------------------------------

// length()
// returns the size of the List linked list.
int length(List L);

// index()
// returns index of cursor element, else returns -1.
int index(List L);

// front()
// returns front element of L.
int front(List L);

// back()
// returns back element of L.
int back(List L);

// get()
// returns cursor element of L.
int get(List L);

// equals()
// returns true iff both lists are exactly the same.
int equals(List L, List M);

// Manipulation procedures ----------------------------------------------------

// clear()
// resets L to its original empty state.
void clear(List L);

// moveFront()
// if L is non-empty, sets cursor under front.
void moveFront(List L);

// moveBack()
// if L is non-empty, sets cursor under back.
void moveBack(List L);

// movePrev()
// if cursor is not at front, moves back by one.
void movePrev(List L);

// moveNext()
// if cursor is not at back, moves up by one.
void moveNext(List L);

// prepend()
// Insers new element to the front of L.
void prepend(List L, int data);

// append()
// Inserts new element into back of L.
void append(List L, int data);

// insertBefore()
// adds new element before the cursor.
void insertBefore(List L, int data);

// insertAfter()
// adds new element after the cursor.
void insertAfter(List L, int data);

// deleteFront()
// deletes front element.
void deleteFront(List L);

// deleteBack()
// deletes back element.
void deleteBack(List L);

// delete()
// deletes cursor element, cursor becomes undefined.
void delete(List L);

// other operations -----------------------------------------------------------

// printList()
// prints to file pointed to by out, will be printed as int int int.
void printList(FILE* out, List L);

// copyList()
// returns a new list which is an exact copy of L, its cursor in undefined.
List copyList(List L);

// concatList()
// returns new list which is a contactination of the two given lists L and M.
List concatList(List L, List M);

// end of ADT operations ------------------------------------------------------

#endif