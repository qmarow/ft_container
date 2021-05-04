#include <list>
#include "list.hpp"

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
void	start_test_reverse_iter()
{
	std::list<T>	of;
	ft::list<T>	my;

	for (int i = 0; i < 10; ++i)
	{
		of.push_back(T(i));
		my.push_back(T(i));
	}

	std::cout << "\nConstruct: ";
	typename std::list<T>::reverse_iterator	begof = of.rbegin();
	typename std::list<T>::reverse_iterator	endof = of.rend();
	typename ft::list<T>::reverse_iterator 	begmy = my.rbegin();
	typename ft::list<T>::reverse_iterator	endmy = my.rend();
	scrolling(begmy, endmy, begof, endof);

	typename std::list<T>::reverse_iterator	begof1;
	typename std::list<T>::reverse_iterator	endof1;
	typename ft::list<T>::reverse_iterator 	begmy1;
	typename ft::list<T>::reverse_iterator	endmy1;

	begof1 = begof;
	endof1 = endof;
	begmy1 = begmy;
	endmy1 = endmy;

	typename std::list<T>::reverse_iterator	begof2(begof);
	typename std::list<T>::reverse_iterator	endof2(endof);
	typename ft::list<T>::reverse_iterator 	begmy2(begmy);
	typename ft::list<T>::reverse_iterator	endmy2(endmy);
	scrolling(begmy2, endmy2, begof2, endof2);

	std::cout << "\noperator != and == : ";
	int errof = 0;
	int errmy = 0;

	if (!(++begof != begof && --begof == begof2))
		errof = 1;
	if (!(++begmy != begmy && --begmy == begmy2))
		errmy = 1;
	if (errof != errmy)
		error();
	else
		ok();
	
	std::cout << "\noperator * : ";
	scrolling(begmy2, endmy2, begof2, endof2);

	std::cout << "\noperator -> : ";
	std::list<std::list<T> >	of5;
	ft::list<ft::list<T> > 		my5;
	for (int i = 0; i < 1; ++i)
	{
		of5.push_back(of);
		my5.push_back(my);
	}

	typename std::list<std::list<T> >::reverse_iterator	begof5 = of5.rbegin();
	typename ft::list<ft::list<T> >::reverse_iterator 	begmy5 = my5.rbegin();

	if (begof5->size() == begmy5->size())
		ok();
	else
		error();

	std::cout << "*iter= : ";
	*begof2 = T(55);
	*begmy2 = T(55);
	check(*begof2, *begmy2, "Test *iter= ");
	{
		std::cout << "\nINC: ";
		typename std::list<T>::reverse_iterator tmpof(begof);
		typename ft::list<T>::reverse_iterator tmpmy(begmy);

		errof = 0;
		if (!(begof++ == tmpof && begmy++ == tmpmy))
			errof = 1;
		if (!(++begof == begof && ++begmy == begmy))
			errof = 1;
		if (errof)
			error();
		else
			ok();
	}
	std::cout << "\n*iter++ :";
	*begof++;
	*begmy++;
	check(*begof, *begmy, "Test *iter++ ");

	{
		std::cout << "\nDEC: ";
		typename std::list<T>::reverse_iterator tmpof(begof);
		typename ft::list<T>::reverse_iterator tmpmy(begmy);

		errof = 0;
		if (!(begof-- == tmpof && begmy-- == tmpmy))
			errof = 1;
		if (!(--begof == begof && --begmy == begmy))
			errof = 1;
		if (errof)
			error();
		else
			ok();
	}
	std::cout << "\n*iter-- :";
	*begof--;
	*begmy--;
	check(*begof, *begmy, "Test *iter-- ");
}

