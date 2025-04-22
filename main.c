#include "treeNode.h"

#include <stdio.h>

int main(void){
	treeAddress root = NULL;
	treeAddress pwd = NULL;

	createMemory(&pwd);
	nodeNaming(&pwd, "home");
	root = pwd;

	createMemory(&pwd);
	nodeNaming(&pwd, "Downloads");
	insertTreeNode(&root, &pwd);

	createMemory(&pwd);
	nodeNaming(&pwd, "Documents");
	insertTreeNode(&root, &pwd);

	createMemory(&pwd);
	nodeNaming(&pwd, "Pictures");
	insertTreeNode(&root, &pwd);

	createMemory(&pwd);
	nodeNaming(&pwd, "Videos");
	insertTreeNode(&root, &pwd);

	createMemory(&pwd);
	nodeNaming(&pwd, "Public");
	insertTreeNode(&root, &pwd);

	pwd = searchTreeNode(root, "Pictures");
	deleteNode(&pwd);
	showSons(root);

	pwd = searchTreeNode(root, "Public");
	deleteNode(&pwd);
	showSons(root);

	pwd = searchTreeNode(root, "Videos");
	deleteNode(&pwd);
	showSons(root);

	pwd = searchTreeNode(root, "Downloads");
	deleteNode(&pwd);
	showSons(root);

	pwd = searchTreeNode(root, "Documents");
	deleteNode(&pwd);
	showSons(root);

	return 0;
}
