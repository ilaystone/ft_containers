#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iostream>

#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "pair.hpp"
#include "algorithm.hpp"
#include <memory>
#include <limits>
#include <stdexcept>

namespace ft
{

	template < class T, class Alloc=std::allocator<T> >
	class vector
	{
	public:
		// * Aliases
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::__wrap_iterator<pointer>				iterator;
		typedef ft::__wrap_iterator<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>          	reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>    	const_reverse_iterator;
		typedef typename allocator_type::size_type       	size_type;
		typedef typename allocator_type::difference_type 	difference_type;

	protected:
		// * Member attributes
		allocator_type		__alloc;
		pointer				__ptr;
		size_type			__capacity;
		size_type			__size;
	public:
		// * Coplien form
		/**
		 * @brief Construct a new vector object
		 *
		 * @param alloc Allocator used to allocate stuff
		 */
		explicit vector(const allocator_type &alloc = allocator_type())
		:	__alloc(alloc),
			__capacity(0),
			__size(0)
		{
			__ptr = __alloc.allocate(__capacity);
		}
		/**
		 * @brief Construct a new vector object with @n number of elements initialzed to @val
		 *
		 * @param n number of objects of Type T to be constructed
		 * @param val value of the objects to construct
		 * @param alloc
		 */
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		:	__alloc(alloc),
			__capacity(n),
			__size(n)
		{
			__ptr = __alloc.allocate(__capacity);
			for (size_type i = 0; i < __size; i++)
				__alloc.construct(__ptr + i, val);
		}
		/**
		 * @brief Construct a new vector object from a range of Iterators
		 * 
		 * @tparam InputIterator Input iterator to extract values from
		 * @param first start of range
		 * @param last end of range
		 * @param alloc
		 */
		template < class InputIterator >
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = 0)
			:	__alloc(alloc),
				__capacity(distance(first, last)),
				__size(distance(first, last))
		{
			__ptr = __alloc.allocate(__capacity);
			for (size_type i = 0; first != last; i++, first++)
				__alloc.construct(__ptr + i, *first);
		}
		/**
		 * @brief Construct a new vector object from a another vector object
		 * 
		 * @param rhs reference to a vector
		 */
		vector(const vector &rhs)
		:	__alloc(rhs.__alloc),
			__capacity(rhs.capacity()),
			__size(rhs.size())
		{
			__ptr = __alloc.allocate(__capacity);
			assign(rhs.begin(), rhs.end());
		}
		/**
		 * @brief Destroy the vector object
		 * 
		 */
		~vector(void)
		{
			this->clear();
			this->__alloc.deallocate(this->__ptr, this->__capacity);
		}
		/**
		 * @brief overload of the assignment operator uses copy constructor and swap function to copy elements
		 * 
		 * @param rhs reference to a vector
		 * @return vector& 
		 */
		vector		&operator=(const vector &rhs)
		{
			this->clear();
			if (this != &rhs && rhs.capacity() != 0)
				assign(rhs.begin(), rhs.end());
			return (*this);
		}

