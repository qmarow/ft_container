#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <deque>
#include "./../list/list.hpp"

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class queue
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
		private:
			container_type	_ctnr;
		public:
			explicit queue (const container_type& ctnr = container_type()): _ctnr(ctnr){};
			bool empty() const{ return (this->_ctnr.empty());};
			size_type size() const { return (this->_ctnr.size());};
			value_type& front() { return (this->_ctnr.front());};
			const value_type& front() const { return (this->_ctnr.front());};
			value_type& back() { return (this->_ctnr.back());};
			const value_type& back() const { return (this->_ctnr.back());};
			void push (const value_type& val) { this->_ctnr.push_back(val);};
			void pop() {this->_ctnr.pop_front();};
		// public:
			// template <class T, class Container>
			friend bool operator== (const queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
			{
				return (lhs._ctnr == rhs._ctnr);
			};
			// template <class T, class Container>
			friend bool operator!= (const queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
			{
				return (lhs._ctnr != rhs._ctnr);
			};
			// template <class T, class Container>
			friend bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
			{
				return (lhs._ctnr < rhs._ctnr);
			};
			// template <class T, class Container>
			friend bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
			{
				return (lhs._ctnr <= rhs._ctnr);
			};
			// template <class T, class Container>
			friend bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
			{
				return (lhs._ctnr > rhs._ctnr);
			};
			// template <class T, class Container>
			friend bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
			{
				return (lhs._ctnr >= rhs._ctnr);
			};
	};
};


#endif
