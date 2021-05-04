#include "list.hpp"
#include <list>
#include <iostream>
#include <cmath>

bool mycomparison (double first, double second)
{ return ( int(first)>int(second) ); }

bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

bool	predicat_int(int a)
{
	if (a > 5 || a == 0)
		return true;
	return false;
}

bool	predicat_char(char a)
{
	if (a > '5' || a == '0')
		return true;
	return false;
}

void	error()
{
	std::cout << "\033[31;1;4m❌ERROR❌\033[0m" << std::endl;
	
}

void	ok()
{
	std::cout << "\033[32;4;24m ✓\033[0m" << std::endl;
}

template <typename T>
void	check(T my, T of, std::string text_error)
{
	std::cout << text_error << "of: "<< of << " my: " << my;
	if (my != of)
		return (error());
	else
		ok();
}

template <class T, class M>
void	scrolling(T my, M of)
{
	typename T::iterator my_begin = my.begin();
	typename M::iterator of_begin = of.begin();
	typename T::iterator my_end = my.end();
	typename M::iterator of_end = of.end();

	check(*my_end, *of_end, "  end() ");
	check(*my_begin, *of_begin, "begin() ");
	// std::cout << "\n";
	while ((my_begin != my_end) || (of_begin != of_end))
	{
		++my_begin;
		++of_begin;
		// check(*my_begin, *of_begin, "begin() ");

		if (*my_begin != *of_begin)
		{
			std::cout << "\033[31;1;4m❌ERROR❌\033[0m" << "of - " << *of_begin << " my - " << *my_begin  << std::endl;
			// return ;
		}
	}
	std::cout << "scrolling ";
	ok();
	std::cout << "\n";

}

