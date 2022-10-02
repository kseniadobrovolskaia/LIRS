#include "LIRS.h"


int get_num(FILE *data);


int main()
{
	FILE *data = fopen("012.dat", "r");
	if (!data)
	{
		perror("fopen");
		return 0;
	}
	
	int len_cache = get_num(data),
	count_nums = get_num(data);

	struct Cash *LIRS = create_Cash(len_cache);

	int hits = 0;

	for (int num = 0; num < count_nums; num++)
	{
		LIRS = append_elem(LIRS, get_num(data), &hits);
	}

	fclose(data);

	destroy_cash(LIRS);

	printf("For %d elems (size of cache %d) - %d hits\n", count_nums, len_cache, hits);

	return 0;
}


int get_num(FILE *data)
{
	int elem;

	if (!fscanf(data, "%d", &elem))
	{
		perror("fscanf");
		_Exit(1);
	}

	return elem;
}
