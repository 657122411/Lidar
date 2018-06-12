#pragma once

#include "iostream"
#include "fstream"
class Wave
{
public:
	Wave();
	~Wave();
	
	int data[320];

    
	void init(FILE *fp);	
	int QuickSortOnce(int a[], int low, int high);
	void QuickSort(int a[], int low, int high);
	int EvaluateMedian(int a[], int n);
};