		// * Iterators
		/**
		 * @brief Returns a read/write iterator that points to the first element in this vector
		 * 
		 * @return iterator 
		 */
		iterator				begin(void)
		{
			return (__wrap_iterator<pointer>(__ptr));
		}
		/**
		 * @brief Returns a read-only iterator that points to the first element in this vector
		 * 
		 * @return const_iterator 
		 */
		const_iterator			begin() const
		{
			return (__wrap_iterator<const_pointer>(__ptr));
		}
		/**
		 * @brief Returns a read/write iterator that points one past the last element in this vector
		 * 
		 * @return iterator 
		 */
		iterator				end(void)
		{
			return (__wrap_iterator<pointer>(__ptr + __size));
		}
		/**
		 * @brief Retruns a read-only iterator that points one past the last element in this vector
		 * 
		 * @return const_iterator 
		 */
		const_iterator			end(void) const
		{
			return (__wrap_iterator<const_pointer>(__ptr + __size));
		}
		/**
		 * @brief Returns a read/write reverse iterator that points to the last element in this vector
		 * iteration is done in the reverse order
		 * 
		 * @return reverse_iterator 
		 */
		reverse_iterator		rbegin(void)
		{
			return (reverse_iterator(end()));
		}
		/**
		 * @brief Returns a read-only reverse iterator that points to the last element in this vector
		 * iteration is done in the reverse order
		 * 
		 * @return reverse_iterator 
		 */
		const_reverse_iterator	rbegin(void) const
		{
			return (reverse_iterator(end()));
		}
		/**
		 * @brief Returns a read/write reverse iterator that points to the first element in this vector
		 * iteration is done in the reverse order
		 * 
		 * @return reverse_iterator 
		 */
		reverse_iterator		rend(void)
		{
			return (reverse_iterator(begin()));
		}
		/**
		 * @brief Returns a read-only reverse iterator that points to the first element in this vector
		 * iteration is done in the reverse order
		 * 
		 * @return reverse_iterator 
		 */
		const_reverse_iterator	rend(void) const
		{
			return (reverse_iterator(begin()));
		}

		// Capacity
		/**
		 * @brief returns number of elements in this vector
		 * 
		 * @return size_type 
		 */
		size_type				size(void) const
		{
			return (this->__size);
		}
		/**
		 * @brief Returns the size() of the largest possible vector
		 * 
		 * @return size_type 
		 */
		size_type				max_size(void) const
		{
			return (std::min<size_type>(std::numeric_limits<difference_type>::max(), this->__alloc.max_size()));
		}
		/**
		 * @brief resizes the vector to the new elements if it was bigger it inserts new elements with @val otherwise it shrinks the vector
		 * 
		 * @param n new size of vector
		 * @param val values of new elements if they were added
		 */
		void					resize(size_type n, value_type val = value_type())
		{
			if (n > this->__capacity)
				this->reserve(this->__capacity * 2);
			while (n < this->__size)
				this->pop_back();
			while (n > this->__size)
				this->push_back(val);
			return ;
		}
		/**
		 * @brief returns the total number of elements the vector can hold befor the need to reallcate memory
		 * 
		 * @return size_type 
		 */
		size_type				capacity(void) const
		{
			return (this->__capacity);
		}
		/**
		 * @brief returns true if vector is empty (if begin == end)
		 * 
		 * @return true 
		 * @return false 
		 */
		bool					empty(void) const
		{
			return (__size == 0);
		}
		/**
		 * @brief attempts to reallocate enough memory to hold @n number of elements if n is bigger than actual capacity
		 * 
		 * @param n number requested
		 */
		void					reserve(size_type n)
		{
			if (n > this->__capacity)
			{
				pointer		ptr;
				size_type	i;

				ptr = this->__alloc.allocate(n);
				i = 0;
				for (iterator it = this->begin(); it != this->end(); it++, i++)
					this->__alloc.construct(ptr + i, *it);

				this->~vector();
				this->__ptr = ptr;
				this->__capacity = n;
				this->__size = i;
			}
		}

