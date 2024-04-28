#include "Tree.h"
#include "FilesLib.h"
#include "List.h"
#include "Concert.h"

static int TotalInstruments;

void main()
{
	bool Cheak;
	int NumOfMusicians, NumOfInstruments, NumOfConcerts;
	char* argv3 = "NoSepsFile.txt";
	char* argv = "instruments.txt";
	Musician** MusiciansGroup;
	InstrumentTree tr;
	tr = BuildTreeFromFile(argv, &NumOfInstruments);     //build the instrument tree
	removeSepsFromFile("musicians.txt", " ,.;:?!-\t'()[]{}<>~_", argv3, &NumOfMusicians);//create text file after filtering the strange chars
	MusiciansGroup = CreateMusicianGroup(argv3, &tr, NumOfMusicians);//creates the Group of Musicians
	int* counters = (int*)malloc(NumOfInstruments * sizeof(int));//Sort of CountingSort to save how many musicians playing on each instrument
	Checkmemoryalloc(counters);
	CountPlayers(counters, MusiciansGroup, NumOfInstruments, NumOfMusicians);//Creates an array of integers that show us how much musicians play totally on every instrument
	Musician*** MusiciansCollection = CreateMusiciansCollection(NumOfInstruments, counters, MusiciansGroup, NumOfMusicians);//Create the "Musician Collection"
	GetDataForConcertFile(&NumOfConcerts);//saving data of concerts to file
	GenerateConcerts(MusiciansGroup, MusiciansCollection, NumOfConcerts, &tr, counters, NumOfInstruments);//Manage Concert Details and print Concert details to screen
	LetMyBitimGo(&tr, MusiciansGroup, NumOfMusicians, MusiciansCollection, NumOfInstruments);//Free all the data Usage
}