int		main(void)
{
	std::cout << "**************TEST**************\n";
	ft::list<int> arr;
	std::list<int> of;

	check(arr.empty(), of.empty(), "empty test ");
	check(arr.size(), of.size(), "size test ");
	check(arr.max_size(), of.max_size(), "size test ");

	{
		arr.push_front(1);
		of.push_front(1);
		arr.push_front(2);
		of.push_front(2);
		arr.push_front(3);
		of.push_front(3);
		arr.push_front(9);
		of.push_front(9);

		arr.push_back(5);
		of.push_back(5);
		arr.push_back(6);
		of.push_back(6);
		arr.push_back(7);
		of.push_back(7);
		arr.push_back(8);
		of.push_back(8);
	}

	check(arr.empty(), of.empty(), "empty test ");
	check(arr.max_size(), of.max_size(), "size test ");
	{
		ft::list<int>::iterator my_begin = arr.begin();
		std::list<int>::iterator of_begin = of.begin();
		ft::list<int>::iterator my_end = arr.end();
		std::list<int>::iterator of_end = of.end();

		check(*my_end, *of_end, "end() ");
		check(*my_begin, *of_begin, "begin() ");
		while ((my_begin != my_end) || (of_begin != of_end))
		{
			++my_begin;
			++of_begin;
			check(*my_begin, *of_begin, "++begin() ");
		}
		check(*my_end, *of_end, "end() ");
		--my_end;
		--of_end;
		check(*my_end, *of_end, "--end() ");


	}
	{
		std::cout << "\n\t\tTest operations\n";
		ft::list<int>::iterator my = arr.begin();
		std::list<int>::iterator off = of.begin();

		check(*my, *off, "begin() ");
		++my;
		++off;
		check(*my, *off, "++a ");
		my++;
		off++;
		check(*my, *off, "a++ ");
		--my;
		--off;
		check(*my, *off, "--a ");
		my--;
		off--;
		check(*my, *off, "a-- ");

		ft::list<int>::iterator my_end = arr.end();
		std::list<int>::iterator of_end = of.end();
		check(*my_end, *of_end, "---------- end() ");

	}
	{
		std::cout << "\t\tCHECK pop_front and back_front" << std::endl;
		check(arr.empty(), of.empty(), "empty test ");
		check(arr.size(), of.size(), "size test ");
		{
			arr.pop_front();
			of.pop_front();
			arr.pop_front();
			of.pop_front();
			arr.pop_front();
			of.pop_front();
			arr.pop_front();
			of.pop_front();
			arr.pop_back();
			arr.pop_back();
			arr.pop_back();
			arr.pop_back();
			of.pop_back();
			of.pop_back();
			of.pop_back();
			of.pop_back();
		}
		check(arr.empty(), of.empty(), "empty test ");
		check(arr.size(), of.size(), "size test \n");
		ft::list<int>::iterator my = arr.begin();
		std::list<int>::iterator off = of.begin();
		ft::list<int>::iterator my_end = arr.end();
		std::list<int>::iterator of_end = of.end();
		check(*my, *off, "---------- begin() ");
		check(*my_end, *of_end, "---------- end() ");
		check(arr.size(), of.size(), "size test ");
		check(arr.empty(), of.empty(), "empty test ");
	}
	{
		std::cout << "\n\t\tTest front() back()\n";
		ft::list<std::string> my_string;
		std::list<std::string> of_string;
		ft::list<char> my_char;
		std::list<char> of_char;
		check(arr.front(), of.front(), "front на пустой контейнер(int) ");
		check(arr.back(), of.back(), "back  на пустой контейнер(int) ");
		// check(my_string.front(), of_string.front(), "front на пустой контейнер(string) ");
		// check(my_string.back(), of_string.back(), "back  на пустой контейнер(string) ");
		check(my_char.front(), of_char.front(), "front на пустой контейнер(char) ");
		check(my_char.back(), of_char.back(), "back  на пустой контейнер(char) ");
		for (int i = 0; i < 10; ++i)
		{
			arr.push_back(i);
			of.push_back(i);
			my_char.push_back(i + '0');
			of_char.push_back(i + '0');
		}
		{
			of_string.push_back("0");
			my_string.push_back("0");
			of_string.push_back("1");
			my_string.push_back("1");
			of_string.push_back("2");
			my_string.push_back("2");
			of_string.push_back("3");
			my_string.push_back("3");
			of_string.push_back("4");
			my_string.push_back("4");
			of_string.push_back("5");
			my_string.push_back("5");
			of_string.push_back("6");
			my_string.push_back("6");
			of_string.push_back("7");
			my_string.push_back("7");
			of_string.push_back("8");
			my_string.push_back("8");
			of_string.push_back("9");
			my_string.push_back("9");
		}
		check(arr.front(), of.front(), "front на заполненный контейнер(int) ");
		check(arr.back(), of.back(), "back  на заполненный контейнер(int) ");
		check(my_string.front(), of_string.front(), "front на заполненный контейнер(string) ");
		check(my_string.back(), of_string.back(), "back  на заполненный контейнер(string) ");
		check(my_char.front(), of_char.front(), "front на заполненный контейнер(char) ");
		check(my_char.back(), of_char.back(), "back  на заполненный контейнер(char) ");
	}
	{
		std::cout << "\n\t\tTest Assing\n";
		{
			ft::list<std::string> my_otherS;
			std::list<std::string> of_otherS;
			ft::list<char> my_otherC;
			std::list<char> of_otherC;
			ft::list<int> my_otherI;
			std::list<int> of_otherI;
			ft::list<std::string> my_string;
			std::list<std::string> of_string;
			ft::list<char> my_char;
			std::list<char> of_char;
			ft::list<int> my_int;
			std::list<int> of_int;
			for (int i = 0; i < 8; ++i)
			{
				my_otherI.push_back(i + i);
				of_otherI.push_back(i + i);
				my_otherC.push_back(i + i + '0');
				of_otherC.push_back(i + i+ '0');
			}
			for (int i = 0; i < 5; ++i)
			{
				my_int.push_back(i);
				of_int.push_back(i);
				my_char.push_back(i + '0');
				of_char.push_back(i + '0');
			}
			{
				my_otherS.push_back("a1");
				of_otherS.push_back("a1");
				my_otherS.push_back("b2");
				of_otherS.push_back("b2");
				my_otherS.push_back("c3");
				of_otherS.push_back("c3");
				my_otherS.push_back("d4");
				of_otherS.push_back("d4");
				my_otherS.push_back("e5");
				of_otherS.push_back("e5");
				of_string.push_back("0");
				my_string.push_back("0");
				of_string.push_back("1");
				my_string.push_back("1");
				of_string.push_back("2");
				my_string.push_back("2");
				of_string.push_back("3");
				my_string.push_back("3");
				of_string.push_back("4");
				my_string.push_back("4");
			}
			std::cout << " Assing с своими же интераторами(string)\n";
			my_string.assign(my_string.begin(), my_string.end());
			of_string.assign(of_string.begin(), of_string.end());
			// scrolling(my_string, of_string);
			std::cout << " Assing с итераторами из вне(string)\n";
			my_string.assign(my_otherS.begin(), my_otherS.end());
			of_string.assign(of_otherS.begin(), of_otherS.end());
			// scrolling(my_string, of_string);

			std::cout << " Assing с своими же интераторами(char)\n";
			my_char.assign(my_char.begin(), my_char.end());
			of_char.assign(of_char.begin(), of_char.end());
			scrolling(my_char, of_char);
			std::cout << " Assing с итераторами из вне(char)\n";
			my_char.assign(my_otherC.begin(), my_otherC.end());
			of_char.assign(of_otherC.begin(), of_otherC.end());
			scrolling(my_char, of_char);

			std::cout << " Assing с своими же интераторами(int)\n";
			my_int.assign(my_int.begin(), my_int.end());
			of_int.assign(of_int.begin(), of_int.end());
			scrolling(my_int, of_int);
			std::cout << " Assing с итераторами из вне(int)\n";
			my_int.assign(my_otherI.begin(), my_otherI.end());
			of_int.assign(of_otherI.begin(), of_otherI.end());
			scrolling(my_int, of_int);
		}
		std::cout << "********************\n";
		{
			ft::list<std::string> 	my_str;
			std::list<std::string> 	of_str;
			ft::list<int> 			my_int;
			std::list<int> 			of_int;

		
			my_str.assign(4, "new str");
			of_str.assign(4, "new str");
			std::cout << "\nAssing на пустой контейнер(string) <\n";
			// scrolling(my_str, of_str);
			my_str.assign(10, "String >");
			of_str.assign(10, "String >");
			std::cout << "\nAssing если кол-во елементов(string) >\n";
			// scrolling(my_str, of_str);
			my_str.assign(2, "String <");
			of_str.assign(2, "String <");
			std::cout << "\nAssing если кол-во елементов(string) <\n";
			// scrolling(my_str, of_str);

			my_int.assign(4, 100);
			of_int.assign(4, 100);
			std::cout << "\nAssing на пустой контейнер(int) <\n";
			scrolling(my_int, of_int);
			my_int.assign(10, 999);
			of_int.assign(10, 999);
			std::cout << "\nAssing если кол-во елементов(int) >\n";
			scrolling(my_int, of_int);
			my_int.assign(1, 12345678);
			of_int.assign(1, 12345678);
			std::cout << "\nAssing если кол-во елементов(int) <\n";
			scrolling(my_int, of_int);
		}
	}

	{ //insert
		{
			std::cout << "\n\t\tInsert (position, val)\n";
			std::list<char> of_char;
			ft::list<char> my_char;
			std::list<char> ofС;
			ft::list<char> myС;

			std::cout << "Insert на пустой контенер (начало)\n";
			of_char.insert(of_char.begin(), 'a');
			my_char.insert(my_char.begin(), 'a');
			scrolling(my_char, of_char);
			std::cout << "Insert на пустой контенер (конец)\n";

			ofС.insert(ofС.end(), 'a');
			myС.insert(myС.end(), 'a');
			scrolling(myС, ofС);

			std::cout << "Insert на заполненный контенер(начало)\n";
			for (int i = 0; i < 5; ++i)
			{
				of_char.push_back(i + '0');
				my_char.push_back(i + '0');
			}
			of_char.insert(of_char.begin(), 'a');
			my_char.insert(my_char.begin(), 'a');
			scrolling(my_char, of_char);
			std::cout << "Insert на заполненный контенер(середину)\n";

			std::list<char>::iterator beg = of_char.begin();
			ft::list<char>::iterator my_beg = my_char.begin();
			++beg;
			++beg;
			++my_beg;
			++my_beg;
			of_char.insert(beg, 'b');
			my_char.insert(my_beg, 'b');
			scrolling(my_char, of_char);
			std::cout << "Insert на заполненный контенер(конец)\n";

			of_char.insert(of_char.end(), 'a');
			my_char.insert(my_char.end(), 'a');
			scrolling(my_char, of_char);
		}
		{
			std::cout << "\n\t\tInsert (position, size, val)\n";
			std::list<char> of_char;
			ft::list<char> my_char;
			std::list<char> ofС;
			ft::list<char> myС;

			std::cout << "Insert на пустой контенер (начало)\n";
			of_char.insert(of_char.begin(), 100,'a');
			my_char.insert(my_char.begin(), 100,'a');
			scrolling(my_char, of_char);
			std::cout << "Insert на пустой контенер (конец)\n";

			ofС.insert(ofС.end(), 100, 'a');
			myС.insert(myС.end(), 100, 'a');
			scrolling(myС, ofС);

			std::cout << "Insert на пустой контенер (начало) c кол-ом 0\n";
			of_char.insert(of_char.begin(), 0,'a');
			my_char.insert(my_char.begin(), 0,'a');
			scrolling(my_char, of_char);
			std::cout << "Insert на пустой контенер (конец) с кол-ом 0\n";

			ofС.insert(ofС.end(), 0, 'a');
			myС.insert(myС.end(), 0, 'a');
			scrolling(myС, ofС);

			std::cout << "Insert на заполненный контенер(начало)\n";
			for (int i = 0; i < 5; ++i)
			{
				of_char.push_back(i + '0');
				my_char.push_back(i + '0');
			}
			of_char.insert(of_char.begin(), 1, 'a');
			my_char.insert(my_char.begin(), 1, 'a');
			scrolling(my_char, of_char);
			std::cout << "Insert на заполненный контенер(середину)\n";

			std::list<char>::iterator beg = of_char.begin();
			ft::list<char>::iterator my_beg = my_char.begin();
			++beg;
			++beg;
			++my_beg;
			++my_beg;
			of_char.insert(beg, 500, 'b');
			my_char.insert(my_beg, 500, 'b');
			scrolling(my_char, of_char);
			std::cout << "Insert на заполненный контенер(конец)\n";

			of_char.insert(of_char.end(), 500, 'a');
			my_char.insert(my_char.end(), 500, 'a');
			scrolling(my_char, of_char);
		}
		{
			std::cout << "\n\t\tInsert (position, first, last)\n";
			std::list<char> of_char;
			ft::list<char> my_char;
			std::list<char> ofC;
			ft::list<char> myC;

			std::cout << "Insert на пустой контенер (пустым)V1\n";
			of_char.insert(of_char.begin(), of_char.begin(), of_char.end());
			my_char.insert(my_char.begin(), my_char.begin(), my_char.end());
			scrolling(my_char, of_char);

			std::cout << "Insert на заполненный контенер (пустым)V1\n";
			ofC.insert(ofC.begin(), of_char.begin(), of_char.end());
			myC.insert(myC.begin(), my_char.begin(), my_char.end());
			scrolling(my_char, of_char);
			std::cout << "Insert на пустой контенер (заполненным)V1\n";
			for (int i = 0; i < 5; ++i)
			{
				ofC.push_back(i + '0');
				myC.push_back(i + '0');
			}
			of_char.insert(of_char.begin(), ofC.begin(), ofC.end());
			my_char.insert(my_char.begin(), myC.begin(), myC.end());
			scrolling(my_char, of_char);
			std::cout << "Insert на заполненный контенер (заполненным)\n";

			std::list<char>::iterator beg = of_char.begin();
			ft::list<char>::iterator my_beg = my_char.begin();
			++beg;
			++beg;
			++my_beg;
			++my_beg;
			of_char.insert(beg, ofC.begin(), ofC.end());
			my_char.insert(my_beg, myC.begin(), myC.end());
			scrolling(my_char, of_char);
		}
	}
	{ // erase
		{
			std::cout << "\n\t\tErase (position)\n";
			std::cout << "Erese на начало";

			std::list<char> of_char;
			ft::list<char> my_char;

			for (int i = 0; i < 1; i++)
			{
				of_char.push_back(i + '0');
				my_char.push_back(i + '0');
			}
			std::list<char>::iterator of_res = of_char.erase(of_char.begin());
			ft::list<char>::iterator my_res = my_char.erase(my_char.begin());
			check(*my_res, *of_res, "result erase ");
			scrolling(my_char, of_char);

			std::cout << "Erese на середину\n";
			for (int i = 0; i < 10; i++)
			{
				of_char.push_back(i + '0');
				my_char.push_back(i + '0');
			}
			std::list<char>::iterator beg = of_char.begin();
			ft::list<char>::iterator my_beg = my_char.begin();
			++beg;
			++beg;
			++my_beg;
			++my_beg;
			beg = of_char.erase(beg);
			my_beg = my_char.erase(my_beg);
			check(*my_beg, *beg, "result erase ");
			scrolling(my_char, of_char);
		}
		{
			std::cout << "\n\t\tErase (first, last)\n";
			std::cout << "Erese от начала и до конца\n";

			std::list<char> of_char;
			ft::list<char> my_char;

			for (int i = 0; i < 10; i++)
			{
				of_char.push_back(i + '0');
				my_char.push_back(i + '0');
			}
			std::list<char>::iterator of_res =  of_char.erase(of_char.begin(), of_char.end());
			ft::list<char>::iterator my_res =  my_char.erase(my_char.begin(), my_char.end());
			check(*my_res, *of_res, "Result erase ");
			scrolling(my_char, of_char);

			std::cout << "Erese на середину\n";
			for (int i = 0; i < 10; i++)
			{
				of_char.push_back(i + '0');
				my_char.push_back(i + '0');
			}
			std::list<char>::iterator beg = of_char.begin();
			ft::list<char>::iterator my_beg = my_char.begin();
			++beg;
			++beg;
			++my_beg;
			++my_beg;
			beg = of_char.erase(beg);
			my_beg = my_char.erase(my_beg);
			check(*my_beg, *beg, "Result erase ");
			scrolling(my_char, of_char);
		}
	} // swap
	{
		std::cout << "\n\t\tSwap\n";
		std::list<char> of_char;
		ft::list<char> my_char;
		std::list<char> of_swap;
		ft::list<char> my_swap;

		for (int i = 0; i < 10; i++)
		{
			of_char.push_back(i + '0');
			of_swap.push_back(i + i + '0');
			my_char.push_back(i + '0');
			my_swap.push_back(i + i + '0');
		}
		of_char.swap(of_swap);
		my_char.swap(my_swap);
		scrolling(my_char, of_char);
	}
	{ // resize clear
		{
			std::cout<< "\n\t\t Resize\n";
			ft::list<std::string> my_string;
			std::list<std::string> of_string;
			ft::list<char> my_char;
			std::list<char> of_char;
			ft::list<int> my_int;
			std::list<int> of_int;
			for (int i = 0; i < 10; ++i)
			{
				my_char.push_back(i - 2 + '0');
				of_char.push_back(i - 2 + '0');
				my_int.push_back(i + 10);
				of_int.push_back(i + 10);
			}
			{
				of_string.push_back("0");
				my_string.push_back("0");
				of_string.push_back("1");
				my_string.push_back("1");
				of_string.push_back("2");
				my_string.push_back("2");
				of_string.push_back("3");
				my_string.push_back("3");
				of_string.push_back("4");
				my_string.push_back("4");
				of_string.push_back("5");
				my_string.push_back("5");
				of_string.push_back("6");
				my_string.push_back("6");
				of_string.push_back("7");
				my_string.push_back("7");
				of_string.push_back("8");
				my_string.push_back("8");
				of_string.push_back("9");
				my_string.push_back("9");
			}
			std::cout << "\tCHECK INT\n";
			check(my_int.size(), of_int.size(), "check size ");
			std::cout << "Уменьшаем на половину\n";
			my_int.resize(11);
			of_int.resize(11);
			// scrolling(my_int, of_int);
			check(my_int.size(), of_int.size(), "check size ");
			std::cout << "Уменьшаем до нуля\n";
			my_int.resize(0);
			of_int.resize(0);
			check(of_int.size(), of_int.size(), "check size ");
			// scrolling(of_int, of_int);
			// while (1);

			std::cout << "Увеличиваем с нуля до 10\n";
			my_int.resize(10);
			of_int.resize(10);
			check(my_int.size(), of_int.size(), "check size ");
			// scrolling(my_int, of_int);
			std::cout << "Увеличиваем с 10 до 10000\n";
			my_int.resize(10000);
			of_int.resize(10000);
			check(my_int.size(), of_int.size(), "check size ");
			// scrolling(my_int, of_int);


			std::cout << "\tCHECK CHAR\n";
			check(my_char.size(), of_char.size(), "check size ");
			std::cout << "Уменьшаем на половину\n";
			my_char.resize(5);
			of_char.resize(5);
			check(my_char.size(), of_char.size(), "check size ");
			std::cout << "Уменьшаем до нуля\n";
			my_char.resize(0);
			of_char.resize(0);
			check(my_char.size(), of_char.size(), "check size ");
			std::cout << "Увеличиваем с нуля до 10\n";
			my_char.resize(10);
			of_char.resize(10);
			check(my_char.size(), of_char.size(), "check size ");
			// scrolling(my_char, of_char);
			std::cout << "Увеличиваем с 10 до 10000\n";
			my_char.resize(10000);
			of_char.resize(10000);
			check(my_char.size(), of_char.size(), "check size ");
			// scrolling(my_char, of_char);

			std::cout << "\tCHECK STRING\n";
			check(my_string.size(), of_string.size(), "check size ");
			std::cout << "Уменьшаем на половину\n";
			my_string.resize(5);
			of_string.resize(5);
			check(my_string.size(), of_string.size(), "check size ");
			std::cout << "Уменьшаем до нуля\n";
			my_string.resize(0);
			of_string.resize(0);
			check(my_string.size(), of_string.size(), "check size ");
			std::cout << "Увеличиваем с нуля до 10\n";
			my_string.resize(10);
			of_string.resize(10);
			check(my_string.size(), of_string.size(), "check size ");
			// scrolling(my_string, of_string);
			std::cout << "Увеличиваем с 10 до 10000\n";
			my_string.resize(10000);
			of_string.resize(10000);
			check(my_string.size(), of_string.size(), "check size ");
			// scrolling(my_string, of_string);

			std::cout << "\n\t\tClear\n";
			my_char.clear();
			of_char.clear();
			of_char.push_back('-');
			my_char.push_back('-');
			check(*(my_char.end()), *(of_char.end()), "checking   end ");
			check(*(++(my_char.end())), *(++(of_char.end())), "checking ++end ");

			my_int.clear();
			of_int.clear();
			check(*(my_int.end()), *(of_int.end()), "checking   end ");
			check(*(++(my_int.end())), *(++(of_int.end())), "checking ++end ");
			of_int.push_back(999);
			my_int.push_back(999);
			check(*(my_int.end()), *(of_int.end()), "checking   end ");
			check(*(++(my_int.end())), *(++(of_int.end())), "checking ++end ");
		}
	}
	{
		std::cout<< "\n\t\t Splice\n";
		{
			std::cout<< "\n\t Splice(position, x, i)\n";
			ft::list<char> my_char;
			std::list<char> of_char;
			ft::list<int> my_int;
			std::list<int> of_int;

			ft::list<char> my_xC;
			std::list<char> of_xC;
			ft::list<int> my_xI;
			std::list<int> of_xI;
			for (int i = 0; i < 10; ++i)
			{
				my_char.push_back(i  + '0');
				of_char.push_back(i  + '0');
				my_int.push_back(i + 10);
				of_int.push_back(i + 10);
				my_xC.push_back(i + '0');
				of_xC.push_back(i  + '0');
				my_xI.push_back(i + 33);
				of_xI.push_back(i + 33);
			}
			std::cout << "\tCheck char\n";
			of_char.splice((++(of_char.begin())), of_xC, ++of_xC.begin());
			my_char.splice((++(my_char.begin())), my_xC, ++my_xC.begin());
			scrolling(my_char, of_char);

			of_char.splice((++(of_char.begin())), of_xC, ++of_char.begin());
			my_char.splice((++(my_char.begin())), my_xC, ++my_char.begin());
			scrolling(my_char, of_char);

			std::cout << "\tCheck int\n";
			of_int.splice((++(of_int.begin())), of_xI, ++of_xI.begin());
			my_int.splice((++(my_int.begin())), my_xI, ++my_xI.begin());
			scrolling(my_int, of_int);

			std::cout << "\tCheck int\n";
			of_int.splice((++(of_int.begin())), of_xI, ++of_xI.begin());
			my_int.splice((++(my_int.begin())), my_xI, ++my_xI.begin());
			scrolling(my_int, of_int);

			check(*(my_xI.end()), *(of_xI.end()), "check end X  int container ");
			check(*(my_xI.end()), *(of_xI.end()), "check end X char container ");
		}
		{
			std::cout<< "\n\t Splice(position, x)\n";
			ft::list<char> my_char;
			std::list<char> of_char;
			ft::list<int> my_int;
			std::list<int> of_int;

			ft::list<char> my_xC;
			std::list<char> of_xC;
			ft::list<int> my_xI;
			std::list<int> of_xI;
			for (int i = 0; i < 10; ++i)
			{
				my_char.push_back(i  + '0');
				of_char.push_back(i  + '0');
				my_int.push_back(i + 10);
				of_int.push_back(i + 10);
				my_xC.push_back(i + '0');
				of_xC.push_back(i  + '0');
				my_xI.push_back(i + 33);
				of_xI.push_back(i + 33);
			}
			std::cout << "\tCheck char\n";
			of_char.splice((++(of_char.begin())), of_xC);
			my_char.splice((++(my_char.begin())), my_xC);
			scrolling(my_char, of_char);

			of_char.splice((++(of_char.begin())), of_xC);
			my_char.splice((++(my_char.begin())), my_xC);
			scrolling(my_char, of_char);

			std::cout << "\tCheck int\n";
			of_int.splice((++(of_int.begin())), of_xI);
			my_int.splice((++(my_int.begin())), my_xI);
			scrolling(my_int, of_int);

			of_int.splice((++(of_int.begin())), of_xI);
			my_int.splice((++(my_int.begin())), my_xI);
			scrolling(my_int, of_int);

			check(*(my_xI.end()), *(of_xI.end()), "check end X  int container ");
			check(*(my_xI.end()), *(of_xI.end()), "check end X char container ");

		}
		{
			std::cout<< "\n\t Splice(position, x, first, last)\n";
			ft::list<char> my_char;
			std::list<char> of_char;
			ft::list<int> my_int;
			std::list<int> of_int;

			ft::list<char> my_xC;
			std::list<char> of_xC;
			ft::list<int> my_xI;
			std::list<int> of_xI;
			for (int i = 0; i < 10; ++i)
			{
				my_char.push_back(i  + '0');
				of_char.push_back(i  + '0');
				my_int.push_back(i + 10);
				of_int.push_back(i + 10);
				my_xC.push_back(i + '0');
				of_xC.push_back(i  + '0');
				my_xI.push_back(i);
				of_xI.push_back(i);
			}
			std::cout << "\tCheck Int\n";
			of_int.splice((++(of_int.begin())), of_xI, ++of_xI.begin(), of_xI.end());
			my_int.splice((++(my_int.begin())), my_xI, ++my_xI.begin(), my_xI.end());
			scrolling(my_int, of_int);
			check(*(my_xI.end()), *(of_xI.end()), "check end X char container ");
			scrolling(my_xI, of_xI);

			of_int.splice((++(of_int.begin())), of_xI, of_xI.begin(), of_xI.end());
			my_int.splice((++(my_int.begin())), my_xI, my_xI.begin(), my_xI.end());
			// scrolling(my_int, of_int);

			of_int.splice((++(of_int.begin())), of_xI, of_xI.begin(), of_xI.end());
			my_int.splice((++(my_int.begin())), my_xI, my_xI.begin(), my_xI.end());
			scrolling(my_int, of_int);

			check(*(my_xI.end()), *(of_xI.end()), "check end X  int container ");

			std::cout << "\tCheck char\n";

			of_char.splice((++(of_char.begin())), of_xC, ++of_char.begin());
			my_char.splice((++(my_char.begin())), my_xC, ++my_char.begin());
			scrolling(my_char, of_char);

			check(*(my_xC.end()), *(of_xC.end()), "check end X char container ");
		}
	
	}
	{ // remove
		{
			std::cout<< "\n\t Remove(val)\n";
			ft::list<char> my_char;
			std::list<char> of_char;

			// for (int i = 0; i < 10; ++i)
			// {
			// 	my_char.push_back(i  + '0');
			// 	of_char.push_back(i  + '0');
			// 	my_int.push_back(i + 10);
			// 	of_int.push_back(i + 10);
			// }
			// for (int i = 0; i < 10; ++i)
			// {
			// 	my_char.push_back(i  + '0');
			// 	of_char.push_back(i  + '0');
			// 	my_int.push_back(i + 10);
			// 	of_int.push_back(i + 10);
			// }
			
			for (int i = 0; i < 10; ++i)
			{
				my_char.push_back('0');
				of_char.push_back('0');
			}
			check(my_char.size(), of_char.size(), "Check size: ");
			my_char.remove('1');
			of_char.remove('1');
			scrolling(my_char, of_char);
			
			check(my_char.size(), of_char.size(), "Check size: ");
			my_char.remove('0');
			of_char.remove('0');
			check(my_char.size(), of_char.size(), "Check size: ");
			scrolling(my_char, of_char);
		}
	}
	{ //remove_if
		std::cout<< "\n\t Remove_if(predicat)\n";
		{
			ft::list<char> my_char;
			std::list<char> of_char;
			ft::list<int> my_int;
			std::list<int> of_int;

			for (int i = 0; i < 10; ++i)
			{
				my_char.push_back(i  + '0');
				of_char.push_back(i  + '0');
				my_int.push_back(i + 10);
				of_int.push_back(i + 10);
			}
			for (int i = 0; i < 10; ++i)
			{
				my_char.push_back(i  + '0');
				of_char.push_back(i  + '0');
				my_int.push_back(i + 10);
				of_int.push_back(i + 10);
			}
			
			for (int i = 0; i < 10; ++i)
			{
				my_char.push_back('0');
				of_char.push_back('0');
			}
			check(my_char.size(), of_char.size(), "Check size: ");
			// bool	(*pr_ch)(char) = predicat_char;
			// bool	(*pr_int)(int) = predicat_int;
			my_char.remove_if(&predicat_char);
			of_char.remove_if(&predicat_char);
			scrolling(my_char, of_char);
			check(my_char.size(), of_char.size(), "Check size: ");

			my_int.remove_if(&predicat_int);
			of_int.remove_if(&predicat_int);
			check(my_int.size(), of_int.size(), "Check size: ");
			scrolling(my_int, of_int);
		}
	// }
	{
		std::cout << "\n\t\tUnique\n";
		ft::list<char> my_char;
		std::list<char> of_char;

		for (int i = 0; i < 10; ++i)
		{
			my_char.push_back(i  + '0');
			of_char.push_back(i  + '0');
			my_char.push_back(i  + '0' + 1);
			of_char.push_back(i  + '0' + 1);
			// my_int.push_back(i + 10);
			// of_int.push_back(i + 10);
		}
		// for (int i = 0; i < 10; ++i)
		// {
		// 	my_char.push_back(i  + '0');
		// 	of_char.push_back(i  + '0');
		// 	// my_int.push_back(i + 10);
		// 	// of_int.push_back(i + 10);
		// }
		for (int i = 0; i < 10; ++i)
		{
			my_char.push_back('0');
			of_char.push_back('0');
		}
		of_char.unique();
		my_char.unique();
		scrolling(my_char, of_char);

		of_char.unique();
		my_char.unique();
		scrolling(my_char, of_char);
	}
	{
		std::cout << "\n\t\tUnique\n";
		ft::list<double> my_d;
		std::list<double> of_d;

		for (int i = 0; i < 10; i++)
		{
			my_d.push_back(i);
			of_d.push_back(i);
			my_d.push_back(i);
			of_d.push_back(i);
		}

		my_d.unique(same_integral_part);
		of_d.unique(same_integral_part);
		scrolling(my_d, of_d);

		my_d.unique(is_near());
		of_d.unique(is_near());
		scrolling(my_d, of_d);

	}}
	{ // Merge
		ft::list<char> my_char;
		std::list<char> of_char;
		ft::list<char> my_oC;
		std::list<char> of_oC;

		for (int i = 0; i < 3; ++i)
		{
			// if (i == 5 || i == 3)
			// {
				my_char.push_back(i  + '0' + 5);
				of_char.push_back(i  + '0' + 5);
			// }
			my_char.push_back(i  + '0' + 2);
			of_char.push_back(i  + '0' + 2);
			my_oC.push_back(i  + '0');
			of_oC.push_back(i  + '0');
			// my_int.push_back(i + 10);
			// of_int.push_back(i + 10);
		}
		// scrolling(of_oC, of_oC);

		of_char.merge(of_oC);
		my_char.merge(my_oC);
		scrolling(my_char, of_char);
		scrolling(my_oC, of_oC);
	}
	{
		std::cout << "Merge(second, comp)\n";
		ft::list<double> my_char;
		std::list<double> of_char;
		ft::list<double> my_oC;
		std::list<double> of_oC;

		for (int i = 0; i < 3; ++i)
		{
			// if (i == 5 || i == 3)
			// {
				my_char.push_back(i + (i / 10));
				of_char.push_back(i + (i / 10));
			// }
			my_char.push_back(i + (i / 10));
			of_char.push_back(i + (i / 10));
			my_oC.push_back(i + (i / 10));
			of_oC.push_back(i + (i / 10));
			// my_int.push_back(i + 10);
			// of_int.push_back(i + 10);
		}
		my_char.merge(my_oC, mycomparison);
		of_char.merge(of_oC, mycomparison);
		scrolling(my_char, of_char);
		scrolling(my_oC, of_oC);

		my_char.merge(my_char, mycomparison);
		of_char.merge(of_char, mycomparison);

		scrolling(my_char, of_char);
	}
	{ // sort
		std::cout << "\tSort()\n";
		ft::list<char> my_char;
		std::list<char> of_char;
		ft::list<char> my_oC;
		std::list<char> of_oC;

		for (int i = 0; i < 3; ++i)
		{
			// if (i == 5 || i == 3)
			// {
				my_char.push_back(i  + '0' + 5);
				of_char.push_back(i  + '0' + 5);
			// }
			my_char.push_back(i  + '0');
			of_char.push_back(i  + '0');
			my_oC.push_back(i  + '0');
			of_oC.push_back(i  + '0');
			// my_int.push_back(i + 10);
			// of_int.push_back(i + 10);
		}
		my_char.sort();
		of_char.sort();
		scrolling(my_char, of_char);

		std::cout << "\tSort(comp)\n";

		std::list<int> of_int;
		ft::list<int> my_int;

		for(int i = 0; i < 5; ++i)
		{
			of_int.push_back(i - (i * 2));
			my_int.push_back(i - (i * 2));

			of_int.push_back(i);
			my_int.push_back(i);

		}
		of_int.sort(mycomparison);
		my_int.sort(mycomparison);

		scrolling(my_int, of_int);
		std::cout << "\tRevers()\n";
		
		of_int.reverse();
		my_int.reverse();

		scrolling(my_int, of_int);
		
	}
	{ // Swap(x,y)
		std::cout << "\tSwap(x, y)\n";
		ft::list<char> my_char;
		std::list<char> of_char;
		ft::list<char> my_oC;
		std::list<char> of_oC;

		for (int i = 0; i < 3; ++i)
		{

			my_char.push_back(i  + '0' + 5);
			of_char.push_back(i  + '0' + 5);
			my_oC.push_back(i  + '0');
			of_oC.push_back(i  + '0');
		}

		std::swap(of_char, of_oC);
		ft::swap(my_char, my_oC);

		scrolling(my_char, of_char);
		scrolling(my_oC, of_oC);
	}
	{ // operator = 
		std::cout << "\n\t\tOperator =\n";
		ft::list<char> my_char;
		std::list<char> of_char;

		for (int i = 0; i < 3; ++i)
		{

			my_char.push_back(i  + '0' + 5);
			of_char.push_back(i  + '0' + 5);
		}
		ft::list<char> my_oC = my_char;
		std::list<char> of_oC = of_char;
		scrolling(my_oC, of_oC);

		ft::list<char> my_oCV1;
		std::list<char> of_oCV1;
		my_oCV1 = my_char;
		of_oCV1 = of_char;
		for (int i = 0; i < 3; ++i)
		{
			my_oC.push_back(i  + '0');
			of_oC.push_back(i  + '0');
		}
		my_oC = my_char;
		of_oC = of_char;
		scrolling(my_oC, of_oC);
	}
}
