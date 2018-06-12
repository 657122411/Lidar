#pragma once

#include "iostream"
#include "fstream"
class Wave2
{
public:
	Wave2();
	~Wave2();

	int data[320];

	void init(FILE *fp);

	void linearSmooth3(double in[], double out[], int N);
	void linearSmooth5(double in[], double out[], int N);
	void linearSmooth7(double in[], double out[], int N);

	void quadraticSmooth5(double in[], double out[], int N);
	void quadraticSmooth7(double in[], double out[], int N);

	void cubicSmooth5(double in[], double out[], int N);
	void cubicSmooth7(double in[], double out[], int N);
};