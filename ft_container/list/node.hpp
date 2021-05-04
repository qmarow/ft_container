#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
class _node
{
	public:
	_node	*prev;
	_node	*next;
	T		elem;
	_node(T _elem = T()): prev(0), next(0), elem(_elem)
	{};
	_node():prev(0), next(0)
	{};
	_node(_node *_prev, _node *_next, T _elem = T()): elem(_elem), prev(_prev), next(_next)
	{};
	_node(const _node &other)
	{
		this->next = other.next;
		this->elem = other.elem;
		this->prev = other.prev;
	}
};

#endif