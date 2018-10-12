#ifndef __LINKED_H // Guard statement
#define __LINKED_H

#ifndef __LL_DATA_TYPE_H  // Guard to avoid defining twice 
#define __LL_DATA_TYPE_H

typedef int LL_DATA_TYPE; // Linked List Data Type
#define LL_DATA_C "%d"    // Linked List Data Conversion

#endif // __LL_DATA_TYPE_H

// Node
typedef struct node
{
  LL_DATA_TYPE data;
  struct node *next;
} Node;

// List pointers
typedef struct list
{
  Node *head;
  Node *tail;
} List;

void isNull(char *);
Node *createNode(DATA_TYPE);
void printList(Node *);
Node *tailInsert(Node *, DATA_TYPE);
Node *headInsert(Node *, DATA_TYPE);
int inList(Node *, DATA_TYPE);
Node *findNode(Node *, DATA_TYPE);
Node *deleteNode(Node *, DATA_TYPE);
Node *destroyList(Node *);
Node *sortAccending(Node *);
Node *sortDecending(Node *);
int listSize(Node *);
int replaceNodeData(Node *, DATA_TYPE, DATA_TYPE);
int isLooping(Node *);
int endLoop(Node *);

#endif // __LINKED_H
