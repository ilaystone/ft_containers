#ifndef __PAIR_HPP__
#define __PAIR_HPP__

namespace ft
{
	/**
	 * @brief structure holding two values of diffrent types
	 * 
	 * @tparam T1 first type
	 * @tparam T2 second type
	 */
	template < typename T1, typename T2 >
	class pair
	{
	public:
		// * Aliases
		typedef	T1		first_type;
		typedef T2		second_type;

		// * Member types
		first_type		first;
		second_type		second;

		// * Coplien form
		/**
		 * @brief Default constructor, initialize values
		 * 
		 */
		pair()
		:	first(),
			second()
		{ }
		/**
		 * @brief Construct a new pair object, initialize values from @a and @b
		 * 
		 * @param a value of first
		 * @param b value of second
		 */
		pair(const first_type &a, const second_type &b)
		:	first(a),
			second(b)
		{ }
		/**
		 * @brief Construct a new pair object, intializes values from @rhs
		 * 
		 * @tparam U first_type
		 * @tparam V second_type
		 * @param rhs pair to copy
		 */
		template < class U, class V >
		pair(const pair<U, V> &rhs)
		:	first(rhs.first),
			second(rhs.second)
		{ }
		/**
		 * @brief assigns the new pair to this
		 * 
		 * @param rhs pair to copy
		 * @return pair& 
		 */
		pair	&operator=(const pair &rhs)
		{
			if (this != &rhs)
			{
				first = rhs.first;
				second = rhs.second;
			}
			return (*this);
		}
	}; // class pair

	// * pair relational operations
	/**
	 * @brief compaires lhs and rhs returns true if equal false if not
	 * 
	 * @tparam T1 type of first
	 * @tparam T2 type of second
	 * @param lhs left pair
	 * @param rhs right pair
	 * @return true 
	 * @return false 
	 */
	template < class T1, class T2 >
	bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	/**
	 * @brief compaires lhs and rhs returns true if equal false if not
	 * 
	 * @tparam T1 type of first
	 * @tparam T2 type of second
	 * @param lhs left pair
	 * @param rhs right pair
	 * @return true 
	 * @return false 
	 */
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs==rhs);
	}
	/**
	 * @brief compaires lhs and rhs returns true if equal false if not
	 * 
	 * @tparam T1 type of first
	 * @tparam T2 type of second
	 * @param lhs left pair
	 * @param rhs right pair
	 * @return true 
	 * @return false 
	 */
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	}
	/**
	 * @brief compaires lhs and rhs returns true if equal false if not
	 * 
	 * @tparam T1 type of first
	 * @tparam T2 type of second
	 * @param lhs left pair
	 * @param rhs right pair
	 * @return true 
	 * @return false 
	 */
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs<lhs);
	}
	/**
	 * @brief compaires lhs and rhs returns true if equal false if not
	 * 
	 * @tparam T1 type of first
	 * @tparam T2 type of second
	 * @param lhs left pair
	 * @param rhs right pair
	 * @return true 
	 * @return false 
	 */
	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return rhs<lhs;
	}
	/**
	 * @brief compaires lhs and rhs returns true if equal false if not
	 * 
	 * @tparam T1 type of first
	 * @tparam T2 type of second
	 * @param lhs left pair
	 * @param rhs right pair
	 * @return true 
	 * @return false 
	 */
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs<rhs);
	}
	/**
	 * @brief creates a new paire from values passed
	 * 
	 * @tparam T1 type of first
	 * @tparam T2 type of second
	 * @param x value of first
	 * @param y value of second
	 * @return pair<T1,T2>
	 */
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 &x, T2 &y)
	{
		return ( pair<T1,T2>(x,y) );
	}

} // namespace ft

#endif
