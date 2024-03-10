#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct {
	char name[20];
	char surname[30];
	int year;
}list_t;

int readFromFile(FILE* inp, list_t* arr) {
	int i = 0;
	while (fscanf(inp, " %s %s %d", arr[i].name, arr[i].surname, &arr[i].year) != EOF)
		i++;
	return i;
}

void sort(list_t* x, list_t* y) {
	list_t temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void bubbleSortTwoLevel(list_t* arr, int size) {
	int k, pass = 1, sorted;
	do {
		sorted = 1;
		for (k = 0; k < size - pass; k++)
		{
			if (strcmp(arr[k].surname, arr[k + 1].surname) > 0)
			{
				sort(&arr[k], &arr[k + 1]);
				sorted = 0;
			}
			if (strcmp(arr[k].surname, arr[k + 1].surname) == 0)
				if (strcmp(arr[k].name, arr[k + 1].name) > 0)
					sort(&arr[k + 1], &arr[k]);
		}
	} while (!sorted);
}

int main(void)
{
	FILE* inp;
	inp = fopen("people.txt", "r");
	if (inp == NULL)
		printf("Error");
	else
	{
		list_t arr[100];
		int size = readFromFile(inp, arr);

		bubbleSortTwoLevel(arr, size);
		FILE* out;
		out = fopen("sorted.txt", "w");
		for (int i = 0; i < size; i++)
			fprintf(out, "%-15s %-20s %10d\n", arr[i].name, arr[i].surname, arr[i].year);
	}
	return 0;
}