#include "List.h"
#include "Tree.h"
int MPIListLen(MPIList lst)
{
	int count = 0;
	MPIListNode* curr;
	curr = lst.head;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return count;
}

void makeEmptyMPIList(MPIList* lst)
{
	lst->head = lst->tail = NULL;
}

MPIListNode* getMPIListNode(MPIList* lst, int i)
{
	MPIListNode* curr;
	curr = lst->head;
	while (curr != NULL && i > 0)
	{
		curr = curr->next;
		i--;
	}
	return curr;
}

void insertDataToStartMPIList(MPIList* lst, MusicianPriceInstrument data)
{
	MPIListNode* newHead;
	newHead = createNewMPIListNode(data, NULL);
	insertNodeToStartMPIList(lst, newHead);
}

MPIListNode* createNewMPIListNode(MusicianPriceInstrument data, MPIListNode* next)
{
	MPIListNode* res;
	res = (MPIListNode*)malloc(sizeof(MPIListNode));
	res->MPI = data;
	res->next = next;
	return res;
}

void insertNodeToStartMPIList(MPIList* lst, MPIListNode* head)
{
	if (isEmptyMPIList(lst) == true)
	{
		head->next = NULL;
		lst->head = lst->tail = head;
	}
	else
	{
		head->next = lst->head;
		lst->head = head;
	}
}

bool isEmptyMPIList(MPIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

void insertDataToEndMPIList(MPIList* lst, MusicianPriceInstrument data)
{
	MPIListNode* newTail;
	newTail = createNewMPIListNode(data, NULL);
	insertNodeToEndMPIList(lst, newTail);
}

void insertNodeToEndMPIList(MPIList* lst, MPIListNode* tail)
{
	if (isEmptyMPIList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

bool insertDataToPlaceInMPIList(MPIList* lst, MusicianPriceInstrument data, int i)
{
	bool res;
	MPIListNode* newNode;
	newNode = createNewMPIListNode(data, NULL);
	res = insertNodeToPlaceInMPIList(lst, newNode, i);
	if (res == false)
		free(newNode);
	return res;
}

bool insertNodeToPlaceInMPIList(MPIList* lst, MPIListNode* node, int i)
{
	MPIListNode* after;
	after = getMPIListNode(lst, i - 1);
	if (after == NULL && i > 0) // Illegal location
		return false;
	else if (i == 0) // Start of MPIList
		insertNodeToStartMPIList(lst, node);
	else if (after->next == NULL) // End of MPIList
		insertNodeToEndMPIList(lst, node);
	else // “Middle”
	{
		node->next = after->next;
		after->next = node;
	}
	return true;
}
void printMPIList(MPIList* lst)
{
	MPIListNode* curr = lst->head;
	while (curr != NULL)
	{
		printf("id: %d , price: %lf\n", curr->MPI.insId, curr->MPI.price);
		curr = curr->next;
	}
}
void invertMPIList(MPIList* lst)
{
	MPIList inverted;
	MPIListNode* curr;
	MPIListNode* saver;
	makeEmptyMPIList(&inverted);
	curr = lst->head;
	while (curr != NULL)
	{
		saver = curr->next;
		insertNodeToStartMPIList(&inverted, curr);
		curr = saver;
	}
	*lst = inverted;
}

void CountPlayers(int* counters, Musician** MusiciansGroup, int sizeOfIns, int sizeofMusicians)
{
	int i;
	MPIListNode* temp;
	for (i = 0; i < sizeOfIns; i++)
		counters[i] = 0;
	for (i = 0; i < sizeofMusicians; i++)
	{
		temp = MusiciansGroup[i]->instruments.head;
		while (temp != NULL)
		{
			counters[temp->MPI.insId]++;
			temp = temp->next;
		}
	}

}

bool IsPlaying(int id, Musician* artist)
{
	MPIListNode* temp;
	temp = artist->instruments.head;
	while (temp != NULL)
	{
		if (temp->MPI.insId == id)
			return true;

		temp = temp->next;
	}
	return false;
}


Musician*** CreateMusiciansCollection(int NumOfInstruments, int* counters, Musician** MusiciansGroup, int NumOfMusicians)
{
	Musician*** MusiciansCollection = (Musician***)malloc(NumOfInstruments * sizeof(Musician**));
	for (int i = 0; i < NumOfInstruments; i++)
	{
		int place = 0;
		Musician* temp = MusiciansGroup[0];
		MusiciansCollection[i] = (Musician**)malloc(counters[i] * sizeof(Musician*));
		for (int j = 0; j < counters[i]; j++)
		{
			MusiciansCollection[i][j] = (Musician*)malloc(sizeof(Musician));
			while (!IsPlaying(i, temp))
			{
				place++;
				temp = MusiciansGroup[place];
			}
			MusiciansCollection[i][j] = temp;
			place++;
			temp = MusiciansGroup[place];
		}
	}
	return MusiciansCollection;
}


void FreeList(MPIList* lst)
{
	MPIListNode* current = lst->head;
	MPIListNode* next;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	lst->head = NULL;
	lst->tail = NULL;
}