#include <stdio.h>?
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "levmar.h"

#include <iostream>
#include <fstream>
using namespace std;

#include "mLM.h"

#ifdef _cplusplus
extern "C" {
#include "f2c.h"
#include "clapack.h"
}
#endif

//假设函数模型
void expfun(double *p, double *x, int m, int n, void *data)
{
	register int i;
	for (i = 0; i<n; ++i)
	{
		//写出参数与x[i]之间的关系式，由于这里方程的右边没有观测值，所以只有参数
		x[i] = p[0] * exp(-(i - p[1])*(i - p[1]) / (2 * p[2])*(2 * p[2])) + p[3] * exp(-(i - p[4])*(i - p[4]) / (2 * p[5])*(2 * p[5]));
	}

}

//函数模型的雅可比矩阵
void jacexpfun(double *p, double *jac, int m, int n, void *data)
{
	register int i, j;
	//写出雅克比矩阵
	for (i = j = 0; i<n; ++i)
	{
		jac[j++] = exp(-(i - p[1])*(i - p[1]) / (2 * p[2])*p[2]);
		jac[j++] = p[0] * (i - p[1]) / (p[2] * p[2])*exp(-(i - p[1])*(i - p[1]) / (2 * p[2] * p[2]));
		jac[j++] = p[0] * (i - p[1])*(i - p[1]) / (p[2] * p[2] * p[2])*exp(-(i - p[1])*(i - p[1]) / (2 * p[2] * p[2]));

		jac[j++] = exp(-(i - p[4])*(i - p[4]) / (2 * p[5])*p[5]);
		jac[j++] = p[3] * (i - p[4]) / (p[5] * p[5])*exp(-(i - p[4])*(i - p[4]) / (2 * p[5] * p[5]));
		jac[j++] = p[3] * (i - p[4])*(i - p[4]) / (p[5] * p[5] * p[5])*exp(-(i - p[4])*(i - p[4]) / (2 * p[5] * p[5]));
	}
}

/*
基于LM算法的参数优化
in:待拟合的原数据，预估的参数值
out:优化后的参数值
*/
void mLM::run(FILE *fdata,FILE *fparam)
{
	const int m = 6,n = 320;//m表示待求参数的维度，n表示测量值的维度
	double p[m],x[n];//待求参数的初值和数据
	 
	
	double data;
	int num = 0;

	while (!feof(fparam))//解算的高斯分量大于两个则不优化
	{
		fscanf(fparam, "%lf", &data);
		num++;
	}
	if (num >7)
	{
		cout << "无优化过程！" << endl;
		cout << endl;
		return;
	}


	fseek(fparam, 0L, 0);//文件指针回到头

	//输入预估参数
	int j = 0;
	while (fscanf_s(fparam, "%lf", &p[j]) != EOF)
	{
		j++;
	}
		
	fclose(fparam);

	//输入拟合数据
	int i = 0;
	while (fscanf_s(fdata, "%lf", &x[i]) != EOF)
		i++;
	fclose(fdata);

	

	

	double info[LM_INFO_SZ];
	// 调用迭代入口函数
	int ret = dlevmar_der(expfun,      //描述测量值之间关系的函数指针
		jacexpfun,   //估计雅克比矩阵的函数指针
		p,          //初始化的待求参数，结果一并保存在其中
		x,          //测量值
		m,          //参数维度
		n,          //测量值维度
		1000,       //最大迭代次数
		NULL,//opts,       //迭代的一些参数
		info,       //关于最小化结果的一些参数，不需要设为NULL
		NULL, NULL, NULL //一些内存的指针，暂时不需要
		); 
	printf("Levenberg-Marquardt returned in %g iter, reason %g, sumsq %g [%g]\n", info[5], info[6], info[1], info[0]);
	printf("Bestfit parameters: A:%.7g b:%.7g sigma:%.7g A:%.7g b:%.7g sigma:%.7g\n", p[0], p[1], p[2], p[3], p[4], p[5]);
	
	cout << "完成参数优化!" << endl;
	cout << endl;

	printf("波峰时间差: %.7g ns\n", abs(p[4]-p[1]));

	//输出优化后高斯分量参数
	ofstream outfile;
	char add[100] = "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt";
	sprintf(add, "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt", "NewParameter");
	outfile.open(add, ios::out);
	
	for (int k = 0; k < 6; k++)
	{
		outfile << p[k] << " ";
	}

	outfile.close();



}