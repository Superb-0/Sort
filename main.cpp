#include "BubbleSort.h"
#include <stdio.h>

int main() {
	int data[] = { 62,32,84,96,19,47 };
	for (int d : data) { printf("%d ", d); }
	printf("\n--------\n");
	BubbleSort bubbleSort;
	bubbleSort.sort(data, 0, 6);
	for (int d : data) { printf("%d ", d); }
	printf("\n--------\n");
	return 0;
}