template <typename T>
void	start_test_const_reverse_iter()
{

	std::list<T>	of11;
	ft::list<T>	my11;

	for (int i = 20; i < 90; ++i)
	{
		of11.push_back(T(i));
		my11.push_back(T(i));
	}

	const std::list<T>	of(of11.begin(), of11.end());
	const ft::list<T>		my(my11.begin(), my11.end());

	std::cout << "\nConstruct: ";
	typename std::list<T>::const_reverse_iterator	begof = of.rbegin();
	typename std::list<T>::const_reverse_iterator	endof = of.rend();
	typename ft::list<T>::const_reverse_iterator 	begmy = my.rbegin();
	typename ft::list<T>::const_reverse_iterator	endmy = my.rend();
	scrolling(begmy, endmy, begof, endof);

	typename std::list<T>::const_reverse_iterator	begof1;
	typename std::list<T>::const_reverse_iterator	endof1;
	typename ft::list<T>::const_reverse_iterator 	begmy1;
	typename ft::list<T>::const_reverse_iterator	endmy1;

	begof1 = begof;
	endof1 = endof;
	begmy1 = begmy;
	endmy1 = endmy;


	typename std::list<T>::const_reverse_iterator	begof2(begof);
	typename std::list<T>::const_reverse_iterator	endof2(endof);
	typename ft::list<T>::const_reverse_iterator 	begmy2(begmy);
	typename ft::list<T>::const_reverse_iterator	endmy2(endmy);
	scrolling(begmy2, endmy2, begof2, endof2);

	std::cout << "\noperator != and == : ";
	int errof = 0;
	int errmy = 0;

	if (!(++begof != begof && --begof == begof2))
		errof = 1;
	if (!(++begmy != begmy && --begmy == begmy2))
		errmy = 1;
	if (errof != errmy)
		error();
	else
		ok();
	
	std::cout << "\noperator * : ";
	scrolling(begmy2, endmy2, begof2, endof2);

	std::cout << "\noperator -> : ";
	std::list<std::list<T> >	of5;
	ft::list<ft::list<T> > 		my5;
	for (int i = 0; i < 1; ++i)
	{
		of5.push_back(of11);
		my5.push_back(my11);
	}
	
	const std::list<std::list<T> >	of15(of5.begin(), of5.end());
	const ft::list<ft::list<T> >		my15(my5.begin(), my5.end());

	typename std::list<std::list<T> >::const_reverse_iterator	begof5 = of15.rbegin();
	typename ft::list<ft::list<T> >::const_reverse_iterator 	begmy5 = my15.rbegin();

	if (begof5->size() == begmy5->size())
		ok();
	else
		error();

	
	{
		std::cout << "\nINC: ";
		typename std::list<T>::const_reverse_iterator tmpof(begof);
		typename ft::list<T>::const_reverse_iterator tmpmy(begmy);

		errof = 0;
		if (!(begof++ == tmpof && begmy++ == tmpmy))
			errof = 1;
		if (!(++begof == begof && ++begmy == begmy))
			errof = 1;
		if (errof)
			error();
		else
			ok();
	}
	{
		std::cout << "\nDEC: ";
		typename std::list<T>::const_reverse_iterator tmpof(begof);
		typename ft::list<T>::const_reverse_iterator tmpmy(begmy);

		errof = 0;
		if (!(begof-- == tmpof && begmy-- == tmpmy))
			errof = 1;
		if (!(--begof == begof && --begmy == begmy))
			errof = 1;
		if (errof)
			error();
		else
			ok();
	}
}

