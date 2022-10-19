#include "LIRS_Test.hpp"




int main()
{
	std::ifstream data;

	int answers_lirs[5] = {0};
	int answers_perf[5] = {0};
	int len_cache, count_nums;

	data.open("data.txt");
	
	for (int num_test = 0; num_test < 5; num_test++)
	{
		data >> len_cache >> count_nums;

		int *numbers = new int[count_nums + 10];
		numbers[0] = count_nums;

		for (int i = 1; i < count_nums + 1; i++)
		{
			data >> numbers[i];
		}

		answers_perf[num_test] = hits_for_perf(len_cache, count_nums, numbers);

		answers_lirs[num_test] = hits_for_lirs(len_cache, count_nums, numbers);

		std::cout << "For " << count_nums << " elems (size of cache " << len_cache << "):" << std::endl;
		std::cout << "Perfect_Cash: " << answers_perf[num_test] << std::endl;
		std::cout << "LIRS: " << answers_lirs[num_test] << std::endl;
	}

	data.close();
	
	print_in_files(answers_lirs, answers_perf);

	return 0;
}

