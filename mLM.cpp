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

//���躯��ģ��
void expfun(double *p, double *x, int m, int n, void *data)
{
	register int i;
	for (i = 0; i<n; ++i)
	{
		//д��������x[i]֮��Ĺ�ϵʽ���������﷽�̵��ұ�û�й۲�ֵ������ֻ�в���
		x[i] = p[0] * exp(-(i - p[1])*(i - p[1]) / (2 * p[2])*(2 * p[2])) + p[3] * exp(-(i - p[4])*(i - p[4]) / (2 * p[5])*(2 * p[5]));
	}

}

//����ģ�͵��ſɱȾ���
void jacexpfun(double *p, double *jac, int m, int n, void *data)
{
	register int i, j;
	//д���ſ˱Ⱦ���
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
����LM�㷨�Ĳ����Ż�
in:����ϵ�ԭ���ݣ�Ԥ���Ĳ���ֵ
out:�Ż���Ĳ���ֵ
*/
void mLM::run(FILE *fdata,FILE *fparam)
{
	const int m = 6,n = 320;//m��ʾ���������ά�ȣ�n��ʾ����ֵ��ά��
	double p[m],x[n];//��������ĳ�ֵ������
	 
	
	double data;
	int num = 0;

	while (!feof(fparam))//����ĸ�˹���������������Ż�
	{
		fscanf(fparam, "%lf", &data);
		num++;
	}
	if (num >7)
	{
		cout << "���Ż����̣�" << endl;
		cout << endl;
		return;
	}


	fseek(fparam, 0L, 0);//�ļ�ָ��ص�ͷ

	//����Ԥ������
	int j = 0;
	while (fscanf_s(fparam, "%lf", &p[j]) != EOF)
	{
		j++;
	}
		
	fclose(fparam);

	//�����������
	int i = 0;
	while (fscanf_s(fdata, "%lf", &x[i]) != EOF)
		i++;
	fclose(fdata);

	

	

	double info[LM_INFO_SZ];
	// ���õ�����ں���
	int ret = dlevmar_der(expfun,      //��������ֵ֮���ϵ�ĺ���ָ��
		jacexpfun,   //�����ſ˱Ⱦ���ĺ���ָ��
		p,          //��ʼ���Ĵ�����������һ������������
		x,          //����ֵ
		m,          //����ά��
		n,          //����ֵά��
		1000,       //����������
		NULL,//opts,       //������һЩ����
		info,       //������С�������һЩ����������Ҫ��ΪNULL
		NULL, NULL, NULL //һЩ�ڴ��ָ�룬��ʱ����Ҫ
		); 
	printf("Levenberg-Marquardt returned in %g iter, reason %g, sumsq %g [%g]\n", info[5], info[6], info[1], info[0]);
	printf("Bestfit parameters: A:%.7g b:%.7g sigma:%.7g A:%.7g b:%.7g sigma:%.7g\n", p[0], p[1], p[2], p[3], p[4], p[5]);
	
	cout << "��ɲ����Ż�!" << endl;
	cout << endl;

	printf("����ʱ���: %.7g ns\n", abs(p[4]-p[1]));

	//����Ż����˹��������
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