template <typename T>
void	start_test_iter()
{
	std::list<T>	of;
	ft::list<T>	my;

	for (int i = 0; i < 10; ++i)
	{
		of.push_back(T(i));
		my.push_back(T(i));
	}

	std::cout << "\nConstruct: ";
	typename std::list<T>::iterator	begof = of.begin();
	typename std::list<T>::iterator	endof = of.end();
	typename ft::list<T>::iterator 	begmy = my.begin();
	typename ft::list<T>::iterator	endmy = my.end();
	scrolling(begmy, endmy, begof, endof);

	typename std::list<T>::iterator	begof1;
	typename std::list<T>::iterator	endof1;
	typename ft::list<T>::iterator 	begmy1;
	typename ft::list<T>::iterator	endmy1;

	begof1 = begof;
	endof1 = endof;
	begmy1 = begmy;
	endmy1 = endmy;

	typename std::list<T>::iterator	begof2(begof);
	typename std::list<T>::iterator	endof2(endof);
	typename ft::list<T>::iterator 	begmy2(begmy);
	typename ft::list<T>::iterator	endmy2(endmy);
	scrolling(begmy2, endmy2, begof2, endof2);

	std::cout << "\noperator != and == : ";
	int errof = 0;
	int errmy = 0;

	if (!(++begof != begof && begof == begof2))
		errof = 1;
	if (!(++begmy != begmy && begmy == begmy2))
		errmy = 1;
	if (errof != errmy)
		error();
	else
		ok();
	
	std::cout << "\noperator * : ";
	scrolling(begmy2, endmy2, begof2, endof2);

	std::cout << "\noperator -> : ";
	std::list<std::list<T> >	of5;
	ft::list<ft::list<T> > 		my5;
	for (int i = 0; i < 1; ++i)
	{
		of5.push_back(of);
		my5.push_back(my);
	}

	typename std::list<std::list<T> >::iterator	begof5 = of5.begin();
	typename ft::list<ft::list<T> >::iterator 	begmy5 = my5.begin();

	if (begof5->size() == begmy5->size())
		ok();
	else
		error();

	std::cout << "*iter= : ";
	*begof2 = T(55);
	*begmy2 = T(55);
	check(*begof2, *begmy2, "Test *iter= ");
	{
		std::cout << "\nINC: ";
		typename std::list<T>::iterator tmpof(begof);
		typename ft::list<T>::iterator tmpmy(begmy);

		errof = 0;
		if (!(begof++ == tmpof && begmy++ == tmpmy))
			errof = 1;
		if (!(++begof == begof && ++begmy == begmy))
			errof = 1;
		if (errof)
			error();
		else
			ok();
	}
	std::cout << "\n*iter++ :";
	*begof++;
	*begmy++;
	check(*begof, *begmy, "Test *iter++ ");

	{
		std::cout << "\nDEC: ";
		typename std::list<T>::iterator tmpof(begof);
		typename ft::list<T>::iterator tmpmy(begmy);

		errof = 0;
		if (!(begof-- == tmpof && begmy-- == tmpmy))
			errof = 1;
		if (!(--begof == begof && --begmy == begmy))
			errof = 1;
		if (errof)
			error();
		else
			ok();
	}
	std::cout << "\n*iter-- :";
	*begof--;
	*begmy--;
	check(*begof, *begmy, "Test *iter-- ");
	// iter + n, n + iter
}

