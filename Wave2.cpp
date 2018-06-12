#include "Wave2.h"
#include <cstring>
#include <iostream>
#include <cassert>
#include <stack>
#include <math.h>
using namespace std;

Wave2::Wave2()
{
}

Wave2::~Wave2()
{
}

//SG滤波
void Wave2::init(FILE *fp)
{
	//读取
	int data[320];
	int m = 0;
	double temp[320], temp1[320], temp2[320],temp3[320];
	while (fscanf_s(fp, "%d", &data[m]) != EOF)
		m++;
	fclose(fp);
	for (m = 0; m < 320; m++)
	{
		temp[m] = (double)data[m];
	}

	//滤波
	linearSmooth5(temp,temp1,320);
	quadraticSmooth5(temp1, temp2, 320);
	cubicSmooth5(temp2, temp3, 320);
	
	//输出
	ofstream outfile;
	char add[100] = "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt";
	sprintf(add, "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt", "wave2");
	outfile.open(add, ios::out);
	for (int i = 0; i < 320; i++)
	{
		outfile << temp3[i] << " ";
	}
	outfile.close();

}


//三点线性平滑
void Wave2::linearSmooth3(double in[], double out[], int N)
{
	int i;
	if (N < 3)
	{
		for (i = 0; i <= N - 1; i++)
		{
			out[i] = in[i];
		}
	}
	else
	{
		out[0] = (5.0 * in[0] + 2.0 * in[1] - in[2]) / 6.0;

		for (i = 1; i <= N - 2; i++)
		{
			out[i] = (in[i - 1] + in[i] + in[i + 1]) / 3.0;
		}

		out[N - 1] = (5.0 * in[N - 1] + 2.0 * in[N - 2] - in[N - 3]) / 6.0;
	}
}

//五点线性平滑
void Wave2::linearSmooth5(double in[], double out[], int N)
{
	int i;
	if (N < 5)
	{
		for (i = 0; i <= N - 1; i++)
		{
			out[i] = in[i];
		}
	}
	else
	{
		out[0] = (3.0 * in[0] + 2.0 * in[1] + in[2] - in[4]) / 5.0;
		out[1] = (4.0 * in[0] + 3.0 * in[1] + 2 * in[2] + in[3]) / 10.0;
		for (i = 2; i <= N - 3; i++)
		{
			out[i] = (in[i - 2] + in[i - 1] + in[i] + in[i + 1] + in[i + 2]) / 5.0;
		}
		out[N - 2] = (4.0 * in[N - 1] + 3.0 * in[N - 2] + 2 * in[N - 3] + in[N - 4]) / 10.0;
		out[N - 1] = (3.0 * in[N - 1] + 2.0 * in[N - 2] + in[N - 3] - in[N - 5]) / 5.0;
	}
}

//七点线性平滑
void Wave2::linearSmooth7(double in[], double out[], int N)
{
	int i;
	if (N < 7)
	{
		for (i = 0; i <= N - 1; i++)
		{
			out[i] = in[i];
		}
	}
	else
	{
		out[0] = (13.0 * in[0] + 10.0 * in[1] + 7.0 * in[2] + 4.0 * in[3] +
			in[4] - 2.0 * in[5] - 5.0 * in[6]) / 28.0;

		out[1] = (5.0 * in[0] + 4.0 * in[1] + 3 * in[2] + 2 * in[3] +
			in[4] - in[6]) / 14.0;

		out[2] = (7.0 * in[0] + 6.0 * in[1] + 5.0 * in[2] + 4.0 * in[3] +
			3.0 * in[4] + 2.0 * in[5] + in[6]) / 28.0;

		for (i = 3; i <= N - 4; i++)
		{
			out[i] = (in[i - 3] + in[i - 2] + in[i - 1] + in[i] + in[i + 1] + in[i + 2] + in[i + 3]) / 7.0;
		}

		out[N - 3] = (7.0 * in[N - 1] + 6.0 * in[N - 2] + 5.0 * in[N - 3] +
			4.0 * in[N - 4] + 3.0 * in[N - 5] + 2.0 * in[N - 6] + in[N - 7]) / 28.0;

		out[N - 2] = (5.0 * in[N - 1] + 4.0 * in[N - 2] + 3.0 * in[N - 3] +
			2.0 * in[N - 4] + in[N - 5] - in[N - 7]) / 14.0;

		out[N - 1] = (13.0 * in[N - 1] + 10.0 * in[N - 2] + 7.0 * in[N - 3] +
			4 * in[N - 4] + in[N - 5] - 2 * in[N - 6] - 5 * in[N - 7]) / 28.0;
	}
}

//二次函数拟合平滑
void Wave2::quadraticSmooth5(double in[], double out[], int N)
{
	int i;
	if (N < 5)
	{
		for (i = 0; i <= N - 1; i++)
		{
			out[i] = in[i];
		}
	}
	else
	{
		out[0] = (31.0 * in[0] + 9.0 * in[1] - 3.0 * in[2] - 5.0 * in[3] + 3.0 * in[4]) / 35.0;
		out[1] = (9.0 * in[0] + 13.0 * in[1] + 12 * in[2] + 6.0 * in[3] - 5.0 *in[4]) / 35.0;
		for (i = 2; i <= N - 3; i++)
		{
			out[i] = (-3.0 * (in[i - 2] + in[i + 2]) +
				12.0 * (in[i - 1] + in[i + 1]) + 17 * in[i]) / 35.0;
		}
		out[N - 2] = (9.0 * in[N - 1] + 13.0 * in[N - 2] + 12.0 * in[N - 3] + 6.0 * in[N - 4] - 5.0 * in[N - 5]) / 35.0;
		out[N - 1] = (31.0 * in[N - 1] + 9.0 * in[N - 2] - 3.0 * in[N - 3] - 5.0 * in[N - 4] + 3.0 * in[N - 5]) / 35.0;
	}
}

