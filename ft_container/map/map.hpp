#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "binary_tree.hpp"
#include "iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<binary_tree<T, Key> > >
	class map
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef typename std::pair<const key_type,mapped_type>	value_type;
			typedef Compare											key_compare;
			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef	iteratorMap<T, Key>								iterator;
			typedef constIteratorMap<T, Key>						const_iterator;
			typedef reverse_iterator<iterator>						reverse_iterator;
			typedef const_reverse_iterator<const_iterator>			const_reverse_iterator;	
			typedef	ptrdiff_t										difference_type;
			typedef size_t											size_type;
		private:
			typedef binary_tree<T, Key>	binary_tree;
			allocator_type				_alloc;
			binary_tree					*_end;
			binary_tree					*_begin;
			key_compare					_comp;
			size_type					count_node;
		public:
		//Member functions
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;

				this->_end = this->_alloc.allocate(1);
				this->_alloc.construct(this->_end, T(), Key());

				this->_begin = this->_alloc.allocate(1);
				this->_alloc.construct(this->_begin, T(), Key());

				this->_comp = comp;
				this->count_node = 0;
			};
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type())
			{
				this->_comp = comp;
				this->_alloc = alloc;

				this->_end = this->_alloc.allocate(1);
				this->_alloc.construct(this->_end, T(), Key());

				this->_begin = this->_alloc.allocate(1);
				this->_alloc.construct(this->_begin, T(), Key());
				
				this->count_node = 0;
				this->insert(first, last);
			};	
			map (const map& x)
			{
				this->_comp = x._comp;
				this->_alloc = x._alloc;

				this->_end = this->_alloc.allocate(1);
				this->_alloc.construct(this->_end, T(), Key());

				this->_begin = this->_alloc.allocate(1);
				this->_alloc.construct(this->_begin, T(), Key());
				
				this->count_node = 0;
				this->insert(x.begin(), x.end());
			};
			~map()
			{
				if (this->count_node)
					this->clear();
				this->_delete(this->_begin);
				this->_delete(this->_end);
			};
			map& operator= (const map& x)
			{
				this->clear();
				
				this->_comp = x._comp;
				this->_alloc = x._alloc;
				
				this->count_node = 0;
				this->insert(x.begin(), x.end());
				return (*this);
			};
		// Iterator
			iterator begin() 
			{
				if (this->_end->left)
					return (this->_begin->right);
				return (this->_end);
			};
			const_iterator begin() const
			{
				if (this->_end->left)
					return (this->_begin->right);
				return (this->_end);
			};
			iterator end()  { return (this->_end);};
			const_iterator end() const
			{
				return (this->_end);
			};
			reverse_iterator rbegin()
			{
				if (this->_begin->right)
				{
					reverse_iterator rev(iterator	(this->_end->left));
					return (rev);
				}
				return (this->rend());
			};
			const_reverse_iterator rbegin() const
			{
				if (this->_begin->right)
				{
					const_reverse_iterator rev(const_iterator(this->_end->left));
					return (rev);
				}
				return (this->rend());
			};
			reverse_iterator rend()
			{
				reverse_iterator	it(iterator(this->_begin));
				return (it);
			};
			const_reverse_iterator rend() const
			{
				const_reverse_iterator	it(const_iterator(this->_begin));
				return (it);
			};
		// Capacity
			bool		empty() const { return (this->count_node == 0);};
			size_type	size() const {return (this->count_node);};
			size_type	max_size() const 
			{
				return (this->_alloc.max_size());
			};
		// Element access
			mapped_type& operator[](const key_type &k)
			{
				binary_tree *node;
				if (this->_end->left)
					node = search(k, search_root(this->_end->left));
				else
					node = NULL;
				if (node != NULL)
					return (node->val.second);
				node = this->newNode(k);
				if (node == this->_end->left->right)
				{
					node->right = this->_end;
					this->_end->left = node;
				}
				if (node == this->_begin->right->left)
				{
					node->left = this->_begin;
					this->_begin->right = node;
				}
				node->fixheight_branch();				
				return (node->val.second);
			};
		// Modifiers
			std::pair<iterator,bool> insert (const value_type& val)
			{
				binary_tree					*node;
				if (this->_end->left)
					node = search(val.first, search_root(this->_end->left));
				else
					node = NULL;
				if (node != NULL)
					return (make_pair<iterator, bool>(iterator(node), false));
				node = this->newNode(val.first);
				node->val.second = val.second;
				if (node == this->_end->left->right)
				{
					node->right = this->_end;
					this->_end->left = node;
				}
				if (node == this->_begin->right->left)
				{
					node->left = this->_begin;
					this->_begin->right = node;
				}
				node->fixheight_branch();
				return (make_pair<iterator, bool>(iterator(node), true));
			};
			iterator insert (iterator , const value_type& val)
			{
				return (insert(val).first);
			};
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				InputIterator tmp;
				while (first != last)
				{
					tmp = first;
					++first;
					this->insert(*tmp);
				}
			};
			void erase (iterator position)
			{
				binary_tree *node = search(position->first, search_root(this->_end->left));
				
				this->deleteNode(node);
			};
			size_type erase (const key_type& k)
			{
				binary_tree *node = search(k, search_root(this->_end->left));
				this->deleteNode(node);
				if (node)
					return (1);
				return 0;
			};
			void erase (iterator first, iterator last)
			{
				iterator tmp;
				while (first != last)
				{
					tmp = first;
					++first;
					this->erase(tmp);
				}
			};
			void swap (map& x)
			{
				binary_tree *x_end = x._end;
				binary_tree *x_beg = x._begin;
				allocator_type x_alloc = x._alloc;
				key_compare x_comp = x._comp;
				size_type x_count_node = x.count_node;

				x._end = this->_end;
				x._comp = this->_comp;
				x._begin = this->_begin;
				x._alloc = this->_alloc;
				x.count_node = this->count_node;

				this->_end = x_end;
				this->_comp = x_comp;
				this->_begin = x_beg;
				this->_alloc = x_alloc;
				this->count_node = x_count_node;
			};
			void clear()
			{
				this->erase(this->begin(), this->end());
			};
		// Observers
			key_compare key_comp() const
			{
				return (this->_comp);
			};
			value_compare value_comp() const
			{
				value_compare val_comp(this->_comp);
				return (val_comp);
			};
		// Operations
			iterator find(const key_type& k)
			{
				binary_tree	*node;
				if (this->_end->left)
					node = search(k, search_root(this->_end->left));
				else
					node = NULL;
				if (node)
					return (node);
				return (this->_end);
			};
			const_iterator find (const key_type& k) const
			{
				binary_tree	*node;
				if (this->_end->left)
					node = search(k, search_root(this->_end->left));
				else
					node = NULL;
				if (node)
					return (node);
				return (this->_end);
			};
			size_type count (const key_type& k) const
			{
				if (this->_end->left && search(k, search_root(this->_end->left)))
					return 1;
				return 0;
			};
			iterator lower_bound (const key_type& k)
			{
				if (this->_end->left == NULL)
					return this->_end;

				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{							// <
					if (this->_comp(beg->first, k) == false)
						return (beg);
					++beg;
				}
				return (beg);
			};
			const_iterator lower_bound (const key_type& k) const
			{
				if (this->_end->left == NULL)
					return this->_end;

				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{							// <
					if (this->_comp(beg->first, k) == false)
						return (beg);
					++beg;
				}
				return (beg);
			};
			iterator upper_bound (const key_type& k)
			{ 
				if (this->_end->left == NULL)
					return this->_end;

				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{                          // <
					if (this->_comp(k, beg->first))
						return (beg);
					++beg;
				}
				return (beg);
			};
			const_iterator upper_bound (const key_type& k) const
			{
				if (this->_end->left == NULL)
					return this->_end;

				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{                          // <
					if (this->_comp(k, beg->first))
						return (beg);
					++beg;
				}
				return (beg);
			};
			std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (make_pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
			};
			std::pair<iterator,iterator>	equal_range(const key_type& k)
			{
				return (make_pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
			};
		private:
		void	cheeck_structur()
			{
				if (search_root(this->_end->left))
				{
					std::cout << "this->bntr.key - " << search_root(this->_end->left)->val.first << "\n";
					if (search_root(this->_end->left)->left)
					{
						std::cout << "this->bntr->left.key  " <<search_root(this->_end->left)->left->val.first << "\n";
						if (search_root(this->_end->left)->left->right)
						{
							std::cout << "this->bntr->left->right->.key  " << search_root(this->_end->left)->left->right->val.first << "\n";
							if (search_root(this->_end->left)->left->right->right)
							{
								std::cout << "this->bntr->left->right->right.key  " << search_root(this->_end->left)->left->right->right->val.first << "\n";
							}
							if (search_root(this->_end->left)->left->right->left)
							{
								std::cout << "this->bntr->left->right->left.key  " << search_root(this->_end->left)->left->right->left->val.first << "\n";
							}
						}
						if (search_root(this->_end->left)->left->left)
						{
							std::cout << "this->bntr->left->left.key  " << search_root(this->_end->left)->left->left->val.first << "\n";
							if (search_root(this->_end->left)->left->left->right)
							{
								std::cout << "this->bntr->left->left->right.key  " << search_root(this->_end->left)->left->left->right->val.first << "\n";
							}
							if (search_root(this->_end->left)->left->left->left)
							{
								std::cout << "this->bntr->left->left->left.key  " << search_root(this->_end->left)->left->left->left->val.first << "\n";
							}
						}

					}
					if (search_root(this->_end->left)->right)
					{
						std::cout << "this->bntr->right.key  " << search_root(this->_end->left)->right->val.first << "\n";
						if (search_root(this->_end->left)->right->right)
						{
							std::cout << "this->bntr->right->right->.key  " << search_root(this->_end->left)->right->right->val.first << "\n";
							if (search_root(this->_end->left)->right->right->right)
							{
								std::cout << "this->bntr->right->right->right.key  " << search_root(this->_end->left)->right->right->right->val.first << "\n";
							}
							if (search_root(this->_end->left)->right->right->left)
							{
								std::cout << "this->bntr->right->right->left.key  " << search_root(this->_end->left)->right->right->left->val.first << "\n";
							}
						}
						if (search_root(this->_end->left)->right->left)
						{
							std::cout << "this->bntr->right->left.key  " << search_root(this->_end->left)->right->left->val.first << "\n";
							if (search_root(this->_end->left)->right->left->right)
							{
								std::cout << "this->bntr->right->left->right.key  " << search_root(this->_end->left)->right->left->right->val.first << "\n";
							}
							if (search_root(this->_end->left)->right->left->left)
							{
								std::cout << "this->bntr->right->left->left.key  " << search_root(this->_end->left)->right->left->left->val.first << "\n";
							}
						}
					}
				}
			};
		template <typename I, typename B>
		std::pair<I, B> make_pair(I first, B second)
		{
			std::pair<I, B> res(first, second);
			return (res);
		};
		void		deleteNode(binary_tree *node)
		{
			if (node == NULL)
				return ;
			if (node->left && node->left != this->_begin)
			{
				binary_tree *replacement = node->left;
				if (replacement->right)
				{
					replacement = replacement->right;
					while (replacement->right)
						replacement = replacement->right;
				}
				
				// переподвязываем дочерние элементы replacement-а
				if (replacement->parent->right == replacement) // тогда понимаем, что replacement справо
				{
					replacement->parent->right = replacement->left;
					if (replacement->left && replacement->left != this->_begin)
						replacement->left->parent = replacement->parent;
				}
				else if (replacement->parent->left == replacement)
				{
					replacement->parent->left = replacement->left;
					if (replacement->left && replacement->left != this->_begin)
						replacement->left->parent = replacement->parent;
				}
				// для того, чтобы можно было с правильной позиции запустить fixheight_branch
				
				binary_tree *cp_replacement;
				if (replacement->left && replacement->left != this->_begin)
					cp_replacement = replacement->left;
				else
				{
					if (replacement->parent != node)
						cp_replacement = replacement->parent;
					else
						cp_replacement = replacement;
				}
				// II заменяем удаляемую ноду
				 //соединяем replacement с окружением
				replacement->parent = node->parent;
				replacement->right = node->right;
				replacement->left = node->left;
				 //соединяем окружение с replacement
				if (node->parent)
				{
					if (node->parent->left == node)
						node->parent->left = replacement;
					else if (node->parent->right == node)
						node->parent->right = replacement;
				}
				if (node->left && node->left != replacement)
					node->left->parent = replacement;

				if (node->right && node->right != this->_end)
					node->right->parent = replacement;
				else if (node->right == this->_end)
				{
					this->_end->left = replacement;
				}
				// III
				this->_delete(node);
				// IV
				cp_replacement->fixheight_branch();
			}
			else
			{
				binary_tree *cp_replacement;
				if (node->parent)
				{
					if (node->parent->right == node)
					{
						node->parent->right = node->right;
					}
					else if (node->parent->left == node)
					{
						if (node->right)
							node->parent->left = node->right;
						else
							node->parent->left = node->left;
					}
					cp_replacement = node->parent;
				}
				if (node->right && node->right != this->_end)
				{
					node->right->parent = node->parent;
					cp_replacement = node->right;
				}
				if (this->_end->left == node)
				{
					this->_end->left = node->parent;
					cp_replacement = node->parent;
				}
				if (this->_begin->right == node)
				{
					if (node->right && node->right != this->_end)
					{
						this->_begin->right = node->right;
						node->right->left = this->_begin;
						cp_replacement = node->right;
					}
					else
					{
						this->_begin->right = node->parent;
						if (node->parent)
							node->parent->left = this->_begin;
						cp_replacement = node->parent;
					}
				}
				this->_delete(node);
				if (cp_replacement)
					cp_replacement->fixheight_branch();
			}
		}
		
		void		_delete(binary_tree *node)
		{
			--this->count_node;
			this->_alloc.destroy(node);
			this->_alloc.deallocate(node, 1);
		};
		binary_tree	*newNode(const key_type &k, mapped_type val = T()) //  Выделяет память под ноду, заполняет ее, определяет место и связывает
		{
			binary_tree *nNode;
			binary_tree *tmp;
			nNode = this->_alloc.allocate(1);
			this->_alloc.construct(nNode, val, k);
			if (this->_end->left)
			{
				int	a = 0;
				tmp = locating(k, &a, search_root(this->_end->left));
				if (a)
					tmp->right = nNode;
				else
					tmp->left = nNode;
				nNode->parent = tmp;
			}
			else
			{
				this->_end->left = nNode; // подвязываем end ноду
				nNode->right = this->_end;

				this->_begin->right = nNode; // подвязываем begin ноду
				nNode->left = this->_begin;
			}
			++this->count_node;
			return (nNode);
		};
		binary_tree *search_root(binary_tree *bntr) const
		{
			if (bntr->parent == NULL)
				return (bntr);
			return search_root(bntr->parent);
		};
		binary_tree	*locating(const key_type &k, int *a, binary_tree *bntr) // второе значение "а", говорит о том какая эта будет ветка - правая или левая. Если а = 0 - левая ветка, если a = 1 - правая.
		{
			if (k >= bntr->val.first) // идем направо 		5
			{
				if (bntr->right == NULL || bntr->right == this->_end)
				{
					*a = 1;
					return (bntr);
				}
				return locating(k, a, bntr->right);
			}
			else              // идем налево            5
			{					/*					   /                 */
				if (bntr->left == NULL || bntr->left == this->_begin) //            4
				{
					*a = 0;
					return (bntr);
				}
				return locating(k, a, bntr->left);
			}
			return (bntr);
		}
		binary_tree *search_min(binary_tree *bntr)
		{
			while (bntr && bntr->left)
			{
				bntr = bntr->left;
			}
			return (bntr);
		}
		binary_tree *search_max(binary_tree *bntr)
		{
			while (bntr && bntr->right && bntr->right != this->_end)
			{
				bntr = bntr->right;
			}
			return (bntr);
		}
		binary_tree	*search(const key_type &k, binary_tree *bntr) const
		{
			if (bntr != NULL)
			{
				if (bntr->val.first == k)
					return (bntr);
			}
			else
				return NULL;
			if (bntr->val.first > k) // идем налево
			{
				if (bntr->left && bntr->left != this->_begin)
				{
					if (bntr->left->val.first == k)
						return (bntr->left);
					return (search(k, bntr->left));
				}
				else
					return (NULL);
			}
			else if (bntr->val.first < k) // идем направо
			{
				if (bntr->right && bntr->right != this->_end)
				{
					if (bntr->right->val.first == k)
						return (bntr->right);
					return (search(k, bntr->right));
				}
				else
					return (NULL);
			}
			return (NULL);
		}
	};
};

#endif
