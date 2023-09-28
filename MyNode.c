#include "MyNode.h"

MyNode* creatNode(void*val)
{
	MyNode* startNode = (MyNode*)malloc(sizeof(MyNode));
	startNode->parent = NULL;
	startNode->child = NULL;
	startNode->val = val;
	return startNode;
}

MyNode* getLastChild(MyNode* startNode)
{
	while (startNode->child) {
		startNode = startNode->child;
	}
	return startNode;
}

MyNode* getFirstParent(MyNode* startNode)
{
	while (startNode->parent) {
		startNode = startNode->parent;
	}
	return startNode;
}

void destroyNode(MyNode** startNode)
{
	if (!(*startNode)) return;
	MyNode** tmp = startNode;

	destroyNode(&((*startNode)->child));
	free((*startNode)->val);
	(*startNode)->val = NULL;
	free(*startNode);
	*startNode = NULL;
}

void deleteSingleNode(MyNode* startNode)
{
	if (!startNode) return;
	if (!startNode->parent) return;
	MyNode* parent = startNode->parent;
	if (!startNode->child) parent->child = NULL;
	else {
		parent->child = startNode->child;
		startNode->child->parent = parent;
	}
	free(startNode->val);
	free(startNode);
}