//二次函数拟合平滑
void Wave2::quadraticSmooth7(double in[], double out[], int N)
{
	int i;
	if (N < 7)
	{
		for (i = 0; i <= N - 1; i++)
		{
			out[i] = in[i];
		}
	}
	else
	{
		out[0] = (32.0 * in[0] + 15.0 * in[1] + 3.0 * in[2] - 4.0 * in[3] -
			6.0 * in[4] - 3.0 * in[5] + 5.0 * in[6]) / 42.0;

		out[1] = (5.0 * in[0] + 4.0 * in[1] + 3.0 * in[2] + 2.0 * in[3] +
			in[4] - in[6]) / 14.0;

		out[2] = (1.0 * in[0] + 3.0 * in[1] + 4.0 * in[2] + 4.0 * in[3] +
			3.0 * in[4] + 1.0 * in[5] - 2.0 * in[6]) / 14.0;
		for (i = 3; i <= N - 4; i++)
		{
			out[i] = (-2.0 * (in[i - 3] + in[i + 3]) +
				3.0 * (in[i - 2] + in[i + 2]) +
				6.0 * (in[i - 1] + in[i + 1]) + 7.0 * in[i]) / 21.0;
		}
		out[N - 3] = (1.0 * in[N - 1] + 3.0 * in[N - 2] + 4.0 * in[N - 3] +
			4.0 * in[N - 4] + 3.0 * in[N - 5] + 1.0 * in[N - 6] - 2.0 * in[N - 7]) / 14.0;

		out[N - 2] = (5.0 * in[N - 1] + 4.0 * in[N - 2] + 3.0 * in[N - 3] +
			2.0 * in[N - 4] + in[N - 5] - in[N - 7]) / 14.0;

		out[N - 1] = (32.0 * in[N - 1] + 15.0 * in[N - 2] + 3.0 * in[N - 3] -
			4.0 * in[N - 4] - 6.0 * in[N - 5] - 3.0 * in[N - 6] + 5.0 * in[N - 7]) / 42.0;
	}
}


//五点三次平滑
void Wave2::cubicSmooth5(double in[], double out[], int N)
{

	int i;
	if (N < 5)
	{
		for (i = 0; i <= N - 1; i++)
			out[i] = in[i];
	}

	else
	{
		out[0] = (69.0 * in[0] + 4.0 * in[1] - 6.0 * in[2] + 4.0 * in[3] - in[4]) / 70.0;
		out[1] = (2.0 * in[0] + 27.0 * in[1] + 12.0 * in[2] - 8.0 * in[3] + 2.0 * in[4]) / 35.0;
		for (i = 2; i <= N - 3; i++)
		{
			out[i] = (-3.0 * (in[i - 2] + in[i + 2]) + 12.0 * (in[i - 1] + in[i + 1]) + 17.0 * in[i]) / 35.0;
		}
		out[N - 2] = (2.0 * in[N - 5] - 8.0 * in[N - 4] + 12.0 * in[N - 3] + 27.0 * in[N - 2] + 2.0 * in[N - 1]) / 35.0;
		out[N - 1] = (-in[N - 5] + 4.0 * in[N - 4] - 6.0 * in[N - 3] + 4.0 * in[N - 2] + 69.0 * in[N - 1]) / 70.0;
	}
	return;
}

//七点三次平滑
void Wave2::cubicSmooth7(double in[], double out[], int N)
{
	int i;
	if (N < 7)
	{
		for (i = 0; i <= N - 1; i++)
		{
			out[i] = in[i];
		}
	}
	else
	{
		out[0] = (39.0 * in[0] + 8.0 * in[1] - 4.0 * in[2] - 4.0 * in[3] +
			1.0 * in[4] + 4.0 * in[5] - 2.0 * in[6]) / 42.0;
		out[1] = (8.0 * in[0] + 19.0 * in[1] + 16.0 * in[2] + 6.0 * in[3] -
			4.0 * in[4] - 7.0* in[5] + 4.0 * in[6]) / 42.0;
		out[2] = (-4.0 * in[0] + 16.0 * in[1] + 19.0 * in[2] + 12.0 * in[3] +
			2.0 * in[4] - 4.0 * in[5] + 1.0 * in[6]) / 42.0;
		for (i = 3; i <= N - 4; i++)
		{
			out[i] = (-2.0 * (in[i - 3] + in[i + 3]) +
				3.0 * (in[i - 2] + in[i + 2]) +
				6.0 * (in[i - 1] + in[i + 1]) + 7.0 * in[i]) / 21.0;
		}
		out[N - 3] = (-4.0 * in[N - 1] + 16.0 * in[N - 2] + 19.0 * in[N - 3] +
			12.0 * in[N - 4] + 2.0 * in[N - 5] - 4.0 * in[N - 6] + 1.0 * in[N - 7]) / 42.0;
		out[N - 2] = (8.0 * in[N - 1] + 19.0 * in[N - 2] + 16.0 * in[N - 3] +
			6.0 * in[N - 4] - 4.0 * in[N - 5] - 7.0 * in[N - 6] + 4.0 * in[N - 7]) / 42.0;
		out[N - 1] = (39.0 * in[N - 1] + 8.0 * in[N - 2] - 4.0 * in[N - 3] -
			4.0 * in[N - 4] + 1.0 * in[N - 5] + 4.0 * in[N - 6] - 2.0 * in[N - 7]) / 42.0;
	}
}