template <typename T>
void	start_test_const_iter()
{

	std::list<T>	of11;
	ft::list<T>	my11;

	for (int i = 20; i < 90; ++i)
	{
		of11.push_back(T(i));
		my11.push_back(T(i));
	}

	const std::list<T>	of(of11.begin(), of11.end());
	const ft::list<T>		my(my11.begin(), my11.end());

	std::cout << "\nConstruct: ";
	typename std::list<T>::const_iterator	begof = of.begin();
	typename std::list<T>::const_iterator	endof = of.end();
	typename ft::list<T>::const_iterator 	begmy = my.begin();
	typename ft::list<T>::const_iterator	endmy = my.end();
	scrolling(begmy, endmy, begof, endof);

	typename std::list<T>::const_iterator	begof1;
	typename std::list<T>::const_iterator	endof1;
	typename ft::list<T>::const_iterator 	begmy1;
	typename ft::list<T>::const_iterator	endmy1;

	begof1 = begof;
	endof1 = endof;
	begmy1 = begmy;
	endmy1 = endmy;


	typename std::list<T>::const_iterator	begof2(begof);
	typename std::list<T>::const_iterator	endof2(endof);
	typename ft::list<T>::const_iterator 	begmy2(begmy);
	typename ft::list<T>::const_iterator	endmy2(endmy);
	scrolling(begmy2, endmy2, begof2, endof2);

	std::cout << "\noperator != and == : ";
	int errof = 0;
	int errmy = 0;

	if (!(++begof != begof  && --begof == begof2))
		errof = 1;
	if (!(++begmy != begmy && --begmy == begmy2))
		errmy = 1;
	if (errof != errmy)
		error();
	else
		ok();
	
	std::cout << "\noperator * : ";
	scrolling(begmy2, endmy2, begof2, endof2);

	std::cout << "\noperator -> : ";
	std::list<std::list<T> >	of5;
	ft::list<ft::list<T> > 		my5;
	for (int i = 0; i < 1; ++i)
	{
		of5.push_back(of11);
		my5.push_back(my11);
	}
	
	const std::list<std::list<T> >	of15(of5.begin(), of5.end());
	const ft::list<ft::list<T> >		my15(my5.begin(), my5.end());

	typename std::list<std::list<T> >::const_iterator	begof5 = of15.begin();
	typename ft::list<ft::list<T> >::const_iterator 	begmy5 = my15.begin();

	if (begof5->size() == begmy5->size())
		ok();
	else
		error();

	
	{
		std::cout << "\nINC: ";
		typename std::list<T>::const_iterator tmpof(begof);
		typename ft::list<T>::const_iterator tmpmy(begmy);

		errof = 0;
		if (!(begof++ == tmpof && begmy++ == tmpmy))
			errof = 1;
		if (!(++begof == begof && ++begmy == begmy))
			errof = 1;
		if (errof)
			error();
		else
			ok();
	}
	{
		std::cout << "\nDEC: ";
		typename std::list<T>::const_iterator tmpof(begof);
		typename ft::list<T>::const_iterator tmpmy(begmy);

		errof = 0;
		if (!(begof-- == tmpof && begmy-- == tmpmy))
			errof = 1;
		if (!(--begof == begof && --begmy == begmy))
			errof = 1;
		if (errof)
			error();
		else
			ok();
	}
}

template <typename T>
void	check_operators()
{	
	std::cout << "\noperator == :";
	{
		std::list<T>		of1;
		ft::list<T>		my1;
		std::list<T>		of2;
		ft::list<T>		my2;

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
		std::list<T>		of1;
		ft::list<T>		my1;
		std::list<T>		of2;
		ft::list<T>		my2;

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
		std::list<T>		of1;
		ft::list<T>		my1;
		std::list<T>		of2;
		ft::list<T>		my2;

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
		std::list<T>		of1;
		ft::list<T>		my1;
		std::list<T>		of2;
		ft::list<T>		my2;

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
		std::list<T>		of1;
		ft::list<T>		my1;
		std::list<T>		of2;
		ft::list<T>		my2;

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
		std::list<T>		of1;
		ft::list<T>		my1;
		std::list<T>		of2;
		ft::list<T>		my2;

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
	std::cout << "########################\n\tIterator\n########################" << std::endl;
	start_test_iter<double>();
	std::cout << "\n########################\n\tConst iterator\n########################\n";
	start_test_const_iter<double>();
	std::cout << "\n########################\n\tReverse iterator\n########################\n";
	start_test_reverse_iter<double>();
	std::cout << "\n########################\n\tConst reverse iterator\n########################\n";
	start_test_const_reverse_iter<double>();

	std::cout << "\n\n########################\n\tOperators\n########################" << std::endl;
	std::cout << "\n\tTest int\n";
	check_operators<int>();
	std::cout << "\n\tTest char\n";
	check_operators<char>();
	std::cout << "\n\tTest int\n";
	check_operators<double>();
	std::cout << "\n\tTest char\n";
	check_operators<float>();
}