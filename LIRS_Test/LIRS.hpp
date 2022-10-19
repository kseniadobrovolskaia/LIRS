#include <iostream>
#include <list>
#include <unordered_map>



namespace LIRS
{
    class Cash
    {
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


        long unsigned int Lhirs;
        long unsigned int count_lirs;
        long unsigned int Llirs;
        std::list<int> lirs_stack;
        std::list<int> cold_cash;
        std::unordered_map<int, struct Hash_map_node> table;


        void visit_lir(int elem)
        {
            raise_elem_in_lirs(elem);
            reduction_lirs_stack();

            return;
        }


        void visit_res_hir(int elem)
        {
            int is_in_stack;
            is_in_stack = table[elem].be_in_stack;

            if (is_in_stack)
            {
                raise_elem_in_lirs(elem);
                table[elem].st = lir;
                count_lirs++;
                if (table[elem].be_in_cold)
                {
                    cold_cash.erase(table[elem].pos_cold);
                    table[elem].be_in_cold = 0;
                }

                reduction_lirs_stack();
            }
            else
            {
                raise_elem_in_cold(elem);
                lirs_stack.push_front(elem);
                table[elem].pos_lirs = lirs_stack.begin();
                table[elem].be_in_stack = 1;
            }

            return;
        }


        void visit_nothing(int elem)
        {
            lirs_stack.push_front(elem);
            table[elem] = {res_hir, 1, 0,  lirs_stack.begin()};
            
            displace_from_cold(elem);

            return;
        }


        void visit_non_res_hir(int elem)
        {
            
            raise_elem_in_lirs(elem);
            table[elem].st = lir;
            count_lirs++;

            reduction_lirs_stack();

            return;
        }


        void displace_from_cold(int elem)
        {
            int is_in_stack, first_hir;

            if (cold_cash.size() < Lhirs)
            {
                cold_cash.push_front(elem);
                table[elem].pos_cold = cold_cash.begin();
                table[elem].be_in_cold = 1;
                return;
            }

            first_hir = cold_cash.back();

            is_in_stack = table[first_hir].be_in_stack;

            if (is_in_stack)
            {
                table[first_hir].st = non_res_hir;
                table[first_hir].be_in_cold = 0;
            }
            else
            {
                table.erase(first_hir);
            }

            cold_cash.pop_back();
            cold_cash.push_front(elem);
            table[elem].pos_cold = cold_cash.begin();
            table[elem].be_in_cold = 1;

            return;
        }


        void reduction_lirs_stack()
        {
            int first_lir, is_res, stat;
            first_lir = lirs_stack.back();

            if ((stat = table[first_lir].st) != lir)
            {
                is_res = (stat == res_hir);
                lirs_stack.pop_back();
                if (is_res)
                {
                    table[first_lir].be_in_stack = 0;
                }
                else
                {
                    table.erase(first_lir);
                }
                
                reduction_lirs_stack();
            }
            else if (count_lirs > Llirs)
            {
                displace_from_cold(first_lir);
                lirs_stack.pop_back();
                table[first_lir].be_in_stack = 0;
                table[first_lir].st = res_hir;
                count_lirs--;

                reduction_lirs_stack();
            }

            return;
        }


        void raise_elem_in_lirs(int elem)
        {

            lirs_stack.erase((table)[elem].pos_lirs);
            lirs_stack.push_front(elem);
            table[elem].pos_lirs = lirs_stack.begin();

            return;
        }


        void raise_elem_in_cold(int elem)
        {
            cold_cash.erase((table)[elem].pos_cold);
            cold_cash.push_front(elem);
            table[elem].pos_cold = cold_cash.begin();

            return;
        }

    public:

        Cash(int len_cache)
        {
            count_lirs = 0;

            if (len_cache > 2)
            {
                Lhirs = (int)(len_cache * 0.4) ;
                Llirs = len_cache - Lhirs;
            }
            else if (len_cache < 2)
            {
                std::cout << "Incorrect cache size" << std::endl;
                _Exit(1);
            }
            else
            {
                Lhirs = 1;
                Llirs = 1;
            }
        }


        ~Cash()
        {
            table.clear();;
            cold_cash.clear();
            lirs_stack.clear();
        }

        
        void append_elem(int elem, int *hits)
        {
            if (table.contains(elem) == 0)
            {
                visit_nothing(elem);
                return;
            }

            (*hits)++;

            int stat = table[elem].st;
            
            if (stat == 0)
            {
                visit_lir(elem);
            }
            else if (stat == 1)
            {
                visit_res_hir(elem);
            }
            else
            {
                visit_non_res_hir(elem);
            }

            return;
        }
        

        void print_cash()
        {
            std::cout << "Lirs_stack: ";

            for (auto elem: lirs_stack)
            {
                std::cout << elem << " " ;
            }

            std::cout << std::endl << "Cold_cash: ";

            for (auto elem: cold_cash)
            {
                std::cout << elem << " ";
            }

            std::cout << std::endl << "Hash_map_table:"<< std::endl;

            for (auto elem: table)
            {
                std::cout << elem.first <<" -> "<< (elem.second).st << " " <<(elem.second).be_in_stack << std::endl;
            }

            return;
        }

    };

}