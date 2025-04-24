#include "treeNode.h"

#include <stdio.h>

int main(void){
	treeAddress root = NULL;
	treeAddress pwd = NULL;
	treeAddress f = NULL;

	createMemory(&pwd);
	nodeNaming(&pwd, "Root");
	root = pwd;

	createMemory(&f);
	nodeNaming(&f, "FolderA");
	insertTreeNode(&pwd, &f);

	createMemory(&f);
	nodeNaming(&f, "FolderB");
	insertTreeNode(&pwd, &f);

	createMemory(&f);
	nodeNaming(&f, "FolderC");
	insertTreeNode(&pwd, &f);

	pwd = searchTreeNode(root, "FolderA");

	createMemory(&f);
	nodeNaming(&f, "FolderA1");
	insertTreeNode(&pwd, &f);

	createMemory(&f);
	nodeNaming(&f, "FolderA2");
	insertTreeNode(&pwd, &f);

	pwd = searchTreeNode(root, "FolderA1");

	createMemory(&f);
	nodeNaming(&f, "FolderA1a");
	insertTreeNode(&pwd, &f);

	pwd = searchTreeNode(root, "FolderB");

	createMemory(&f);
	nodeNaming(&f, "FolderB1");
	insertTreeNode(&pwd, &f);

	createMemory(&f);
	nodeNaming(&f, "FolderB2");
	insertTreeNode(&pwd, &f);

	pwd = searchTreeNode(root, "FolderB2");

	createMemory(&f);
	nodeNaming(&f, "FolderB2a");
	insertTreeNode(&pwd, &f);

	pwd = searchTreeNode(root, "FolderB2a");

	createMemory(&f);
	nodeNaming(&f, "FolderB2a1");
	insertTreeNode(&pwd, &f);

	pwd = searchTreeNode(root, "Root");

	viewAllFolders(root, inOrder);
	return 0;
}
