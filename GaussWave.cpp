#include "GaussWave.h"
#include <cstring>
#include <iostream>
#include <cassert>
#include <stack>
#include <math.h>
#include <vector>
using namespace std;


/*
高斯分解参数预估
in:滤波后的波形数据
out:去噪后的的波形数据和高斯函数三未知参数
*/
GaussWave::GaussWave()
{
}

GaussWave::~GaussWave()
{
}

//高斯分量参数
struct WaveForm
{
	double Ai;//振幅
	int bi;//脉冲距离
	double sigmai;//脉冲宽度
};

//高斯分量参数预估
void GaussWave::init(FILE *fp)
{
	//读取数据
	double data[320];
	int m = 0;
	double temp[320];
	while (fscanf_s(fp, "%lf", &data[m]) != EOF)
		m++;
	fclose(fp);

	double min = data[0];//噪声最小值
	for (m = 0; m < 320; m++)
	{
		temp[m] = data[m];
		if (data[m] < min)	min = data[m];
	}

	//去噪
	for (m = 0; m < 320; m++)
	{
		temp[m] -= min;
	}

	//输出
	ofstream outfile;
	char add[100] = "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt";
	sprintf(add, "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt", "Gauss");
	outfile.open(add, ios::out);
	for (int i = 0; i < 320; i++)
	{
		outfile << temp[i] << " ";
	}
	outfile.close();

	//高斯分量
	double A;//振幅
	int b,tg,tgl,tgr;//脉冲距离，峰值时间位置，半峰时间位置（左右）
	vector<WaveForm> mywave;
	int len = 0;
	

	do
	{
		A = 0;
		//找最大值并记录位置
		for (m = 0; m < 320; m++)
		{
			if (temp[m] > A)
			{
				A = temp[m];
				b = m;
			}
		}

		//寻找半宽位置
		for (m = b; m < 319; m++)
		{
			if ((temp[m - 1] > A / 2) && (temp[m + 1] < A / 2))
			{
				tgr = m;
				break;
			}
		}
		for (m = b; m > 0; m--)
		{
			if ((temp[m - 1] < A / 2) && (temp[m + 1] > A / 2))
			{
				tgl = m;
				break;
			}
		}
		if ((b - tgl) > (tgr - b))
		{
			tg = tgr;
		}			
		else
		{
			tg = tgl;
		}
			

		//计算sigma
		double sigma = fabs(tg - b) / sqrt(2 * log(2));
		len++;
		WaveForm wf{ A,b,sigma };
		mywave.push_back(wf);

	

		//剥离
		for (m = 0; m < 320; m++)
		{
			if (temp[m] > A*exp(-(m - b)*(m - b) / (2 * sigma*sigma)))
			{
				temp[m] -= A*exp(-(m - b)*(m - b) / (2 * sigma*sigma));
			}
			else
				temp[m] = 0;
		}
	
		//判断是否继续剥离
		A = 0;
		for (m = 0; m < 320; m++)
		{
			if (temp[m] > A)
			{
				A = temp[m];
			}
		}
	} while(A>50);//循环条件
	

	//输出高斯分量参数
	ofstream outfile1;
	char add1[100] = "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt";
	sprintf(add1, "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt", "Parameter");
	outfile1.open(add1, ios::out);
	
	for (vector<WaveForm>::iterator i = mywave.begin(); i != mywave.end(); i++)
	{
		outfile1 <<i->Ai<<" "<<i->bi<<" "<<i->sigmai<<" ";
		cout<< "A:"<<i->Ai << " " << "b:"<<i->bi << " " <<"sigma:" <<i->sigmai << endl;
	}
	outfile1.close();
	
	

}