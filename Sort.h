#pragma once
class Sort
{
public:
	/* ÅÅĞò½Ó¿Ú */
	virtual void sort(int* data, int begin, int len, bool (*cmp)(int, int)=asc) = 0;

	/* Ä¬ÈÏÉıĞò */
	static inline bool asc(int a, int b) { return a < b; }

	static inline bool desc(int a, int b) { return a > b; }
};

