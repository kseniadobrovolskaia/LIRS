#include <stdio.h>
#include <iostream>
#include <list>
#include <unordered_map>
#include <fstream>



namespace Perfect_Cash
{
    class Cash
    {

        struct Hash_map_node
        {
            int be_in_cache = 0;
            int num_place = 0;
            std::list<int>::iterator position;
            std::list<int> positions;
        };

        long unsigned int size;
        long unsigned int max_size_cash;
        std::list<int> cache;
        std::unordered_map<int, struct Hash_map_node> table;


        void add_in_cache(int elem, int place)
        {
            cache.push_front(elem);
            table[elem].be_in_cache = 1;
            table[elem].num_place = place;
            table[elem].position = cache.begin();
        }


        void displace_from_cache(int place, int *numbers)
        {
            int worst;

            if (size < max_size_cash)
            {
                size++;
                return;
            }

            worst = find_worst(place, numbers);

            cache.erase(table[worst].position);
            table[worst].be_in_cache = 0;
        }


        int find_worst(int place, int *numbers)
        {
            int worst, interval, max = -1;

            for (auto elem: cache)
            {
                auto curr = (table[elem].positions).begin();
                auto last = (table[elem].positions).end();
                
                while (*curr < place)
                {
                    curr++;
                    if (curr == last)
                    {
                        return elem;
                    }
                }

                interval = *curr - *(table[elem].position);
                
                if (interval > max)
                {
                    max = interval;
                    worst = elem;
                }
            }
            
            return worst;
        }


    public:

        Cash(int len_cache)
        {
            size = 0;
            max_size_cash = len_cache;
        }


        ~Cash()
        {
            table.clear();;
            cache.clear();
        }


        void add_in_table(int place, int elem)
        {
            (table[elem].positions).push_back(place);
        }


        void append_elem(int place, int *hits, int *numbers)
        {
            int elem;
            elem = numbers[place];

            if (table[elem].be_in_cache)
            {
                (*hits)++;
                table[elem].num_place = place; 
            }
            else
            {
                displace_from_cache(place, numbers); 
                add_in_cache(elem, place);       
            }
        }


        void print_cache()
        {
            std::cout << "Cache: ";

            for (auto elem: cache)
            {
                std::cout << elem << " " ;
            }

            std::cout << std::endl;
        }
    };
}

