#include <stdio.h>
#include <iostream>
#include <list>
#include <unordered_set>
#include <fstream>


struct Cash *append_elem(struct Cash *Cache, int place, int *hits, int *numbers);
struct Cash *add_in_cache(struct Cash *Cache, int elem, int place);
struct Cash *displace_from_cache(struct Cash *Cache, int place, int *numbers);
int find_in_cache(struct Cash *Cache, int elem);
int find_worst(struct Cash *Cache, int place, int *numbers);
void print_cache(struct Cash *Cache);
void *destroy_cache(struct Cash *Cache);

struct Hash_map_node
{
    int be_in_cache;
    int num_place;
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
    long unsigned int max_size_cash;
    std::list<int> cache;
    std::unordered_set<struct Hash_map_node, Hash_function, Equal_function> table;
};

