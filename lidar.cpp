// lidar.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "iostream"
#include "HS_Lidar.h"

#include "Wave.h"
#include "Wave1.h"
#include "Wave2.h"
#include "Wave3.h"

#include "GaussWave.h"

#include "mLM.h"

#include <cstring>
#include <direct.h>

using namespace std;

extern uint16_t week;
extern double second;
extern uint16_t week1;
extern double second1;

HS_Lidar hs;


//��������
void progress()
{
	//������ʱ�洢�ļ���
	string	dirName = "C:\\Users\\CUGtjh\\Desktop\\out";
	_mkdir(dirName.c_str());

	cout << "-----------------------------------" << endl;
	cout << "ʱ�䣺" <<hs.header.dGPSSecond <<"s"<<hs.header.nGPSBreakdownTime<< endl;

	//��ȡͨ��ԭʼ����
	ofstream outfile;
	char add[100] = "C:\\Users\\CUGtjh\\Desktop\\out\\%d.txt";
	sprintf(add, "C:\\Users\\CUGtjh\\Desktop\\out\\%d.txt", hs.CH2.nChannelNo);
	outfile.open(add, ios::out);
	for (int i = 0; i < 320; i++)
	{
		outfile << hs.CH2.nD0[i] << " ";
	}
	outfile.close();


	FILE * mf1;

	//�˲�
	mf1 = fopen("C:\\Users\\CUGtjh\\Desktop\\out\\3855.txt", "rb");
	Wave3 wa;
	wa.init(mf1);
	cout << "����˲�!" << endl;
	fclose(mf1);
	cout << endl;


	//����Ԥ��	
	mf1 = fopen("C:\\Users\\CUGtjh\\Desktop\\out\\Wave3.txt", "rb");
	GaussWave ga;
	ga.init(mf1);
	cout << "��ɲ���Ԥ��!" << endl;
	fclose(mf1);
	cout << endl;


	//LM�����Ż�
	FILE *f1, *f2;
	f1 = fopen("C:\\Users\\CUGtjh\\Desktop\\out\\Gauss.txt", "rb");
	f2 = fopen("C:\\Users\\CUGtjh\\Desktop\\out\\Parameter.txt", "rb");
	mLM mlm;
	mlm.run(f1, f2);
	fclose(f1);
	fclose(f2);

	_rmdir(dirName.c_str());

}


int main()  
{
	FILE * mf;
	mf = fopen("C:\\Users\\CUGtjh\\Desktop\\data.bin","rb");
	if (mf == NULL)
	{
		printf("��ȡ�ļ�����");
		return 0;
	}

	cout << "������ʼGPS�ܣ�" << endl;
	cin >> week;
	cout << "������ʼGPS�룺" << endl;
	cin >> second;
	cout << "������ֹGPS�ܣ�" << endl;
	cin >> week1;
	cout << "������ֹGPS�룺" << endl;
	cin >> second1;
	cout << endl;

	
	//�����ļ���ȡ����
	uint32_t j = 0;
	while (!feof(mf))
	{
		fseek(mf, j * 2688, SEEK_SET);
		hs.initData(mf);

		//�ж�����Χ
		if ((hs.header.nGPSWeek >= week) && (hs.header.dGPSSecond >= second) && (hs.header.nGPSWeek <= week1) && (hs.header.dGPSSecond <= second1))
		{
			progress();
		}
		
		j++;
	}

	fclose(mf);
	system("pause");
	exit(0);
}




