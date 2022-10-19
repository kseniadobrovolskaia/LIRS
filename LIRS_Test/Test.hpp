#pragma once

#include <gtest/gtest.h>
#include <iostream>
#include <stdio.h>
#include <fstream>


enum name
{
	answers_lirs,
	answers_perf,
	results_lirs,
	results_perf,
	
};


std::ifstream fans_l("../answers_lirs.txt");
std::ifstream fans_p("../answers_perf.txt");
std::ifstream fres_l("../results_lirs.txt");
std::ifstream fres_p("../results_perf.txt");


int read_file(int file, int elem)
{
	static int elems[20];
	static int flag = 0;

	if (flag == 0)
	{
		flag++;
		for (int i = 0; i < 5; i++)
		{
			fans_l >> elems[0*5 + i];
		}
		fans_l.close();

		for (int i = 0; i < 5; i++)
		{
			fans_p >> elems[1*5 + i];
		}
		fans_p.close();

		for (int i = 0; i < 5; i++)
		{
			fres_l >> elems[2*5 + i];
		}
		fres_l.close();

		for (int i = 0; i < 5; i++)
		{
			fres_p >> elems[3*5 + i];
		}
		fres_p.close();
	}

	return elems[file*5 + elem - 1];
}


