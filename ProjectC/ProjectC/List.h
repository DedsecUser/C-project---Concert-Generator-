#ifndef __MPIList_h
#define __MPIList_h

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h> 

typedef struct
{
	unsigned short insId;
	float price;
} MusicianPriceInstrument;

typedef struct mpilListNode
{
	MusicianPriceInstrument MPI; // Musician Price Instrument
	struct mpilListNode* next;
} MPIListNode;

typedef struct
{
	MPIListNode* head;
	MPIListNode* tail;
} MPIList;

typedef struct
{
	char** name;
	int nameSize;
	float curPrice;
	MPIList instruments;
	bool Available;
} Musician;

int MPIListLen(MPIList lst);//the function gets a MPI list and returns its size
void makeEmptyMPIList(MPIList* lst);//the function makes empty MPI List
MPIListNode* getMPIListNode(MPIList* lst, int i);
void insertDataToStartMPIList(MPIList* lst, MusicianPriceInstrument data);//function inserts Node of data to start of MPI List
MPIListNode* createNewMPIListNode(MusicianPriceInstrument data, MPIListNode* next);
void insertNodeToStartMPIList(MPIList* lst, MPIListNode* head);
bool isEmptyMPIList(MPIList* lst);
void insertDataToEndMPIList(MPIList* lst, MusicianPriceInstrument data);
void insertNodeToEndMPIList(MPIList* lst, MPIListNode* tail);
bool insertDataToPlaceInMPIList(MPIList* lst, MusicianPriceInstrument data, int i);
bool insertNodeToPlaceInMPIList(MPIList* lst, MPIListNode* node, int i);
void printMPIList(MPIList* lst);
void invertMPIList(MPIList* lst);
void FreeList(MPIList* lst);
void CountPlayers(int* counters, struct Musician** MusiciansGroup, int sizeOfIns, int sizeofMusicians);//the function gets array of pointers to musicians
																									   //the function creates and array of intagers that represent number of musicians that plays on each instrument 

Musician*** CreateMusiciansCollection(int NumOfInstruments, int* counters, struct Musician** MusiciansGroup, int NumOfMusicians);//the function gets array of musicians and how much of them play on each instruments
																																 //the function creates the "Musician Collection" in which each array include list of allof  the  musicians that play on same instrument by id
bool IsPlaying(int id, struct Musician* artist);//the function gets and id of instrument and a Musician
												//the function returns true if the given artist plays on the given instrument's id,-1 otherwise
#endif          