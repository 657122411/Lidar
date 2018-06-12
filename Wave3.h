#pragma once

#include "iostream"
#include "fstream"
class Wave3
{
public:
	Wave3();
	~Wave3();

	int data[320];

	void init(FILE *fp);

};