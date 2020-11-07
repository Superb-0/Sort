#pragma once

#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>

/*
* ʮ�������㷨
*/

namespace byx {

	/* ���� */
	template <class T>
	bool _asc(const T& a, const T& b) { return a < b; }
	/* ���� */
	template <class T>
	bool _desc(const T& a, const T& b) { return a > b; }
	/* ���������������Զ��庯�����Զ�������ĳ���������� */
	template <class T>
	T _sortself(const T& a) { return a; }

	/* �Ƚ������� */
	/* ð������ ���ʣ�1��ʱ�临�Ӷȣ�O(n^2)  2���ռ临�Ӷȣ�O(1)  3���ȶ�����  4��ԭ������ */
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ��ȽϺ�������ָ�룬Ĭ������*/
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

	/* ѡ������ ���ʣ�1��ʱ�临�Ӷȣ�O(n^2)  2���ռ临�Ӷȣ�O(1)  3�����ȶ�����  4��ԭ������ */
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ��ȽϺ�������ָ�룬Ĭ������*/
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

	/* �������� ���ʣ�1��ʱ�临�Ӷȣ�O(n^2)  2���ռ临�Ӷȣ�O(1)  3���ȶ�����  4��ԭ������*/
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ��ȽϺ�������ָ�룬Ĭ������*/
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

	/* ϣ������ */
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ��ȽϺ�������ָ�룬Ĭ������*/
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

	/* �Ƚϼ������� ���ʣ�1��ʱ�临�Ӷȣ�O(n^2)  2���ռ临�Ӷȣ�O(n)  3���ȶ�����  4����ԭ������ */
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ��ȽϺ�������ָ�룬Ĭ������*/
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

	/* �������� ���ʣ�1��ʱ�临�Ӷȣ�O(nlogn)  2���ռ临�Ӷȣ�O(logn)  3�����ȶ�����  4��ԭ������*/
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ��ȽϺ�������ָ�룬Ĭ������*/
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

	/* �鲢���� ���ʣ�1��ʱ�临�Ӷȣ�O(nlogn)  2���ռ临�Ӷȣ�O(n)  3���ȶ�����  4����ԭ������ */
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ��ȽϺ�������ָ�룬Ĭ������*/
	template <class T>
	void mergeSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc) {
		if (!data || len < 2) return;
		T* dataCopy = (T*)malloc(len * sizeof(T));
		_mergeSort(data, begin, len, dataCopy, cmp);
		free(dataCopy);
		dataCopy = nullptr;
	}

	/* ������ ���ʣ�1��ʱ�临�Ӷȣ�O(nlogn)  2���ռ临�Ӷȣ�O(1)  3�����ȶ�����  4��ԭ������ */
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ��ȽϺ�������ָ�룬Ĭ������*/
	template <class T>
	void heapSort(T* data, int begin, int len, bool (*cmp)(const T&, const T&) = _asc) {
		for (int i = begin; i < len; i++) {
			int rindex = len - i, r = rindex - 1;
			for (int i = r / 2; i >= 0; i--) {
				int k = i;
				T v = data[k];
				while (2 * k + 1 < rindex) {
					int j = 2 * k + 1;
					if (j + 1 < rindex && cmp(data[j], data[j + 1])) {//����������Ů���ҵ�������С��Ů�±�
						j++;
					}
					if (cmp(v, data[j])) {//������С��Ů�븸���Ƚϲ�����
						data[k] = data[j];
						data[j] = v;
						v = data[k];
					}
					else break;
				}
			}
			T Temp = data[0];//�����Ѷ�Ԫ���뱾��ĩβԪ�أ�ĩβԪ���´β���������
			data[0] = data[len - i - 1];
			data[len - i - 1] = Temp;
		}
	}

	//�ǱȽ������򣬻�������ʵ��
	/* �������� ���ʣ�1��ʱ�临�Ӷȣ�O(n+k) kΪmax-min+1  2���ռ临�Ӷȣ�O(k)  3���ȶ�����  4����ԭ������ */
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ�����ʽ��Ĭ������*/
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

	/* Ͱ���� ���ʣ�1��ʱ�临�Ӷȣ�O(n+k)  2���ռ临�Ӷȣ�O(n+k)  3���ȶ�����  4����ԭ������ */
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ��ȽϺ�������ָ�룬Ĭ�����򣬴��������ԣ�Ĭ��Ϊdata���������ݱ����Զ������������������Զ��庯��*/
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
		//���� d / 5 + 1 ��Ͱ���� i Ͱ���  5*i ~ 5*i+5-1��Χ����
		int bucketNum = d / 5 + 1;
		std::vector<std::vector<T>> bucketList(bucketNum, std::vector<T>());

		//����ԭ���飬��ÿ��Ԫ�ط���Ͱ��
		for (int i = 0; i < len; i++) {
			bucketList[(sortValue(data[i]) - min) / 5].push_back(data[i]);
		}
		//��Ͱ�ڵ�Ԫ�ؽ���������Ҫ��vector�������������������ϵͳ�Դ������򹤾�
		for (int i = 0; i < bucketNum; i++) {
			std::sort(bucketList[i].begin(), bucketList[i].end(), cmp);
		}
		//��ÿ��Ͱ����õ����ݽ��кϲ����ܷŻ�ԭ����
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

	/* �������� ���ʣ�1��ʱ�临�Ӷȣ�O(kn)  2���ռ临�Ӷȣ�O(n+k)  3���ȶ�����  4����ԭ������ */
	/* �����������׵�ַ����ʼλ�ã����򳤶ȣ�����ʽ��Ĭ�����򣬴��������ԣ�Ĭ��Ϊdata���������ݱ��� */
	template <class T>
	void radioSort(T* data, int begin, int len, bool asc = true, int (*sortValue)(const T&) = _sortself) {
		if (!data || len < 2) return;

		int max = sortValue(data[begin]);
		for (int i = 1; i < len; i++) {
			if (sortValue(data[i + begin]) > max) max = sortValue(data[i + begin]);
		}
		//������ֵλ��
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