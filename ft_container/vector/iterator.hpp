#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

template <typename T>
class IteratorVector: public std::iterator<std::random_access_iterator_tag, T>
{
	public:
			typedef T											value_type;
			typedef ptrdiff_t									difference_type;
			typedef T*											pointer;
			typedef T&											reference;
			typedef typename std::random_access_iterator_tag	iterator_category;
	private:
		pointer		point;		
	public:
		IteratorVector()
		{
			this->point = NULL;
		};
		IteratorVector(pointer _point)
		{
			this->point = _point;
		};
		IteratorVector(IteratorVector const &other)
		{
			this->point = other.point;
		};
		IteratorVector	&operator=(const IteratorVector &other)
		{
			this->point = other.point;
			return (*this);
		};
		~IteratorVector()
		{};
		bool operator==(const IteratorVector &a) const
		{
			return (this->point == a.point);
		};
		bool operator!=(const IteratorVector &a) const
		{
			return (this->point != a.point);
		};
		reference	operator*()
		{
		return (*(this->point));
		}
		pointer operator->()
		{
			return (this->point);
		};
			// *a = t
			// *a++
			// *a--
		IteratorVector	&operator++()
		{
			this->point++;
			return (*this);
		};
		IteratorVector	&operator--()
		{
			this->point--;
			return (*this);
		};
		IteratorVector	operator++(int) // постфиксный инкримент
		{
			IteratorVector a(*this);
			this->point++;
			return (a);
		};
		IteratorVector	operator--(int) // постфиксный декремент
		{
			IteratorVector a(*this);
			this->point--;
			return (a);
		};
		IteratorVector	operator+(difference_type n)
		{
			IteratorVector tmp(*this);
			tmp.point += n;
			return (tmp);
		};
		IteratorVector	operator-(difference_type n)
		{
			IteratorVector	a(*this);
			a.point -= n;
			return (a);
		};
		difference_type	operator-(IteratorVector const &b)
		{
			return (this->point - b.point);
		};
		bool	operator<(IteratorVector const &b)
		{
			return (this->point < b.point);
		};
		bool	operator>(IteratorVector const &b)
		{
			return (this->point > b.point);
		};
		bool	operator<=(IteratorVector const &b)
		{
			return (this->point <= b.point);
		};
		bool	operator>=(IteratorVector const &b)
		{
			return (this->point >= b.point);
		};
		IteratorVector	&operator+=(difference_type n)
		{
			this->point += n;
			return (*this);
		};
		IteratorVector	&operator-=(difference_type n)
		{
			this->point -= n;
			return (*this);
		};
		reference	operator[](difference_type n)
		{
			return (*(this->point + n));
		};
		friend IteratorVector	operator+(difference_type n, IteratorVector const &a)
		{
			IteratorVector tmp(a);
			tmp.point += n;
			return (tmp);
		};
};
template <typename Iterator>
	class ReversIteratorVector
	{
		public:
				typedef Iterator								iterator_type;
                typedef typename Iterator::value_type       	value_type;
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::iterator_category	iterator_category;
		private:
			iterator_type		iter;		
		public:
			ReversIteratorVector(): iter()
			{};
			ReversIteratorVector(iterator_type _iter): iter(_iter)
			{};
			ReversIteratorVector(ReversIteratorVector const &other): iter(other.base())
			{};
            ~ReversIteratorVector()
			{};
			ReversIteratorVector	&operator=(const ReversIteratorVector &other)
			{
				this->iter = other.iter;
				return (*this);
			};
            iterator_type base () const
            {
                return (this->iter);
            };

			bool operator==(const ReversIteratorVector &a) const
			{
				return (this->iter == a.iter);
			};
			bool operator!=(const ReversIteratorVector &a) const
			{
				return (this->iter != a.iter);
			};

			reference	operator*()
			{
				return (*iter);
			}
			pointer operator->()
			{
				return &(operator*());
			};
			// *a = t

			ReversIteratorVector	&operator++()
			{
				--this->iter;
				return (*this);
			};
			ReversIteratorVector	operator--()
			{
				++this->iter;
				return (*this);
			};
			ReversIteratorVector	operator++(int) // постфиксный инкримент
			{
				ReversIteratorVector a(*this);
				--this->iter;
				return (a);
			};
			ReversIteratorVector	operator--(int) // постфиксный декремент
			{
				ReversIteratorVector a(*this);
				++this->iter;
				return (a);
			};
			ReversIteratorVector	operator+(difference_type n)
			{
				ReversIteratorVector tmp(*this);
				tmp.iter -= n;
				return (tmp);
			};
			ReversIteratorVector	operator-(difference_type n)
			{
				ReversIteratorVector	a(*this);
				a.iter += n;
				return (a);
			};
			difference_type	operator-(ReversIteratorVector const &b)
			{
				return (this->iter + b.iter);
			};

			bool	operator<(ReversIteratorVector const &b)
			{
				return (this->iter > b.iter);
			};
			bool	operator>(ReversIteratorVector const &b)
			{
				return (this->iter < b.iter);
			};
			bool	operator<=(ReversIteratorVector const &b)
			{
				return (this->iter >= b.iter);
			};
			bool	operator>=(ReversIteratorVector const &b)
			{
				return (this->iter <= b.iter);
			};

			ReversIteratorVector	&operator+=(difference_type n)
			{
				this->iter -= n;
				return (*this);
			};
			ReversIteratorVector	&operator-=(difference_type n)
			{
				this->iter += n;
				return (*this);
			};
			reference	operator[](difference_type n)
			{
				return (this->iter[-n]);
			};
	};

#endif
