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

/*功能：  高斯核生成
//kernel：存储生成的高斯核
//size：  核的大小
//sigma： 正态分布标准差
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


/*功能： 高斯模糊
//src：  输入原图
//dst：  模糊图像
//size： 核的大小
//sigma：正态分布标准差
*/
void gaussian(double src[], double dst[])
{
	double kernel[5];
	gau_kernel(kernel, 5, 1);
	//gaussian卷积,此时边界没加处理
	for (int i = (5 - 1) / 2; i <= 319 - (5 - 1) / 2; i++)
	{
		dst[i] = src[i - 2] * kernel[0] + src[i - 1] * kernel[1] + src[i] * kernel[2] + src[i + 1] * kernel[3] + src[i + 2] * kernel[4];
	}
}




//高斯滤波
void Wave3::init(FILE *fp)
{
	//读取
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


	//滤波
	gaussian(temp, temp1);


	//输出
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



