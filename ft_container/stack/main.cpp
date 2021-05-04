#include <iostream>       // std::cout
#include <stack>          // std::stack
#include "stack.hpp"
#include <vector>

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
		std::vector<int> myvector (1,200);
		for (int i = 0; i < 10; i++)
			myvector.push_back(i);
		std::stack<int>	of_s;
		ft::stack<int>	my_s;
		std::stack<int, std::vector<int> >	of_sv(myvector);
		ft::stack<int, std::vector<int> >	my_sv(myvector);

		std::cout << "empty:";
		check(my_s.empty(), of_s.empty(), "Test empty() ");
		check(my_sv.empty(), of_sv.empty(), "Test empty() ");
		std::cout << "\nsize: ";
		check(my_s.size(), of_s.size(), "Test empty() ");
		check(my_sv.size(), of_sv.size(), "Test empty() ");

		std::cout << "\ntop:   ";
		check(my_sv.top(), of_sv.top(), "Test top(1) ");

		std::cout << "\npush_back:";
		of_s.push(199);
		my_s.push(199);
		of_s.push(50);
		my_s.push(50);
		check(my_s.top(), of_s.top(), "Test push ");

		std::cout << "\npop_back: ";
		of_s.pop();
		my_s.pop();
		check(my_s.size(), of_s.size(), "Test pop ");
		std::cout << "\n";
	}
	{
		std::stack<int, std::vector<int> >	of_s;
		ft::stack<int, std::vector<int> >	my_s;
		for (int i = 0; i < 10; i++)
		{
			of_s.push(i);
			my_s.push(i);
		}
		std::cout << "operator == :";
		{
			std::stack<int, std::vector<int> >	of_sv;
			ft::stack<int, std::vector<int> >	my_sv;
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
			std::stack<int, std::vector<int> >	of_sv;
			ft::stack<int, std::vector<int> >	my_sv;
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
			std::stack<int, std::vector<int> >	of_sv;
			ft::stack<int, std::vector<int> >	my_sv;
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
			std::stack<int, std::vector<int> >	of_sv;
			ft::stack<int, std::vector<int> >	my_sv;
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
			std::stack<int, std::vector<int> >	of_sv;
			ft::stack<int, std::vector<int> >	my_sv;
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
			std::stack<int, std::vector<int> >	of_sv;
			ft::stack<int, std::vector<int> >	my_sv;
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