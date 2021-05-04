#include "map.hpp"
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <iostream>
#include <string>
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
int	scrolling(T my_begin, T my_end, M of_begin, M of_end)
{
	int		i = 0;
	while ((my_begin != my_end) || (of_begin != of_end))
	{
		// std::cout << " i - " << i << " of - |" << (*of_begin).second << "| my - |" << (*my_begin).second  << "|\n";
		if ((*my_begin).second != (*of_begin).second)
		{
			std::cout << "\033[31;1;4m❌ERROR❌\033[0m" << " i - " << i << " of - |" << (*of_begin).second << "| my - |" << (*my_begin).second  << "|\n";
			return 1;
		}
		++my_begin;
		++of_begin;
	}
	ok();
		return 0;
}

template <typename K, typename T>
void	check_Iterators()
{
	std::cout << "\n##########################################\n\t\tCHECK Iterators\n";
	std::cout << "##########################################\n";
	{//iterator
		std::cout << "iterator: ";
		std::map<K, T>		of1;
		ft::map<K, T>		my1;

		for (int i = 0; i < 40; ++i)
		{
			of1[i] = i;
			my1[i] = i;
		}

		std::map<K, T>		of(of1.begin(), of1.end());
		ft::map<K, T>			my(my1.begin(), my1.end());


		typename std::map<K, T>::iterator of_beg = of.begin();
		typename std::map<K, T>::iterator of_end = of.end();
		typename ft::map<K, T>::iterator my_beg = my.begin();
		typename ft::map<K, T>::iterator my_end = my.end();

		scrolling(my_beg, my_end, of_beg, of_end);
		check(my_beg->second, of_beg->second, "Test iterator ");
		check((*my_beg).second, (*of_beg).second, "Test iterator ");

		++my_beg;
		++of_beg;
		typename std::map<K, T>::iterator of_beg1(of_beg);
		typename ft::map<K, T>::iterator my_beg1(my_beg);

		--my_beg1;
		--of_beg1;
		check((*my_beg1).second, (*of_beg1).second, "Test iterator ");
		++my_beg;
		++of_beg;

		of_beg1 = of_beg;
		my_beg1 = my_beg;

		check((*my_beg1).second, (*of_beg1).second, "Test iterator ");

		if ((of_beg1 == of_beg) == (my_beg1 == my_beg))
			ok();
		else
			error();
		
		if ((of_beg1 != of_beg) == (my_beg1 != my_beg))
			ok();
		else
			error();
		
		++my_beg;
		++of_beg;
		++my_beg;
		++of_beg;

		if ((of_beg1 == of_beg) == (my_beg1 == my_beg))
			ok();
		else
			error();
		
		if ((of_beg1 != of_beg) == (my_beg1 != my_beg))
			ok();
		else
			error();
		
		*of_beg++;
		*my_beg++;
		check((*my_beg).second, (*of_beg).second, "Test iterator ");
		*of_beg--;
		*my_beg--;
		check((*my_beg).second, (*of_beg).second, "Test iterator ");
	
		// std::pair<K, T> a(of_beg->first, 10);
		// *my_beg = a;
		// *of_beg = a;
		// check((*my_beg).second, (*of_beg).second, "Test iterator ");
	}	
	{//const_iter
		std::cout << "\nconst_iter: ";
		std::map<K, T>		of1;
		ft::map<K, T>		my1;

		for (int i = 0; i < 40; ++i)
		{
			of1[i] = i;
			my1[i] = i;
		}

		const std::map<K, T>		of(of1.begin(), of1.end());
		const ft::map<K, T>			my(my1.begin(), my1.end());


		typename std::map<K, T>::const_iterator of_beg = of.begin();
		typename std::map<K, T>::const_iterator of_end = of.end();
		typename ft::map<K, T>::const_iterator my_beg = my.begin();
		typename ft::map<K, T>::const_iterator my_end = my.end();

		scrolling(my_beg, my_end, of_beg, of_end);
		check(my_beg->second, of_beg->second, "Test const_iterator ");
		check((*my_beg).second, (*of_beg).second, "Test const_iterator ");

		++my_beg;
		++of_beg;
		typename std::map<K, T>::const_iterator of_beg1(of_beg);
		typename ft::map<K, T>::const_iterator my_beg1(my_beg);

		--my_beg1;
		--of_beg1;
		check((*my_beg1).second, (*of_beg1).second, "Test const_iterator ");
		++my_beg;
		++of_beg;

		of_beg1 = of_beg;
		my_beg1 = my_beg;

		check((*my_beg1).second, (*of_beg1).second, "Test const_iterator ");

		if ((of_beg1 == of_beg) == (my_beg1 == my_beg))
			ok();
		else
			error();
		
		if ((of_beg1 != of_beg) == (my_beg1 != my_beg))
			ok();
		else
			error();
		
		++my_beg;
		++of_beg;
		++my_beg;
		++of_beg;

		if ((of_beg1 == of_beg) == (my_beg1 == my_beg))
			ok();
		else
			error();
		
		if ((of_beg1 != of_beg) == (my_beg1 != my_beg))
			ok();
		else
			error();
		
		*of_beg++;
		*my_beg++;
		check((*my_beg).second, (*of_beg).second, "Test const_iterator ");
		*of_beg--;
		*my_beg--;
		check((*my_beg).second, (*of_beg).second, "Test const_iterator ");
	}
	{//reverse_iter
		std::cout << "\nreverse_iter: ";
		std::map<K, T>		of1;
		ft::map<K, T>		my1;

		for (int i = 0; i < 40; ++i)
		{
			of1[i] = i;
			my1[i] = i;
		}

		std::map<K, T>			of(of1.begin(), of1.end());
		ft::map<K, T>			my(my1.begin(), my1.end());


		typename std::map<K, T>::reverse_iterator of_beg = of.rbegin();
		typename std::map<K, T>::reverse_iterator of_end = of.rend();
		typename ft::map<K, T>::reverse_iterator my_beg = my.rbegin();
		typename ft::map<K, T>::reverse_iterator my_end = my.rend();

		scrolling(my_beg, my_end, of_beg, of_end);
		check(my_beg->second, of_beg->second, "Test reverse_iterator ");
		check((*my_beg).second, (*of_beg).second, "Test reverse_iterator ");

		++my_beg;
		++of_beg;
		typename std::map<K, T>::reverse_iterator of_beg1(of_beg);
		typename ft::map<K, T>::reverse_iterator my_beg1(my_beg);

		--my_beg1;
		--of_beg1;
		check((*my_beg1).second, (*of_beg1).second, "Test reverse_iterator ");
		++my_beg;
		++of_beg;

		of_beg1 = of_beg;
		my_beg1 = my_beg;

		check((*my_beg1).second, (*of_beg1).second, "Test reverse_iterator ");

		if ((of_beg1 == of_beg) == (my_beg1 == my_beg))
			ok();
		else
			error();
		
		if ((of_beg1 != of_beg) == (my_beg1 != my_beg))
			ok();
		else
			error();
		
		++my_beg;
		++of_beg;
		++my_beg;
		++of_beg;

		if ((of_beg1 == of_beg) == (my_beg1 == my_beg))
			ok();
		else
			error();
		
		if ((of_beg1 != of_beg) == (my_beg1 != my_beg))
			ok();
		else
			error();
		
		*of_beg++;
		*my_beg++;
		check((*my_beg).second, (*of_beg).second, "Test reverse_iterator ");
		*of_beg--;
		*my_beg--;
		check((*my_beg).second, (*of_beg).second, "Test reverse_iterator ");
	}
	{
		std::cout << "\nconst_iter: ";
		std::map<K, T>		of1;
		ft::map<K, T>		my1;

		for (int i = 0; i < 40; ++i)
		{
			of1[i] = i;
			my1[i] = i;
		}

		const std::map<K, T>		of(of1.begin(), of1.end());
		const ft::map<K, T>			my(my1.begin(), my1.end());


		typename std::map<K, T>::const_reverse_iterator of_beg = of.rbegin();
		typename std::map<K, T>::const_reverse_iterator of_end = of.rend();
		typename ft::map<K, T>::const_reverse_iterator my_beg = my.rbegin();
		typename ft::map<K, T>::const_reverse_iterator my_end = my.rend();

		scrolling(my_beg, my_end, of_beg, of_end);
		check(my_beg->second, of_beg->second, "Test const_reverse_iterator ");
		check((*my_beg).second, (*of_beg).second, "Test const_reverse_iterator ");

		++my_beg;
		++of_beg;
		typename std::map<K, T>::const_reverse_iterator of_beg1(of_beg);
		typename ft::map<K, T>::const_reverse_iterator my_beg1(my_beg);

		--my_beg1;
		--of_beg1;
		check((*my_beg1).second, (*of_beg1).second, "Test const_reverse_iterator ");
		++my_beg;
		++of_beg;

		of_beg1 = of_beg;
		my_beg1 = my_beg;

		check((*my_beg1).second, (*of_beg1).second, "Test const_reverse_iterator ");

		if ((of_beg1 == of_beg) == (my_beg1 == my_beg))
			ok();
		else
			error();
		
		if ((of_beg1 != of_beg) == (my_beg1 != my_beg))
			ok();
		else
			error();
		
		++my_beg;
		++of_beg;
		++my_beg;
		++of_beg;

		if ((of_beg1 == of_beg) == (my_beg1 == my_beg))
			ok();
		else
			error();
		
		if ((of_beg1 != of_beg) == (my_beg1 != my_beg))
			ok();
		else
			error();
		
		*of_beg++;
		*my_beg++;
		check((*my_beg).second, (*of_beg).second, "Test const_reverse_iterator ");
		*of_beg--;
		*my_beg--;
		check((*my_beg).second, (*of_beg).second, "Test const_reverse_iterator ");
	}
}

