#include "FilesLib.h"
#include "List.h"
#include "Tree.h"

bool isNum(char* str)
{
	if (str[0] >= '0' && str[0] <= '9')
		return true;
	return false;
}
long int fileSize(FILE* fp)
{
	long int res, saver;

	saver = ftell(fp);

	fseek(fp, 0, SEEK_END);

	res = ftell(fp);

	fseek(fp, saver, SEEK_SET);

	return res;
}

void removeSepsFromFile(char* srcFile, char* seps, char* dest, int* NumOfMusicians)
{
	bool FirstPrice = false;
	int count = 0, Linecount = 0;
	char* token;

	FILE* SourceF = fopen(srcFile, "r");
	FILE* OutputF = fopen(dest, "w");

	char string[MAXSIZE];

	long int MusicFileSize = fileSize(SourceF);
	while (ftell(SourceF) != MusicFileSize)
	{
		fgets(string, MAXSIZE, SourceF);
		Linecount++;
		token = strtok(string, seps);
		while (token != NULL)
		{
			if (!FirstPrice)
				count++;
			if (isNum(token) && !FirstPrice)
			{
				FirstPrice = true;
				count = count - 2;
			}
			fprintf(OutputF, "%s ", token);

			token = strtok(NULL, seps);
		}

		fseek(OutputF, -1, SEEK_CUR);
		if (feof(SourceF))
			fprintf(OutputF, "\n", count);
		fprintf(OutputF, "%d\n", count);
		FirstPrice = false;
		count = 0;
	}
	*NumOfMusicians = Linecount;
	fclose(OutputF);
	fclose(SourceF);
}

struct Musician** CreateMusicianGroup(char* FileName, InstrumentTree* tr, int NumOfMusicions)
{
	FILE* F = fopen(FileName, "r");
	if (F == NULL)
		printf("File  does not exist\n");
	else
	{
		int endofFile = fileSize(F);
		char seps[] = " ";
		char* token;
		char samanMove;
		char** name;
		int size, i, id, j = 0;
		float price;
		char line[MAXSIZE], tempName[MAXSIZE];
		MPIList instruments;
		MusicianPriceInstrument tempMPI;
		Musician* Artist;
		Musician** MusiciansGroup = (Musician**)malloc(NumOfMusicions * sizeof(Musician*));
		while (ftell(F) != endofFile)
		{
			Artist = (Musician*)malloc(sizeof(Musician));
			makeEmptyMPIList(&instruments);
			fgets(line, MAXSIZE, F);
			fscanf(F, "%d", &size);
			fscanf(F, "%c", &samanMove);

			name = (char**)malloc(size * sizeof(char*));
			token = strtok(line, seps);

			for (i = 0; i < size; i++)
			{
				name[i] = strdup(token);
				token = strtok(NULL, seps);
			}

			while (token != NULL && token[0] != '\n')
			{
				id = findInsId(*tr, token);
				token = strtok(NULL, seps);
				price = atof(token);
				tempMPI.insId = id;
				tempMPI.price = price;
				insertDataToStartMPIList(&instruments, tempMPI);
				token = strtok(NULL, seps);
			}

			Artist->instruments = instruments;
			Artist->name = name;
			Artist->nameSize = size;
			Artist->Available = true;
			MusiciansGroup[j] = Artist;
			j++;
			/*
			printf("\n");
			printMPIList(&Artist->instruments);
			printf("\n");
			*/
		}
		return MusiciansGroup;
	}


}