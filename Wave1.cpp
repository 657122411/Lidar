#include "Wave1.h"
#include <cstring>
#include <iostream>
#include <cassert>
#include <stack>
#include <math.h>
using namespace std;


Wave1::Wave1()
{
}

Wave1::~Wave1()
{
}

//lanmuda/miu�˲�
void Wave1::init(FILE *fp)
{
	//��ȡ
	int data[320];
	int m = 0;
	double temp[320],temp1[320], temp2[320];

	while (fscanf_s(fp, "%d", &data[m]) != EOF)
		m++;
	fclose(fp);
	for (m=0; m < 320; m++)
	{
		temp[m] = (double)data[m];
	}
	
	
	//�˲�
	int cycle = 1;//ѭ������
	do
	{
		memcpy(temp1, temp, sizeof(temp));
		int W = 11;//�����С
		double w = 0;//Ӱ��ϵ��
		int count;
		double tep;
		for (int h = W; h <= (320 - W); h++)
		{
			tep = 0;
			count = 0;
			for (int j = h - W; j <= h + W; j++)
			{
				if (((temp[h] - temp[j]) * (temp[h] - temp[j]) + (h - j)*(h - j)) <= W*W)
				{
					count++;
					tep += (temp[j] - temp[h]);
				}
			}
			temp1[h] = temp[h] + 0.6307 / ((double)count)*tep;
		}

		memcpy(temp2, temp1, sizeof(temp1));

		for (int g = W; g <= (320 - W); g++)
		{
			tep = 0;
			count = 0;
			for (int j = g - W; j <= g + W; j++)
			{
				if (((temp1[g] - temp1[j]) * (temp1[g] - temp1[j]) + (g - j)*(g - j)) <= W*W)
				{
					count++;
					tep += (temp1[j] - temp1[g]);
				}
			}
			temp2[g] = temp1[g] - 0.6372 / ((double)count)*tep;
		}

		memcpy(temp, temp2, sizeof(temp2));
		
	} while (cycle++ < 3);
	

	//���
	ofstream outfile;
	char add[100] = "C:\\Users\\CUGtjh\\Desktop\\%s.txt";
	sprintf(add, "C:\\Users\\CUGtjh\\Desktop\\%s.txt", "wave1");


	outfile.open(add, ios::out);
	for (int i = 0; i < 320; i++)
	{
		outfile << temp2[i] << " ";
	}
	outfile.close();

}



