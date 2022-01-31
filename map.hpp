#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <cmath>
#include <memory>
#include <limits>
#include <functional>
#include "pair.hpp"
#include "algorithm.hpp"
#include "iterator.hpp"
#include "choose_const.hpp"
#include "type_traits.hpp"

namespace ft
{
	/**
	 * @brief 
	 * 
	 * @tparam Key 
	 * @tparam T 
	 * @tparam Compare 
	 * @tparam Node 
	 * @tparam B 
	 */
	template <class Key, class T, class Compare, typename Node, bool B>
    class map_iterator
    {
            /* ------------------------------------------------------------- */
            /* -------------------------- ALIASES -------------------------- */

        public:
        
            typedef Key                                             key_type;
            typedef Compare                                         key_compare;
            typedef T                                               mapped_type;
            
            typedef ft::pair<const key_type, mapped_type>           value_type;
            typedef long int                                        difference_type;
            typedef size_t                                          size_type;
            
            typedef std::bidirectional_iterator_tag                                     iterator_category;
            typedef typename chooseConst<B, value_type&, const value_type&>::type       reference;
            typedef typename chooseConst<B, value_type*, const value_type*>::type       pointer;
            typedef Node*                                                               nodePtr;
            

            /* ------------------------------------------------------------- */
            /* ------------------------- ATTRIBUTES ------------------------ */
            
        private:

            nodePtr         _node;      // Pointer to a binary tree's node
            nodePtr         _lastElem;  // Pointer to the dummy node of binary tree
            key_compare     _comp;      // Comparison object used to sort the binary tree
            

            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */

        public:

            /**
            *   Default constructor, creates a map_iterator pointing to a node.
            *
            *   @param node     A pointer to a node containing a T element. Value initialized if not provided.
            *   @param lastElem A pointer to the dummy node of the binary tree. Value initialized if not provided.
            *   @param comp     The comparison object used to sort the binary tree.  Value initialized if not provided.
            */
            map_iterator(nodePtr node = 0, nodePtr lastElem = 0, 
                        const key_compare& comp = key_compare()) :
                _node(node), _lastElem(lastElem), _comp(comp) {}
        
            /**
            *   Copy constructor : creates a const map_iterator pointing to the same node.
            *   Convert constructor : creates a map_iterator from a const map_iterator,
            *   pointing to the same node.
            *   
            *   @param copy     The iterator that will be copied.
            */
            map_iterator(const map_iterator<Key, T, Compare, Node, false>& copy)
            {
                _node = copy.getNode();
                _lastElem = copy.getLastElem();
                _comp = copy.getCompare();
            }
            
            ~map_iterator() {}

            /**
            *   Assigns a map_iterator to this map_iterator. Both iterators will point to the
            *   same node.
            *   
            *   @param x    The map_iterator that will be assigned.
            */
            map_iterator& operator=(const map_iterator& assign)
            {
                if (this != &assign)
                {
                    _node = assign._node;
                    _lastElem = assign._lastElem;
                    _comp = assign._comp;
                }
                return (*this);
            }


            /* ------------------------------------------------------------- */
            /* -------------------------- GETTERS -------------------------- */

            /**
            *   @return A non constant pointer to the actual node that the iterator is 
            *           pointing to.
            */
            nodePtr getNode() const             { return _node; }
            
            /**
            *   @return A non constant pointer to the dummy node at the end of the 
            *           binary tree.
            */
            nodePtr getLastElem() const         { return _lastElem; }
            
            /**
            *   @return The comparison object used to sort the binary tree.
            */
            key_compare getCompare() const      { return _comp; }


            /* ------------------------------------------------------------- */
            /* -------------------------- OPERATORS ------------------------ */
            
            reference operator*() const         { return (_node->content); }
            pointer operator->() const          { return (&_node->content); }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest superior key 
            *   key in the tree.
            */
            map_iterator& operator++()
            {
                // To save base value and compare it with parents if no right son
                nodePtr previousNode = _node;

                // Special case where iterator is on lastElem : we're looping to the beginning
                // of the tree
                if (_node == _lastElem)
                {
                    _node = _lastElem->right;
                    return (*this);
                }

                // _comp is equivalent to operator <. So:
                //      - operator>(lhs, rhs)  <==>  _comp(rhs, lhs)
                //      - operator<=(lhs, rhs)  <==>  !_comp(rhs, lhs)
                //      - operator>=(lhs, rhs)  <==>  !_comp(lhs, rhs)

                // Moving node* until we find a node with an higher value or equal value (_lastElem == end)
                //                            <=> _node->content.first <= previousNode->content.first   
                while (_node != _lastElem && !_comp(previousNode->content.first, _node->content.first))
                {
                    // Case right son is either node with higher value or _lastElem node    
                    if (_node->right && (_node->right == _lastElem || 
                            _comp(previousNode->content.first, _node->right->content.first)))
                            // <=> _node->right->content.first > previousNode->content.first
                    {
                        _node = _node->right;
                        
                        // Starting from the minimum key in the right subtree
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMinNode(_node)))
                            _node = tmp;
                    }

