#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "iterator.hpp"

namespace ft
{	
	template<typename T, typename Alloc = std::allocator<T> >
	class vector{
		public:
			typedef	T									value_type;
			typedef	Alloc								allocator_type;
			typedef	typename Alloc::reference			reference;
			typedef	typename Alloc::const_reference		const_reference;
			typedef typename Alloc::pointer				pointer;
			typedef typename Alloc::const_pointer		const_pointer;
			typedef ptrdiff_t							difference_type;
			typedef size_t								size_type;

			typedef	IteratorVector<T>						iterator;
			typedef	IteratorVector<const T>					const_iterator;
			typedef	ReversIteratorVector<iterator>			reverse_iterator;
			typedef	ReversIteratorVector<const_iterator>	const_reverse_iterator;

		private:
			pointer 			point; // указатель на выделенную память
			pointer				endPoint; // указатель на конец
			size_type			capasity; // выделенная память
			size_type			countElem; // кол-во элементов 
			allocator_type		alloc;	// некий механизм, с помощью которого будем выделять память
		public:
			// конструкторы vector
			explicit vector (const allocator_type& _alloc = allocator_type())
			{
				this->capasity = 0;
				this->countElem = 0;
				this->alloc = _alloc;
				this->point = NULL;
				this->endPoint = NULL;
			};

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& _alloc = allocator_type()) // создает контейнер из n-ов заполненный val
			{
				this->capasity = 0;
				this->countElem = 0;
				this->alloc = _alloc;
				this->point = NULL;
				this->endPoint = NULL;
				this->assign(n, val);
			};
			
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& _alloc = allocator_type(), char (*)[sizeof(*first)] = NULL)
			{
				this->capasity = 0;
				this->countElem = 0;
				this->alloc = _alloc;
				this->point = NULL;
				this->endPoint = NULL;
				this->assign(first, last);
			};

			vector (const vector& x)
			{
				this->capasity = x.size();
				this->countElem = 0;
				this->alloc = x.alloc;
				this->point = NULL;
				this->endPoint = NULL;
				size_type	length = x.size();

				this->point = this->alloc.allocate(length);
				this->endPoint = this->point;
				for (size_type i  = 0; i < length; ++i)
				{
					this->alloc.construct(this->endPoint, *(x.point + i));
					++this->endPoint;
				}
				this->countElem = length;
			};

			~vector()
			{
				this->clear();
				this->alloc.deallocate(this->point, this->capasity);
			};

			vector& operator= (const vector& x)
			{
				this->point = x.point;
				this->endPoint = x.endPoint;
				this->alloc = x.alloc;
				this->countElem = x.countElem;
				this->capasity = x.capasity;

				return (*this);
			};

			// Iterators:
			iterator begin(){ return (this->point);};
			const_iterator begin() const {return (this->point);};
			iterator end(){return (this->endPoint);};
			const_iterator end() const {return (this->endPoint);};

			reverse_iterator rbegin(){ return (this->end() - 1);};
			const_reverse_iterator rbegin() const {return (this->end() - 1);};
			reverse_iterator rend(){return (this->begin() - 1);};
			const_reverse_iterator rend() const {return (this->begin() - 1);};

			//Capacity:
			size_type	size() const {return (this->countElem);};
			
			size_type	max_size() const
			{
				size_t size1 = (size_t) std::numeric_limits<ptrdiff_t>::max();
				size_t size2 = std::numeric_limits<size_t>::max() / sizeof(value_type);
				if (size1 < size2)
					return (size1);
				return (size2);
			}; // возрващает макс кол-во элементов, которые контейнер может содержать
			
			void		resize (size_t n, value_type val = value_type())
			{
				if ((int)this->countElem > (int)n)
				{
					while (this->countElem != n)
					{
						this->pop_back();
					}
				}
				else
				{
					if ((int)this->countElem < (int)n)
					{
						this->reserve(n);
						while (this->endPoint != this->point + n)
						{
							this->alloc.construct(this->endPoint++, val);
						}
						this->countElem = n;
					}
				}
								
			}; // изменяет размер контейнера на n
			size_type	capacity() const
			{
				return (this->capasity);
			};
			bool		empty() const
			{
				return (this->countElem == 0);
			};
			void		reserve(size_type n)
			{
				if (n > this->capasity)
				{
					this->capasity = n;
					size_type	prevCapacity = this->capasity;
					pointer		prevPoint = this->point;
					size_type	prevCountElem = this->countElem;
					this->point = this->alloc.allocate(this->capasity);
					this->endPoint = this->point;
					for (size_type i = 0; i < prevCountElem; ++i)
					{
						this->alloc.construct(this->endPoint, *(prevPoint + i));
						++this->endPoint;
					}
					this->alloc.deallocate(prevPoint, prevCapacity);
				}
			};

			// Element access
			reference operator[](size_type n)
			{
				return (reference(this->point[n]));
			};
			const_reference operator[] (size_type n) const
			{
				return (*(this->point + n));
			};
			reference at (size_type n)
			{
				std::stringstream error;

				if (this->countElem < n || n < 0)
				{
					error << "vector";
					throw std::out_of_range(error.str());
				}
				return (*(this->point + n));
			};
			const_reference at (size_type n) const
			{
				std::stringstream error;

				if (this->countElem < n || n < 0)
				{
					error << "vector";
					throw std::out_of_range(error.str());
				}
				return (*(this->point + n));
			};
			reference front()
			{
				return (*this->point);
			};
			const_reference front() const
			{
				return (*this->point);
			};
			reference back()
			{
				return (*(this->endPoint - 1));
			};
			const_reference back() const
			{
				return (*(this->endPoint - 1));
			};


			//Modifiers:
			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL)
			{
				size_type	length = last - first;

				while (this->countElem)
					this->pop_back();
				this->reserve(length);
				for (; first != last; ++first)
				{
					this->alloc.construct(this->endPoint, T(*first));
					++this->endPoint;
				}
				this->countElem = length;
			};
			void		assign(size_t n, const value_type& val)
			{	
				while (this->countElem != 0)
					this->pop_back();		
				if (n > this->capasity)
					this->reserve(n);
				for (size_t i = 0; i < n; i++)
				{
					this->alloc.construct(this->endPoint, val);
					this->endPoint++;
				}
				this->countElem = n;
			};
			void		push_back (const value_type& val)
			{
				if (this->countElem == this->capasity)
					this->checkAndResizeCapacity(1);
				this->alloc.construct(this->point + this->countElem, val);
				++this->countElem;
				++this->endPoint;
			};
			void		pop_back()
			{
				--this->endPoint;
				this->alloc.destroy(this->endPoint);
				--this->countElem;
			};	
			iterator	insert(iterator position, const value_type& val)
			{
				this->insert(position, (size_type)1, val);
				return (position);
			};
			
			void		insert(iterator position, size_type n, const value_type& val)
			{
				iterator p(this->point);
				size_type	i = (position - p) + n;
				
				this->reserve(this->countElem + n);
				for (size_type a = this->size() + n - 1; a >= i; --a)
				{
					this->alloc.construct(this->point + a, *(this->point + a - n));
				}
				i = position - p;
				for (size_type a = 0; a < n; ++a)
				{
					this->alloc.construct(this->point + i,  val);
					++i;
				}
				this->countElem += n;
				this->endPoint += n;
			};
			template <class InputIterator>
			void		insert (iterator position, InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL)
			{
				iterator p(this->point);
				size_type	n = last - first;
				size_type	i = (position - p) + n;

				this->reserve(this->countElem + n);
				for (size_type a = this->size() + n - 1; a >= i; --a)
				{
					this->alloc.construct(this->point + a, *(this->point + a - n));
				}
				i = position - p;
				for (size_type a = 0; a < n; ++a)
				{
					this->alloc.construct(this->point + i,  *first);
					++first;
					++i;
				}
				this->countElem += n;
				this->endPoint += n;
			};
			
			iterator	erase (iterator position)
			{
				this->erase(position, position + 1);
				return (position);
			};
			iterator	erase (iterator first, iterator last)
			{
				iterator	tmp = this->begin();
				iterator	end = this->end();
				int i = 0;
	
				for (; tmp != first; tmp++)
					++i;
				if (tmp == end)
					return (tmp);
				while (first != last)
				{
					this->alloc.destroy(this->point + i);
					--this->endPoint;
					++i;
					++first;
				}
				this->endPoint -= end - first;
				while (first != end)
				{
					this->alloc.construct(this->endPoint, *first);
					++first;
					this->endPoint++;
				}
				this->countElem = this->endPoint - this->point;
				return (last);
			};
			void	swap(vector& x)
			{
				size_type		countX = x.countElem;
				size_type		capacityX = x.capasity;
				allocator_type	allocX = x.alloc;
				pointer			pointX = x.point;
				pointer			endPointX = x.endPoint;

				x.countElem = this->countElem;
				x.capasity = this->capasity;
				x.alloc = this->alloc;
				x.point = this->point;
				x.endPoint = this->endPoint;

				this->countElem = countX;
				this->capasity = capacityX;
				this->alloc = allocX;
				this->point = pointX;
				this->endPoint = endPointX;
			};
			void	clear()
			{
				for (size_type i = 0; i < this->countElem; ++i)
				{
					this->alloc.destroy(this->point + i);
					--this->endPoint;
				}
				this->countElem = 0;
			};

			private:
				void	checkAndResizeCapacity(size_type n)
				{
					if (this->countElem + n > this->capasity)
					{
						size_type	prevCapacity = this->capasity;
						if (this->countElem + n == 1 && this->capasity == 0)
							this->capasity = 1;
						else
							this->capasity *= 2;
						pointer		prevPoint = this->point;
						size_type	prevCountElem = this->countElem;
						this->point = this->alloc.allocate(this->capasity);
						this->endPoint = this->point;
						for (size_type i = 0; i < prevCountElem; ++i)
						{
							this->alloc.construct(this->point + i, *(prevPoint + i));
						}
						iterator p(this->point);
						this->endPoint += prevCountElem;
						this->alloc.deallocate(prevPoint, prevCapacity);
					}
				};
	};
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename ft::vector<T>::const_iterator b_lhs = lhs.begin();
		typename ft::vector<T>::const_iterator e_lhs = lhs.end();
		typename ft::vector<T>::const_iterator b_rhs = rhs.begin();
		typename ft::vector<T>::const_iterator e_rhs = rhs.end();
	
		while (1)
		{
			if (b_lhs == e_lhs && b_rhs == e_rhs)
				return true;
			if (b_lhs == e_lhs || b_rhs == e_rhs)
				return false;
			if (*b_lhs != *b_rhs)
				return false;
			++b_rhs;
			++b_lhs;
		}
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (operator==(lhs, rhs))
			return false;
		return true;
	};
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename ft::vector<T>::const_iterator b_lhs = lhs.begin();
		typename ft::vector<T>::const_iterator e_lhs = lhs.end();
		typename ft::vector<T>::const_iterator b_rhs = rhs.begin();
		typename ft::vector<T>::const_iterator e_rhs = rhs.end();

		while (1)
		{
			if (b_lhs == e_lhs && b_rhs == e_rhs)
				return false;
			if (b_lhs == e_lhs || b_rhs == e_rhs)
				return (lhs.size() < rhs.size());
			if (*b_lhs != *b_rhs)
				return (*b_lhs < *b_rhs);
			++b_rhs;
			++b_lhs;
		}
	};
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename ft::vector<T>::const_iterator b_lhs = lhs.begin();
		typename ft::vector<T>::const_iterator e_lhs = lhs.end();
		typename ft::vector<T>::const_iterator b_rhs = rhs.begin();
		typename ft::vector<T>::const_iterator e_rhs = rhs.end();

		while (1)
		{
			if (b_lhs == e_lhs && b_rhs == e_rhs)
				return true;
			if (b_lhs == e_lhs || b_rhs == e_rhs)
				return (lhs.size() < rhs.size());
			if (*b_lhs != *b_rhs)
				return (*b_lhs < *b_rhs);
			++b_rhs;
			++b_lhs;
		}
	};
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename ft::vector<T>::const_iterator b_lhs = lhs.begin();
		typename ft::vector<T>::const_iterator e_lhs = lhs.end();
		typename ft::vector<T>::const_iterator b_rhs = rhs.begin();
		typename ft::vector<T>::const_iterator e_rhs = rhs.end();

		while (1)
		{
			if (b_lhs == e_lhs && b_rhs == e_rhs)
				return false;
			if (b_lhs == e_lhs || b_rhs == e_rhs)
				return (lhs.size() > rhs.size());
			if (*b_lhs != *b_rhs)
				return (*b_lhs > *b_rhs);
			++b_rhs;
			++b_lhs;
		}
	};
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename ft::vector<T>::const_iterator b_lhs = lhs.begin();
		typename ft::vector<T>::const_iterator e_lhs = lhs.end();
		typename ft::vector<T>::const_iterator b_rhs = rhs.begin();
		typename ft::vector<T>::const_iterator e_rhs = rhs.end();

		while (1)
		{
			if (b_lhs == e_lhs && b_rhs == e_rhs)
				return true;
			if (b_lhs == e_lhs || b_rhs == e_rhs)
				return (lhs.size() > rhs.size());
			if (*b_lhs != *b_rhs)
				return (*b_lhs > *b_rhs);
			++b_rhs;
			++b_lhs;
		}
	};
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	};

};



#endif
