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

	return 0;
}
