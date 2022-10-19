#include <fstream>
#include "LIRS.hpp"
#include "Perfect_Cash.hpp"


int hits_for_perf(int len_cache, int count_nums, int *numbers);
int hits_for_lirs(int len_cache, int count_nums, int *numbers);
void print_in_files(int *answers_lirs, int *answers_perf);



int hits_for_perf(int len_cache, int count_nums, int *numbers)
{
	int hits = 0;
	Perfect_Cash::Cash Cache(len_cache);

	for (int i = 1; i < count_nums + 1; i++)
	{
		Cache.add_in_table(i, numbers[i]);
	}

	for (int i = 1; i < count_nums + 1; i++)
	{
		Cache.append_elem(i, &hits, numbers);
	}

	return hits;
}


int hits_for_lirs(int len_cache, int count_nums, int *numbers)
{
	int hits = 0;
	LIRS::Cash LIRS(len_cache);

	for (int num = 0; num < count_nums; num++)
	{
		LIRS.append_elem(numbers[num + 1], &hits);
	}

	return hits;
}


void print_in_files(int *answers_lirs, int *answers_perf)
{
	std::ofstream results_lirs;
	std::ofstream results_perf;

	results_lirs.open("results_lirs.txt");
	results_perf.open("results_perf.txt");

	for (int num_test = 0; num_test < 5; num_test++)
	{
		results_lirs << answers_lirs[num_test] << " ";
		results_perf << answers_perf[num_test] << " ";
	}
	
	results_lirs.close();
	results_perf.close();
}
