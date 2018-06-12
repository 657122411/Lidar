#include "Wave.h"
#include <cstring>
#include <iostream>
#include <cassert>
#include <stack>
#include <math.h>
using namespace std;

/*
����MAD������λ���˲�
in:ԭʼ����
out:�˲�������
*/
Wave::Wave()
{
}

Wave::~Wave()
{
}

//MAD��ֵ
void Wave::init(FILE *fp)
{
	//��ȡ
	int data[320],i=0;
	int temp1[320],temp2[320];
	
	while (fscanf_s(fp, "%d", &data[i]) != EOF)
		i++;
	fclose(fp);
	memcpy(temp1, data, sizeof(data));
	memcpy(temp2, data, sizeof(data));

	/*
	�˲�����
	*/
	//����λ��
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

	//���
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



// ��n��������λ��
int Wave::QuickSortOnce(int a[], int low, int high)
{
	// ����Ԫ����Ϊ���ᡣ
	int pivot = a[low];
	int i = low, j = high;

	while (i < j)
	{
		// ���ҵ���Ѱ���׸�С��pivot��Ԫ�ء�
		while (a[j] >= pivot && i < j)
		{
			j--;
		}

		// ִ�е��ˣ�j��ָ����Ҷ����׸�С�ڻ����pivot��Ԫ�ء�
		// ִ���滻��
		a[i] = a[j];

		// �����ң�Ѱ���׸�����pivot��Ԫ�ء�
		while (a[i] <= pivot && i < j)
		{
			i++;
		}

		// ִ�е��ˣ�i��ָ���������׸����ڻ����pivot��Ԫ�ء�
		// ִ���滻��
		a[j] = a[i];
	}

	// �˳�whileѭ��,ִ������,�ض���i=j�������
	// i����j��ָ��ļ��������λ�ã���λ������������Ტ����λ�÷��ء�
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

	// ���������˽�������
	QuickSort(a, low, pivot - 1);

	// ��������Ҷ˽�������
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


