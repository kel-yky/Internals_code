#include <stdio.h>
#include "medianFilter.h"

void printArr(int* array, int size){
	for(int i = 0; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

void sorting(int* ccdValue, int startingPoint){
	for(int i = startingPoint + 1; i < startingPoint + 4; i++){
		int moveValue = ccdValue[i];
		for(int j = i - 1; j >= 0; j--){
			if (moveValue <= ccdValue[j]){
				ccdValue[j + 1] = ccdValue[j];
				if(j == 0)ccdValue[0] = moveValue;
				
			} else {
				ccdValue[j + 1] = moveValue;
			}
		}
	}
}

int median(int* ccdValue, int startingPoint){
	 return (ccdValue[startingPoint + 1] + ccdValue[startingPoint + 2]) / 2;
}


void medianFilter(int* ccdValue, int* _32BitArray, const int THRESHOLD, const int SIZE){
	int _32BitArrayIndicator = 0;
		for(int startingPoint = 0; startingPoint < SIZE; startingPoint += 4){
			sorting(ccdValue, startingPoint);
			if(median(ccdValue, startingPoint) > THRESHOLD) _32BitArray[_32BitArrayIndicator] = 1;
			else _32BitArray[_32BitArrayIndicator] = 0;
			_32BitArrayIndicator++;
		}
	
}


u32 binaryToDecimal(int* BitArray, const int BIT){
	u32 decimal = 0, tmp = 0;
	for(int i = 0; i < BIT; i++){
			tmp = BitArray[i];
			if(tmp == 0) continue;
		for(int j = i; j < BIT - 1; j++){
			tmp *= 2;

		}
		decimal += tmp;
	}
	return decimal;
}
