#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "node.hpp"
#include "iterator.hpp"

// #include "../iterator/iterator.hpp"

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class list
	{
		public:
			typedef	T									value_type;
			typedef	Alloc								allocator_type;
			typedef	typename Alloc::reference			reference;
			typedef	typename Alloc::const_reference		const_reference;
			typedef typename Alloc::pointer				pointer;
			typedef typename Alloc::const_pointer		const_pointer;
			typedef ptrdiff_t							difference_type;
			typedef size_t								size_type;

			typedef	iteratorList<T>							iterator;
			typedef	constIteratorList<T>					const_iterator;
			typedef	reverse_iterator<iterator>				reverse_iterator;
			typedef	const_reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			typedef	typename std::allocator<_node<T> > nodeAlloc_type;
			nodeAlloc_type		nodeAlloc;
			allocator_type		alloc;
			_node<T>			*_end;
			size_type			countNode;
		public:
			// конструкторы list
			explicit list (const allocator_type& _alloc = allocator_type())
			{
				this->alloc = _alloc;
				this->_end = newNode(T());
				this->countNode = 0;
			};
			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& _alloc = allocator_type()) // создает контейнер из n-ов заполненный val
			{
				this->alloc = _alloc;

				this->_end = newNode(T());
				this->countNode = 0;
				this->assign(n, val);
			};			
			template <class InputIterator>
			list (InputIterator first, InputIterator last, const allocator_type& _alloc = allocator_type())
			{
				this->alloc = _alloc;

				this->_end = newNode(T());
				this->countNode = 0;
				this->assign(first, last);
			};
			list (const list& x)
			{
				this->_end = newNode(T());
				this->countNode = 0;
				this->alloc = x.alloc;
				this->nodeAlloc = x.nodeAlloc;
				this->assign(x.begin(), x.end());
			};
			~list()
			{
				while (this->countNode)
					pop_back();
				this->_delete(this->_end);
			};
			list& operator= (const list& x)
			{
				this->clear();
				// this->pop_back();
				// this->_end = newNode(T());
				this->countNode = 0;
				this->alloc = x.alloc;
				this->nodeAlloc = x.nodeAlloc;
				this->assign(x.begin(), x.end());
				return (*this);
			};

			// Iterators:
			iterator begin(){ return (this->_end->next);};
			const_iterator begin() const {return (this->_end->next);};
			iterator end(){return (this->_end);};
			const_iterator end() const {
				const_iterator it (this->_end);
				return (it);
				};
			reverse_iterator rbegin(){return (reverse_iterator (--this->end()));};
			const_reverse_iterator rbegin() const{return (const_reverse_iterator (--this->end()));};
			reverse_iterator rend(){return (reverse_iterator (this->end()));};
			const_reverse_iterator rend() const{return (const_reverse_iterator (this->end()));};

			//Capacity:
			bool empty() const{ return (this->countNode == 0);};
			size_type size() const{ return (this->countNode);};
			size_type max_size() const{ return (this->nodeAlloc.max_size());};
			
			//Element access
			reference front(){ return (this->_end->next->elem);}; // возвращает прямую ссылку на элемент контейнера, в отличие от begin(), который возвращает итератор
			const_reference front() const{ return (this->_end->next->elem);};
			reference back(){ return (this->_end->prev->elem);}; // возвращает прямую ссылку на элемент контейнера, в отличие от begin(), который возвращает итератор
			const_reference back() const{ return (this->_end->prev->elem);};
			
			//Modifiers:
			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last, char [sizeof(*first)] = NULL)
			{
				_node<T> *start = this->_end->next;
				
				while (first != last && start != this->_end)
				{
					start->elem = *first;
					++first;
					start = start->next;
				}
				if (start == this->_end)
				{
					while (first != last)
					{
						this->push_back(*first);
						++first;
					}
				}
				else
				{
					while (start->next != this->_end)
					{
						this->pop_back();
					}
				}

			};
			void assign (size_type n, const value_type& val)
			{
				_node<T> *start = this->_end->next;
				size_type		i = 0;

				while (i < n && start != this->_end)
				{
					start->elem = val;
					start = start->next;
					++i;
				}
				if (i < n)
					while (i < n && ++i)
						this->push_back(val);
				else
					while (n != this->countNode)
						this->pop_back();
			};
			void	push_front(const value_type& val)
			{
				_node<T> *tmp = newNode(val);

				++this->countNode;
				if (this->countNode == 0)
				{
					tmp->next = this->_end;
					tmp->prev = this->_end;
					this->_end->next = tmp;
					this->_end->prev = tmp;
					*reinterpret_cast<int*>(&this->_end->elem) += 1;
				}
				else
				{
					this->_end->next->prev = tmp;
					tmp->prev = this->_end;
					tmp->next = this->_end->next;
					this->_end->next = tmp;
					*reinterpret_cast<int*>(&this->_end->elem) += 1;
				}
			};			
			void	pop_front()
			{
				if (this->countNode)
					--this->countNode;
				this->_end->next->next->prev = this->_end;
				_node<T> *copy_nx_end = this->_end->next;
				this->_end->next = this->_end->next->next;
				*reinterpret_cast<int*>(&this->_end->elem) -= 1;
				this->_delete(copy_nx_end);
			};
			void	push_back(const value_type& val)
			{
				_node<T> *tmp = newNode(val);

				++this->countNode;
				if (countNode == 1)
				{
					tmp->next = this->_end;
					tmp->prev = this->_end;
					this->_end->next = tmp;
					this->_end->prev = tmp;
					*reinterpret_cast<int*>(&this->_end->elem) += 1;
				}
				else
				{
					this->_end->prev->next = tmp;
					tmp->prev = this->_end->prev;
					tmp->next = this->_end;
					this->_end->prev = tmp;
					*reinterpret_cast<int*>(&this->_end->elem) += 1;
				}
			};
			void	pop_back()
			{
				if (this->countNode)
					--this->countNode;
				_node<T> *copy_pr_end = this->_end->prev;
				this->_end->prev->prev->next = this->_end;
				this->_end->prev = this->_end->prev->prev;
				*reinterpret_cast<int*>(&this->_end->elem) -= 1;
				this->_delete(copy_pr_end);
			};
			iterator insert (iterator position, const value_type& val)
			{
				_node<T> *start = this->_end->next;
				iterator iter(start);

				while (iter != position)
				{
					start = start->next;
					++iter;
				}
				if (iter == this->_end)
				{
					this->push_back(val);
					return (iter);
				}
				_node<T> *node = this->newNode(val);
				node->prev = start->prev;
				start->prev->next = node;
				start->prev = node;
				node->next = start;
				node->elem = val;
				*reinterpret_cast<int*>(&this->_end->elem) += 1;
				++this->countNode;
				return (iter);
			};
			void insert (iterator position, size_type n, const value_type& val)
			{
				while (n--)
					this->insert(position, val);
			};
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL)
			{
				while (first != last)
				{
					this->insert(position, *first);
					++first;
				}
			};
			iterator erase (iterator position)
			{
				_node<T> *start = this->_end->next;
				iterator iter(start);

				*reinterpret_cast<int*>(&this->_end->elem) -= 1;
				--this->countNode;
				while (iter != position)
				{
					start = start->next;
					++iter;
				}
				if (start == this->_end)
				{
					this->_delete(start);
					this->pop_back();
					return (++iter);
				}
				start->prev->next = start->next;
				start->next->prev = start->prev;
				++iter;
				this->_delete(start);
				return (iter);
			};
			iterator erase (iterator first, iterator last)
			{
				while (first != last)
				{
					first = this->erase(first);
				}
				return (first);
			};
			void swap (list& x)
			{
				_node<T> *x_end = x._end;
				size_type x_countNode = x.countNode;
				nodeAlloc_type x_nodeAlloc = x.nodeAlloc;

				x._end = this->_end;
				x.countNode = this->countNode;
				x.nodeAlloc = this->nodeAlloc;
				this->_end = x_end;
				this->countNode = x_countNode;
				this->nodeAlloc = x_nodeAlloc;
			};
			void resize (size_type n, value_type val = value_type())
			{
				if (n > this->countNode)
					while (n > this->countNode)
						this->push_back(val);
				else
					while (n < this->countNode)
						this->pop_back();
			};
			void clear()
			{
				while (this->countNode)
					pop_back();
			};

			// Operations
			void splice (iterator position, list& x)
			{
				iterator iter = x.begin();
				iterator iter_end = x.end();

				while (iter != iter_end)
				{
					this->insert(position, *iter);
					++iter;
				}
				x.clear();
			};
			void splice (iterator position, list& x, iterator i)
			{
				iterator iter = x.begin();
				iterator iter_end = x.end();

				while (iter != iter_end)
				{
					if (iter == i)
					{

						this->insert(position, *i);
						x.erase(i);
						return ;
					}
					++iter;
				}
			};
			void splice (iterator position, list& x, iterator first, iterator last)
			{
				iterator 	iter = x.begin();
				iterator 	iter_end = x.end();
				iterator	cpy_first = first;

				// std::cout << "cpy - " << *cpy_first << std::endl;
				int a = 0;

				while (iter != iter_end)
				{
					if (iter == first)
					{
						++a;
						this->insert(position, *first);
						++first;
					}
					++iter;
				}
				while (cpy_first != last)
				{
					// std::cout << "size - " << x.size() << "\niter - " << *cpy_first << "\n";
					cpy_first = x.erase(cpy_first);
					// std::cout << "size - " << x.size() << "\niter - " << *cpy_first << "\n";
					// ++cpy_first;
				}
			};
			void remove (const value_type& val)
			{
				iterator begin = this->begin();
				iterator end = this->end();

				while (begin != end)
				{
					if (*begin == val)
						begin = this->erase(begin);
					else
						++begin;
				}
			};
			template <class Predicate>
			void remove_if (Predicate pred)
			{
				iterator begin = this->begin();
				iterator end = this->end();

				while (begin != end)
				{
					if (pred(*begin))
						begin = this->erase(begin);
					else
						++begin;
				}
			};
			void unique()
			{
				iterator	begin = ++this->begin(); // начианем с второго эл-та
				iterator	end = this->end();
				value_type	val = this->_end->next->elem;

				while (begin != end) 
				{
					if (*begin == val)
						begin = this->erase(begin);
					else
					{
						val = *begin;
						++begin;
					}
				}
			};
			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred)
			{
				iterator	begin = ++this->begin(); // начианем с второго эл-та
				iterator	end = this->end();
				value_type	val = this->_end->next->elem;

				while (begin != end) 
				{
					if (binary_pred(*begin, val))
						begin = this->erase(begin);
					else
					{
						val = *begin;
						++begin;
					}
				}
			};
			void merge (list& x)
			{
				iterator begin = this->begin();
				iterator end = this->_end;
				iterator xbegin = x._end->next;
				iterator xend = x._end;

				if (*this == x)
					return ;
				while (begin != end && xbegin != xend)
				{
					if (*xbegin < *begin)
					{
						this->insert(begin, *xbegin);
						xbegin = x.erase(xbegin);
					}
					else
						++begin;
				}
				while (xbegin != xend)
				{
					this->push_back(*xbegin);
					xbegin = x.erase(xbegin);
				}
			};
			template <class Compare>
			void merge (list& x, Compare comp)
			{
				iterator begin = this->_end->next;
				iterator end = this->_end;
				iterator xbegin = x._end->next;
				iterator xend = x._end;

				if (*this == x)
					return ;
				while (begin != end && xbegin != xend)
				{
					if (comp(*xbegin, *begin))
					{
						this->insert(begin, *xbegin);
						xbegin = x.erase(xbegin);
					}
					else
						++begin;
				}
				while (xbegin != xend)
				{
					this->push_back(*xbegin);
					xbegin = x.erase(xbegin);
				}
			};
			void sort()
			{
				_node<T> *tmp;
				_node<T> *begin = this->_end->next;

				for (size_type a = 0; a < this->countNode; ++a)
				{
					
					begin = this->_end->next;
					while (begin != this->_end)
					{
						if (begin->next != this->_end && (begin->elem > begin->next->elem))
						{
							tmp = begin->next;
							
							begin->prev->next = tmp;
							tmp->next->prev = begin;
							begin->next = tmp->next;
							tmp->prev = begin->prev;
							begin->prev = tmp;
							tmp->next = begin;
						}
						else
							begin = begin->next;
					}
				}
			};
			template <class Compare>
			void sort (Compare comp)
			{
				_node<T> *tmp;
				_node<T> *begin = this->_end->next;

				for (size_type a = 0; a < this->countNode; ++a)
				{
					
					begin = this->_end->next;
					while (begin != this->_end)
					{
						if (begin->next != this->_end && comp(begin->next->elem, begin->elem))
						{
							tmp = begin->next;
							
							begin->prev->next = tmp;
							tmp->next->prev = begin;
							begin->next = tmp->next;
							tmp->prev = begin->prev;
							begin->prev = tmp;
							tmp->next = begin;
						}
						else
							begin = begin->next;
					}
				}
			};
			void reverse()
			{
				_node<T> *point = this->_end->next;
				_node<T> *prev_end = this->_end->prev;


				std::cout << "Coun node " << this->countNode << std::endl;
				for (size_type a = 1; a < this->countNode; ++a) // если провести столько же итерация сколько node, то this->_end он тоже переместит
				{
					prev_end = this->_end->prev;

					prev_end->prev->next = this->_end;
					this->_end->prev = prev_end->prev;
					prev_end->prev = point->prev;
					prev_end->next = point;
					point->prev->next = prev_end;
					point->prev = prev_end;
				}
			};
			private:
				_node<T> *newNode(T val)
				{
					_node<T> *tmp;
					tmp = this->nodeAlloc.allocate(1);
					this->nodeAlloc.construct(tmp, val);
					tmp->next = tmp;
					tmp->prev = tmp;
					return (tmp);
				};
				void	_delete(_node<T> *node)
				{
					this->nodeAlloc.destroy(node);
					this->nodeAlloc.deallocate(node, 1);
				};
	};
	template <class T, class Alloc>
	bool	operator==(const list<T, Alloc> &lhs, const list<T, Alloc>& rhs)
	{
		typename ft::list<T>::const_iterator b_lhs = lhs.begin();
		typename ft::list<T>::const_iterator e_lhs = lhs.end();
		typename ft::list<T>::const_iterator b_rhs = rhs.begin();
		typename ft::list<T>::const_iterator e_rhs = rhs.end();

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
	};
	template <class T, class Alloc>
	bool	operator!=(const list<T, Alloc> &lhs, const list<T, Alloc>& rhs)
	{
		if (operator==(lhs, rhs))
			return false;
		return true;
	};
	template <class T, class Alloc>
	bool	operator<(const list<T, Alloc> &lhs, const list<T, Alloc>& rhs)
	{
		typename ft::list<T>::const_iterator b_lhs = lhs.begin();
		typename ft::list<T>::const_iterator e_lhs = lhs.end();
		typename ft::list<T>::const_iterator b_rhs = rhs.begin();
		typename ft::list<T>::const_iterator e_rhs = rhs.end();

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
	bool	operator<=(const list<T, Alloc> &lhs, const list<T, Alloc>& rhs)
	{
		typename ft::list<T>::const_iterator b_lhs = lhs.begin();
		typename ft::list<T>::const_iterator e_lhs = lhs.end();
		typename ft::list<T>::const_iterator b_rhs = rhs.begin();
		typename ft::list<T>::const_iterator e_rhs = rhs.end();

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
	bool	operator>(const list<T, Alloc> &lhs, const list<T, Alloc>& rhs)
	{
		if (operator<(lhs, rhs) || operator==(lhs, rhs))
			return false;
		return true;
	};
	template <class T, class Alloc>
	bool	operator>=(const list<T, Alloc> &lhs, const list<T, Alloc>& rhs)
	{
		typename ft::list<T>::const_iterator b_lhs = lhs.begin();
		typename ft::list<T>::const_iterator e_lhs = lhs.end();
		typename ft::list<T>::const_iterator b_rhs = rhs.begin();
		typename ft::list<T>::const_iterator e_rhs = rhs.end();

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
  	void swap (list<T,Alloc>& x, list<T,Alloc>& y)
	{
		x.swap(y);
	};
};



#endif