template <typename K, typename T>
void	check_cons_des_oper()
{
	std::cout << "\n##########################################\n\t\tCHECK Constructor\n";
	std::cout << "##########################################\n";
	std::cout << "default constructor: ";
	{
		std::map<K, T>	of1;
		ft::map<K, T>	my1;

		scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		check(my1.size(), of1.size(), "default constructor size ");
		std::cout << "\ncopy constructor: ";
		for (int i = 0; i < 20; i++)
		{
			of1[i] = i;
			my1[i] = i;
		}
		std::map<K, T> of2 = of1;
		ft::map<K, T> my2 = my1;
		scrolling(my2.begin(), my2.end(), of2.begin(), of2.end());
		check(my2.size(), of2.size(), "copy constructor size ");
		
		
		std::cout << "\noperator = : ";
		std::map<K, T> of3;
		of3 = of1;
		ft::map<K, T> my3;
		my3 = my1;

		scrolling(my3.begin(), my3.end(), of3.begin(), of3.end());
		check(my3.size(), of3.size(), "operator = size ");

		for (int i = 20; i < 50; ++i)
		{
			of3[i] = i;
			my3[i] = i;
		}
		of1 = of3;
		my1 = my3;
		scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		check(my1.size(), of1.size(), "operator = size ");

		std::cout << "\ninterval constructor: ";
		ft::map<K, T> my4(my1.begin(), my1.end());
		std::map<K, T> of4(of1.begin(), of1.end());

		scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		check(my1.size(), of1.size(), "interval constructor size ");
	}
}

