#include "GaussWave.h"
#include <cstring>
#include <iostream>
#include <cassert>
#include <stack>
#include <math.h>
#include <vector>
using namespace std;


/*
��˹�ֽ����Ԥ��
in:�˲���Ĳ�������
out:ȥ���ĵĲ������ݺ͸�˹������δ֪����
*/
GaussWave::GaussWave()
{
}

GaussWave::~GaussWave()
{
}

//��˹��������
struct WaveForm
{
	double Ai;//���
	int bi;//�������
	double sigmai;//������
};

//��˹��������Ԥ��
void GaussWave::init(FILE *fp)
{
	//��ȡ����
	double data[320];
	int m = 0;
	double temp[320];
	while (fscanf_s(fp, "%lf", &data[m]) != EOF)
		m++;
	fclose(fp);

	double min = data[0];//������Сֵ
	for (m = 0; m < 320; m++)
	{
		temp[m] = data[m];
		if (data[m] < min)	min = data[m];
	}

	//ȥ��
	for (m = 0; m < 320; m++)
	{
		temp[m] -= min;
	}

	//���
	ofstream outfile;
	char add[100] = "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt";
	sprintf(add, "C:\\Users\\CUGtjh\\Desktop\\out\\%s.txt", "Gauss");
	outfile.open(add, ios::out);
	for (int i = 0; i < 320; i++)
	{
		outfile << temp[i] << " ";
	}
	outfile.close();

	//��˹����
	double A;//���
	int b,tg,tgl,tgr;//������룬��ֵʱ��λ�ã����ʱ��λ�ã����ң�
	vector<WaveForm> mywave;
	int len = 0;
	

	do
	{
		A = 0;
		//�����ֵ����¼λ��
		for (m = 0; m < 320; m++)
		{
			if (temp[m] > A)
			{
				A = temp[m];
				b = m;
			}
		}

		//Ѱ�Ұ��λ��
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
			

		//����sigma
		double sigma = fabs(tg - b) / sqrt(2 * log(2));
		len++;
		WaveForm wf{ A,b,sigma };
		mywave.push_back(wf);

	

		//����
		for (m = 0; m < 320; m++)
		{
			if (temp[m] > A*exp(-(m - b)*(m - b) / (2 * sigma*sigma)))
			{
				temp[m] -= A*exp(-(m - b)*(m - b) / (2 * sigma*sigma));
			}
			else
				temp[m] = 0;
		}
	
		//�ж��Ƿ��������
		A = 0;
		for (m = 0; m < 320; m++)
		{
			if (temp[m] > A)
			{
				A = temp[m];
			}
		}
	} while(A>50);//ѭ������
	

	//�����˹��������
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