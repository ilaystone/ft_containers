#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

namespace ft

{
	// this is iterator wrap is just a wraper in a senese that it does not change the semantic
	// of the operators of its iterator parametre. It's primary purpose is just to convert an
	// iterator that is not a class,  e.g. a pointer, into an iterator that is a class.
	template < class Iterator >
	class __wrap_iterator
	{
	protected:
		Iterator											__base_ptr;

		typedef iterator_traits<Iterator>					__traits_type;
	public:
		typedef Iterator                                    iterator_type;
		typedef typename __traits_type::iterator_category	iterator_category;
		typedef typename __traits_type::value_type			value_type;
		typedef typename __traits_type::difference_type 	difference_type;
		typedef typename __traits_type::reference       	reference;
		typedef typename __traits_type::pointer         	pointer;

		__wrap_iterator(void)
		: __base_ptr(Iterator())
		{ }

		explicit
		__wrap_iterator(const Iterator &rhs)
		: __base_ptr(rhs)
		{ }

		// Allow iterator to const iterator conversion
		template<typename Iter>
		__wrap_iterator(const __wrap_iterator<Iter> &rhs)
		: __base_ptr(rhs.base())
		{ }

		~__wrap_iterator(void)
		{ }

		__wrap_iterator		operator=(const __wrap_iterator &rhs)
		{
			__base_ptr = rhs.base();
			return (*this);
		}

		// Forward Iterator Definition
		reference
		operator*(void) const
		{ return (*__base_ptr); }

		pointer
		operator->(void) const
		{ return (__base_ptr); }

		__wrap_iterator		&
		operator++(void)
		{
			++__base_ptr;
			return (*this);
		}

		__wrap_iterator
		operator++(int)
		{ return (__wrap_iterator(__base_ptr++)); }

		// Bidirectional Iterator Definition
		__wrap_iterator		&
		operator--(void)
		{
			--__base_ptr;
			return (*this);
		}

		__wrap_iterator
		operator--(int)
		{ return (__wrap_iterator(__base_ptr--)); }

		// Random Access Iterator
		reference
		operator[](difference_type n)
		{ return (__base_ptr[n]); }

		__wrap_iterator		&
		operator+=(difference_type n)
		{
			__base_ptr += n;
			return (*this);
		}

		__wrap_iterator
		operator+(difference_type n) const
		{ return (__wrap_iterator(__base_ptr + n)); }

		__wrap_iterator		&
		operator-=(difference_type n)
		{
			__base_ptr -= n;
			return (*this);
		}
		__wrap_iterator
		operator-(difference_type n) const
		{ return (__wrap_iterator(__base_ptr - n)); }

		const Iterator		&
		base() const
		{ return (__base_ptr); }
	};

	// Forward Iterator Continuations
	template < typename Iter1, typename Iter2 >
	inline bool
	operator==(const __wrap_iterator<Iter1> &lhs, const __wrap_iterator<Iter2> &rhs)
	{ return (lhs.base() == rhs.base()); }

	template < typename Iter1, typename Iter2 >
	inline bool
	operator!=(const __wrap_iterator<Iter1> &lhs, const __wrap_iterator<Iter2> &rhs)
	{ return (lhs.base() != rhs.base()); }

	// Random Access Iterator Continuation

	template < typename Iter1, typename Iter2 >
	inline bool
	operator<(const __wrap_iterator<Iter1> &lhs, const __wrap_iterator<Iter2> &rhs)
	{ return (lhs.base() < rhs.base()); }

	template < typename Iter1, typename Iter2 >
	inline bool
	operator>(const __wrap_iterator<Iter1> &lhs, const __wrap_iterator<Iter2> &rhs)
	{ return (lhs.base() > rhs.base()); }

	template < typename Iter1, typename Iter2 >
	inline bool
	operator<=(const __wrap_iterator<Iter1> &lhs, const __wrap_iterator<Iter2> &rhs)
	{ return (lhs.base() <= rhs.base()); }

	template < typename Iter1, typename Iter2 >
	inline bool
	operator>=(const __wrap_iterator<Iter1> &lhs, const __wrap_iterator<Iter2> &rhs)
	{ return (lhs.base() >= rhs.base()); }

	// operator + and - must accept mixed up parametres (const iterator / iterator / numerical values)
	template < typename Iter1, typename Iter2 >
	inline typename __wrap_iterator<Iter1>::difference_type
	operator-(const __wrap_iterator<Iter1> &lhs, __wrap_iterator<Iter2> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template < typename Iter >
	inline __wrap_iterator<Iter>
	operator+(typename __wrap_iterator<Iter>::difference_type n, const __wrap_iterator<Iter> &rhs)
	{ return (__wrap_iterator<Iter>(rhs.base() + n)); }

	// reverse_iterator
	/**
	 * @brief Bidirectional and random access Iterators have corresponding reverse iterator adapters that iterate
	 * through the data structor in the oposite direction, they have the same signature as rhe corresponsing iterators.
	 * 
	 * @tparam Iterator 
	 */
	template < class Iterator >
	class reverse_iterator
		: public __iterator__<	typename iterator_traits<Iterator>::iterator_category,
								typename iterator_traits<Iterator>::value_type,
								typename iterator_traits<Iterator>::difference_type,
								typename iterator_traits<Iterator>::pointer,
								typename iterator_traits<Iterator>::reference >
	{
	protected:
		Iterator	    								current;

		typedef iterator_traits<Iterator>				__traits_type;
	public:
		typedef Iterator                                iterator_type;
		typedef typename __traits_type::difference_type difference_type;
		typedef typename __traits_type::reference       reference;
		typedef typename __traits_type::pointer         pointer;

		reverse_iterator(void) : current() { return; }
		reverse_iterator(Iterator const &iter) : current(iter) { return; }
		template < class __iter >
		reverse_iterator(reverse_iterator<__iter> const &rev_iter) : current(rev_iter.base()) { return; }
		template < class __iter >
		reverse_iterator				&operator=(reverse_iterator<__iter> const &rev_iter) { current = rev_iter.base(); return (*this); }
		~reverse_iterator() {}

		Iterator                        base(void) const { return (this->current); }

		reference                       operator*(void) const { Iterator tmp = this->current; return (*--tmp); }
		reverse_iterator				operator+(difference_type n) const { return (reverse_iterator(current - n)); }
		reverse_iterator                &operator++(void) { --current; return (*this); }
		reverse_iterator                operator++(int) {reverse_iterator tmp(*this); --current; return (tmp); }
		reverse_iterator				&operator+=(difference_type n) { current -= n; return (*this); }
		reverse_iterator				operator-(difference_type n) const { return (reverse_iterator(current + n)); }
		reverse_iterator				&operator--(void) { ++current; return (*this); }
		reverse_iterator				operator--(int) {reverse_iterator tmp(*this); ++current; return (tmp); }
		reverse_iterator				&operator-=(difference_type n) {current += n; return (*this); }
		pointer							operator->(void) const { return (&(operator*())); }
		reference						operator[](difference_type n) { return (*(*this + n)); }
	};

	template < class Iterator >
	bool	operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template < class Iterator >
	bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template < class Iterator >
	bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template < class Iterator >
	bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template < class Iterator >
	bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template < class Iterator >
	bool	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	// end of reveser Iterator
	template < class InputIterator >
	typename ft::iterator_traits<InputIterator>::difference_type		distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type result = 0;
		while (first != last)
		{
			first++;
			result++;
		}
		return (result);
	}

}

#endif