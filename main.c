#include "treeNode.h"

#include <stdio.h>

int main(void){
	treeAddress root = NULL;
	treeAddress pwd = NULL;
	treeAddress f = NULL;

	createMemory(&pwd);
	nodeNaming(&pwd, "A");
	root = pwd;

	/*
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
	*/
	createMemory(&f);
	nodeNaming(&f, "B");	
	insertTreeNode(&pwd, &f);

	createMemory(&f);
	nodeNaming(&f, "C");	
	insertTreeNode(&pwd, &f);

	pwd = searchTreeNode(root, "B");

	createMemory(&f);
	nodeNaming(&f, "D");	
	insertTreeNode(&pwd, &f);

	pwd = searchTreeNode(root, "C");

	createMemory(&f);
	nodeNaming(&f, "E");	
	insertTreeNode(&pwd, &f);

	createMemory(&f);
	nodeNaming(&f, "F");	
	insertTreeNode(&pwd, &f);
	
	pwd = searchTreeNode(root, "F");

	createMemory(&f);
	nodeNaming(&f, "G");	
	insertTreeNode(&pwd, &f);

	printf("\nDEBUGGGGGGGGG\n");

	//dari root ke E
//	pwd = searchTreeNode(root, "E");
//	showSons(pwd);

	//dari C ke G
//	pwd = searchTreeNode(root, "C");
//	pwd = searchTreeNode(pwd, "G");
//	showSons(pwd);

	//dari B ke G
	//pwd = searchTreeNode(root, "B");
	//pwd = searchTreeNode(pwd, "G");
	//showSons(pwd);

	//dari A ke Z
	pwd = searchTreeNode(root, "Z");
//	showSons(pwd);

	return 0;
}
