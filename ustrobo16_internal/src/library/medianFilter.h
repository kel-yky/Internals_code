#ifndef __MEDIANFILTER_H
#define __MEDIANFILTER_H

#include "stm32f10x.h"

void printArr(int* array, int size);
void sorting(int* ccdValue, int startingPoint);
int median(int* ccdValue, int startingPoint);
void medianFilter(int* ccdValue, int* _32BitArray, const int THRESHOLD, const int SIZE);
u32 binaryToDecimal(int* BitArray, const int BIT);
	
#endif