template <typename K, typename T>
void	check_Capacity()
{
	std::cout << "\n##########################################\n\t\tCHECK Capacity\n";
	std::cout << "##########################################\n";
	
	{//clear
		std::cout << "empty(): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;

		check(my1.empty(), of1.empty(), "Empty container ");
		for(int i = 1; i < 11; ++i)
		{
			of1[i] = i + 40;
			my1[i] = i + 40;
		}
		check(my1.empty(), of1.empty(), "No empty container ");
		of1.clear();
		my1.clear();
		check(my1.empty(), of1.empty(), "Empty container after clear()");
	}
	{//size
		std::cout << "\nsize(): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;

		check(my1.size(), of1.size(), "Empty container ");
		for(int i = 1; i < 11; ++i)
		{
			of1[i] = i + 40;
			my1[i] = i + 40;
		}
		check(my1.size(), of1.size(), "No empty container ");
		of1.clear();
		my1.clear();
		check(my1.size(), of1.size(), "Empty container after clear()");
		of1.max_size();
	}
	{//max_size
		std::cout << "\nmax_size(): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;

		check(my1.max_size(), of1.max_size(), "Max size empty container ");
		for(int i = 0; i < 40; ++i)
		{
			of1[i] = T();
			my1[i] = T();
		}
		check(my1.max_size(), of1.max_size(), "Max size empty container ");
	}
}

template <typename K, typename T>
void	check_Element_access()
{
	std::cout << "\n##########################################\n\t\tCHECK Element access\n";
	std::cout << "##########################################\n";
	std::cout << "\n\t\tCHECK OPERATOR[]\n";
	std::cout << "operator[]: ";
	
	std::map<K, T> of1;
	ft::map<K, T> my1;

	int err = 0;
	for(int i = 1; i < 11; ++i)
	{
		if (of1[i] != my1[i])
			err = 1;
	}
	if (err)
		error();
	else
	scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());

	for(int i = 1; i < 11; ++i)
	{
		of1[i] = i + 40;
		my1[i] = i + 40;
	}
	scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());

	err = 0;
	for(int i = 1; i < 11; ++i)
	{
		if (of1[i] != my1[i])
			err = 1;
	}
	if (err)
		error();
	else
	scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
}

