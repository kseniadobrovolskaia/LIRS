#include <stdio.h>
#include <iostream>
#include <list>
#include <unordered_map>
#include <errno.h>
#include <assert.h>



struct Cash *create_Cash(int len_cache);
void *destroy_cash(struct Cash *LIRS);
struct Cash *append_elem(struct Cash *LIRS, int elem, int *hits);
int get_status(struct Hash_map table, int elem);
struct Cash *visit_lir(struct Cash *LIRS, int elem);
struct Cash *visit_res_hir(struct Cash *LIRS, int elem);
struct Cash *visit_non_res_hir(struct Cash *LIRS, int elem);
struct Cash *visit_nothing(struct Cash *LIRS, int elem);
struct Cash *reduction_lirs_stack(struct Cash *LIRS);
int find_in_stack(struct Cash *LIRS, int elem);
struct Cash *displace_from_cold(struct Cash *LIRS, int elem);
struct Cash *raise_elem_in_cold(struct Cash *LIRS, int elem);
struct Cash *raise_elem_in_lirs(struct Cash *LIRS, int elem);
void print_cash(struct Cash *LIRS);





enum status
{
    lir,
    res_hir,
    non_res_hir,
};

struct Hash_map_node
{
    status st;
    int be_in_stack = 0;
    int be_in_cold = 0;
    std::list<int>::iterator pos_lirs;
    std::list<int>::iterator pos_cold;
};


struct Cash
{
    long unsigned int Lhirs;
    long unsigned int count_lirs;
    long unsigned int Llirs;
    std::list<int> lirs_stack;
    std::list<int> cold_cash;
    std::unordered_map<int, struct Hash_map_node> table;
};

