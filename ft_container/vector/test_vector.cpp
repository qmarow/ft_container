#include "vector.hpp"
#include <vector>
#include <algorithm>
#include <sstream>

void	error()
{
	std::cout << "\033[31;1;4m❌ERROR❌\033[0m" << std::endl;
	
}

void	ok()
{
	std::cout << "\033[32;4;24m ✓\033[0m";
}

template <typename T>
void	check(T my, T of, std::string text_error)
{
	if (my != of)
	{
		std::cout << text_error << "of: "<< of << " my: " << my;
		return (error());
	}
	else
		ok();
}

template <class T, class M>
int	scrolling(T my, M of)
{
	typename T::iterator my_begin = my.begin();
	typename M::iterator of_begin = of.begin();
	typename T::iterator my_end = my.end();
	typename M::iterator of_end = of.end();
	int		i = 0;
	while ((my_begin != my_end) || (of_begin != of_end))
	{

		if (*my_begin != *of_begin)
		{
			std::cout << "\033[31;1;4m❌ERROR❌\033[0m" << " i - " << i << "of - " << *of_begin << "my - " << *my_begin  << std::endl;
			return 1;
		}
		++my_begin;
		++of_begin;
	}
	ok();
		return 0;
}

template <typename T>
void	start_test()
{
	{
		{
			ft::vector<T>		my_v2(32, T());
			std::vector<T>		of_v2(32, T());
			// ft::vector<std::string>		my_v1(10, 0);
			// std::vector<std::string>	of_v1(10, 0);
			ft::vector<T>			my_v;
			std::vector<T>			of_v;
			ft::vector<T>			my_v3(++my_v2.begin(), --my_v2.end());
			std::vector<T>		of_v3(++of_v2.begin(), --of_v2.end());
			ft::vector<T>			my_v4(my_v3);
			std::vector<T>		of_v4(of_v3);

			std::cout << "Capacity: ";
			check(my_v.capacity(), of_v.capacity(), "Capacity test afte constructor()");
			check(my_v2.capacity(), of_v2.capacity(), "Capacity test afte constructor(size, value)");
			// check(of_v1.capacity(), of_v1.capacity(), "Capacity test afte constructor(size, value)");
			check(of_v3.capacity(), of_v3.capacity(), "Capacity test afte constructor(iterator first, iterator last)");
			check(of_v4.capacity(), of_v4.capacity(), "Capacity test afte constructor(vector &x)");
			
			std::cout << "\nSize:	  ";
			check(my_v.size(), of_v.size(), "Size test afte constructor()");
			check(my_v2.size(), of_v2.size(), "Size test afte constructor(size, value)");
			check(my_v3.size(), of_v3.size(), "Size test afte constructor(iterator first, iterator last)");
			check(my_v4.size(), of_v4.size(), "Size test afte constructor(vector &x)");
		
			std::cout << "\nBegin(): ";
			// check(*my_v.begin(), *of_v.begin(), "Begin() test afte constructor()"); // выдает сегу
			check(*my_v2.begin(), *of_v2.begin(), "Begin() test afte constructor(size, value)");
			check(*my_v3.begin(), *of_v3.begin(), "Begin() test afte constructor(iterator first, iterator last)");
			check(*my_v4.begin(), *of_v4.begin(), "Begin() test afte constructor(vector &x)");

			// std::cout << "\nEnd():   ";
			// my_v4.push_back(1);
			// of_v4.push_back(1);
			// check(*my_v.end(), *of_v.end(), "End() test afte constructor()");
			// check(*my_v2.end(), *my_v2.end(), "End() test afte constructor(size, value)");
			// check(*my_v3.end(), *of_v3.end(), "End() test afte constructor(iterator first, iterator last)");
			// check(*my_v4.end(), *of_v4.end(), "End() test afte constructor(vector &x)");
			// std::cout << "\nScroll:  ";
			// // check(*my_v.end(), *of_v.end(), "End() test afte constructor()");
			// 	std::cout << "end 0f_v2 - " << *of_v2.end() << std::endl;
			// scrolling(my_v2, of_v2); //  "End() test afte constructor(size, value)")
			// 	std::cout << "end 0f_v2 - " << *of_v2.end() << std::endl;
			
			// scrolling(my_v3, of_v3); //"End() test afte constructor(iterator first, iterator last)");
			// scrolling(my_v4, of_v4); //"End() test afte constructor(vector &x)");
			
			std::cout << "\n\t\tCheck operator";
			std::cout << "\nOperator '==':";
			check((my_v4 == my_v3), (of_v4 == of_v3), "Test == ");
			check((my_v4 == my_v4), (of_v4 == of_v4), "Test == ");
			check((my_v4 == my_v2), (of_v4 == of_v2), "Test == ");

			std::cout << "\nOperator '!=':";
			check((my_v4 != my_v3), (of_v4 != of_v3), "Test != ");
			check((my_v4 != my_v4), (of_v4 != of_v4), "Test != ");
			check((my_v4 != my_v2), (of_v4 != of_v2), "Test != ");

			std::cout << "\nOperator  '<':";
			check((my_v4 < my_v3), (of_v4 < of_v3), "Test < ");
			check((my_v4 < my_v4), (of_v4 < of_v4), "Test < ");
			check((my_v4 < my_v2), (of_v4 < of_v2), "Test < ");

			std::cout << "\nOperator  '>':";
			check((my_v4 > my_v3), (of_v4 > of_v3), "Test > ");
			check((my_v4 > my_v4), (of_v4 > of_v4), "Test > ");
			check((my_v4 > my_v2), (of_v4 > of_v2), "Test > ");

			std::cout << "\nOperator  '<=':";
			check((my_v4 <= my_v3), (of_v4 <= of_v3), "Test <=");
			check((my_v4 <= my_v4), (of_v4 <= of_v4), "Test <=");
			check((my_v4 <= my_v2), (of_v4 <= of_v2), "Test <=");

			std::cout << "\nOperator  '>=':";
			check((my_v4 >= my_v3), (of_v4 >= of_v3), "Test >=");
			check((my_v4 >= my_v4), (of_v4 >= of_v4), "Test >=");
			check((my_v4 >= my_v2), (of_v4 >= of_v2), "Test >=");

			std::cout << "\n\t\tCheck swap\n";
			std::cout << "swap: ";
			ft::swap(my_v4, my_v2);
			std::swap(of_v4, of_v2);

			scrolling(my_v4, of_v4);
			scrolling(my_v2, of_v2);
		
			std::cout << "\n\t\tCapacity\n";
			std::cout << "size: ";
			check(my_v.size(), of_v.size(), "Size test afte size(v)");
			check(my_v2.size(), of_v2.size(), "Size test afte size(2)");
			check(my_v3.size(), of_v3.size(), "Size test afte size(3)");
			check(my_v4.size(), of_v4.size(), "Size test afte size(4)");
			std::cout << "\nmax_size: ";
			check(my_v.max_size(), of_v.max_size(), "");
			check(my_v2.max_size(), of_v2.max_size(), "");
			check(my_v3.max_size(), of_v3.max_size(), "");
			check(my_v4.max_size(), of_v4.max_size(), "");
			std::cout << "\nresize: ";
			my_v4.resize(500);
			of_v4.resize(500);
			check(my_v4.size(), of_v4.size(), "resize ");
			scrolling(my_v4, of_v4);
			my_v4.resize(0);
			of_v4.resize(0);
			check(my_v4.size(), of_v4.size(), "resize size 0");
			scrolling(my_v4, of_v4);
	// check empty container
			my_v.resize(500);
			of_v.resize(500);
			check(my_v.size(), of_v.size(), "resize ");
			scrolling(my_v, of_v);
			my_v.resize(0);
			of_v.resize(0);
			check(my_v.size(), of_v.size(), "resize size 0");
			scrolling(my_v, of_v);

			std::cout << "\ncapacity: ";
			check(my_v.capacity(), of_v.capacity(), "Capacity test 1");
			check(my_v2.capacity(), of_v2.capacity(), "Capacity test 2");
			// check(of_v1.capacity(), of_v1.capacity(), "Capacity test afte constructor(size, value)");
			check(of_v3.capacity(), of_v3.capacity(), "Capacity test 3");
			check(of_v4.capacity(), of_v4.capacity(), "Capacity test 4");

			std::cout << "\nempty: ";
			check(my_v.empty(), of_v.empty(), "Empty test empty container");
			check(my_v2.empty(), of_v2.empty(), "Empty test no empty container");

			std::cout << "\nreserve: ";
			{
				std::vector<T>	my;
				ft::vector<T>		of;

				my.reserve(99);
				of.reserve(99);
				check(my.size(), of.size(), "Reserve test empty container(size)");
				check(my.capacity(), of.capacity(), "Reserve test empty container(capacity)");

				my.reserve(0);
				of.reserve(0);
				check(my.size(), of.size(), "Reserve test empty container(size)");
				check(my.capacity(), of.capacity(), "Reserve test empty container(capacity)");

				my_v4.reserve(1000);
				of_v4.reserve(1000);
				check(my_v4.size(), of_v4.size(), "Reserve test no empty container(size)");
				check(my_v4.capacity(), of_v4.capacity(), "Reserve test no empty container(capacity)");
			}
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			std::cout << "\n\t\tElement access\n";
			std::cout << "\noperator[]: ";
			check(my_v4[2], of_v4[2], "Check operator[2] ");
			check(my_v4[0], of_v4[0], "Check operator[0] ");
			check(my_v4[10], of_v4[10], "Check operator[10] ");
			
			std::cout << "\nat: ";
			std::stringstream smy;
			std::stringstream sof;

			try
			{
				my_v4.at(-1);
			}
			catch(const std::exception& e)
			{
				smy << e.what() << '\n';
			}
			
			try
			{
				of_v4.at(-1);
			}
			catch(const std::exception& e)
			{
				sof << e.what() << '\n';
			}
			check(smy.str(), sof.str(), "Exseption at(-1) ");
			check(my_v3.at(1), of_v3.at(1), "Check at(1) ");
			try
			{
				my_v4.at(100000);
			}
			catch(const std::exception& e)
			{
				smy << e.what() << '\n';
			}
			
			try
			{
				of_v4.at(100000);
			}
			catch(const std::exception& e)
			{
				sof << e.what() << '\n';
			}
			check(smy.str(), sof.str(), "Exseption at(100000) ");
			std::cout << "\nfront: ";
			check(my_v4.front(), of_v4.front(), "Test front() ");
			check(my_v.front(), of_v.front(), "Test front() ");
			std::cout << "\nback: ";
			check(my_v4.front(), of_v4.front(), "Test front() ");
			check(my_v.front(), of_v.front(), "Test front() ");
		}
			
	}
}

