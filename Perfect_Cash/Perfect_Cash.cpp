#include "Perfect_Cash.h"


int main()
{
	int n, hits;
	std::ifstream data("data.txt");
	struct Cash *LIRS;

	for (int k = 0; k < 5; k++)
	{
		LIRS = new struct Cash;
		hits = 0;
		data >> n;

		int *numbers = new int[n];
		numbers[0] = n;
	
		for (int i = 1; i < n + 1; i++)
		{
    		data >> numbers[i];
		}

		for (int i = 1; i < n + 1; i++)
		{
			LIRS = append_elem(LIRS, i, &hits, numbers);
		}

		destroy_cache(LIRS);
		printf("For %d elems - %d hits\n", n, hits);
	}

	return 0;
}


struct Cash *append_elem(struct Cash *LIRS, int place, int *hits, int *numbers)
{
	int elem;
	elem = numbers[place];

	if ((LIRS->table).count({1, elem}) == 0)
	{
		LIRS = displace_from_cache(LIRS, place, numbers);
		LIRS = add_in_cache(LIRS, elem);
		return LIRS;
	}

	if (find_in_cache(LIRS, elem))
	{
		(*hits)++;
	}
	else
	{
		LIRS = add_in_cache(LIRS, elem);
		LIRS = displace_from_cache(LIRS, place, numbers);
		
	}

	return LIRS;

}

struct Cash *add_in_cache(struct Cash *LIRS, int elem)
{
	(LIRS->cache).push_front(elem);
	(LIRS->table).insert({1, elem});

	return LIRS;

}




int find_in_cache(struct Cash *LIRS, int elem)
{
	int is_in_table;
	is_in_table = (LIRS->table).count({1, elem}); 
	//is_in_table = (LIRS->table).contains({1, elem}); // -std=c++20

	if (!is_in_table)
	{
		return 0;
	}

	return ((LIRS->table).find({0, elem}))->be_in_cache;

}


struct Cash *displace_from_cache(struct Cash *LIRS, int place, int *numbers)
{
	int worst;

	if ((LIRS->cache).size() < MAX_SIZE_CACHE)
	{
		return LIRS;
	}

	worst = find_worst(LIRS, place, numbers);

	auto begin = (LIRS->cache).begin();
	
	while ((*begin) != worst)
	{
		begin++;
	}

	(LIRS->cache).erase(begin);
	(LIRS->table).erase({1, worst});
	(LIRS->table).insert({0, worst});

	return LIRS;

}

int find_worst(struct Cash *LIRS, int place, int *numbers)
{
	int worst, intervalmax, interval, size, i, curr;

	size = numbers[0];

	intervalmax = 0;
	interval = 0;

	for (auto elem: LIRS->cache)
	{
		i = place;
		curr = numbers[i];
		while (curr != elem && i < size + 1)
		{
			i++;
		}
		interval = i;
		if (i == (size + 1))
		{
			interval++;
		}

		if (interval > intervalmax)
		{
			intervalmax = interval;
			worst = elem;
		}

		interval = 0;
	}

	return worst;

}


void *destroy_cache(struct Cash *LIRS)
{
	LIRS->table.clear();;
	LIRS->cache.clear();
	free(LIRS);

	return NULL;

}


void print_cache(struct Cash *LIRS)
{
	std::cout << "Cache: ";

	for (auto elem: LIRS->cache)
	{
		std::cout << elem << " " ;
	}

	std::cout << std::endl;

}