template <typename K, typename T>
void	check_Modifiers()
{
	std::cout << "\n##########################################\n\t\tCHECK Modifiers\n";
	std::cout << "##########################################\n";
	std::cout << "\n\t\tCHECK INSERT\n";
	{//insert
		std::map<K, T> of1;
		ft::map<K, T> my1;
		std::cout << "insert(value_type &val): ";

		int err = 0;
		for(int i = 0; i < 10; i++)
		{
			std::pair<K, T> a(i, i);
			if (of1.insert(a).second != my1.insert(a).second)
				err = 1;
		}
		if (err)
			error();
		else
			scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		
		for(int i = 0; i < 15; i++)
		{
			std::pair<K, T> a(i, i);
			if (of1.insert(a).second != my1.insert(a).second)
				err = 1;
		}
		if (err)
			error();
		else
			scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		std::cout << "\ninsert(iter position, value_type& val): ";
		typename std::map<K, T>::iterator ofit = of1.begin();
		typename ft::map<K, T>::iterator mit = my1.begin();

		for(int i = 0; i < 10; i++)
		{
			std::pair<K, T> a(i, i);
			if (of1.insert(ofit, a)->second != my1.insert(mit, a)->second)
				err = 1;
		}
		if (err)
			error();
		else
			scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		
		for(int i = 0; i < 15; i++)
		{
			std::pair<K, T> a(i, i);
			if (of1.insert(ofit, a)->second != my1.insert(mit, a)->second)
				err = 1;
		}
		if (err)
			error();
		else
			scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		std::cout << "\ninsert(iter first, iter last): ";
		std::map<K, T> of2;
		ft::map<K, T> my2;

		of2.insert(of1.begin(), of1.end());
		my2.insert(of1.begin(), of1.end());
		scrolling(my2.begin(), my2.end(), of2.begin(), of2.end());
		std::map<K, T> of3;
		ft::map<K, T> my3;

		of3.insert(my1.begin(), my1.end());
		my3.insert(my1.begin(), my1.end());
		scrolling(my3.begin(), my3.end(), of3.begin(), of3.end());
	}
	std::cout << "\n\t\tCHECK ERESE\n";
	{//erese
		std::map<K, T> of1;
		ft::map<K, T> my1;

		for(int i = 1; i < 11; ++i)
		{
			of1[i] = i + 40;
			my1[i] = i + 40;
		}
		std::cout << "erase(iter position): ";
		my1.erase(my1.begin());
		of1.erase(of1.begin());
		scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		my1.erase(++(my1.begin()));
		of1.erase(++(of1.begin()));
		scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		my1.erase(--(my1.end()));
		of1.erase(--(of1.end()));
		scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());

		std::cout << "\nerase(const key_type &k): ";
		if (my1.erase(5) == of1.erase(5))
			scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		else
			error();
		if (my1.erase(7) == of1.erase(7))
			scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		else
			error();
		if (my1.erase(1) == of1.erase(1)) // удаления не произойдет. Erase вернут 0
			scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		else
			error();
		if (my1.erase(55) == of1.erase(55))
			scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		else
			error();

		std::cout << "\nerase(iter first, iter last): ";
		std::map<K, T> of2;
		ft::map<K, T> my2;

		for(int i = 1; i < 20; ++i)
		{
			of2[i] = i;
			my2[i] = i;
		}
		my2.erase(my2.begin(), my2.end());
		of2.erase(of2.begin(), of2.end());

		scrolling(my2.begin(), my2.end(), of2.begin(), of2.end());

		for(int i = 1; i < 20; ++i)
		{
			of2[i] = i;
			my2[i] = i;
		}
		my2.erase(++my2.begin(), --my2.end());
		of2.erase(++of2.begin(), --of2.end());
		scrolling(my2.begin(), my2.end(), of2.begin(), of2.end());

		my2.erase(my2.begin(), my2.begin());
		of2.erase(of2.begin(), of2.begin());
		scrolling(my2.begin(), my2.end(), of2.begin(), of2.end());

	}
	std::cout << "\n\t\tCHECK SWAP\n";
	{//swap
		std::cout << "swap(map &x): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;
		std::map<K, T> of2;
		ft::map<K, T> my2;

		for (int i = 0; i < 100; ++i)
		{
			of1[i] = T(i);
			my1[i] = T(i);
		}
		of1.swap(of2);
		my1.swap(my2);
		scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		scrolling(my2.begin(), my2.end(), of2.begin(), of2.end());

		for (int i = 0; i < 50; ++i)
		{
			of1[i] = T(i + 30);
			my1[i] = T(i + 30);
		}
		of1.swap(of2);
		my1.swap(my2);
		scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		scrolling(my2.begin(), my2.end(), of2.begin(), of2.end());
	}
	std::cout << "\n\t\tCHECK CLEAR\n";
	{//clear
		std::cout << "clear(): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;

		for (int i = 0; i < 100; ++i)
		{
			of1[i] = T(i);
			my1[i] = T(i);
		}
		of1.clear();
		my1.clear();
		scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
		of1.clear();
		my1.clear();
		scrolling(my1.begin(), my1.end(), of1.begin(), of1.end());
	}
}

