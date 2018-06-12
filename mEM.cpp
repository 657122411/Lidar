#include "mEM.h"
#include <iostream>
using namespace std;


#define PI 3.1415926

/**
* 一維情況下的EM算法實現
* @author aturbo
*1、求期望（e-step)
*2、期望最大化（估值）（M-step)
*3、循環以上兩部直到收斂
*/





/**
* 高斯分布计算公式，也就是先验概率
* @param point
* @param mean
* @param variance
* @return
*/
double gaussianPro(double point, double mean, double variance) {
	double prob = 0.0;
	prob = (1 / (sqrt(2 * PI)*sqrt(variance)))*exp(-(point - mean)*(point - mean) / (2 * variance));
	return prob;
}






/**
* E-step的主要逻辑
* @param means
* @param variances
* @param points
* @param probs
* @return
*/
void mEM::eStep() {
	const int clusterNum = 2;// means.length;
	const int pointNum = 320;// points.length;
	double postProbs[clusterNum][pointNum];
	double denominator[pointNum];
	for (int m = 0; m <pointNum; m++) {
		denominator[m] = 0.0;
		for (int n = 0; n<clusterNum; n++) {
			denominator[m] += (gaussianPro(m_points[m], m_means[n], m_variances[n])*m_probs[n]);
		}
	}
	for (int i = 0; i<clusterNum; i++) {
		for (int j = 0; j<pointNum; j++) {
			if (denominator[j] > 0)
				postProbs[i][j] = (gaussianPro(m_points[j], m_means[i], m_variances[i])*m_probs[i]) / (denominator[j]);
			else
				postProbs[i][j] = 0;
		}
	}
	
	memcpy(m_w, postProbs, sizeof(postProbs));
}






/**
* M-step的主要逻辑之一：由E-step得到的期望，重新计算均值
* @param w
* @param points
* @return
*/
void mEM::guessMean(double w[2][320], double points[]) {

	const int wLength = 2;//w.length;
	double means[wLength];
	double wi[wLength];
	for (int m = 0; m < wLength; m++) {
		wi[m] = 0.0;
		for (int n = 0; n<320/*points.length*/; n++) {
			wi[m] += m_w[m][n];
		}
	}
	for (int i = 0; i<2/*w.length*/; i++) {
		means[i] = 0.0;
		for (int j = 0; j<320/*points.length*/; j++) {
			means[i] += (m_w[i][j] * m_points[j]);
		}
		means[i] /= wi[i];
	}
	memcpy(m_means, means, sizeof(means));
}
/**
* M-step的主要逻辑之一：由E-step得到的期望，重新计算方差
* @param w
* @param points
* @return
*/
void mEM::guessVariance(double w[2][320], double points[]) {
	const int wLength = 2;//w.length;
	double means[wLength];
	double variances[wLength];
	double wi[wLength];
	for (int m = 0; m < wLength; m++) {
		wi[m] = 0.0;
		for (int n = 0; n<320/*points.length*/; n++) {
			wi[m] += m_w[m][n];
		}
	}
	guessMean(m_w, m_points);
	for (int i = 0; i<wLength; i++) {
		variances[i] = 0.0;
		for (int j = 0; j<320/*points.length*/; j++) {
			variances[i] += (m_w[i][j] * (m_points[j] - m_means[i])*(m_points[j] - m_means[i]));
		}
		variances[i] /= wi[i];
	}

	memcpy(m_variances, variances, sizeof(variances));
}
/**
* M-step的主要逻辑之一：由E-step得到的期望，重新计算概率
* @param w
* @return
*/
void mEM::guessProb(double w[2][320]) {
	const int wLength = 2/*w.length*/;
	double probs[wLength];
	for (int i = 0; i<wLength; i++) {
		probs[i] = 0.0;
		for (int j = 0; j<320/*w[i].length*/; j++) {
			probs[i] += m_w[i][j];
		}
		probs[i] /= 320/*w[i].length*/;
	}
	memcpy(m_probs, probs, sizeof(probs));
}

void mEM::mStep() {
	mEM::guessMean(m_w, m_points);
	mEM::guessVariance(m_w, m_points);
	mEM::guessProb(m_w);
}





/**
* 计算前后两次迭代的参数的差值
* @param bef_values
* @param values
* @return
*/
double threshold(double bef_values[], double values[]) {
	double diff = 0.0;
	for (int i = 0; i < 2/*values.length*/; i++) {
		diff += (values[i] - bef_values[i]);
	}
	return fabs(diff);
}






void mEM::run(){

	FILE *f1, *f2;
	f1 = fopen("C:\\Users\\CUGtjh\\Desktop\\out\\Gauss.txt", "rb");
	f2 = fopen("C:\\Users\\CUGtjh\\Desktop\\out\\Parameter.txt", "rb");

	double points[320];
	//输入拟合数据
	int i = 0;
	while (fscanf_s(f1, "%lf", &points[i]) != EOF)
		i++;
	fclose(f1);
	
	



	//输入预估参数
	double p[6];
	int j = 0;
	while (fscanf_s(f2, "%lf", &p[j]) != EOF)
		j++;
	fclose(f2);




	double m_points[320];
	double temp[320];
	for (int i = 0; i < 320; i++)
	{
		temp[i] = p[0] * exp(-(i - p[1])*(i - p[1]) / (2 * p[2] * p[2]));
	}
	double temp1[320];
	for (int i = 0; i < 320; i++)
	{
		temp1[i] = points[i] - temp[i];
	}
	for (int i = 0; i < 320; i++)
	{
		if (temp[i] >= temp1[i])
			m_points[i] = temp[i];
		else
			m_points[i] = temp1[i];
	}

	for (int i = 0; i < 320; i++)
	{
		cout << points[i] << endl;
	}

	
	
	
	double means[] = { p[1],p[4] };//均值
	memcpy(m_means, means, sizeof(means));

	double variances[] = { p[2],p[5] };//方差
	memcpy(m_variances, variances, sizeof(variances));

	double probs[] = { p[0]/(p[0]+p[3]),p[3]/ (p[0] + p[3]) };//每个类的概率；这里默认选择k=2了；
	memcpy(m_probs, probs, sizeof(probs));

	double w[2][11] = { 0 };
	memcpy(m_w, w, sizeof(w));
	
	
	
	

	double bef_means[2];
	double bef_var[2];
	do {
		/*bef_means = means;
		bef_var = variances;*/
		memcpy(bef_means, m_means, sizeof(m_means));
		memcpy(bef_var, m_variances, sizeof(m_variances));
		eStep();
		mStep();
	} while (threshold(bef_means, m_means)<0.01);
	for (int i = 0; i < 2; i++)
	{
		cout << m_means[i] << " " << m_variances[i] << " " << m_probs[i]<<endl;
	}
	
}
