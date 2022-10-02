#include "LIRS.h"




struct Cash *create_Cash(int len_cache)
{
	struct Cash *LIRS = new struct Cash;

	LIRS->count_lirs = 0;

	if (len_cache > 2)
	{
		LIRS->Lhirs = (int)(len_cache * 0.4) ;
		LIRS->Llirs = len_cache - LIRS->Lhirs;
	}
	else if (len_cache < 2)
	{
		printf("Incorrect cache size\n");
		_Exit(1);
	}
	else
	{
		LIRS->Lhirs = 1;
		LIRS->Llirs = 1;
	}

	return LIRS;
}


struct Cash *append_elem(struct Cash *LIRS, int elem, int *hits)
{
	if ((LIRS->table).contains(elem) == 0)
	{
		return visit_nothing(LIRS, elem);
	}

	int stat = (LIRS->table)[elem].st;
	
	if (stat == 0)
	{
		(*hits)++;
		return visit_lir(LIRS, elem);
	}
	else if (stat == 1)
	{
		(*hits)++;
		return visit_res_hir(LIRS, elem);
	}
	else
	{
		(*hits)++;
		return visit_non_res_hir(LIRS, elem);
	}

}


struct Cash *visit_lir(struct Cash *LIRS, int elem)
{
	LIRS = raise_elem_in_lirs(LIRS, elem);
	return reduction_lirs_stack(LIRS);


}


struct Cash *visit_res_hir(struct Cash *LIRS, int elem)
{
	int is_in_stack;
	is_in_stack = (LIRS->table)[elem].be_in_stack;

	if (is_in_stack)
	{
		LIRS = raise_elem_in_lirs(LIRS, elem);
		(LIRS->table)[elem].st = lir;
		(LIRS->count_lirs)++;
		if ((LIRS->table)[elem].be_in_cold)
		{
			(LIRS->cold_cash).erase((LIRS->table)[elem].pos_cold);
			(LIRS->table)[elem].be_in_cold = 0;
		}

		return reduction_lirs_stack(LIRS);
	}
	else
	{
		LIRS = raise_elem_in_cold(LIRS, elem);
		LIRS->lirs_stack.push_front(elem);
		(LIRS->table)[elem].pos_lirs = (LIRS->lirs_stack).begin();
		(LIRS->table)[elem].be_in_stack = 1;

		return LIRS;
	}

}


struct Cash *visit_nothing(struct Cash *LIRS, int elem)
{
	(LIRS->lirs_stack).push_front(elem);
	(LIRS->table)[elem] = {res_hir, 1, 0,  (LIRS->lirs_stack).begin()};
	
 
	return displace_from_cold(LIRS, elem);

}


struct Cash *visit_non_res_hir(struct Cash *LIRS, int elem)
{
	
	LIRS = raise_elem_in_lirs(LIRS, elem);
	(LIRS->table)[elem].st = lir;
	(LIRS->count_lirs)++;

	return reduction_lirs_stack(LIRS);

}



struct Cash *displace_from_cold(struct Cash *LIRS, int elem)
{
	int is_in_stack, first_hir;

	if ((LIRS->cold_cash).size() < LIRS->Lhirs)
	{
		(LIRS->cold_cash).push_front(elem);
		(LIRS->table)[elem].pos_cold = (LIRS->cold_cash).begin();
		(LIRS->table)[elem].be_in_cold = 1;
		return LIRS;
	}

	first_hir = LIRS->cold_cash.back();

	is_in_stack = (LIRS->table)[first_hir].be_in_stack;

	if (is_in_stack)
	{
		(LIRS->table)[first_hir].st = non_res_hir;
		(LIRS->table)[first_hir].be_in_cold = 0;
	}
	else
	{
		(LIRS->table).erase(first_hir);
	}

	(LIRS->cold_cash).pop_back();
	(LIRS->cold_cash).push_front(elem);
	(LIRS->table)[elem].pos_cold = (LIRS->cold_cash).begin();
	(LIRS->table)[elem].be_in_cold = 1;

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
	int first_lir, is_res, stat;
	first_lir = (LIRS->lirs_stack).back();

	if ((stat = (LIRS->table)[first_lir].st) != lir)
	{
		is_res = (stat == res_hir);
		(LIRS->lirs_stack).pop_back();
		if (is_res)
		{
			(LIRS->table)[first_lir].be_in_stack = 0;
		}
		else
		{
			(LIRS->table).erase(first_lir);
		}
		
		return reduction_lirs_stack(LIRS);
	}
	else if (LIRS->count_lirs > LIRS->Llirs)
	{
		LIRS = displace_from_cold(LIRS, first_lir);
		(LIRS->lirs_stack).pop_back();
		(LIRS->table)[first_lir].be_in_stack = 0;
		(LIRS->table)[first_lir].st = res_hir;
		(LIRS->count_lirs)--;

		return reduction_lirs_stack(LIRS);
	}

	return LIRS;

}


struct Cash *raise_elem_in_lirs(struct Cash *LIRS, int elem)
{

	(LIRS->lirs_stack).erase((LIRS->table)[elem].pos_lirs);
	(LIRS->lirs_stack).push_front(elem);
	(LIRS->table)[elem].pos_lirs = (LIRS->lirs_stack).begin();

	return LIRS;

}

struct Cash *raise_elem_in_cold(struct Cash *LIRS, int elem)
{
	(LIRS->cold_cash).erase((LIRS->table)[elem].pos_cold);
	(LIRS->cold_cash).push_front(elem);
	(LIRS->table)[elem].pos_cold = (LIRS->cold_cash).begin();
	
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

	for (auto elem: LIRS->table)
    {
        std::cout << elem.first <<" -> "<< (elem.second).st << " " <<(elem.second).be_in_stack << std::endl;
    }

}
