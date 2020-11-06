#include "BubbleSort.h"

void BubbleSort::sort(int* data, int begin, int len, bool (*cmp)(int, int))
{
	for (int i = begin; i < len - 1; i++) {
		bool flag = false;
		for (int j = begin; j < len - i - 1; j++) {
			if (cmp(data[j + 1], data[j])) {
				int temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
				if (!flag) flag = true;
			}
		}
		if (!flag) return;
	}
}
