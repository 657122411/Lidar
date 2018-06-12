#pragma once

#include "iostream"
#include "fstream"
class GaussWave
{
public:
	GaussWave();
	~GaussWave();

	int data[320];

	void init(FILE *fp);

};