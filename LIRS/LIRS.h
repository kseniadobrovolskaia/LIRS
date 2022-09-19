#include <stdio.h>
#include <iostream>
#include <list>
#include <unordered_set>

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


#define MAX_SIZE_LIRS_STACK 30
#define MAX_SIZE_COLD_CASH 15


enum status
{
    lir,
    res_hir,
    non_res_hir,
    nothing
};

struct Hash_map_node
{
    status st;
    int be_in_stack;
    int num;
};

struct Hash_function
{
    size_t operator()(struct Hash_map_node elem) const
    {
        return elem.num;
    };
};

struct Equal_function
{
    int operator()(struct Hash_map_node elem1, struct Hash_map_node elem2) const
    {
        return (elem1.num) == (elem2.num);
    };
};

struct Cash
{
    std::list<int> lirs_stack;
    std::list<int> cold_cash;
    std::unordered_set<struct Hash_map_node, Hash_function, Equal_function> table;
};

