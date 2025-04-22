#include "treeNode.h"

#include <stdio.h>

int main(void){
	treeAddress root = NULL;
	treeAddress pwd = NULL;
	treeAddress f = NULL;

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

	pwd = searchTreeNode(root, "Documents");

	createMemory(&f);
	nodeNaming(&f, "PROJEK");
	insertTreeNode(&pwd, &f);

	createMemory(&f);
	nodeNaming(&f, "SDA");
	insertTreeNode(&pwd, &f);

	createMemory(&f);
	nodeNaming(&f, "TEKPRO");
	insertTreeNode(&pwd, &f);

	showSons(pwd);


	return 0;
}
