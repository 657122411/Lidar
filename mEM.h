#pragma once

#include "stdio.h"
#include "string.h"
#include "math.h"


class mEM
{
public:
	void run();
	
	void mEM::eStep();
	void mEM::guessMean(double w[2][320], double points[]);
	void mEM::guessVariance(double w[2][320], double points[]);
	void mEM::guessProb(double w[2][320]);

	void mEM::mStep();

	double m_points[10];//ԭ����
	double m_w[2][320];
	double m_means[2];//��ֵ
	double m_variances[2];//����
	double m_probs[];//ÿ����ĸ��ʣ�����Ĭ��ѡ��k=2�ˣ�
};



