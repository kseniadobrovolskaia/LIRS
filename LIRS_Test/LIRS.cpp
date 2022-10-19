#include "LIRS.hpp"



int main()
{
	int len_cache, count_nums;
	std::cin >> len_cache >> count_nums;

	LIRS::Cash LIRS(len_cache);

	int elem, hits = 0;

	for (int num = 0; num < count_nums; num++)
	{
		std::cin >> elem;
		LIRS.append_elem(elem, &hits);
	}

	std::cout << "For " << count_nums << " elems (size of cache " << len_cache << ") - " << hits << " hits" << std::endl;

	return 0;
}