template <typename K, typename T>
void	check_Observers()
{
	std::cout << "\n##########################################\n\t\tCHECK Observers\n";
	std::cout << "##########################################\n";
	{//key_comp
		std::cout << "key_comp(): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;
		
		typename std::map<K, T>::key_compare of_comp = of1.key_comp();
		typename ft::map<K, T>::key_compare my_comp = my1.key_comp();

		check(my_comp(T(10), T(10)), of_comp(T(10), T(10)), "Comp(10, 10)");
		check(my_comp(T(5), T(10)), of_comp(T(5), T(10)), "Comp(5, 10)");
		check(my_comp(T(144), T(10)), of_comp(T(144), T(10)), "Comp(144, 10)");
	}
	{//value_comp
		std::cout << "\nvalue_comp(): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;
		
		typename std::map<K, T>::value_compare of_comp = of1.value_comp();
		typename ft::map<K, T>::value_compare my_comp = my1.value_comp();

		std::pair<K, T> a(10, 234);
		std::pair<K, T> b(10, 234);

		check(my_comp(a, b), of_comp(a, b), "Comp(10, 10)");
		a.first = 5;
		check(my_comp(a, b), of_comp(a, b), "Comp(5, 10)");
		a.first = 144;
		check(my_comp(a, b), of_comp(a, b), "Comp(144, 10)");
	}
}

