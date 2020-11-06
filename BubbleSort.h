#pragma once
#include "Sort.h"
class BubbleSort : public Sort
{
public:
	void sort(int* data, int begin, int len, bool (*cmp)(int, int) = asc) override;
};

