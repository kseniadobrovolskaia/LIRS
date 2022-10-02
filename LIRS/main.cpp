#include "LIRS.h"



int main()
{
	int len_cache, count_nums;
	std::cin >> len_cache >> count_nums;

	struct Cash *LIRS = create_Cash(len_cache);

	int elem, hits = 0;

	for (int num = 0; num < count_nums; num++)
	{
		std::cin >> elem;
		LIRS = append_elem(LIRS, elem, &hits);
	}
	
	destroy_cash(LIRS);

	printf("For %d elems (size of cache %d) - %d hits\n", count_nums, len_cache, hits);

	return 0;
}
