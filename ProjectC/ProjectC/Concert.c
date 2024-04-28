#include "Concert.h"
#include "FilesLib.h"
#include "List.h"
#include "Tree.h"


void GetDataForConcertFile(int* size)
{
	FILE* f;
	int counter = 0;
	f = fopen("ConcertInput.txt", "w");
	Checkmemoryalloc(f);
	char c1;
	char c2;
	scanf("%c", &c1);
	scanf("%c", &c2);
	while (!(c1 == '\n' && c2 == '\n'))
	{
		fprintf(f, "%c", c1);
		fprintf(f, "%c", c2);
		scanf("%c", &c1);
		scanf("%c", &c2);
		if (c1 == '\n' || c1 == '\n')
			counter++;
	}
	counter++;
	*size = counter;
	fclose(f);
}
float CharToTime(char c1, char c2, char c4, char c5)
{
	int c1n, c2n, c4n, c5n;
	c1n = c1 - '0';
	c2n = c2 - '0';
	c4n = c4 - '0';
	c5n = c5 - '0';
	float res;
	float res2;
	res = c1n * 10 + c2n;
	res2 = ((float)(c4n * 10 + c5n) / 60.0);
	return res + res2;
}


ConcertInstrumentNode* CreateCINodeFromData(int id, int quantity, char importance)
{
	ConcertInstrumentNode* CINode;
	CINode = (ConcertInstrumentNode*)malloc(sizeof(ConcertInstrumentNode));
	Checkmemoryalloc(CINode);
	CINode->data.inst = id;
	CINode->data.importance = importance;
	CINode->data.num = quantity;
	CINode->next = NULL;
	return CINode;
}
void makeEmptyCIList(CIList* res)
{
	res->head = NULL;
	res->tail = NULL;
}