template <typename T>
void	check_size_capacity(std::vector<T> of, ft::vector<T> my)
{
	check(my.capacity(), of.capacity(), "Capacity test ");
	check(my.size(), of.size(), "Size test ");
}

void	end_test_string()
{
	{ // Assaing
		std::cout << "\n\t\tModifiers";
		std::cout << "\nassing(size n, value_type val): ";
		std::vector<std::string>	of1(10, std::string());
		ft::vector<std::string>		my1(10, std::string());
		
		of1.assign(5, "@#@!@");
		my1.assign(5, "@#@!@");
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		of1.assign(100, "-------");
		my1.assign(100, "-------");
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		of1.assign(0, "-------");
		my1.assign(0, "-------");
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
	}
	{ // Assaing
		std::cout << "\nassing(iter first, iter second): ";
		std::vector<std::string>	of1(10, std::string());
		ft::vector<std::string>		my1(10, std::string());
		std::vector<std::string>	of2;
		ft::vector<std::string>		my2;
		{
			of2.push_back("123");
			of2.push_back("234");
			of2.push_back("345");
			of2.push_back("456");
			of2.push_back("567");
			of2.push_back("678");
			of2.push_back("789");
			of2.push_back("890");
			of2.push_back("90-");
			of2.push_back("0-=");
			of2.push_back("-=+");
			of2.push_back("=+!");
			my2.push_back("123");
			my2.push_back("234");
			my2.push_back("345");
			my2.push_back("456");
			my2.push_back("567");
			my2.push_back("678");
			my2.push_back("789");
			my2.push_back("890");
			my2.push_back("90-");
			my2.push_back("0-=");
			my2.push_back("-=+");
			my2.push_back("=+!");
		}
		of1.assign(of2.begin(), of2.end());
		my1.assign(my2.begin(), my2.end());
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		of1.assign((of2.begin()) + 3, (of2.end()) - 2);
		my1.assign((my2.begin()) + 3, (my2.end()) - 2);
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		of1.assign(of2.begin(), of2.begin());
		my1.assign(my2.begin(), my2.begin());
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		of1.assign(of2.end(), of2.end());
		my1.assign(my2.end(), my2.end());
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
	}
	{ // Push_back // pop_back
		std::cout << "\npush_back: ";
		std::vector<std::string>	of2;
		ft::vector<std::string>		my2;
		{
			of2.push_back("123");
			my2.push_back("123");
			check(*my2.begin(), *of2.begin(), "Check push_bach(123) ");
			check_size_capacity(of2, my2);
			of2.push_back("234");
			my2.push_back("234");
			check(*(my2.begin() + 1), *(of2.begin() + 1), "Check push_back(234) ");
			check_size_capacity(of2, my2);
			of2.push_back(")_)");
			my2.push_back(")_)");
			check(*(my2.begin() + 2), *(of2.begin() + 2), "Check push_bach()_)) ");
			check_size_capacity(of2, my2);
			of2.push_back("&&**&&&*&&&*");
			my2.push_back("&&**&&&*&&&*");
			check(*(my2.begin() + 3), *(of2.begin() + 3), "Check push_back(&&**&&&*&&&*) ");
			check_size_capacity(of2, my2);

			std::cout << "\npop_back: ";
			of2.pop_back();
			my2.pop_back();
			check_size_capacity(of2, my2);
			of2.pop_back();
			my2.pop_back();
			check_size_capacity(of2, my2);	
			of2.pop_back();
			my2.pop_back();
			check_size_capacity(of2, my2);	
			of2.pop_back();
			my2.pop_back();
			check_size_capacity(of2, my2);	
			scrolling(my2, of2);	
		}
	}
	{ // Insert // erase // swap // clear
		std::cout << "\ninsert(iter pos, value_type val): ";

		std::vector<std::string>	of;
		ft::vector<std::string>		my;

		of.insert(of.begin(), "***");
		my.insert(my.begin(), "***");
		of.insert(of.begin(), "123");
		my.insert(my.begin(), "123");
		of.insert(of.begin(), "234");
		my.insert(my.begin(), "234");
		of.insert(of.begin(), "2344");
		my.insert(my.begin(), "2344");
		of.insert(of.begin(), "*daf");
		my.insert(my.begin(), "*daf");
		scrolling(my, of);
		check_size_capacity(of, my);

		std::vector<std::string>	of1(10, std::string());
		ft::vector<std::string>		my1(10, std::string());

		of1.insert(of1.begin(), "***");
		my1.insert(my1.begin(), "***");
		
		of1.insert(of1.begin() + 5, "*^*");
		my1.insert(my1.begin() + 5, "*^*");

		of1.insert(of1.end() - 1, "/^\\");
		my1.insert(my1.end() - 1, "/^\\");

		of1.insert(of1.end(), "<^>");
		my1.insert(my1.end(), "<^>");

		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		// ---
		std::cout << "\ninsert(iter pos, size_type n, value_type val): ";
		std::vector<std::string> of3;
		ft::vector<std::string> my3;

		of3.insert(of3.begin(), 999, "string");
		my3.insert(my3.begin(), 999, "string");
		scrolling(my3, of3);
		check_size_capacity(of3, my3);

		of1.insert(of1.begin(), 20, "***");
		my1.insert(my1.begin(), 20, "***");
		
		of1.insert(of1.begin() + 5, 100,  "*^*");
		my1.insert(my1.begin() + 5, 100, "*^*");

		of1.insert(of1.end() - 1, 1000,  "/^\\");
		my1.insert(my1.end() - 1, 1000, "/^\\");

		of1.insert(of1.end(), 10, "<^>");
		my1.insert(my1.end(), 10, "<^>");

		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		// --- 
		std::cout << "\ninsert(iter pos, iter first, iter last): ";
		std::vector<std::string>	of4;
		ft::vector<std::string>		my4;
		scrolling(my4, of4);
		check_size_capacity(of4, my4);

		of4.insert(of4.begin(), of1.begin(), of1.end());
		my4.insert(my4.begin(), my1.begin(), my1.end());

		of1.insert(of1.begin(), of.begin(), of.end());
		my1.insert(my1.begin(), my.begin(), my.end());
		
		of1.insert(of1.begin() + 5, of1.begin(), of1.end());
		my1.insert(my1.begin() + 5, my1.begin(), my1.end());

		of1.insert(of1.end(), of3.begin(), of3.end());
		my1.insert(my1.end(), my3.begin(), my3.end());
		scrolling(my1, of1);
		check_size_capacity(of1, my1);

		// ERASE
		
		std::cout << "\nerase(iter pos): ";
		for (int i = 0; i < 10; ++i)
		{
			of1.erase(of1.begin());
			my1.erase(my1.begin());
		}
		scrolling(my1, of1);
		check_size_capacity(of1, my1);

		std::cout << "\nerase(iter firs, iter last): ";
		of3.erase(of3.begin() + 10, of3.end() - 10);
		my3.erase(my3.begin() + 10, my3.end() - 10);
		scrolling(my3, of3);
		check_size_capacity(of3, my3);
		of3.erase(of3.begin(), of3.end());
		my3.erase(my3.begin(), my3.end());
		scrolling(my3, of3);
		check_size_capacity(of3, my3);

		// SWAP

		std::cout << "\nswap: ";
		of.swap(of1);
		my.swap(my1);

		scrolling(my, of);
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		check_size_capacity(of, my);

		// CLEAR

		std::cout << "\nclear: ";
		of1.clear();
		my1.clear();

		scrolling(my1, of1);
		check_size_capacity(of1, my1);
	}
}

