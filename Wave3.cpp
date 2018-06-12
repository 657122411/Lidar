#include "Wave3.h"
#include <cstring>
#include <iostream>
#include <cassert>
#include <stack>
#include <math.h>
using namespace std;

Wave3::Wave3()
{
}

Wave3::~Wave3()
{
}

/*���ܣ�  ��˹������
//kernel���洢���ɵĸ�˹��
//size��  �˵Ĵ�С
//sigma�� ��̬�ֲ���׼��
*/
void gau_kernel(double kernel[], int size, double sigma)
{
	if (size <= 0 || sigma == 0)
		return;
	int x;
	float sum = 0;
	int m = (size - 1) / 2;

	//get kernel	
	for (x = 0; x <size; x++)
	{
		kernel[x] = (1 / sigma * sqrt(2 * 3.1415 )) * exp(-(x-m)*(x-m)/2*sigma*sigma);
		sum += kernel[x];
	}
	
	//normal
	for (x = 0; x < size; x++)
	{
			kernel[x] /= sum;
	}
}


/*���ܣ� ��˹ģ��
//src��  ����ԭͼ
//dst��  ģ��ͼ��
//size�� �˵Ĵ�С
//sigma����̬�ֲ���׼��
*/
void gaussian(double src[], double dst[])
{
	double kernel[5];
	gau_kernel(kernel, 5, 1);
	//gaussian���,��ʱ�߽�û�Ӵ���
	for (int i = (5 - 1) / 2; i <= 319 - (5 - 1) / 2; i++)
	{
		dst[i] = src[i - 2] * kernel[0] + src[i - 1] * kernel[1] + src[i] * kernel[2] + src[i + 1] * kernel[3] + src[i + 2] * kernel[4];
	}
}




//��˹�˲�
void Wave3::init(FILE *fp)
{
	//��ȡ
	int data[320];
	int m = 0;
	double temp[320], temp1[320];

	while (fscanf_s(fp, "%d", &data[m]) != EOF)
		m++;
	fclose(fp);
	for (m = 0; m < 320; m++)
	{
		temp[m] = (double)data[m];
	}
	memcpy(temp1, temp, sizeof(temp));


	//�˲�
	gaussian(temp, temp1);


	//���
	ofstream outfile;
	char add[100] = "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt";
	sprintf(add, "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt", "wave3");


	outfile.open(add, ios::out);
	for (int i = 0; i < 320; i++)
	{
		outfile << temp1[i] << " ";
	}
	outfile.close();

}



