#ifndef STACK_HPP
#define STACK_HPP

#include <deque>
#include "./../vector/vector.hpp"

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
		
		private:
			container_type	_ctnr;
		public:	
			explicit stack (const container_type& ctnr = container_type()): _ctnr(ctnr){};
			~stack(){};

			bool empty() const {return (_ctnr.empty());};
			size_type size() const {return (_ctnr.size());};
			value_type& top() {return (this->_ctnr.back());};
			const value_type& top() const {return (this->_ctnr.back());};
			void push (const value_type& val){this->_ctnr.push_back(val);};
			void pop(){this->_ctnr.pop_back();};

			friend bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs._ctnr == rhs._ctnr);
			};
			// template <class T, class Container>
			friend bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{
				return (lhs._ctnr != rhs._ctnr);
			};
			// template <class T, class Container>
			friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs._ctnr < rhs._ctnr);
			};
			// template <class T, class Container>
			friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs._ctnr <= rhs._ctnr);
			};
			// template <class T, class Container>
			friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs._ctnr > rhs._ctnr);
			};
			// template <class T, class Container>
			friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs._ctnr >= rhs._ctnr);
			};
	};
};

#endif