template <typename T>
void	end_test()
{
	{ // Assaing
		std::cout << "\n\t\tModifiers";
		std::cout << "\nassing(size n, value_type val): ";
		std::vector<T>	of1(10, T());
		ft::vector<T>		my1(10, T());
		
		of1.assign(5, T(15));
		my1.assign(5, T(15));
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		of1.assign(100, T(55));
		my1.assign(100, T(55));
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		of1.assign(0, T(32));
		my1.assign(0, T(32));
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
	}
	{ // Assaing
		std::cout << "\nassing(iter first, iter second): ";
		std::vector<T>	of1(10, T());
		ft::vector<T>		my1(10, T());
		std::vector<T>	of2;
		ft::vector<T>		my2;
		for (int i = 0; i < 10; i++)
		{
			of2.push_back(T(i));
			my2.push_back(T(i));
		}
		of1.assign(of2.begin(), of2.end());
		my1.assign(my2.begin(), my2.end());
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		of1.assign((of2.begin()) + 3, (of2.end()) - 2);
		my1.assign((my2.begin()) + 3, (my2.end()) - 2);
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		of1.assign(of2.begin(), of2.begin());
		my1.assign(my2.begin(), my2.begin());
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		of1.assign(of2.end(), of2.end());
		my1.assign(my2.end(), my2.end());
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
	}
	{ // Push_back // pop_back
		std::cout << "\npush_back: ";
		std::vector<T>	of2;
		ft::vector<T>		my2;
		{
			of2.push_back(T(50));
			my2.push_back(T(50));
			check(*my2.begin(), *of2.begin(), "Check push_bach(123) ");
			check_size_capacity(of2, my2);
			of2.push_back(T(88));
			my2.push_back(T(88));
			check(*(my2.begin() + 1), *(of2.begin() + 1), "Check push_back(234) ");
			check_size_capacity(of2, my2);
			of2.push_back(T(45));
			my2.push_back(T(45));
			check(*(my2.begin() + 2), *(of2.begin() + 2), "Check push_bach()_)) ");
			check_size_capacity(of2, my2);
			of2.push_back(T(700));
			my2.push_back(T(700));
			check(*(my2.begin() + 3), *(of2.begin() + 3), "Check push_back(&&**&&&*&&&*) ");
			check_size_capacity(of2, my2);

			std::cout << "\npop_back: ";
			of2.pop_back();
			my2.pop_back();
			check_size_capacity(of2, my2);
			of2.pop_back();
			my2.pop_back();
			check_size_capacity(of2, my2);	
			of2.pop_back();
			my2.pop_back();
			check_size_capacity(of2, my2);	
			of2.pop_back();
			my2.pop_back();
			check_size_capacity(of2, my2);	
			scrolling(my2, of2);	
		}
	}
	{ // Insert // erase // swap // clear
		std::cout << "\ninsert(iter pos, value_type val): ";

		std::vector<T>	of;
		ft::vector<T>		my;

		for (int i = 0; i < 10; i++)
		{
			of.push_back(T(i + 40));
			my.push_back(T(i + 40));
		}
		scrolling(my, of);
		check_size_capacity(of, my);

		std::vector<T>		of1(10, T());
		ft::vector<T>		my1(10, T());

		of1.insert(of1.begin(), T(67));
		my1.insert(my1.begin(), T(67));
		
		of1.insert(of1.begin() + 5, T(98));
		my1.insert(my1.begin() + 5, T(98));

		of1.insert(of1.end() - 1, T(26));
		my1.insert(my1.end() - 1, T(26));

		of1.insert(of1.end(), T(47));
		my1.insert(my1.end(), T(47));

		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		// ---
		std::cout << "\ninsert(iter pos, size_type n, value_type val): ";
		std::vector<T> of3;
		ft::vector<T> my3;

		of3.insert(of3.begin(), 999, T(88));
		my3.insert(my3.begin(), 999, T(88));
		scrolling(my3, of3);
		check_size_capacity(of3, my3);

		of1.insert(of1.begin(), 20, T(28));
		my1.insert(my1.begin(), 20, T(28));
		
		of1.insert(of1.begin() + 5, 100,  T(38));
		my1.insert(my1.begin() + 5, 100, T(38));

		of1.insert(of1.end() - 1, 1000,  T(66));
		my1.insert(my1.end() - 1, 1000, T(66));

		of1.insert(of1.end(), 10, T(62));
		my1.insert(my1.end(), 10, T(62));

		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		// --- 
		std::cout << "\ninsert(iter pos, iter first, iter last): ";
		std::vector<T>		of4;
		ft::vector<T>		my4;
		scrolling(my4, of4);
		check_size_capacity(of4, my4);

		of4.insert(of4.begin(), of1.begin(), of1.end());
		my4.insert(my4.begin(), my1.begin(), my1.end());

		of1.insert(of1.begin(), of.begin(), of.end());
		my1.insert(my1.begin(), my.begin(), my.end());
		
		of1.insert(of1.begin() + 5, of1.begin(), of1.end());
		my1.insert(my1.begin() + 5, my1.begin(), my1.end());

		of1.insert(of1.end(), of3.begin(), of3.end());
		my1.insert(my1.end(), my3.begin(), my3.end());
		scrolling(my1, of1);
		check_size_capacity(of1, my1);

		// ERASE
		
		std::cout << "\nerase(iter pos): ";
		for (int i = 0; i < 10; ++i)
		{
			of1.erase(of1.begin());
			my1.erase(my1.begin());
		}
		scrolling(my1, of1);
		check_size_capacity(of1, my1);

		std::cout << "\nerase(iter firs, iter last): ";
		of3.erase(of3.begin() + 10, of3.end() - 10);
		my3.erase(my3.begin() + 10, my3.end() - 10);
		scrolling(my3, of3);
		check_size_capacity(of3, my3);
		of3.erase(of3.begin(), of3.end());
		my3.erase(my3.begin(), my3.end());
		scrolling(my3, of3);
		check_size_capacity(of3, my3);

		// SWAP

		std::cout << "\nswap: ";
		of.swap(of1);
		my.swap(my1);

		scrolling(my, of);
		scrolling(my1, of1);
		check_size_capacity(of1, my1);
		check_size_capacity(of, my);

		// CLEAR

		std::cout << "\nclear: ";
		of1.clear();
		my1.clear();

		scrolling(my1, of1);
		check_size_capacity(of1, my1);
	}
}

