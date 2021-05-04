#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "map.hpp"

template <typename T, typename Key>
class iteratorMap: public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
	typedef std::pair<Key, T>				value_type;
	typedef ptrdiff_t							difference_type;
	typedef value_type*									pointer;
    typedef value_type&									reference;
	typedef std::bidirectional_iterator_tag 	iterator_category;
	
private:
	binary_tree<T, Key>	*point;
		
public:
	iteratorMap(): point(NULL){};
	iteratorMap(binary_tree<T, Key>	*other): point(other) {};
	iteratorMap(const iteratorMap &other): point(other.point){};
	iteratorMap &operator=(const iteratorMap &other)
	{
		this->point = other.point;
		return (*this);
	};
	~iteratorMap(){};
	// == !=
	bool	operator==(const iteratorMap &a){return (this->point == a.point);};
	bool	operator!=(const iteratorMap &a){return (this->point != a.point);};
	
	//* -> *=
	reference operator*(void) const {return (this->point->val);};
	pointer operator->(void) const {return &(this->point->val);};
	
	// // //++a a++ *a++
	iteratorMap &operator++(void)
	{
		this->point = this->more(this->point, this->point->val.first);
		return *this;
	};
	iteratorMap operator++(int)
	{
		iteratorMap a(*this);
		operator++();
		return (a);
	};
	// // *a++
	// //--a a-- *a--
	iteratorMap &operator--()
	{
		this->point = this->less(this->point, this->point->val.first);
		return (*this);
	};
	iteratorMap operator--(int)
	{
		iteratorMap a(*this);
		operator--();
		return (a);
    };
	// *a--
private:	
	binary_tree<T, Key> *more(binary_tree<T, Key> *node, const Key &k)
	{
		if (node->right && node->right->val.first > k)
		{
			if (node->right->left)
			{
				node = node->right->left;
				while (node->left)
					node = node->left;
				return node;
			}
			return node->right;
		}
		binary_tree<T, Key> *copy_node = node;
		while (node->parent)
		{
			if (node->parent->val.first > k)
				return node->parent;
			node = node->parent;
		}
		return copy_node->right;
	};
	binary_tree<T, Key> *less(binary_tree<T, Key> *node, const Key &k)
	{
		if (node->left && node->left->val.first < k)
		{
			if (node->left->right)
			{
				node = node->left->right;
				while (node->right)
					node = node->right;
				return node;
			}
			return node->left;
		}
		binary_tree<T, Key> *copy_node = node;
		while (node->parent)
		{
			if (node->parent->val.first < k)
				return node->parent;
			node = node->parent;
		}
		return copy_node->left;
	};
};

template <typename T, typename Key>
class constIteratorMap: public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
	typedef const std::pair<Key, T>					value_type;
	typedef ptrdiff_t							difference_type;
	typedef value_type*									pointer;
    typedef value_type&									reference;
	typedef std::bidirectional_iterator_tag 	iterator_category;
	
private:
	const binary_tree<T, Key>	*point;
		
public:
	constIteratorMap(): point(NULL){};
	constIteratorMap(binary_tree<T, Key>	*other): point(other) {};
	constIteratorMap(const constIteratorMap &other): point(other.point){};
	constIteratorMap &operator=(const constIteratorMap &other)
	{
		this->point = other.point;
		return (*this);
	};
	~constIteratorMap(){};
	// == !=
	bool	operator==(const constIteratorMap &a) const {return (this->point == a.point);};
	bool	operator!=(const constIteratorMap &a) const {return (this->point != a.point);};
	
	//* -> *=
	reference operator*(void) const {return (this->point->val);};
	pointer operator->(void) const {return &(this->point->val);};
	
	// // //++a a++ *a++
	constIteratorMap &operator++(void)
	{
		this->point = this->more(this->point, this->point->val.first);
		return *this;
	};
	constIteratorMap operator++(int)
	{
		constIteratorMap a(*this);
		operator++();
		return (a);
	};
	// // *a++
	// //--a a-- *a--
	constIteratorMap &operator--()
	{
		this->point = this->less(this->point, this->point->val.first);
		return (*this);
	};
	constIteratorMap operator--(int)
	{
		constIteratorMap a(*this);
		operator--();
		return (a);
    };
	// *a--
private:	
	const binary_tree<T, Key> *more(const binary_tree<T, Key> *node, const Key &k)
	{
		if (node->right && node->right->val.first > k)
		{
			if (node->right->left)
			{
				node = node->right->left;
				while (node->left)
					node = node->left;
				return node;
			}
			return node->right;
		}
		const binary_tree<T, Key> *copy_node = node;
		while (node->parent)
		{
			if (node->parent->val.first > k)
				return node->parent;
			node = node->parent;
		}
		return copy_node->right;
	};
	const binary_tree<T, Key> *less(const binary_tree<T, Key> *node, const Key &k)
	{
		if (node->left && node->left->val.first < k)
		{
			if (node->left->right)
			{
				node = node->left->right;
				while (node->right)
					node = node->right;
				return node;
			}
			return node->left;
		}
		const binary_tree<T, Key> *copy_node = node;
		while (node->parent)
		{
			if (node->parent->val.first < k)
				return node->parent;
			node = node->parent;
		}
		return copy_node->left;
	};
};

template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator								iterator_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::pointer				pointer;
    typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
private:
	Iterator iter;
public:
	// Constructs
	reverse_iterator(): iter(NULL){};
	explicit reverse_iterator (iterator_type it): iter(it){};
	template <class Iter>
	reverse_iterator (const reverse_iterator<Iter>& rev_it): iter(rev_it.iter){};
	iterator_type base() const { return (this->iter);};
	bool	operator==(const reverse_iterator &a){return (this->iter == a.iter);};
	bool	operator!=(const reverse_iterator &a){return (this->iter != a.iter);};
	reference operator*() const { return (this->iter.operator*());};
	reverse_iterator& operator++()
	{
		--this->iter;
		return (*this);
	};
	reverse_iterator  operator++(int)
	{
		reverse_iterator tmp(this->iter);
		--this->iter;
		return (tmp);
	};
	reverse_iterator& operator--()
	{
		++this->iter;
		return (*this);
	};
	reverse_iterator  operator--(int)
	{
		reverse_iterator tmp(this->iter);
		++this->iter;
		return (tmp);
	};
	pointer operator->() const { return &(this->operator*());};
};

template <class Iterator>
class const_reverse_iterator
{
public:
	typedef Iterator								iterator_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::pointer				pointer;
    typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
private:
	Iterator iter;
public:
	const_reverse_iterator(): iter(NULL){};
	explicit const_reverse_iterator (iterator_type it): iter(it){};
	template <class Iter>
	const_reverse_iterator (const const_reverse_iterator<Iter>& rev_it): iter(rev_it.iter){};
	iterator_type base() const { return (this->iter);};
	bool	operator==(const const_reverse_iterator &a){return (this->iter == a.iter);};
	bool	operator!=(const const_reverse_iterator &a){return (this->iter != a.iter);};
	reference operator*() const { return (this->iter.operator*());};
	const_reverse_iterator& operator++()
	{
		--this->iter;
		return (*this);
	};
	const_reverse_iterator  operator++(int)
	{
		const_reverse_iterator tmp(this->iter);
		--this->iter;
		return (tmp);
	};
	const_reverse_iterator& operator--()
	{
		++this->iter;
		return (*this);
	};
	const_reverse_iterator  operator--(int)
	{
		const_reverse_iterator tmp(this->iter);
		++this->iter;
		return (tmp);
	};
	pointer operator->() const { return &(this->operator*());};
};

#endif
