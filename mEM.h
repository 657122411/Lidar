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

	double m_points[10];//原数据
	double m_w[2][320];
	double m_means[2];//均值
	double m_variances[2];//方差
	double m_probs[];//每个类的概率；这里默认选择k=2了；
};



