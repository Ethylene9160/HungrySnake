#include<stdio.h>
#include<stdlib.h>

#ifndef _MY_NODE_ 
#define _MY_NODE_ 1

/*
A double-trip node of linked list, 
and use a pointer of 'void' type to store the information in each node.
*/
struct MyNode {
	void* val;
	struct MyNode* parent;
	struct MyNode* child;
};

typedef struct MyNode MyNode;

/*
A function to creat a single node.
val will be assigned as parameter val,
pointer 'parent' 'child' will be assigned as 'NULL'.
*/
MyNode* creatNode(void*val);

/*
A function that will return the pointer of the end node of the list.
*/
MyNode* getLastChild(MyNode* startNode);

/*
A function that will return the ointer of the beginning of the list.
*/
MyNode* getFirstParent(MyNode* startNode);

/*
release the memory of node, and each node will be assigned to 'NULL'.
it will use 'free(node->val)' to free the memory of node->val.
*/
void destroyNode(MyNode** startNode);

/*
for example, 1->3->6->4, use this function to delete node with value 3,
the final node will be 1->6->4.
and the memory of the node with value 3 will be release.
*/
void deleteSingleNode(MyNode* startNode);

#endif
