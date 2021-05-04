#include <iostream>       // std::cout
#include <queue>          // std::queue
#include "queue.hpp"
#include <list>

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
		std::cout << text_error << "of: "<< (int)of << " my: " << (int)my;
		return (error());
	}
	else
		ok();
}

int main ()
{
	{
		std::list<int> list (10,200);
		for (int i = 0; i < 10; i++)
			list.push_back(i);
		std::queue<int>	of_s;
		ft::queue<int>	my_s;
		std::queue<int, std::list<int> >	of_sv(list);
		ft::queue<int, std::list<int> >		my_sv(list);

		std::cout << "empty:";
		check(my_s.empty(), of_s.empty(), "Test empty() ");
		check(my_sv.empty(), of_sv.empty(), "Test empty() ");
		std::cout << "\nsize: ";
		check(my_s.size(), of_s.size(), "Test empty() ");
		check(my_sv.size(), of_sv.size(), "Test empty() ");

		std::cout << "\nfront:   ";
		check(my_sv.front(), of_sv.front(), "Test top(1) ");
		of_sv.pop();
		my_sv.pop();
		check(my_sv.front(), of_sv.front(), "Test top(1) ");

		std::cout << "\nback:   ";
		check(my_sv.back(), of_sv.back(), "Test top(1) ");
		of_sv.pop();
		my_sv.pop();
		check(my_sv.back(), of_sv.back(), "Test top(1) ");

		std::cout << "\npush:";
		of_s.push(199);
		my_s.push(199);
		check(my_s.back(), of_s.back(), "Test push ");

		std::cout << "\npop: ";
		of_s.pop();
		my_s.pop();
		check(my_s.size(), of_s.size(), "Test pop ");
		std::cout << "\n";
	}
	{
		std::queue<int, std::list<int> >	of_s;
		ft::queue<int, std::list<int> >	my_s;
		for (int i = 0; i < 10; i++)
		{
			of_s.push(i);
			my_s.push(i);
		}
		std::cout << "operator == :";
		{
			std::queue<int, std::list<int> >	of_sv;
			ft::queue<int, std::list<int> >	my_sv;
			check((my_s == my_sv), (of_s == of_sv), "Test == (!=): ");

			for (int i = 0; i < 10; i++)
			{
				of_sv.push(i);
				my_sv.push(i);
			}
			check((my_s == my_sv), (of_s == of_sv), "Test == (==): ");
		}
		std::cout << "\noperator != :";
		{
			std::queue<int, std::list<int> >	of_sv;
			ft::queue<int, std::list<int> >	my_sv;
			check((my_s != my_sv), (of_s != of_sv), "Test != (!=): ");

			for (int i = 0; i < 10; i++)
			{
				of_sv.push(i);
				my_sv.push(i);
			}
			check((my_s != my_sv), (of_s != of_sv), "Test == (==): ");
		}
		std::cout << "\noperator >  :";
		{
			std::queue<int, std::list<int> >	of_sv;
			ft::queue<int, std::list<int> >	my_sv;
			check((my_s > my_sv), (of_s > of_sv), "Test > (!=): ");

			for (int i = 0; i < 10; i++)
			{
				of_sv.push(i);
				my_sv.push(i);
			}
			check((my_s > my_sv), (of_s > of_sv), "Test > (==): ");
		}
		std::cout << "\noperator >= :";
		{
			std::queue<int, std::list<int> >	of_sv;
			ft::queue<int, std::list<int> >	my_sv;
			check((my_s >= my_sv), (of_s >= of_sv), "Test >= (!=): ");

			for (int i = 0; i < 10; i++)
			{
				of_sv.push(i);
				my_sv.push(i);
			}
			check((my_s >= my_sv), (of_s >= of_sv), "Test >= (==): ");
		}
		std::cout << "\noperator <  :";
		{
			std::queue<int, std::list<int> >	of_sv;
			ft::queue<int, std::list<int> >	my_sv;
			check((my_s < my_sv), (of_s < of_sv), "Test < (!=): ");

			for (int i = 0; i < 10; i++)
			{
				of_sv.push(i);
				my_sv.push(i);
			}
			check((my_s < my_sv), (of_s < of_sv), "Test < (==): ");
		}
		std::cout << "\noperator <= :";
		{
			std::queue<int, std::list<int> >	of_sv;
			ft::queue<int, std::list<int> >	my_sv;
			check((my_s <= my_sv), (of_s <= of_sv), "Test <= (!=): ");

			for (int i = 0; i < 10; i++)
			{
				of_sv.push(i);
				my_sv.push(i);
			}
			check((my_s <= my_sv), (of_s <= of_sv), "Test <= (==): ");
			std::cout << "\n";
		}

	}
	return 0;
}