template <typename T>
void	check_operators()
{	
	std::cout << "\noperator == :";
	{
		std::vector<T>		of1;
		ft::vector<T>		my1;
		std::vector<T>		of2;
		ft::vector<T>		my2;

		if ((my1 == my2) == (of1 == of2))
			ok();
		else
			error();
		
		of1.push_back(T(20));
		my1.push_back(T(20));

		if ((my1 == my2) == (of1 == of2))
			ok();
		else
			error();

		of2.push_back(T(20));
		my2.push_back(T(20));

		if ((my1 == my2) == (of1 == of2))
			ok();
		else
			error();
	}
	std::cout << "\noperator != :";
	{
		std::vector<T>		of1;
		ft::vector<T>		my1;
		std::vector<T>		of2;
		ft::vector<T>		my2;

		if ((my1 == my2) == (of1 == of2))
			ok();
		else
			error();
		
		of1.push_back(T(20));
		my1.push_back(T(20));

		if ((my1 == my2) == (of1 == of2))
			ok();
		else
			error();

		of2.push_back(T(20));
		my2.push_back(T(20));

		if ((my1 == my2) == (of1 == of2))
			ok();
		else
			error();
	}
	std::cout << "\noperator <  :";
	{
		std::vector<T>		of1;
		ft::vector<T>		my1;
		std::vector<T>		of2;
		ft::vector<T>		my2;

		if ((my1 < my2) == (of1 < of2))
			ok();
		else
			error();
		
		of1.push_back(T(20));
		my1.push_back(T(20));

		if ((my1 < my2) == (of1 < of2))
			ok();
		else
			error();

		of2.push_back(T(20));
		my2.push_back(T(20));

		if ((my1 < my2) == (of1 < of2))
			ok();
		else
			error();
		
		of2.push_back(T(20));
		my2.push_back(T(20));

		if ((my1 < my2) == (of1 < of2))
			ok();
		else
			error();
	}
	std::cout << "\noperator >  :";
	{
		std::vector<T>		of1;
		ft::vector<T>		my1;
		std::vector<T>		of2;
		ft::vector<T>		my2;

		if ((my1 > my2) == (of1 > of2))
			ok();
		else
			error();
		
		of1.push_back(T(20));
		my1.push_back(T(20));

		if ((my1 > my2) == (of1 > of2))
			ok();
		else
			error();

		of2.push_back(T(20));
		my2.push_back(T(20));

		if ((my1 > my2) == (of1 > of2))
			ok();
		else
			error();
		
		of1.push_back(T(20));
		my1.push_back(T(20));

		if ((my1 > my2) == (of1 > of2))
			ok();
		else
			error();
	}
	std::cout << "\noperator <= :";
	{
		std::vector<T>		of1;
		ft::vector<T>		my1;
		std::vector<T>		of2;
		ft::vector<T>		my2;

		if ((my1 <= my2) == (of1 <= of2))
			ok();
		else
			error();
		
		of1.push_back(T(20));
		my1.push_back(T(20));

		if ((my1 <= my2) == (of1 <= of2))
			ok();
		else
			error();

		of2.push_back(T(20));
		my2.push_back(T(20));

		if ((my1 <= my2) == (of1 <= of2))
			ok();
		else
			error();
		
		of2.push_back(T(20));
		my2.push_back(T(20));

		if ((my1 <= my2) == (of1 <= of2))
			ok();
		else
			error();
	}
	std::cout << "\noperator >= :";
	{
		std::vector<T>		of1;
		ft::vector<T>		my1;
		std::vector<T>		of2;
		ft::vector<T>		my2;

		if ((my1 >= my2) == (of1 >= of2))
			ok();
		else
			error();
		
		of1.push_back(T(20));
		my1.push_back(T(20));

		if ((my1 >= my2) == (of1 >= of2))
			ok();
		else
			error();

		of2.push_back(T(20));
		my2.push_back(T(20));

		if ((my1 >= my2) == (of1 >= of2))
			ok();
		else
			error();
		
		of1.push_back(T(20));
		my1.push_back(T(20));

		if ((my1 >= my2) == (of1 >= of2))
			ok();
		else
			error();
	}
}

int     main()
{
	std::cout << "\t\tCheck constructor\n";
	std::cout << "\n\t\tTEST VECTOR WITH TYPE STRING\n";
	start_test<std::string>();
	end_test_string();
	std::cout << "\n\t\tTEST VECTOR WITH TYPE INT\n";
	start_test<int>();
	end_test<int>();
	check_operators<int>();
	std::cout << "\n\t\tTEST VECTOR WITH TYPE CHAR\n";
	start_test<char>();
	end_test<char>();
	check_operators<char>();
}