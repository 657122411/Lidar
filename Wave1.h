#pragma once

#include "iostream"
#include "fstream"
class Wave1
{
public:
	Wave1();
	~Wave1();

	int data[320];

	void init(FILE *fp);
	
};