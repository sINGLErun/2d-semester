#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE 10

void first_max (int* arr1, int* arr2);

void main (void)
{
	int arr1[SIZE], arr2[SIZE];
	srand(time(NULL));
	for (int i = 0; i < SIZE; ++i)
	{
		arr1[i] = rand()%21-10;
	}

	first_max(arr1, arr2);

	for (int i = 0; i < SIZE; ++i)
	{
		printf("%6.0d  |  %6.0d\n", arr1[i], arr2[i]);
	}
}

void first_max (int* arr1, int* arr2)
{
	int max;
	for (int i = 0; i < SIZE; ++i)
	{
		if (i == 1) max = arr1[1];
		if (arr1[i] > max) max = arr1[i];
	}

	arr2[0] = max;
	arr2[SIZE - 1] = arr1[0];
	for (int i = 1; i < SIZE - 1; ++i)
	{
		arr2[i] = arr1[i];
	}
}

//все работает так как и ожидалось мы работаем с двумя массивами в памяти при этом их значения изменяются