template <typename K, typename T>
void	check_Operations()
{
	std::cout << "\n##########################################\n\t\tCHECK Operations\n";
	std::cout << "##########################################\n";
	{//find
		std::cout << "find(key_type &k): ";
		
		std::map<K, T> of1;
		ft::map<K, T> my1;

		for(int i = 1; i < 20; ++i)
		{
			of1[i] = i;
			my1[i] = i;
		}

		if ((of1.find(5) == of1.end()) == (my1.find(5) == my1.end()))
			ok();
		else
			error();
		if ((of1.find(30) == of1.end()) == (my1.find(30) == my1.end()))
			ok();
		else
			error();
		if ((of1.find(19) == of1.end()) == (my1.find(19) == my1.end()))
			ok();
		else
			error();
	}
	{//count
		std::cout << "\ncount(): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;

		for(int i = 1; i < 20; ++i)
		{
			of1[i] = i;
			my1[i] = i;
		}
		if (of1.count(5) == my1.count(5))
			ok();
		else
			error();
		if (of1.count(0) == my1.count(0))
			ok();
		else
			error();
		if (of1.count(19) == my1.count(19))
			ok();
		else
			error();
	}
	{//lower_bound
		std::cout << "\nlower_bonder(): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;

		for(int i = 1; i < 20; ++i)
		{
			++i;
			of1[i] = i;
			my1[i] = i;
		}
		typename std::map<K, T>::iterator ofit = of1.lower_bound(-10);
		typename ft::map<K, T>::iterator myit = my1.lower_bound(-10);
		check(myit->second, ofit->second, "lowew_bonder(-10): ");
		ofit = of1.lower_bound(6);
		myit = my1.lower_bound(6);
		check(myit->second, ofit->second, "lowew_bonder(6): ");
		ofit = of1.lower_bound(3);
		myit = my1.lower_bound(3);
		check(myit->second, ofit->second, "lowew_bonder(6): ");
		ofit = of1.lower_bound(60);
		myit = my1.lower_bound(60);
		if ((ofit == of1.end()) == (myit == my1.end()))
			ok();
		else
			error();
	}
	{//upper_bound
		std::cout << "\nupper_bound(): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;

		for(int i = 1; i < 20; ++i)
		{
			++i;
			of1[i] = i;
			my1[i] = i;
		}
		typename std::map<K, T>::iterator ofit = of1.upper_bound(-10);
		typename ft::map<K, T>::iterator myit = my1.upper_bound(-10);
		check(myit->second, ofit->second, "upper_bound(-10): ");
		ofit = of1.upper_bound(6);
		myit = my1.upper_bound(6);
		check(myit->second, ofit->second, "upper_bound(6): ");
		ofit = of1.upper_bound(3);
		myit = my1.upper_bound(3);
		check(myit->second, ofit->second, "upper_bound(6): ");
		ofit = of1.upper_bound(60);
		myit = my1.upper_bound(60);
		if ((ofit == of1.end()) == (myit == my1.end()))
			ok();
		else
			error();
	}
	{//equal_range
		std::cout << "\nequal_range(): ";
		std::map<K, T> of1;
		ft::map<K, T> my1;

		for(int i = 1; i < 20; ++i)
		{
			++i;
			of1[i] = i;
			my1[i] = i;
		}
		typedef typename std::map<K, T>::iterator ofiterator;
		typedef typename ft::map<K, T>::iterator myiterator;

		std::pair<ofiterator, ofiterator> resof = of1.equal_range(5);
		std::pair<myiterator, myiterator> resmy = my1.equal_range(5);
		check((resmy.first)->second,(resof.first)->second, "First iter, equal_range ");
		check((resmy.second)->second,(resof.second)->second, "First iter, equal_range ");

		resof = of1.equal_range(0);
		resmy = my1.equal_range(0);
		check((resmy.first)->second,(resof.first)->second, "First iter, equal_range ");
		check((resmy.second)->second,(resof.second)->second, "First iter, equal_range ");
		
		resof = of1.equal_range(15);
		resmy = my1.equal_range(15);
		check((resmy.first)->second,(resof.first)->second, "First iter, equal_range ");
		check((resmy.second)->second,(resof.second)->second, "First iter, equal_range ");

		resof = of1.equal_range(999);
		resmy = my1.equal_range(999);
		if ((resof.first == of1.end()) == (resmy.first == my1.end()))
			ok();
		else
			error();
		if ((resof.second == of1.end()) == (resmy.second == my1.end()))
			ok();
		else
			error();
	}
}

int     main(void)
{
	std::cout << " ■  ■■  ■ ■■■■■\n";
	std::cout << "| | ■ ■ ■   ■\n";
	std::cout << "| | ■  ■■   ■\n";
	check_cons_des_oper<int, int>();
	check_Iterators<int, int>();
	check_Capacity<char, int>();
	check_Modifiers<int, int>();
	check_Element_access<int, int>();
	check_Observers<int, int>();
	check_Operations<int, int>();
	// std::cout << " ■  ■■  ■ ■■■■■\n";
	// std::cout << "| | ■ ■ ■   ■\n";
	// std::cout << "| | ■  ■■   ■\n";
	// check_cons_des_oper<char, int>();
	// check_Iterators<int, char>();
	// check_Capacity<char, int>();
	// check_Modifiers<int, char>();
	// check_Element_access<char, int>();
	// check_Observers<int, char>();
	// check_Operations<int, int>();
	std::cout << "\n■■■■   ■■ ■■■■■■■■   ■■■     ■■■■■■■■■■■■■\n";
	std::cout << "■■■ ■■■■■ ■■■■■■■ ■■■ ■■ ■■■■ ■■■■■■■■■■■■■\n";
	std::cout << "■■ ■■■■■■    ■■■ ■■■■■ ■ ■■■■ ■■■■■■■■■■■■■■\n";
	std::cout << "■■■ ■■■■■ ■■■ ■■       ■     ■■■■■■■■■■■■\n";
	std::cout << "■■■■   ■■ ■■■ ■■ ■■■■■ ■ ■■■■ ■■■■■■■■■■■■■\n";

	// check_cons_des_oper<char, char>();
	// check_Iterators<char, char>();
	// check_Capacity<char, char>();
	// check_Modifiers<char, char>();
	// check_Element_access<char, char>();
	// check_Observers<char, char>();
	// check_Operations<char, char>();

	// while (1);
}