                    // No right son so need to go up of one level and try same loop with node's parent
                    else
                        _node = _node->parent;
                }
                return (*this);
            }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest superior key 
            *   key in the tree.
            */
            map_iterator operator++(int)
            {
                // Same logic than in ++operator
                map_iterator res(*this);

                if (_node == _lastElem)
                {
                    _node = _lastElem->right;
                    return (res);
                }
                
                while (_node != _lastElem && !_comp(res->first, _node->content.first))
                {
                    if (_node->right && (_node->right == _lastElem || 
                            _comp(res->first, _node->right->content.first)))
                    {
                        _node = _node->right;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMinNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }
                
                return (res);
            }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest inferior key 
            *   key in the tree.
            */
            map_iterator& operator--()
            {
                // Opposite logic than in ++operator
                nodePtr previousNode = _node;

                if (_node == _lastElem)
                {
                    _node = _lastElem->left;
                    return (*this);
                }

                while (_node != _lastElem && !_comp(_node->content.first, previousNode->content.first))
                {
                    if (_node->left && (_node->left == _lastElem || 
                            _comp(_node->left->content.first, previousNode->content.first)))
                    {
                        _node = _node->left;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }

                return (*this);
            }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest inferior key 
            *   key in the tree.
            */
            map_iterator operator--(int)
            {
                // Opposite logic than in ++operator
                map_iterator res(*this);

                if (_node == _lastElem)
                {
                    _node = _lastElem->left;
                    return (res);
                }
                
                while (_node != _lastElem && !_comp(_node->content.first, res->first))
                {
                    if (_node->left && (_node->left == _lastElem || 
                            _comp(_node->left->content.first, res->first)))
                    {
                        _node = _node->left;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }
                
                return (res);
            }

            bool operator==(const map_iterator& it) const   { return (it._node == _node); }
            bool operator!=(const map_iterator& it) const   { return (it._node != _node); }


            /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
            /* ------------------------------------------------------------- */

        private:

            /**
            *   Searches for the element with the highest key in the tree.
            *
            *   @param root     First node of the tree.
            *   @param return   The element containing the highest key in the tree.
            */
            Node* searchMaxNode(Node *root)
            {
                // Until we meet tree's right extremity and circular link _lastElem
                if (root && root != _lastElem && root->right && root->right != _lastElem)
                    return searchMaxNode(root->right);
                return root;
            }

            /**
            *   Searches for the element with the lowest key in the tree.
            *
            *   @param root     First node of the tree.
            *   @param return   The element containing the lowest key in the tree.
            */
            Node* searchMinNode(Node *root)
            {
                // Until we meet tree's left extremity and circular link _lastElem
                if (root && root != _lastElem && root->left && root->left != _lastElem)
                    return searchMinNode(root->left);
                return root;
            }
            
    }; // class map_iterator

    template<class Key, class T, class Compare, typename Node, bool B>
    class rev_map_iterator
    {
        /* ------------------------------------------------------------- */
        /* -------------------------- ALIASES -------------------------- */
        
        public:
        
            typedef Key                                             key_type;
            typedef Compare                                         key_compare;
            typedef T                                               mapped_type;
            
            typedef ft::pair<const key_type, mapped_type>           value_type;
            typedef long int                                        difference_type;
            typedef size_t                                          size_type;
            
            typedef std::bidirectional_iterator_tag                                     iterator_category;
            typedef typename chooseConst<B, value_type&, const value_type&>::type       reference;
            typedef typename chooseConst<B, value_type*, const value_type*>::type       pointer;
            typedef Node*                                                               nodePtr;
            

            /* ------------------------------------------------------------- */
            /* ------------------------- ATTRIBUTES ------------------------ */
            
        private:

            nodePtr         _node;      // Pointer to a binary tree's node
            nodePtr         _lastElem;  // Pointer to the dummy node of binary tree
            key_compare     _comp;      // Comparison object used to sort the binary tree
        
        
            /* ------------------------------------------------------------- */
            /* ------------------------ COPLIEN FORM ----------------------- */

        public:
        
            /**
            *   Default constructor, creates a rev_map_iterator pointing to a node.
            *
            *   @param node     A pointer to a node containing a T element. Value initialized if not provided.
            *   @param lastElem A pointer to the dummy node of the binary tree. Value initialized if not provided.
            *   @param comp     The comparison object used to sort the binary tree.  Value initialized if not provided.
            */
            rev_map_iterator(nodePtr node = 0, nodePtr lastElem = 0,
                            const key_compare& comp = key_compare()) :
                _node(node), _lastElem(lastElem), _comp(comp) {}
        
            /**
            *   Copy constructor : creates a const rev_map_iterator pointing to the same node.
            *   Convert constructor : creates a rev_map_iterator from a const rev_map_iterator,
            *   pointing to the same node.
            *   
            *   @param copy     The iterator that will be copied.
            */
            rev_map_iterator(const rev_map_iterator<Key, T, Compare, Node, false>& copy)
            {
                _node = copy.getNonConstNode();
                _lastElem = copy.getNonConstLastElem();
                _comp = copy.getCompare();
            }
            
            /**
            *   Convert constructor : creates a rev_map_iterator from a const / not const 
            *   map_iterator, pointing to the previous T element. This is necessary so 
            *   begin() == rend(), and end == rbegin().
            *   
            *   @param copy     The map_iterator that will be converted.
            */
            explicit rev_map_iterator(map_iterator<Key, T, Compare, Node, false> copy)
            {
                --copy;
                _node = copy.getNonConstNode();
                _lastElem = copy.getNonConstLastElem();
                _comp = copy.getCompare();
            }

            ~rev_map_iterator() {}

            /**
            *   Assigns a rev_map_iterator to this rev_map_iterator. Both iterators will point to the
            *   same node.
            *   
            *   @param x    The rev_map_iterator that will be assigned.
            */
            rev_map_iterator& operator=(const rev_map_iterator& assign)
            {
                if (this != &assign)
                {
                    _node = assign._node;
                    _lastElem = assign._lastElem;
                    _comp = assign._comp;
                }
                return (*this);
            }


            /* ------------------------------------------------------------- */
            /* --------------------------- GETTERS ------------------------- */

            /**
            *   @return A non constant pointer to the actual node that the iterator is 
            *           pointing to.
            */
            nodePtr getNonConstNode() const         { return _node; }

            /**
            *   @return A non constant pointer to the dummy node at the end of the 
            *           binary tree.
            */
            nodePtr getNonConstLastElem() const     { return _lastElem; }

            /**
            *   @return The comparison object used to sort the binary tree.
            */
            key_compare getCompare() const          { return _comp; }


            /* ------------------------------------------------------------- */
            /* -------------------------- OPERATORS ------------------------ */

            reference operator*() const             { return (_node->content); }
            pointer operator->() const              { return (&_node->content); }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest inferior key 
            *   key in the tree.
            */
            rev_map_iterator& operator++()
            {
                // Opposite logic than in --operator
                nodePtr previousNode = _node;

                if (_node == _lastElem)
                {
                    _node = _lastElem->left;
                    return (*this);
                }

                while (_node != _lastElem && !_comp(_node->content.first, previousNode->content.first))
                {
                    if (_node->left && (_node->left == _lastElem || 
                            _comp(_node->left->content.first, previousNode->content.first)))
                    {
                        _node = _node->left;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }

                return (*this);
            }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest inferior key 
            *   key in the tree.
            */
            rev_map_iterator operator++(int)
            {
                // Opposite logic than in --operator
                rev_map_iterator res(*this);

                if (_node == _lastElem)
                {
                    _node = _lastElem->left;
                    return (res);
                }
                
                while (_node != _lastElem && !_comp(_node->content.first, res->first))
                {
                    if (_node->left && (_node->left == _lastElem || 
                            _comp(_node->left->content.first, res->first)))
                    {
                        _node = _node->left;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }
                
                return (res);
            }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest superior key 
            *   key in the tree.
            */
            rev_map_iterator& operator--()
            {
                // To save base value and compare it with parents if no right son
                nodePtr previousNode = _node;

                // Special case where iterator is on lastElem : we're looping to the beginning
                // of the tree
                if (_node == _lastElem)
                {
                    _node = _lastElem->right;
                    return (*this);
                }

                // _comp is equivalent to operator <. So:
                //      - operator>(lhs, rhs)  <==>  _comp(rhs, lhs)
                //      - operator<=(lhs, rhs)  <==>  !_comp(rhs, lhs)
                //      - operator>=(lhs, rhs)  <==>  !_comp(lhs, rhs)

                // Moving node* until we find a node with an higher value or equal value (_lastElem == end)
                //                              <=> _node->content.first <= previousNode->content.first)
                while (_node != _lastElem && !_comp(previousNode->content.first, _node->content.first))
                {
                    // Case right son is either node with higher value or _lastElem node    
                    if (_node->right && (_node->right == _lastElem || 
                        // <=> _node->right->content.first > previousNode->content.first))
                            _comp(previousNode->content.first, _node->right->content.first)))
                    {
                        _node = _node->right;
                        
                        // Starting from the minimum key in the right subtree
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMinNode(_node)))
                            _node = tmp;
                    }

                    // No right son so need to go up of one level and try same loop with node's parent
                    else
                        _node = _node->parent;
                }
                return (*this);
            }

            /**
            *   Starts from a specific key inside the tree, and looks for the closest superior key 
            *   key in the tree.
            */
            rev_map_iterator operator--(int)
            {
                // Same logic than in ++operator
                rev_map_iterator res(*this);

                if (_node == _lastElem)
                {
                    _node = _lastElem->right;
                    return (res);
                }
                
                while (_node != _lastElem && !_comp(res->first, _node->content.first))
                {
                    if (_node->right && (_node->right == _lastElem || 
                            _comp(res->first, _node->right->content.first)))
                    {
                        _node = _node->right;
                        
                        Node* tmp = 0;
                        if (_node != _lastElem && (tmp = searchMinNode(_node)))
                            _node = tmp;
                    }
                    else
                        _node = _node->parent;
                }
                
                return (res);
            }

            bool operator==(const rev_map_iterator& it) const   { return (it._node == _node); }
            bool operator!=(const rev_map_iterator& it) const   { return (it._node != _node); }


            /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
            /* ------------------------------------------------------------- */
            
        private:

            /**
            *   Searches for the element with the highest key in the tree.
            *
            *   @param root     First node of the tree.
            *   @param return   The element containing the highest key in the tree.
            */
            Node* searchMaxNode(Node *root)
            {
                // Until we meet tree's right extremity and circular link _lastElem
                if (root && root != _lastElem && root->right && root->right != _lastElem)
                    return searchMaxNode(root->right);
                return root;
            }

            /**
            *   Searches for the element with the lowest key in the tree.
            *
            *   @param root     First node of the tree.
            *   @param return   The element containing the lowest key in the tree.
            */
            Node* searchMinNode(Node *root)
            {
                // Until we meet tree's left extremity and circular link _lastElem
                if (root && root != _lastElem && root->left && root->left != _lastElem)
                    return searchMinNode(root->left);
                return root;
            }

    }; // class rev_map_iterator


	template < class Key, class T, class Compare = ft::less<Key>, 
            class Alloc = std::allocator<ft::pair<const Key, T> >
    > class map
    {
        private:        

            struct Node
            {
                ft::pair<const Key, T>  content;
                Node*                   parent;
                Node*                   left;
                Node*                   right;
            };
            
        public:

            typedef Key                                             key_type;
            typedef Compare                                         key_compare;
            typedef Alloc                                           allocator_type;
            typedef T                                               mapped_type;
            
            typedef ft::pair<const key_type, mapped_type>           value_type;
            typedef long int                                        difference_type;
            typedef size_t                                          size_type;

            typedef T&                                              reference;
            typedef const T&                                        const_reference;
            typedef T*                                              pointer;
            typedef const T*                                        const_pointer;
            
            typedef typename ft::map_iterator<Key, T, Compare, Node, false>     iterator;
            typedef typename ft::map_iterator<Key, T, Compare, Node, true>      const_iterator;

            typedef typename ft::rev_map_iterator<Key, T, Compare, Node, false> reverse_iterator;
            typedef typename ft::rev_map_iterator<Key, T, Compare, Node, true>  const_reverse_iterator;

            class value_compare
            {
                friend class map;
                
                protected:
                
                    key_compare comp;
                    
                    value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object

                public:
                
                    typedef bool        result_type;
                    typedef value_type  first_argument_type;
                    typedef value_type  second_argument_type;

                    bool operator()(const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            };
            
        private:

            Node*                   _root;          // Pointer to the first element of the tree (root)
            Node*                   _lastElem;      // Pointer to the last elem of the tree
            size_type               _size;          // Number of T values inside the map
            allocator_type          _allocPair;     // Copy of allocator_type object
            key_compare             _comp;          // Copy of comp key_compare predicate
            std::allocator<Node>     _allocNode;     // Node's allocator
            
        public:
            
            explicit map(const key_compare& comp = key_compare(),
                        const allocator_type& alloc = allocator_type()) :
                _size(0), _allocPair(alloc), _comp(comp)
            {
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;
            }

            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type(), 
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
                _size(0), _allocPair(alloc), _comp(comp)
            {
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;
                
                for (; first != last; ++first)
                    insert(*first);
            }

            map(const map& x) :
                _size(0), _allocPair(x._allocPair), _comp(x._comp), _allocNode(x._allocNode)
            {
                _lastElem = createNode(ft::pair<const key_type, mapped_type>());
                _root = _lastElem;
                _lastElem->left = _lastElem;
                _lastElem->right = _lastElem;

                for (const_iterator it = x.begin(); it != x.end(); ++it)
                    insert(*it);
            }
            ~map()
            {
                clear();
                deallocateNode(_lastElem);
            }

            map& operator=(const map& x)
            {
                map tmp(x);
                this->swap(tmp);
                
                return *this;
            }

            iterator begin()                        { return iterator(_lastElem->right, _lastElem, _comp); }
            const_iterator begin() const            { return const_iterator(_lastElem->right, _lastElem, _comp); }
            iterator end()                          { return iterator(_lastElem, _lastElem, _comp); }
            const_iterator end() const              { return const_iterator(_lastElem, _lastElem, _comp); }
            reverse_iterator rbegin()               { return reverse_iterator(_lastElem->left, _lastElem, _comp); }
            const_reverse_iterator rbegin() const   { return const_reverse_iterator(_lastElem->left, _lastElem, _comp); }
            reverse_iterator rend()                 { return reverse_iterator(_lastElem, _lastElem, _comp); }
            const_reverse_iterator rend() const     { return const_reverse_iterator(_lastElem, _lastElem, _comp); }
            bool empty() const              { return _size == 0; }
            size_type size() const          { return _size; }
            size_type       max_size() const
            {
                return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type))) - 1;
            }
            mapped_type& operator[](const key_type& k)
            {
                Node* tmp = searchNode(_root, k);

                if (tmp)
                    return tmp->content.second;

                value_type val = make_pair<key_type, mapped_type>(k, mapped_type());
                return insertNode(_root, val)->content.second;
            }
            
            ft::pair<iterator,bool> insert (const value_type& val)
            {
                // Searches in the tree if val's key is already present and returns 
                // an iterator to the key inside the tree if it's the case
                Node* elemIsPresent = searchNode(_root, val.first);
                if (elemIsPresent)
                    return ft::pair<iterator, bool>(iterator(elemIsPresent, _lastElem, _comp), false);

                // Inserts the pair in the tree and returns an iterator to its position
                ++_size;
                return ft::pair<iterator, bool>(iterator(insertNode(_root, val), _lastElem, _comp), true);
            }
            iterator insert (iterator position, const value_type& val)
            {   
                // If position key is higher than val, we need to decrease position 
                // until we find the closest highest key from val in the tree
                if (position->first > val.first)
                {
                    iterator prev(position);
                    --prev;
                    while (prev != end() && prev->first >= val.first)
                    {
                        --position;
                        --prev;
                    }
                }

                // Opposite case
                else if (position->first < val.first)
                {
                    iterator next(position);
                    ++next;
                    while (next != end() && next->first <= val.first)
                    {
                        ++position;
                        ++next;
                    }
                }

                // If the value already exist, and the tree isn't empty
                if (position != end() && val.first == position->first)
                    return position;

                ++_size;
                return iterator(insertNode(position.getNode(), val), _lastElem, _comp);
            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last,
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
            {
                while (first != last)
                    insert(*first++);
            }
            void erase (iterator position)
            {
                deleteNode(position.getNode(), position->first);
                --_size;
            }

            size_type erase (const key_type& k)
            {
                size_type ret = deleteNode(_root, k);
                _size -= ret;
                return ret;
            }

            void erase (iterator first, iterator last)
            {
                while (first != last)
                {
                    iterator tmp(first);
                    ++first;
                    erase(tmp);
                }
            }

            void swap (map& x)
            {
                swap(_root, x._root);
                swap(_lastElem, x._lastElem);
                swap(_size, x._size);
                swap(_comp, x._comp);
                swap(_allocPair, x._allocPair);
                swap(_allocNode, x._allocNode);
            }

            void clear()        { erase(begin(), end()); }


            key_compare key_comp() const        { return _comp; }

            value_compare value_comp() const    { return value_compare(_comp); }
            
            
           
            iterator find(const key_type& k)
            {
                Node* tmp = searchNode(_root, k);

                if (tmp)
                    return iterator(tmp, _lastElem, _comp);
                
                // Case no match
                return end();
            }

            const_iterator find(const key_type& k) const
            {
                Node* tmp = searchNode(_root, k);

                if (tmp)
                    return const_iterator(tmp, _lastElem, _comp);
                
                // Case no match
                return end();
            }

            
            size_type count (const key_type& k) const
            {
                Node* tmp = searchNode(_root, k);
                
                return tmp ? true: false;
            }

            iterator lower_bound(const key_type& k)
            {
                iterator it = begin();

                for (; it != end(); ++it)
                    if (!_comp(it->first, k))
                        break;
                
                return it;  
            }
            
          
            const_iterator lower_bound(const key_type& k) const
            {
                const_iterator it = begin();

                for (; it != end(); ++it)
                    if (!_comp(it->first, k))
                        break;
                
                return it;  
            }

            iterator upper_bound(const key_type& k)
            {
                iterator it = begin();

                for (; it != end(); ++it)
                    if (_comp(k, it->first))
                        break;
                
                return it;  
            }

            const_iterator upper_bound(const key_type& k) const
            {
                const_iterator it = begin();

                for (; it != end(); ++it)
                    if (_comp(k, it->first))
                        break;
                
                return it;  
            }

            pair<iterator,iterator> equal_range(const key_type& k)
            {
                iterator it = upper_bound(k);

                if (it != begin())
                {
                    --it;

                    if (_comp(it->first, k) || _comp(k, it->first))
                        ++it;
                }

                iterator next(it);
                if (it != end())
                    ++next;
                
                return make_pair<iterator, iterator>(it, next);
            }

            pair<const_iterator,const_iterator> equal_range(const key_type& k) const
            {
                const_iterator it = upper_bound(k);

                if (it != begin())
                {
                    --it;

                    if (_comp(it->first, k) || _comp(k, it->first))
                        ++it;
                }

                const_iterator next(it);
                if (it != end())
                    ++next;
                
                return make_pair<const_iterator, const_iterator>(it, next);
            }

        private:

            template <typename U>
            void swap(U& a, U& b)
            {
                U tmp = a;
                a = b;
                b = tmp;
            }

            template <class T1,class T2>
            pair<T1,T2> make_pair(T1 x, T2 y) const
            {
                return pair<T1,T2>(x,y);
            }

            Node* createNode(const value_type& pair)
            {
                Node* newNode = _allocNode.allocate(1);

                _allocPair.construct(&newNode->content, pair);
                newNode->parent = 0;
                newNode->left = 0;
                newNode->right = 0;

                return newNode;
            }

            void deallocateNode(Node* del)
            {
                _allocPair.destroy(&del->content);
                _allocNode.deallocate(del, 1);
            }

            int heightTree(Node *root, int height)
            {
                // We reached a NULL, returning
                if (!root || root == _lastElem)
                    return height - 1;

                // Exploring left side of the actual node, then right side
                int leftHeight = heightTree(root->left, height + 1);
                int rightHeight = heightTree(root->right, height + 1);

                return leftHeight > rightHeight ? leftHeight : rightHeight;
            }

            Node* searchNode(Node* root, key_type key) const
            {
                // We reached a leaf or tree is empty
                if (!root || root == _lastElem)
                    return 0;
                
                // Case we find a match
                if (!_comp(root->content.first, key) && !_comp(key, root->content.first))
                    return root;
                
                // Recursive loop until we find key
                if (root->content.first > key && root->left && root->left != _lastElem)
                    return searchNode(root->left, key);
                else if (root->content.first < key && root->right && root->right != _lastElem)
                    return searchNode(root->right, key);

                // If we reach this step in the first searchNode func that was called
                // with root (first node of the tree), then element is missing.
                return 0;
            }

            Node* searchMaxNode(Node *root) const
            {
                // Until we meet tree's right extremity and circular link _lastElem
                if (root->right && root->right != _lastElem)
                    return searchMaxNode(root->right);
                return root;
            }

            Node* searchMinNode(Node *root) const
            {
                // Until we meet tree's left extremity and circular link _lastElem
                if (root->left && root->left != _lastElem)
                    return searchMinNode(root->left);
                return root;
            }

            Node* insertNode(Node* insertPos, const value_type& pair)
            {
                // Case creating first node of the tree
                if (_root == _lastElem)
                {
                    _root = createNode(pair);
                    
                    _root->left = _lastElem;
                    _root->right = _lastElem;
                    _lastElem->left = _root;
                    _lastElem->right = _root;

                    return _root;
                }

                // Case key already exist in the tree
                if (insertPos->content.first == pair.first)
                    return 0;

                // Recursive loop until we reach a leaf or fake last node (_lastElem)
                if (insertPos->content.first > pair.first && 
                        insertPos->left && insertPos->left != _lastElem)
                    return insertNode(insertPos->left, pair);
                else if (insertPos->content.first < pair.first && 
                        insertPos->right && insertPos->right != _lastElem)
                    return insertNode(insertPos->right, pair);

                // If we reach this step, we arrived to a leaf or to the max node / min node 
                // of the tree (they're both linked to _lastElem): inserting new node to his correct position
                Node *newNode = createNode(pair);

                // Case we reached a left or right leaf
                if (insertPos->content.first > newNode->content.first && !insertPos->left)
                    insertPos->left = newNode;
                else if (insertPos->content.first < newNode->content.first && !insertPos->right)
                    insertPos->right = newNode;

                // Case we reach min node or max node, inserting the node between min / max
                // and lastElem
                else if (insertPos->left && insertPos->content.first > newNode->content.first)
                {
                    newNode->left = _lastElem;
                    _lastElem->right = newNode;
                    insertPos->left = newNode;
                }
                else if (insertPos->right && insertPos->content.first < newNode->content.first)
                {
                    newNode->right = _lastElem;
                    _lastElem->left = newNode;
                    insertPos->right = newNode;
                }
                    
                newNode->parent = insertPos;

                // Equilibrating the tree from newNode to root node
                balanceTheTree(&_root, newNode);

                return newNode;
            }

            bool deleteNode(Node* deletePos, key_type key)
            {
                // Balance node will point to the first node impacted by the deletion (if we delete a node, 
                // it will be the parent node; if we delete root, it will be one of his son). 
                // We will then call balanceTheTree function to equilibrate the AVL tree
                Node* balanceNode = 0;
                
                // The node to delete, looking from deletePos node until we match key
                Node* del = searchNode(deletePos, key);

                // If element isn't present, nothing to delete
                if (!del)
                    return false;
                
                /* --------------- CASE DELETING ROOT --------------- */
                // Case the node to delete is the root
                if (!del->parent)
                {
                    // Root is the only node in the tree, it will be empty
                    if (del->left == _lastElem && del->right == _lastElem)
                    {
                        _root = _lastElem;
                        _lastElem->left = _lastElem;
                        _lastElem->right = _lastElem;
                    }

                    // Case only one son (left or right, need to equilibrate the tree
                    // for only root)
                    else if (del->left && del->right == _lastElem)
                    {
                        balanceNode = del->parent;
                        _root = del->left;
                        del->left->parent = 0;
                        
                        // Since the tree is AVL, if _root has only one son, this son is 
                        // a leaf and has no left and right son. So the new root has to be 
                        // llastElem from left and right side, but he's already 
                        // linked to inked to _it from one side (in this case, left)
                        _lastElem->left = del->left;
                        del->left->right = _lastElem;
                    }
                    else if (del->left == _lastElem && del->right)
                    {
                        balanceNode = del->parent;
                        _root = del->right;
                        del->right->parent = 0;

                        // Same explanation but with opposite side than just above
                        _lastElem->right = del->right;
                        del->right->left = _lastElem;
                    }
                    
                    // Case two sons, need to switch the key of the node to delete with the highest key
                    // in the left subtree, and to delete the node with this highest key in the left subtree
                    else
                    {
                        Node* maxNode = searchMaxNode(del->left);
                        
                        // Need to destroy then construct for copying const variable)
                        _allocPair.destroy(&del->content);
                        _allocPair.construct(&del->content, maxNode->content);
                        
                        return deleteNode(del->left, maxNode->content.first);
                    }
                }


                /* --------------- CASE DELETING NODE --------------- */
                // Case the node to delete is a leaf
                else if ((!del->left || del->left == _lastElem) && (!del->right || del->right == _lastElem))
                {
                    balanceNode = del->parent;

                    // Case min node / max node, linking differs for _lastElem
                    Node* linkToParent = 0;
                    if (del->left == _lastElem || del->right == _lastElem)
                    {
                        linkToParent = _lastElem;
                        del->content.first <= del->parent->content.first ?
                            _lastElem->right = del->parent : _lastElem->left = del->parent;
                    }
                        
                    del->content.first <= del->parent->content.first ?
                        del->parent->left = linkToParent : del->parent->right = linkToParent;
                }
                
                // Case only one son (only left son or only right son)
                else if ((del->left && del->left != _lastElem) && (!del->right || del->right == _lastElem))
                {
                    balanceNode = del->parent;

                    del->content.first <= del->parent->content.first ?
                            del->parent->left = del->left : del->parent->right = del->left;
                    del->left->parent = del->parent;

                    // Case the node to delete is max node, need to relink _lastElem
                    if (del->right == _lastElem)
                    {
                        _lastElem->left = del->left;
                        del->left->right = _lastElem;
                    }
                }
                else if ((!del->left || del->left == _lastElem) && del->right && del->right != _lastElem)
                {
                    balanceNode = del->parent;

                    del->content.first <= del->parent->content.first ?
                            del->parent->left = del->right : del->parent->right = del->right;
                    del->right->parent = del->parent;
                    
                    // Case the node to delete is max node, need to relink _lastElem
                    if (del->left == _lastElem)
                    {
                        _lastElem->right = del->right;
                        del->right->left = _lastElem;
                    }
                }

                // Case two sons, need to switch the key of the node to delete with the highest key
                // in the left subtree, and to delete the node with this highest key in the left subtree
                else
                {
                    Node* maxNode = searchMaxNode(del->left);

                    // Need to destroy then construct for copying const variable)
                    _allocPair.destroy(&del->content);
                    _allocPair.construct(&del->content, maxNode->content);
                    
                    return deleteNode(del->left, maxNode->content.first);
                }

                // Equilibrating the tree from balanceNode to root node
                balanceTheTree(&_root, balanceNode);

                deallocateNode(del);
                return true;
            }

            int balanceOfSubtrees(Node* node)
            {
                if (!node)
                    return 0;
                return heightTree(node->left, 1) - heightTree(node->right, 1);
            }

            void rotateRight(Node** root, Node* nodeGoingDown)
            {
                //   P (nodeGoingUp) is going up and will replace Q (nodeGoingDown)
                //
                //
                //               Q                                 P              |
                //              / \     RIGHT ROTATION            / \             |
                //             P   C  ------------------->>>     A   Q            |
                //            / \                                   / \           |
                //           A   B                                 B   C          |

                Node* nodeGoingUp = nodeGoingDown->left;
                
                // Left Q' son become right P' son
                nodeGoingDown->left = nodeGoingUp->right;
                
                // Case right son is NULL to prevent segfault
                if (nodeGoingUp->right)
                    nodeGoingUp->right->parent = nodeGoingDown;
                
                // rigth P' son is Q
                nodeGoingUp->right = nodeGoingDown;
                
                // Parent P = Parent Q
                nodeGoingUp->parent = nodeGoingDown->parent;
                
                // Determinating if Q has a parent (if not, Q is root) and if it's the case,
                // determinating if it's left son or right son. Then updating Q's parent with
                // his new son, P node
                if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
                    nodeGoingDown->parent->left = nodeGoingUp;
                else if (nodeGoingDown->parent)
                    nodeGoingDown->parent->right = nodeGoingUp;
                
                // Parent of Q is now P
                nodeGoingDown->parent = nodeGoingUp;

                // Updating root node if the rotation occured on root
                if (!nodeGoingUp->parent)
                    *root = nodeGoingUp;
            }

            void rotateLeft(Node** root, Node* nodeGoingDown)
            {
                //   Q (nodeGoingUp) is going up and will replace P (nodeGoingDown)
                //
                //
                //               Q                                 P              |
                //              / \          LEFT ROTATION        / \             |
                //             P   C    <<<-------------------   A   Q            |
                //            / \                                   / \           |
                //           A   B                                 B   C          |

                Node* nodeGoingUp = nodeGoingDown->right;
                
                // Right P' son become left Q' son
                nodeGoingDown->right = nodeGoingUp->left;

                // Case Q left son is NULL to prevent segfault
                if (nodeGoingUp->left)
                    nodeGoingUp->left->parent = nodeGoingDown;
                
                // Left Q' son is now P
                nodeGoingUp->left = nodeGoingDown;
                
                // Parent Q = Parent P
                nodeGoingUp->parent = nodeGoingDown->parent;
                
                // Determinating if P has a parent (if not, P is root) and if it's the case,
                // determinating if it's left son or right son. Then updating P's parent with
                // his new son, Q node
                if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
                    nodeGoingDown->parent->left = nodeGoingUp;
                else if (nodeGoingDown->parent)
                    nodeGoingDown->parent->right = nodeGoingUp;

                // Parent of P is now Q
                nodeGoingDown->parent = nodeGoingUp;

                // Updating root node if the rotation occured on root
                if (!nodeGoingUp->parent)
                    *root = nodeGoingUp;
            }

            void balanceTheTree(Node** root, Node* node)
            {
                // Checking balance of subtrees every parents of this node until we 
                // reach root node          
                while (node)
                {
                    int balance;
                    
                    // Right right case (right subtree is deeper, and right right subtree aswell)
                    if ((balance = balanceOfSubtrees(node)) < -1 && balanceOfSubtrees(node->right) < 0)
                        rotateLeft(root, node);

                    // Right left case (if balance of right node == 0, no difference between right 
                    // right case and and right left case)
                    else if (balance < -1 && balanceOfSubtrees(node->right) >= 0)
                    {
                        rotateRight(root, node->right);
                        rotateLeft(root, node);
                    }
                    
                    // Left left case (opposite of right right case)
                    else if (balance > 1 && balanceOfSubtrees(node->left) > 0)
                        rotateRight(root, node);

                    // Left right case (opposite of right left case)
                    else if (balance > 1 && balanceOfSubtrees(node->left) <= 0)
                    {
                        rotateLeft(root, node->left);
                        rotateRight(root, node);
                    }
                    node = node->parent;
                }
            }
            
    };  // class map
} // namespace ft

#endif          node = node->parent;
                }
            }
            
    };  // class map
} // namespace ft

#endif