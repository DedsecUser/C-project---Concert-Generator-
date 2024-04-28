#ifndef __FilesLib_h
#define __FilesLib_h

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h> 

bool isNum(char* str); //the function returns true if char is a number,false otherwise
long int fileSize(FILE* fp);//the function calculates the size of file
void removeSepsFromFile(char* srcFile, char* eps, char* dest, int* NumOfMusicians);//the function gets name of file with array of chars
                                                                                    //the function creates new file after filtering the chars that are meaningless
struct Musician** CreateMusicianGroup(char* FileName, struct tree* tr, int NumOfMusicions);//the function gets name of file with Musicians details and Creates the "Musician group" from the instrument tree and the 



#endif