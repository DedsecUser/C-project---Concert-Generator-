#ifndef __Tree_h
#define __Tree_h

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h> 


#define MAXSIZE 150
#define InitID 0
#define NotFound -1
typedef struct treeNode {
	char* instrument;
	unsigned short insId;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree {
	TreeNode* root;
} InstrumentTree;

char* findIdToStr(InstrumentTree tree, int id);
char** findIdToStrHelper(TreeNode* root, int id);
InstrumentTree BuildTreeFromFile(char* fileName, int* NumOfInstruments);   //the function gets file name that contains all the instruments
																		   //the function returns Tree of instruments and its size as output parameter
TreeNode* MakeNewTreeNode(char* data, int id);
void InsertToTree(InstrumentTree* tr, TreeNode* trNode);
TreeNode* FindPlace(TreeNode* t, char* val);//the function finds the father of the instrument,after whom the current new instrument will be saved
bool isEmptyTree(InstrumentTree t);

void printTreeLDR(InstrumentTree* tr);
void printTreeLDRHelper(TreeNode* root);
void freeTree(InstrumentTree* tr);
void freeTreeHelper(TreeNode* root);
int findInsId(InstrumentTree tree, char* instrument);//calles for Helper
int findInsIdHelper(TreeNode* root, char* instrument);//the function gets name of instrument
													  //the function returns the id of given instrument if found,
void Checkmemoryalloc(void* value);
char** getInsMPIList(FILE* fIns, int* sizePelet);




#endif