#pragma once

#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>

/*
* 十大排序算法
*/

namespace byx {

	/* 升序 */
	template <class T>
	bool _asc(const T& a, const T& b) { return a < b; }
	/* 降序 */
	template <class T>
	bool _desc(const T& a, const T& b) { return a > b; }
	/* 排序数据自身，可自定义函数以自定义类型某个属性排序 */
	template <class T>
	T _sortself(const T& a) { return a; }

	/* 比较型排序 */
	/* 冒泡排序 性质：1、时间复杂度：O(n^2)  2、空间复杂度：O(1)  3、稳定排序  4、原地排序 */
	/* 待排序数组首地址，起始位置，排序长度，比较函数函数指针，默认升序*/
	template <class T>
	void bubbleSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc) {
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

	/* 选择排序 性质：1、时间复杂度：O(n^2)  2、空间复杂度：O(1)  3、非稳定排序  4、原地排序 */
	/* 待排序数组首地址，起始位置，排序长度，比较函数函数指针，默认升序*/
	template <class T>
	void selectionSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc) {
		for (int i = begin; i < begin + len - 1; i++) {
			int min = i;
			for (int j = i + 1; j < begin + len; j++) {
				min = cmp(data[j], data[min]) ? j : min;
			}
			T temp = data[i];
			data[i] = data[min];
			data[min] = temp;
		}
	}

	/* 插入排序 性质：1、时间复杂度：O(n^2)  2、空间复杂度：O(1)  3、稳定排序  4、原地排序*/
	/* 待排序数组首地址，起始位置，排序长度，比较函数函数指针，默认升序*/
	template <class T>
	void insertSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc) {
		int tmp, i, j;
		for (i = begin + 1; i < begin + len; i++) {
			tmp = data[i];
			for (j = i - 1; j >= begin && cmp(tmp, data[j]); j--)
			{
				data[j + 1] = data[j];
			}
			data[j + 1] = tmp;
		}
	}

	/* 希尔排序 */
	/* 待排序数组首地址，起始位置，排序长度，比较函数函数指针，默认升序*/
	template <class T>
    void shellSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc) {
		int n = len;
		for (n >>= 1; n > 0; n >>= 1) {
			for (int i = n; i < len; i++) {
				int j = i;
				T current = data[i];
				while (j - n >= 0 && cmp(current, data[j - n])) {
					data[j] = data[j - n];
					j = j - n;
				}
				data[j] = current;
			}
		}
	}

	/* 比较计数排序 性质：1、时间复杂度：O(n^2)  2、空间复杂度：O(n)  3、稳定排序  4、非原地排序 */
	/* 待排序数组首地址，起始位置，排序长度，比较函数函数指针，默认升序*/
	template <class T>
	void comparisonCountingSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc) {
		int* count = (int*)malloc(len * sizeof(int));
		memset(count, 0, len * sizeof(int));
		for (int i = 0; i < len - 1; i++) {
			for (int j = i + 1; j < len; j++) {
				int index = cmp(data[i + begin], data[j + begin]) ? j : i;
				count[index]++;
			}
		}
		T* dataCopy = (T*)malloc(len * sizeof(T));
		for (int i = 0; i < len; i++) {
			dataCopy[i] = data[i + begin];
		}
		for (int i = 0; i < len; i++) {
			data[count[i] + begin] = dataCopy[i];
		}
		free(dataCopy);
		free(count);
	}

	/* 快速排序 性质：1、时间复杂度：O(nlogn)  2、空间复杂度：O(logn)  3、非稳定排序  4、原地排序*/
	/* 待排序数组首地址，起始位置，排序长度，比较函数函数指针，默认升序*/
	template <class T>
	void quickSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc) {
		if (len > 1) {
			T partition = data[begin];
			int i = begin, j = begin + len - 1;
			while (i < j) {
				while (i < j && cmp(partition, data[j])) {
					j--;
				}
				data[i] = data[j];
				while (i < j && cmp(data[i], partition)) {
					i++;
				}
				data[j] = data[i];
			}
			data[i] = partition;
			quickSort(data, begin, i - begin, cmp);
			quickSort(data, i + 1, begin + len - 1 - i, cmp);
		}
	}

	template <class T>
	void _mergeSort(T* data, int begin, int len, T* merge, bool (*cmp)(const T&, const T&) = _asc) {
		if (len > 1) {
			int llen = (len - 1) / 2, p = begin, q = begin + len - 1;
			int mid = begin + llen, lbegin = begin, rbegin = mid + 1, rlen = len - 1 - llen;

			_mergeSort(data, begin, llen + 1, merge, cmp);
			_mergeSort(data, mid + 1, len - 1 - llen, merge, cmp);

			int i = lbegin;
			while (lbegin <= mid && rbegin <= begin + len - 1) {
				merge[i++] = cmp(data[rbegin], data[lbegin]) ? data[rbegin++] : data[lbegin++];
			}
			while (lbegin <= mid) merge[i++] = data[lbegin++];
			while (rbegin <= begin + len - 1) merge[i++] = data[rbegin++];
			while (p <= q) data[p] = merge[p++];
		}
	}

	/* 归并排序 性质：1、时间复杂度：O(nlogn)  2、空间复杂度：O(n)  3、稳定排序  4、非原地排序 */
	/* 待排序数组首地址，起始位置，排序长度，比较函数函数指针，默认升序*/
	template <class T>
	void mergeSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc) {
		if (!data || len < 2) return;
		T* dataCopy = (T*)malloc(len * sizeof(T));
		_mergeSort(data, begin, len, dataCopy, cmp);
		free(dataCopy);
		dataCopy = nullptr;
	}

	/* 堆排序 性质：1、时间复杂度：O(nlogn)  2、空间复杂度：O(1)  3、非稳定排序  4、原地排序 */
	/* 待排序数组首地址，起始位置，排序长度，比较函数函数指针，默认升序*/
	template <class T>
	void heapSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc) {
		for (int i = begin; i < len; i++) {
			int rindex = len - i, r = rindex - 1;
			for (int i = r / 2; i >= 0; i--) {
				int k = i;
				T v = data[k];
				while (2 * k + 1 < rindex) {
					int j = 2 * k + 1;
					if (j + 1 < rindex && cmp(data[j], data[j + 1])) {//存在两个子女并找到最大或最小子女下标
						j++;
					}
					if (cmp(v, data[j])) {//最大或最小子女与父结点比较并交换
						data[k] = data[j];
						data[j] = v;
						v = data[k];
					}
					else break;
				}
			}
			T Temp = data[0];//交换堆顶元素与本次末尾元素，末尾元素下次不参与排序
			data[0] = data[len - i - 1];
			data[len - i - 1] = Temp;
		}
	}

	//非比较型排序，基于整型实现
	/* 计数排序 性质：1、时间复杂度：O(n+k) k为max-min+1  2、空间复杂度：O(k)  3、稳定排序  4、非原地排序 */
	/* 待排序数组首地址，起始位置，排序长度，排序方式，默认升序*/
	void countingSort(int* data, int begin, int len, bool asc = true) {
		if (!data || len < 2) return;
		int max = data[begin], min = data[begin];
		for (int i = begin; i < len + begin; i++) {
			max = data[i] > max ? data[i] : max;
			min = data[i] < min ? data[i] : min;
		}
		int d = max - min + 1;
		int* count = (int*)malloc(d * sizeof(int));
		if (count) memset(count, 0, d * sizeof(int));
		for (int i = begin; i < begin + len; i++) {
			count[data[i] - min]++;
		}
		int k = 0;
		if (asc) {
			for (int i = 0; i < d; i++) {
				for (int j = count[i]; j > 0; j--) {
					data[k++] = i + min;
				}
			}
		}
		else {
			for (int i = d - 1; i >= 0; i--) {
				for (int j = count[i]; j > 0; j--) {
					data[k++] = i + min;
				}
			}
		}
		free(count);
		count = nullptr;
	}

	/* 桶排序 性质：1、时间复杂度：O(n+k)  2、空间复杂度：O(n+k)  3、稳定排序  4、非原地排序 */
	/* 待排序数组首地址，起始位置，排序长度，比较函数函数指针，默认升序，待排序属性，默认为data数组中数据本身，自定义以上两个规则需自定义函数*/
	template <class T, class SortValue = int>
	void bucketSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc, SortValue(*sortValue)(const T&) = _sortself) {
		if (!data || len < 2) return;
		SortValue max = sortValue(data[begin]), min = sortValue(data[begin]);
		for (int i = begin; i < len + begin; i++) {
			max = sortValue(data[i]) > max ? data[i] : max;
			min = sortValue(data[i]) < min ? data[i] : min;
		}
		bool asc = cmp(min, max);
		int d = max - min;
		//创建 d / 5 + 1 个桶，第 i 桶存放  5*i ~ 5*i+5-1范围的数
		int bucketNum = d / 5 + 1;
		std::vector<std::vector<T>> bucketList(bucketNum, std::vector<T>());

		//遍历原数组，将每个元素放入桶中
		for (int i = 0; i < len; i++) {
			bucketList[(sortValue(data[i]) - min) / 5].push_back(data[i]);
		}
		//对桶内的元素进行排序，需要对vector的内容排序，我这里采用系统自带的排序工具
		for (int i = 0; i < bucketNum; i++) {
			std::sort(bucketList[i].begin(), bucketList[i].end(), cmp);
		}
		//把每个桶排序好的数据进行合并汇总放回原数组
		if (asc) {
			for (int i = 0, k = 0; i < bucketNum; i++) {
				for (auto t : bucketList[i]) {
					data[k++] = t;
				}
			}
		}else {
			for (int i = bucketNum - 1, k = 0; i >= 0; i--) {
				for (auto t : bucketList[i]) {
					data[k++] = t;
				}
			}
		}
	}

	/* 基数排序 性质：1、时间复杂度：O(kn)  2、空间复杂度：O(n+k)  3、稳定排序  4、非原地排序 */
	/* 待排序数组首地址，起始位置，排序长度，排序方式，默认升序，待排序属性，默认为data数组中数据本身 */
	template <class T>
	void radioSort(T* data, int begin, int len, bool asc = true, int (*sortValue)(const T&) = _sortself) {
		if (!data || len < 2) return;

		int max = sortValue(data[begin]);
		for (int i = 1; i < len; i++) {
			if (sortValue(data[i + begin]) > max) max = sortValue(data[i + begin]);
		}
		//获得最大值位数
		int num = 1 + (int)log10(max);
		std::vector<std::vector<T>> bucketList(10, std::vector<T>());
		for (int i = 1; i <= num; i++) {
			for (int j = 0; j < len; j++) {
				int radio = (sortValue(data[j]) / (int)pow(10, i - 1)) % 10;
				bucketList[radio].push_back(data[j]);
			}
			int k = 0;
			if (asc) {
				for (int j = 0; j < 10; j++) {
					for (auto t : bucketList[j]) {
						data[k++] = t;
					}
					bucketList[j].clear();
				}
			} else {
				for (int j = 9; j >= 0; j--) {
					for (auto t : bucketList[j]) {
						data[k++] = t;
					}
					bucketList[j].clear();
				}
			}
		}
	}
}
#endif // !SORT_H