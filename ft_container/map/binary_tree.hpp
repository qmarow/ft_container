#ifndef BINARY_TREE
#define BINARY_TREE

#include "map.hpp"

template <typename T, typename K>
class binary_tree
{
	public:
		binary_tree		*left;
		binary_tree		*right;
		binary_tree		*parent;
		std::pair<K, T>	val;
		unsigned char			height;
	binary_tree(T _data = T(), K _key = K()): left(NULL), right(NULL), parent(NULL)
	{
		this->val.first = _key;
		this->val.second = _data;
		this->height = 0;
	};
	~binary_tree(){};
	size_t		get_height(binary_tree *node)
	{
		return ((node != NULL ? node->height : 0));
	};
	int		bfactor()
	{
		return (get_height(this->left) - get_height(this->right));
	};
	void	fixheight()
	{
		unsigned char	hl = this->get_height(this->left);
		unsigned char	hr = this->get_height(this->right);

		this->height = (hl>hr?hl:hr)+1;
	};
	binary_tree	*fixheight_branch()
	{
		this->fixheight();
		int balance = this->bfactor();
		if (balance == 2)
			this->fixbalance_L();
		else if (balance == -2)
			this->fixbalance_R();
		if (this->parent == NULL)
			return this;		
		return this->parent->fixheight_branch();
	};
	void	fixbalance_L()
	{
		if (this->left->bfactor() < 0)
			this->left->left_turn();
		this->right_turn();
	};
	void	fixbalance_R()
	{
		if (this->right->bfactor() > 0)
			this->right->right_turn();
		this->left_turn();
	};
	void right_turn() // node - корень, относительно которого будет происходить поворот
	{
		binary_tree	*lnode = this->left; // берем левую ноду, потому что поворачиваем направо
		if (lnode->right != NULL)
			lnode->right->parent = this;
		this->left = lnode->right;
		lnode->right = this;
		if (this->parent)
		{
			if (this->parent->left == this)
				this->parent->left = lnode;
			else if (this->parent->right == this)
				this->parent->right = lnode;
		}
		lnode->parent = this->parent;
		this->parent = lnode;
		this->fixheight();
		lnode->fixheight();
		
	}
	void	left_turn() // node - корень, относительно которого будет происходить поворот
	{
		binary_tree	*rnode = this->right; // берем правую ноду, потому что поворачиваем налево
		if (rnode->left != NULL)
			rnode->left->parent = this;
		this->right = rnode->left;
		rnode->left = this;
		if (this->parent)
		{
			if (this->parent->left == this)
				this->parent->left = rnode;
			else if (this->parent->right == this)
				this->parent->right = rnode;
		}
		rnode->parent = this->parent;
		this->parent = rnode;
		this->fixheight();
		rnode->fixheight();
	}
};
template <typename T, typename K>
bool    operator==(binary_tree<T, K> const &a, binary_tree<T, K> const &b)
{
	if (a.left == b.left && a.right == b.right && a.parent == b.parent)
		return (true);
	return (false);
}

template <typename T, typename K>
bool    operator!=(binary_tree<T, K> const &a, binary_tree<T, K> const &b)
{
	if (a.left == b.left && a.right == b.right && a.parent == b.parent)
		return (false);
	return (true);
}

#endif
