#include "Wave.h"
#include <cstring>
#include <iostream>
#include <cassert>
#include <stack>
#include <math.h>
using namespace std;

/*
基于MAD绝对中位数滤波
in:原始数据
out:滤波后数据
*/
Wave::Wave()
{
}

Wave::~Wave()
{
}

//MAD阈值
void Wave::init(FILE *fp)
{
	//读取
	int data[320],i=0;
	int temp1[320],temp2[320];
	
	while (fscanf_s(fp, "%d", &data[i]) != EOF)
		i++;
	fclose(fp);
	memcpy(temp1, data, sizeof(data));
	memcpy(temp2, data, sizeof(data));

	/*
	滤波过程
	*/
	//求中位数
	int mad = EvaluateMedian(temp1, 320);
	for (i = 0; i < 320; i++)
	{
		temp2[i] -= mad;
		if (temp2[i] < 0)
			temp2[i] = -temp2[i];
	}
	mad = EvaluateMedian(temp2, 320);
	double Mad = mad*1.4826;
	mad = (int)Mad;
	for (i = 0; i < 320; i++)
	{
		if (data[i] < mad)
			data[i] = mad;
	}
	
	for (i = 0; i < 320; i++)
	{
		cout << data[i] << endl;
	}

	//输出
	ofstream outfile;
	char add[100] = "C:\\Users\\CUGtjh\\Desktop\\%s.txt";
	sprintf(add, "C:\\Users\\CUGtjh\\Desktop\\%s.txt", "out");
	outfile.open(add, ios::out);
	for (int i = 0; i < 320; i++)
	{
		outfile << data[i] << " ";
	}
	outfile.close();
	
}



// 求n个数的中位数
int Wave::QuickSortOnce(int a[], int low, int high)
{
	// 将首元素作为枢轴。
	int pivot = a[low];
	int i = low, j = high;

	while (i < j)
	{
		// 从右到左，寻找首个小于pivot的元素。
		while (a[j] >= pivot && i < j)
		{
			j--;
		}

		// 执行到此，j已指向从右端起首个小于或等于pivot的元素。
		// 执行替换。
		a[i] = a[j];

		// 从左到右，寻找首个大于pivot的元素。
		while (a[i] <= pivot && i < j)
		{
			i++;
		}

		// 执行到此，i已指向从左端起首个大于或等于pivot的元素。
		// 执行替换。
		a[j] = a[i];
	}

	// 退出while循环,执行至此,必定是i=j的情况。
	// i（或j）指向的即是枢轴的位置，定位该趟排序的枢轴并将该位置返回。
	a[i] = pivot;

	return i;
}

void Wave::QuickSort(int a[], int low, int high)
{
	if (low >= high)
	{
		return;
	}

	int pivot = QuickSortOnce(a, low, high);

	// 对枢轴的左端进行排序。
	QuickSort(a, low, pivot - 1);

	// 对枢轴的右端进行排序。
	QuickSort(a, pivot + 1, high);
}

int Wave::EvaluateMedian(int a[], int n)
{
	QuickSort(a, 0, n - 1);

	if (n % 2 != 0)
	{
		return a[n / 2];
	}
	else
	{
		return (a[n / 2] + a[n / 2 - 1]) / 2;
	}
}


