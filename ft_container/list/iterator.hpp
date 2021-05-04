
#include <iostream>
#include "node.hpp"

template <typename T>
class constIteratorList: public std::iterator<std::bidirectional_iterator_tag, T>
{
	public:
		typedef const T									value_type;
		typedef ptrdiff_t							difference_type;
		typedef const T*									pointer;
		typedef const T&									reference;
		typedef std::bidirectional_iterator_tag 	iterator_category;
	
	private:

		typedef const _node<T>* node;
		node	point;
		
	public:
		constIteratorList(): point(NULL){};
		constIteratorList(node other): point(other) {};
		constIteratorList(const constIteratorList &other): point(other.point){};
		constIteratorList &operator=(const constIteratorList &other)
		{
			this->point = other.point;
			return (*this);
		};
		~constIteratorList(){};

		// == !=
		bool	operator==(const constIteratorList &a){return (this->point == a.point);};
		bool	operator!=(const constIteratorList &a){return (this->point != a.point);};
		
		// //* -> *=
		reference operator*(void){return (this->point->elem);};
		pointer operator->(void){return &(this->operator*());};
		
		// //++a a++ *a++
		constIteratorList &operator++(void)
		{
			this->point = this->point->next;
			return (*this);
		};
		constIteratorList operator++(int)
		{
			constIteratorList a(*this);
			operator++();
			return (a);
		};
			// *a++
		//--a a-- *a--
		constIteratorList &operator--()
		{
			this->point = this->point->prev;
			return (*this);
		};
		constIteratorList operator--(int)
		{
			constIteratorList a(*this);
			operator--();
			return (a);
		};
			// *a--
};

template <typename T>
class iteratorList: public std::iterator<std::bidirectional_iterator_tag, T>
{
	public:
		typedef T									value_type;
		typedef ptrdiff_t							difference_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::bidirectional_iterator_tag 	iterator_category;
	
	private:
		_node<T> *point;
		
	public:
		iteratorList(): point(NULL){};
		iteratorList(_node<T>	*other): point(other) {};
		iteratorList(const iteratorList &other): point(other.point){};
		iteratorList &operator=(const iteratorList &other)
		{
			this->point = other.point;
			return (*this);
		};
		~iteratorList(){};

		// == !=
		bool	operator==(const iteratorList &a){return (this->point == a.point);};
		bool	operator!=(const iteratorList &a){return (this->point != a.point);};
		
		// //* -> *=
		reference operator*(void){return (this->point->elem);};
		pointer operator->(void){return &(this->operator*());};
		
		// //++a a++ *a++
		iteratorList &operator++(void)
		{
			this->point = this->point->next;
			return (*this);
		};
		iteratorList operator++(int)
		{
			iteratorList a(*this);
			operator++();
			return (a);
		};
			// *a++
		//--a a-- *a--
		iteratorList &operator--()
		{
			this->point = this->point->prev;
			return (*this);
		};
		iteratorList operator--(int)
		{
			iteratorList a(*this);
			operator--();
			return (a);
		};
			// *a--
};

template <class Iterator>
class reverse_iterator
{
	public:
		typedef Iterator iterator_type;
		typedef	typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type		value_type;
		typedef typename Iterator::difference_type	difference_type;
		typedef typename Iterator::pointer			pointer;
		typedef typename Iterator::reference			reference;
	private:
		iterator_type	iter;
	public:
		reverse_iterator():iter(NULL) {};
		explicit reverse_iterator (iterator_type it):iter(it) {};
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it): iter(rev_it.iter) {};

		bool operator==(const reverse_iterator &a) {return (this->iter == a.iter);};
		bool operator!=(const reverse_iterator &a) {return (this->iter != a.iter);};

		reference	operator*(void){return (*this->iter);};
		pointer		operator->(void){return &(operator*());};

		reverse_iterator &operator--()
		{
			++this->iter;
			return (*this);
		};
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(this->iter);
			++this->iter;
			return (tmp);
		};
		reverse_iterator &operator++()
		{
			
			--this->iter;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(this->iter);
			--this->iter;
			return (tmp);
		}
};

template <class Iterator>
class const_reverse_iterator
{
	public:
		typedef Iterator iterator_type;
		typedef	typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type		value_type;
		typedef typename Iterator::difference_type	difference_type;
		typedef typename Iterator::pointer			pointer;
		typedef typename Iterator::reference			reference;
	private:
		iterator_type	iter;
	public:
		const_reverse_iterator():iter(NULL) {};
		explicit const_reverse_iterator (iterator_type it):iter(it) {};
		template <class Iter>
		const_reverse_iterator (const const_reverse_iterator<Iter>& rev_it): iter(rev_it.iter) {};

		bool operator==(const const_reverse_iterator &a) {return (this->iter == a.iter);};
		bool operator!=(const const_reverse_iterator &a) {return (this->iter != a.iter);};

		reference	operator*(void){return (*this->iter);};
		pointer		operator->(void){return &(operator*());};

		const_reverse_iterator &operator--()
		{
			++this->iter;
			return (*this);
		};
		const_reverse_iterator operator--(int)
		{
			const_reverse_iterator tmp(this->iter);
			++this->iter;
			return (tmp);
		};
		const_reverse_iterator &operator++()
		{
			--this->iter;
			return (*this);
		}
		const_reverse_iterator operator++(int)
		{
			const_reverse_iterator tmp(this->iter);
			--this->iter;
			return (tmp);
		}
};
