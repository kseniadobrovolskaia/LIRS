#include "LIRS.h"


int main()
{
	int n, hits, elem;
	FILE *data, *results;
	int answers[5] = {0};
	
	struct Cash *LIRS;
	data = fopen("data.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		LIRS = new struct Cash;
		fscanf(data, "%d", &n); 
		hits = 0;

		for (int i = 0; i < n; i++)
		{
			fscanf(data, "%d", &elem); 
			LIRS = append_elem(LIRS, elem, &hits);
		}
		answers[i] = hits;
		printf("For %d elems - %d hits\n", n, hits);
		destroy_cash(LIRS);
	}

	fclose(data);

	
	results = fopen("build/results.txt", "w");
	for (int i = 0; i < 5; i++)
	{
		fprintf(results, "%d ", answers[i]);
	}
	
	fclose(results);

	return 0;
}


struct Cash *append_elem(struct Cash *LIRS, int elem, int *hits)
{
	int be_in_stack, st;

	if ((LIRS->table).count({lir, 0, elem}) == 0)
	{
		return visit_nothing(LIRS, elem);
	}

	st = (LIRS->table).find({lir, 0, elem})->st;
	be_in_stack = (LIRS->table).find({lir, 0, elem})->be_in_stack;

	if (be_in_stack)
	{
		(*hits)++;
	}

	if (st == 0)
	{
		LIRS = visit_lir(LIRS, elem);
	}
	else if (st == 1)
	{
		LIRS = visit_res_hir(LIRS, elem);
	}
	else
	{
		LIRS = visit_non_res_hir(LIRS, elem);
	}

	return LIRS;

}


struct Cash *visit_lir(struct Cash *LIRS, int elem)
{
	LIRS = raise_elem_in_lirs(LIRS, elem);
	LIRS = reduction_lirs_stack(LIRS);

	return LIRS;

}


struct Cash *visit_res_hir(struct Cash *LIRS, int elem)
{
	int is_in_stack;
	is_in_stack = (LIRS->table).find({res_hir, 0, elem})->be_in_stack;

	if (is_in_stack)
	{
		LIRS = raise_elem_in_lirs(LIRS, elem);
		(LIRS->table).erase({res_hir, 1, elem});
		(LIRS->table).insert({lir, 1, elem});
		LIRS->cold_cash.remove(elem);

		LIRS = reduction_lirs_stack(LIRS);
	}
	else
	{
		LIRS = raise_elem_in_cold(LIRS, elem);
		LIRS->lirs_stack.push_front(elem);
		(LIRS->table).erase({res_hir, 0, elem});
		(LIRS->table).insert({res_hir, 1, elem});

		LIRS = reduction_lirs_stack(LIRS);
	}

	return LIRS;

}


struct Cash *visit_nothing(struct Cash *LIRS, int elem)
{
	LIRS = displace_from_cold(LIRS, elem);

	(LIRS->lirs_stack).push_front(elem);
	LIRS = reduction_lirs_stack(LIRS);
	(LIRS->table).insert({res_hir, 1, elem});

	return LIRS;

}


struct Cash *visit_non_res_hir(struct Cash *LIRS, int elem)
{
	int first_lir;
	
	LIRS = raise_elem_in_lirs(LIRS, elem);
	(LIRS->table).erase({non_res_hir, 1, elem});
	(LIRS->table).insert({lir, 1, elem});

	first_lir = LIRS->lirs_stack.back();

	if ((LIRS->table).find({lir, 1, first_lir})->st == lir)
	{
		LIRS = displace_from_cold(LIRS, first_lir);
		(LIRS->lirs_stack).pop_back();
		(LIRS->table).erase({lir, 1, first_lir});
		(LIRS->table).insert({res_hir, 0, first_lir});
	}

	LIRS = reduction_lirs_stack(LIRS);

	return LIRS;

}


int find_in_stack(struct Cash *LIRS, int elem)
{
	int is_in_table;
	is_in_table = (LIRS->table).count({res_hir, 0, elem}); 
	//is_in_table = (LIRS->table).contains({res_hir, 0, elem}); // -std=c++20

	if (!is_in_table)
	{
		return 0;
	}

	return ((LIRS->table).find({res_hir, 0, elem}))->be_in_stack;

}


struct Cash *displace_from_cold(struct Cash *LIRS, int elem)
{
	int is_in_stack, first_hir;

	if ((LIRS->cold_cash).size() < MAX_SIZE_COLD_CASH)
	{
		(LIRS->cold_cash).push_front(elem);
		return LIRS;
	}

	first_hir = LIRS->cold_cash.back();

	is_in_stack = (LIRS->table).find({res_hir, 0, first_hir})->be_in_stack;

	if (is_in_stack)
	{
		(LIRS->table).erase({res_hir, 1, first_hir});
		(LIRS->table).insert({non_res_hir, 1, first_hir});
	}
	else
	{
		(LIRS->table).erase({res_hir, 0, first_hir});
	}

	(LIRS->cold_cash).pop_back();
	(LIRS->cold_cash).push_front(elem);

	return LIRS;

}


void *destroy_cash(struct Cash *LIRS)
{
	LIRS->table.clear();;
	LIRS->cold_cash.clear();
	LIRS->lirs_stack.clear();
	free(LIRS);

	return NULL;

}


struct Cash *reduction_lirs_stack(struct Cash *LIRS)
{
	int first_lir, is_res;
	first_lir = (LIRS->lirs_stack).back();

	if ((LIRS->lirs_stack).size() < MAX_SIZE_LIRS_STACK)
	{
		return LIRS;
	}

	if ((LIRS->table).find({res_hir, 1, first_lir})->st != lir)
	{
		is_res = (LIRS->table).find({res_hir, 1, first_lir})->st == res_hir;
		(LIRS->lirs_stack).pop_back();
		(LIRS->table).erase({res_hir, 1, first_lir});
		if (is_res)
		{
			(LIRS->table).insert({res_hir, 0, first_lir});
		}
	}
	else
	{
		if ((LIRS->lirs_stack).size() > MAX_SIZE_LIRS_STACK)
		{
			(LIRS->lirs_stack).pop_back();
			(LIRS->table).erase({lir, 1, first_lir});
			(LIRS->table).insert({res_hir, 0, first_lir});
			LIRS = displace_from_cold(LIRS, first_lir);
		}
		return LIRS;
	}

	return reduction_lirs_stack(LIRS);

}


struct Cash *raise_elem_in_lirs(struct Cash *LIRS, int elem)
{
	(LIRS->lirs_stack).remove(elem);
	(LIRS->lirs_stack).push_front(elem);

	return LIRS;

}


struct Cash *raise_elem_in_cold(struct Cash *LIRS, int elem)
{
	(LIRS->cold_cash).remove(elem);
	(LIRS->cold_cash).push_front(elem);

	return LIRS;

}


void print_cash(struct Cash *LIRS)
{
	std::cout << "Lirs_stack: ";

	for (auto elem: LIRS->lirs_stack)
	{
		std::cout << elem << " " ;
	}

	std::cout << std::endl << "Cold_cash: ";

	for (auto elem: LIRS->cold_cash)
	{
		std::cout << elem << " ";
	}

	std::cout << std::endl << "Hash_map_table:"<< std::endl;

	for (std::unordered_set<struct Hash_map_node>::const_iterator it = LIRS->table.begin(); it != LIRS->table.end(); ++it)
    {
        std::cout << "{" << it->st <<", "<< it->be_in_stack<< ", "<<it->num<< "}"<< std::endl;
    }

}



