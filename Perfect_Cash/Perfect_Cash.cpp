#include "Perfect_Cash.hpp"




int main()
{
	int hits = 0;
	int len_cache, n;
	std::cin >> len_cache;
	std::cin >> n;

	Perfect_Cash::Cash Cache(len_cache);

	int *numbers = new int[n + 10];
	numbers[0] = n;

	for (int i = 1; i < n + 1; i++)
	{
		std::cin >> numbers[i];
		Cache.add_in_table(i, numbers[i]);
	}
	
	for (int i = 1; i < n + 1; i++)
	{
		Cache.append_elem(i, &hits, numbers);
	}

	std::cout << "For " << n << " elems (size of cache " << len_cache << ") - " << hits << " hits" << std::endl;

	return 0;
}