void insertCINodeToEndCIList(CIList* lst, ConcertInstrumentNode* tail)
{
	if (isEmptyCIList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;

}

void insertNodeToStartCIList(CIList* lst, ConcertInstrumentNode* head)
{
	if (isEmptyCIList(lst) == true)
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

bool isEmptyCIList(CIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

int SortLowToHigh(void* a, void* b)
{
	Musician* m1 = *((Musician**)a);
	Musician* m2 = *((Musician**)b);
	MPIListNode* node1 = m1->instruments.head;
	MPIListNode* node2 = m2->instruments.head;
	while (node1->MPI.insId != CMPID)
	{
		node1 = node1->next;
	}
	while (node2->MPI.insId != CMPID)
	{
		node2 = node2->next;
	}
	float res = (node1->MPI.price) - (node2->MPI.price);
	if (res > 0)
		return 1;
	else if (res == 0)
		return 0;
	else
		return -1;

}
int SortHighToLow(void* a, void* b)
{
	Musician* m1 = *((Musician**)a);
	Musician* m2 = *((Musician**)b);
	MPIListNode* node1 = m1->instruments.head;
	MPIListNode* node2 = m2->instruments.head;
	while (node1->MPI.insId != CMPID)
	{
		node1 = node1->next;
	}
	while (node2->MPI.insId != CMPID)
	{
		node2 = node2->next;
	}
	float res = (node1->MPI.price) - (node2->MPI.price);
	if (res > 0)
		return -1;
	else if (res == 0)
		return 0;
	else
		return 1;
}

void GenerateConcerts(struct Musician** MusiciansGroup, struct Musician*** MusiciansCollection, int NumOfConcerts, InstrumentTree* tr, int* counters, int NumOfInstruments)
{
	p2f LowToHigh = SortLowToHigh;
	p2f HighToLow = SortHighToLow;
	char c1, c2, dump, c4, c5,*name;
	FILE* f;
	ConcertInstrumentNode* CINode;
	Concert temp;
	char c, importance;
	char ins[MAXSIZE];
	int quantity, id;
	f = fopen("ConcertInput.txt", "r");
	Checkmemoryalloc(f);
	for (int i = 0; i < NumOfConcerts; i++)
	{
		//Function!!!
		temp.name = CreateName(f);
		//FUNCITON!!!
		fscanf(f, "%d%d%d", &temp.date_of_concert.day, &temp.date_of_concert.month, &temp.date_of_concert.year);
		fscanf(f, "%c%c%c%c%c%c", &dump, &c1, &c2, &dump, &c4, &c5);
		temp.date_of_concert.hour = CharToTime(c1, c2, c4, c5);
		makeEmptyCIList(&temp.instruments);
		fscanf(f, "%c", &dump);
		while (dump != '\n' && ftell(f) != fileSize(f))
		{
			static int Count = 0;
			fscanf(f, "%s%d%c%c", ins, &quantity, &dump, &importance);
			id = findInsId(*tr, ins);
			CINode = CreateCINodeFromData(id, quantity, importance);
			if (Count == 0)
				insertNodeToStartCIList(&temp.instruments, CINode);
			else
				insertCINodeToEndCIList(&temp.instruments, CINode);
			Count++;
			CMPID = id;
			if (importance == '0')
				qsort(MusiciansCollection[id], counters[id], sizeof(Musician*), LowToHigh);
			else
				qsort(MusiciansCollection[id], counters[id], sizeof(Musician*), HighToLow);
			fscanf(f, "%c", &dump);
		}
		PrintConcert(temp, MusiciansCollection, counters, NumOfInstruments, tr);
		FreeCIList(&(temp.instruments));
		free(temp.name);
	}

}
bool CanCreateConcert(Concert list, struct Musician*** MusiciansCollection, int* counters, int NumOfInstruments)
{
	Musician** arr;

	ConcertInstrumentNode* CINODE = list.instruments.head;
	while (CINODE != NULL)
	{
		int COUNTER = 0;

		int id = CINODE->data.inst;
		arr = MusiciansCollection[id];
		int num = CINODE->data.num; //Quantity of instruments wanted
		for (int i = 0; i < num; i++) //Look for the quantity needed
		{
			for (int j = 0; j < counters[id] && COUNTER < num; j++) //check if there's musicians available
			{
				if (arr[j]->Available == true)
				{
					arr[j]->Available = false;
					COUNTER++;
				}
			}
		}
		if (COUNTER < num)
			return false;
		CINODE = CINODE->next;
	}
	resetAvailable(MusiciansCollection, counters, NumOfInstruments);
	return true;
}

void PrintConcert(Concert list, struct Musician*** MusiciansCollection, int* counters, int NumOfInstruments, struct tree* tr)
{
	float sum, CurrMusicianPrice;
	Musician** arr;
	ConcertInstrumentNode* CINODE = list.instruments.head;
	if (CanCreateConcert(list, MusiciansCollection, counters, NumOfInstruments) == false)
		printf("\nCould not find musicians for the concert %s", list.name);
	else
	{
		sum = PrintAndSum(list, MusiciansCollection, counters, NumOfInstruments, tr);
	}
	resetAvailable(MusiciansCollection, counters, NumOfInstruments);
}



float PrintAndSum(Concert list, struct Musician*** MusiciansCollection, int* counters, int NumOfInstruments, struct tree* tr)
{
	char** ptrIns;
	float sum = 0;
	Musician** arr;
	ConcertInstrumentNode* CINODE = list.instruments.head;
	printf("\n%s %d %d %d ", list.name, list.date_of_concert.day, list.date_of_concert.month, list.date_of_concert.year);
	float minute = list.date_of_concert.hour - (int)list.date_of_concert.hour;
	minute = minute * 60;
	printf("%d:%02d ", (int)list.date_of_concert.hour, (int)minute);
	while (CINODE != NULL)
	{
		int COUNTER = 0;
		float price = 0;
		int id = CINODE->data.inst;
		arr = MusiciansCollection[id];
		int num = CINODE->data.num; //Quantity of instruments wanted
		for (int i = 0; i < num; i++) //Look for the quantity needed
		{
			for (int j = 0; j < counters[id] && COUNTER < num; j++) //check if there's musicians available
			{
				if (arr[j]->Available == true)
				{
					arr[j]->Available = false;
					COUNTER++;
					PrintFullName(arr[j]);
					printf("- ");
					ptrIns = findIdToStr(*tr, id);
					printf("%s ", *ptrIns);
					price = getPriceForID(&arr[j]->instruments, id);
					printf("(%.2lf) ", price);
					sum += price;
				}
			}
		}
		CINODE = CINODE->next;
	}
	printf(" Total Cost: %.2lf", sum);
	return sum;
}
float getPriceForID(MPIList* InsList, int id)
{
	struct mpilListNode* mpiNode = InsList->head;
	while (mpiNode->MPI.insId != id)
	{
		mpiNode = mpiNode->next;
	}
	return mpiNode->MPI.price;
}




void resetAvailable(struct Musician*** MusiciansCollection, int* counters, int NumOfInstruments)
{
	Musician** arr;
	for (int i = 0; i < NumOfInstruments; i++)
	{
		arr = MusiciansCollection[i];
		for (int j = 0; j < counters[i]; j++)
			arr[j]->Available = true;
	}
}

void PrintFullName(Musician* artist)
{
	int size = artist->nameSize;
	int i;
	for (i = 0; i < size; i++)
		printf("%s ", artist->name[i]);
}

void LetMyBitimGo(struct InstrumentTree* tr, struct Musician** MusiciansGroup, int NumofArtists, struct Musician*** MusiciansCollection, int NumOfInstruments)
{
	freeTree(tr);
	FreeMusicianGroup(MusiciansGroup, NumofArtists);
	FreeMusiciansCollection(MusiciansCollection, NumOfInstruments);
}


void FreeMusicianGroup(struct Musician** MusiciansGroup, int NumofArtists)
{
	for (int i = 0; i < NumofArtists; i++)
	{
		Musician* artist = MusiciansGroup[i];
		for (int j = 0; j < artist->nameSize; j++)
			free(artist->name[j]);
		free(artist->name);
		FreeList(&(artist->instruments));
		free(artist);
	}
	free(MusiciansGroup);

}
void FreeMusiciansCollection(struct Musician*** MusiciansCollection, int NumOfInstruments)
{
	for (int i = 0; i < NumOfInstruments; i++)
	{
		
		free(MusiciansCollection[i]);
	}
	free(MusiciansCollection);
}
void FreeCIList(CIList* lst)
{
	ConcertInstrumentNode* current = lst->head;
	ConcertInstrumentNode* next;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	lst->head = NULL;
	lst->tail = NULL;
}

char* CreateName(FILE* f)
{
	char c;
	char* name = (char*)malloc(sizeof(char));
	int physSize = 1;
	int logsize = 0;
	fscanf(f, "%c", &c);
	while (c != ' ')
	{
		if (logsize == physSize)
		{
			physSize *= 2;
			name = realloc(name, physSize);
		}
		name[logsize] = c;
		logsize++;
		fscanf(f, "%c", &c);
	}
	if (logsize == physSize)
	{
		physSize++;
		name = realloc(name, physSize);
	}
	else
	{
		name = realloc(name, logsize + 1);
	}
	name[logsize] = '\0';
	return name;

}