		// * Element Access
		/**
		 * @brief read/write access to data in vector in array-style
		 * 
		 * @param n position of the element to access
		 * @return reference 
		 */
		reference				operator[](size_type n)
		{
			return (*(this->begin() + n));
		}
		/**
		 * @brief read-only access to data in the vector in an array-style
		 * 
		 * @param n position of the element to access
		 * @return const_reference 
		 */
		const_reference			operator[](size_type n) const
		{
			return (*(this->begin() + n));
		}
		/**
		 * @brief read/write access to data in vector
		 * 
		 * @param n index of data to access
		 * @throw std::out_of_range if @n passed is invalid
		 * @return reference 
		 */
		reference				at(size_type n)
		{
			if (n < 0 || n > this->__size)
				throw (std::out_of_range("vector"));
			return (operator[](n));
		}
		/**
		 * @brief read-only access to data in vector
		 * 
		 * @param n index of data to access
		 * @throw std::out_of_range if @n passed is invalid
		 * @return reference 
		 */
		const_reference			at(size_type n) const
		{
			if (n < 0 || n > this->__size)
				throw std::out_of_range("vector");
			return (*operator[](n));
		}
		/**
		 * @brief a read/write reference to the first element in the vector
		 * 
		 * @return reference 
		 */
		reference				front(void)
		{
			return (*begin());
		}
		/**
		 * @brief a read-only reference to the first element in the vector
		 * 
		 * @return const_reference 
		 */
		const_reference			front(void) const
		{
			return (*begin());
		}
		/**
		 * @brief a read/write reference to the last element in the vector
		 * 
		 * @return reference 
		 */
		reference				back(void)
		{
			return (*(end() - 1));
		}
		/**
		 * @brief a read-only reference to the last element in the vector
		 * 
		 * @return const_reference 
		 */
		const_reference			back(void) const
		{
			return (*(end() - 1));
		}

