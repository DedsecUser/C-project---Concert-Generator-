
#include "Tree.h"


void Checkmemoryalloc(void* value) //function cheak if memory allocated proparlly
{
	if (value == NULL)
	{
		printf("ERROR In memory alloaction");
		exit(1);
	}
}
void printTreeLDR(InstrumentTree* tr)
{
	printTreeLDRHelper(tr->root);
	printf("\n");
}
void printTreeLDRHelper(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		printTreeLDRHelper(root->left);
		printf("%s %d \n", root->instrument, root->insId);
		printTreeLDRHelper(root->right);
	}
}
void freeTree(InstrumentTree* tr)
{
	freeTreeHelper(tr->root);
}
void freeTreeHelper(TreeNode* root)
{
	if (root != NULL)
	{
		freeTreeHelper(root->left);
		freeTreeHelper(root->right);
		free(root);
	}
}

int findInsId(InstrumentTree tree, char* instrument)
{
	return(findInsIdHelper(tree.root, instrument));
}
int findInsIdHelper(TreeNode* root, char* instrument)
{
	if (root == NULL)
		return NotFound;
	else if (strcmp((root->instrument), instrument) == 0)
		return root->insId;
	else if (strcmp((root->instrument), instrument) < 0)
		return(findInsIdHelper((root->right), instrument));
	else
		return(findInsIdHelper((root->left), instrument));
}
bool isEmptyTree(InstrumentTree t)
{
	if (t.root == NULL)
		return true;
	return false;

}


InstrumentTree BuildTreeFromFile(char* fileName, int* NumOfInstruments)
{
	InstrumentTree tr;
	tr.root = NULL;
	int id = InitID;
	TreeNode* CurTreeNode;
	FILE* fIns;
	char InsName[MAXSIZE];
	fIns = fopen(fileName, "r");
	if (fIns == NULL)
		printf("File  does not exist\n");
	else
	{
		long int endF = fileSize(fIns);
		while (ftell(fIns) != endF) //Creating nodes for all the instruments and adding them  to the tree
		{
			fscanf(fIns, "%s", InsName);
			CurTreeNode = MakeNewTreeNode(InsName, id);
			InsertToTree(&tr, CurTreeNode);
			id++;
		}
	}
	fclose(fIns);
	*NumOfInstruments = id;
	return tr;
}

TreeNode* MakeNewTreeNode(char* data, int id)
{
	TreeNode* new_one = (TreeNode*)malloc(sizeof(TreeNode));
	Checkmemoryalloc(new_one);
	new_one->instrument = (char*)malloc(sizeof(char) * (strlen(data)));
	Checkmemoryalloc(new_one->instrument);
	strcpy(new_one->instrument, data);
	new_one->insId = id;
	new_one->left = NULL;
	new_one->right = NULL;
	return new_one;
}
void InsertToTree(InstrumentTree* tr, TreeNode* trNode)
{
	TreeNode* father;
	TreeNode* new_one = trNode;

	if (tr->root == NULL)
		tr->root = trNode;
	else
	{
		father = FindPlace(tr->root, trNode->instrument);
		if (strcmp(father->instrument, trNode->instrument) > 0)
			father->left = new_one;
		else
			father->right = new_one;
	}
}
TreeNode* FindPlace(TreeNode* t, char* val)
{
	if (strcmp(t->instrument, val) > 0)
	{
		if (t->left == NULL)
			return t;
		else
			return FindPlace(t->left, val);
	}
	else
	{
		if (t->right == NULL)
			return t;
		else
			return FindPlace(t->right, val);
	}
}
char* findIdToStr(InstrumentTree tree, int id)
{
	return(findIdToStrHelper(tree.root, id));
}
char** findIdToStrHelper(TreeNode* root, int id)
{
	char** right = NULL;
	char** left = NULL;
	if (root == NULL)
		return NULL;
	if (root->insId == id)
	{
		return &root->instrument;
	}
	else
	{
		right = findIdToStrHelper(root->right, id);
		left = findIdToStrHelper(root->left, id);
		if (right != NULL)
			return right;
		if (left != NULL)
			return left;
	}
}


