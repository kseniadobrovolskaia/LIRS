#include "Perfect_Cash.h"


int main()
{
	int n, hits, len_cache;
	std::ifstream data("data.txt");
	struct Cash *Cache;

	for (int k = 0; k < 5; k++)
	{
		Cache = new struct Cash;
		hits = 0;
		data >> len_cache;
		data >> n;

		Cache->max_size_cash = len_cache;

		int *numbers = new int[n + 1];
		numbers[0] = n;
	
		for (int i = 1; i < n + 1; i++)
		{
    		data >> numbers[i];
		}

		for (int i = 1; i < n + 1; i++)
		{
			Cache = append_elem(Cache, i, &hits, numbers);
		}

		destroy_cache(Cache);
		printf("For %d elems - %d hits\n", n, hits);
	}

	return 0;
}


struct Cash *append_elem(struct Cash *Cache, int place, int *hits, int *numbers)
{
	int elem;
	elem = numbers[place];

	if ((Cache->table).count({1, 1, elem}) == 0)
	{
		Cache = add_in_cache(Cache, elem, place);
		Cache = displace_from_cache(Cache, place, numbers);
		return Cache;
	}

	if (find_in_cache(Cache, elem))
	{
		(*hits)++;
		(Cache->table).erase({1, 1, elem});
		(Cache->table).insert({1, place, elem});
	}
	else
	{
		Cache = add_in_cache(Cache, elem, place);
		Cache = displace_from_cache(Cache, place, numbers);
		
	}

	return Cache;

}


struct Cash *add_in_cache(struct Cash *Cache, int elem, int place)
{
	(Cache->cache).push_front(elem);
	(Cache->table).insert({1, place, elem});

	return Cache;

}


int find_in_cache(struct Cash *Cache, int elem)
{
	int is_in_table;
	is_in_table = (Cache->table).count({1, 1,elem}); 
	//is_in_table = (Cache->table).contains({1, elem}); // -std=c++20

	if (!is_in_table)
	{
		return 0;
	}

	return ((Cache->table).find({0, 1, elem}))->be_in_cache;

}


struct Cash *displace_from_cache(struct Cash *Cache, int place, int *numbers)
{
	int worst;

	if ((Cache->cache).size() <= Cache->max_size_cash)
	{
		return Cache;
	}

	worst = find_worst(Cache, place, numbers);

	auto begin = (Cache->cache).begin();
	
	while ((*begin) != worst)
	{
		begin++;
	}

	(Cache->cache).erase(begin);
	(Cache->table).erase({1, 1, worst});
	(Cache->table).insert({0, 1, worst});

	return Cache;

}


int find_worst(struct Cash *Cache, int place, int *numbers)
{
	int worst, intervalmax, interval, size, i, curr;

	size = numbers[0];

	intervalmax = -100;
	interval = 0;

	for (auto elem: Cache->cache)
	{
		i = place + 1;
		curr = numbers[i];
		while ((curr != elem) && (i < (size + 1)))
		{
			curr = numbers[i];
			i++;
		}
		interval = i - 1 - ((Cache->table).find({0, 1, elem}))->num_place;
		if (curr != elem)
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


void *destroy_cache(struct Cash *Cache)
{
	Cache->table.clear();;
	Cache->cache.clear();
	free(Cache);

	return NULL;

}


void print_cache(struct Cash *Cache)
{
	std::cout << "Cache: ";

	for (auto elem: Cache->cache)
	{
		std::cout << elem << " " ;
	}

	std::cout << std::endl;

}
