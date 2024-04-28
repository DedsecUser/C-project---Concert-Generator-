#ifndef __Concert_h
#define __Concert_h

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h> 

#define TimeSize 5
static int CMPID = 0;
typedef struct
{
	int day, month, year;
	float hour;
} Date;

typedef struct
{
	int num;
	int inst;
	char importance;
} ConcertInstrument;

typedef struct
{
	ConcertInstrument data;
	ConcertInstrument* next;
}ConcertInstrumentNode;

typedef struct
{
	ConcertInstrumentNode* head;
	ConcertInstrumentNode* tail;
}CIList;

typedef struct
{
	Date date_of_concert;
	char* name;
	CIList instruments;
} Concert;

typedef int(*p2f)(void*, void*);

float CharToTime(char c1, char c2, char c4, char c5);//function get chars that represents concert time
													 //function returns the time in float

void GetDataForConcertFile(int* size);       //Getting data for single concert

void GenerateConcerts(struct Musician** MusiciansGroup, struct Musician*** MusiciansCollection, int NumOfConcerts, struct tree* tr, int* counters, int NumOfMusicians);
void insertNodeToStartCIList(CIList* lst, ConcertInstrumentNode* head);
ConcertInstrumentNode* CreateCINodeFromData(int id, int quantity, char importance);
void makeEmptyCIList(CIList* res);
void insertCINodeToEndCIList(CIList* lst, ConcertInstrumentNode* tail);
bool isEmptyCIList(CIList* lst);
int SortLowToHigh(void* a, void* b);//function gets two musicians and id of an instrument
									//function returns the difference between the cost of left-right 
int SortHighToLow(void* a, void* b);//function gets two musicians and id of an instrument
									//function returns the difference between the cost of right-left
void PrintConcert(Concert list, struct Musician*** MusiciansCollection, int* counters, int NumOfInstruments, struct tree* tr);					//Manage the Concert details
					//if can create concert-prints all the data to the screen
					//if cannot,prints error messege
void resetAvailable(struct Musician*** MusiciansCollection, int* counters, int NumOfInstruments);
bool CanCreateConcert(Concert list, struct Musician*** MusiciansCollection, int* counters, int NumOfInstruments);

float PrintAndSum(Concert list, struct Musician*** MusiciansCollection, int* counters, int NumOfInstruments, struct tree* tr);

void PrintFullName(struct Musician* artist);

float getPriceForID(struct MPIList* InsList, int id);

void LetMyBitimGo(struct InstrumentTree* tr, struct Musician** MusiciansGroup, int NumofArtists, struct Musician*** MusiciansCollection, int NumOfInstruments);
void FreeMusicianGroup(struct Musician** MusiciansGroup, int NumofArtists);
void FreeMusiciansCollection(struct Musician*** MusiciansCollection, int NumOfInstruments);
void FreeCIList(CIList* lst);
char* CreateName(FILE* f);
#endif