		// * mofifiers
		/**
		 * @brief fills the vector with elements from the range of @InputIterator
		 * 
		 * @tparam InputIterator 
		 * @param first start of range
		 * @param last end of range
		 */
		template < class InputIterator >
		void					assign(InputIterator first, InputIterator last,
			typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = 0)
		{
			this->clear();
			difference_type			dist = distance(first, last);
			if (dist > this->__capacity)
				this->reserve(dist);
			for (difference_type i = 0; i < dist; i++)
				this->__alloc.construct(this->__ptr + i, *first++);
			this->__size = dist;
		}
		/**
		 * @brief fills the vector with @n copies of the given @val
		 * changing it's content accordingly
		 * 
		 * @param n number of elements to assign
		 * @param val value of elements to insert
		 */
		void 					assign (size_type n, const value_type& val)
		{
			this->clear();
			if (n > this->__capacity)
				this->reserve(n);
			for (difference_type i = 0; i < n; i++)
				this->__alloc.construct(this->__ptr + i, val);
			this->__size = n;
		}
		/**
		 * @brief typical stack operation, add the givven element at the end of vector
		 * rellocating the vector if such operation is needded
		 * 
		 * @param val value to insert
		 */
		void					push_back(value_type const	&val)
		{
			if (this->__capacity == 0)
				this->reserve(1);
			else if (this->__size == this->__capacity)
				this->reserve(this->__capacity * 2);
			this->__alloc.construct(&(*(this->end())), val);
			this->__size++;
		}
		/**
		 * @brief deletes the last element inserted in the vector reducing the size by one
		 * 
		 */
		void					pop_back(void)
		{
			if (this->__size <= 0)
				return ;
			this->__size--;
			this->__alloc.destroy(&(*this->end()));
		}
		/**
		 * @brief insert an object befor the specified @position
		 * 
		 * @param position pos to insert in
		 * @param val value to construct object with
		 * @return iterator 
		 */
		iterator				insert(iterator position, const value_type &val)
		{
			difference_type			dist = distance(this->begin(), position);

			this->insert(position, 1, val);
			return (iterator(&this->__ptr[dist]));
		}
		/**
		 * @brief insert @n objects starting at specified @postion
		 * 
		 * @param position postion to insert in
		 * @param n number of objects to insert
		 * @param val value of objects
		 */
		void					insert(iterator position, size_type n, const value_type &val)
		{
			difference_type			dist = distance(this->begin(), position);
			size_type				old_size = this->__size;
			iterator				new_pos;

			if (this->__size + n > this->__capacity)
				this->reserve(this->__capacity + n);
			this->__size = old_size;
			new_pos  = iterator((&this->__ptr[dist]));
			if (new_pos != this->end())
			{
				for (iterator ite = this->end() - 1; ite + 1 != new_pos; ite--)
				{
					this->__alloc.construct(&(*(ite + n)), *ite);
					this->__alloc.destroy(&(*ite));
				}
			}
			for (size_type i = 0; i < n; i++)
				this->__alloc.construct(&(*new_pos++), val);
			this->__size += n;
		}
		/**
		 * @brief insert a range of objects starting from @first until @last
		 * 
		 * @tparam InputIterator 
		 * @param position postion to start inserting in
		 * @param first start of range @InputIterator
		 * @param last end of range of @InputIterator
		 */
		template < class InputIterator >
		void					insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type* = 0)
		{
			difference_type			dist = distance(this->begin(), position);
			size_type				n = distance(first, last);
			size_type				old_size = this->__size;
			iterator				new_pos;

			if (this->__size + n > this->__capacity)
				this->reserve(this->__capacity + n);
			this->__size = old_size;
			new_pos  = iterator((&this->__ptr[dist]));
			if (new_pos != this->end())
			{
				for (iterator ite = this->end() - 1; ite + 1 != new_pos; ite--)
				{
					this->__alloc.construct(&(*(ite + n)), *ite);
					this->__alloc.destroy(&(*ite));
				}
			}
			for (size_type i = 0; i < n; i++)
				this->__alloc.construct(&(*new_pos++), *first++);
			this->__size += n;
		}
		iterator				erase(iterator position)
		{
			return (erase(position, position + 1));
		}
		iterator				erase(iterator first, iterator last)
		{
			difference_type		dist = distance(this->begin(), first);

			if (last < end())
			{
				this->__move_elements_to_left(first, last);
				this->__size -= static_cast<size_type>(last - first);
			}
			else
			{
				size_type	new_size = this->__size - static_cast<size_type>(last - first);
				while (this->__size != new_size)
					this->pop_back();
			}
			return (iterator(&this->__ptr[dist]));
		}
		void	swap(vector &rhs)
		{
			ft::swap(__alloc, rhs.__alloc);
			ft::swap(__ptr, rhs.__ptr);
			ft::swap(__size, rhs.__size);
			ft::swap(__capacity, rhs.__capacity);
		}
		void					clear(void)
		{
			for (difference_type i = 0; i < distance(begin(), end()); i++)
				this->__alloc.destroy(this->__ptr + i);
			this->__size = 0;
		}
		// return a copy of __alloc
		allocator_type get_allocator() const
		{
			return (this->__alloc());
		}
	private:
		void	__move_elements_to_left(iterator first, iterator last)
		{
			for (; first != this->end(); first++, last++)
			{
				this->__alloc.destroy(&(*first));
				if (last < end())
					this->__alloc.construct(&(*first), *last);
			}
		}
	public:
		friend bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin()); it.first != lhs.end(); it.first++, it.second++)
			{
				if (*(it.first) != (*it.second))
					return (false);
			}
			return (true);
		}
		friend bool	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
		{
			return (!operator==(lhs, rhs));
		}
		friend bool	operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
		{
			for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin()); it.first != lhs.end() && it.second != rhs.end(); it.first++, it.second++)
			{
				if (*(it.first) < *(it.second))
					return (true);
			}
			return (lhs.size() < rhs.size());
		}
		friend bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
		{
			for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin()); it.first != lhs.end() && it.second != rhs.end(); it.first++, it.second++)
			{
				if (*(it.first) <= *(it.second))
					return (true);
			}
			return (lhs.size() <= rhs.size());
		}
		friend bool	operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
		{
			for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin()); it.first != lhs.end() && it.second != rhs.end(); it.first++, it.second++)
			{
				if (*(it.first) > *(it.second))
					return (true);
			}
			return (lhs.size() > rhs.size());
		}
		friend bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
		{
			for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin()); it.first != lhs.end() && it.second != rhs.end(); it.first++, it.second++)
			{
				if (*(it.first) >= *(it.second))
					return (true);
			}
			return (lhs.size() >= rhs.size());
		}
	}; // vector

} // namespace

#endif