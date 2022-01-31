#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <cstdio>

#include "pair.hpp"
#include "iterator.hpp"
#include "iterator_traits.hpp"

#define BLACK false
#define RED true
#define RIGHT 'R'
#define LEFT 'L'
#define NONE 'N'

namespace ft
{

	template <typename T>
	class TreeNode
	{
	public:
		typedef T value_type;
		typedef TreeNode<T> *node_ptr;

		bool color;
		bool isRightChild;
		node_ptr parent;
		node_ptr left;
		node_ptr right;
		value_type value;

		TreeNode(value_type const &value = value_type(),
				 bool color = RED,
				 node_ptr parent = nullptr,
				 node_ptr left = nullptr,
				 node_ptr right = nullptr,
				 bool isRightChild = true)
			: color(color),
			  isRightChild(isRightChild),
			  parent(parent),
			  left(left),
			  right(right),
			  value(value)
		{
		}

		TreeNode(TreeNode const &other)
			: color(other.color),
			  isRightChild(other.isRightChild),
			  parent(other.parent),
			  left(other.left),
			  right(other.right),
			  value(other.value)
		{
		}

		~TreeNode()
		{
		}

		void linkRight(node_ptr nodePtr)
		{
			nodePtr->parent = this;
			nodePtr->right = this->right;
			if (this->right)
				this->right->parent = nodePtr;
			this->right = nodePtr;
			nodePtr->isRightChild = true;
		}

		void linkLeft(node_ptr nodePtr)
		{
			nodePtr->parent = this;
			this->left = nodePtr;
			nodePtr->isRightChild = false;
		}

		node_ptr unlinkRight(node_ptr nodePtr)
		{
			this->right = nullptr;
			return nodePtr;
		}

		node_ptr unlinkLeft(node_ptr nodePtr)
		{
			this->left = nullptr;
			return nodePtr;
		}

		void copyLinks(node_ptr node)
		{
			node->parent = this->parent;
			if (this->parent != nullptr)
			{
				if (this->isRightChild)
					node->parent->right = node;
				else
					node->parent->left = node;
			}
			node->left = this->left;
			if (node->left != nullptr)
				node->left->parent = node;
			node->right = this->right;
			if (node->right != nullptr)
				node->right->parent = node;
			node->isRightChild = this->isRightChild;
		}

		bool isLeaf(node_ptr end) const
		{
			return (this->left == nullptr && (this->right == end || this->right == nullptr));
		}

		ft::pair<node_ptr, bool> hasOnlyOneChild(node_ptr end) const
		{
			if (this->left == nullptr && (this->right != nullptr && this->right != end))
				return ft::make_pair(this->right, true);
			if (this->left != nullptr && (this->right == nullptr || this->right == end))
				return ft::make_pair(this->left, true);
			return ft::make_pair(nullptr, false);
		}

	}; // struct TreeNode

	// TreeIterator : Binary Search Tree Iterator definition
	template <typename T>
	class TreeIterator : public __iterator__<std::bidirectional_iterator_tag,
										 typename ft::iterator_traits<T *>::value_type>
	{
	public:
		typedef TreeNode<T> *node_ptr;
		typedef T value_type;

		TreeIterator(node_ptr pos = nullptr) : current(pos), end(findEnd(current))
		{
		}

		TreeIterator(TreeIterator const &other)
		{
			*this = other;
		}

		TreeIterator &operator=(TreeIterator const &other)
		{
			if (this != &other)
			{
				this->current = other.current;
				this->end = other.end;
			}
			return *this;
		}

		~TreeIterator() {}

		bool operator==(TreeIterator const &other) const
		{
			return (this->current == other.current);
		}

		bool operator!=(TreeIterator const &other) const
		{
			return (this->current != other.current);
		}

		value_type &operator*() const
		{
			return this->current->value;
		}

		value_type *operator->() const
		{
			return &(this->current->value);
		}

		TreeIterator &operator++()
		{
			if (this->current == end)
			{
				this->current = nullptr;
				return *this;
			}
			if (this->current->right != nullptr)
			{
				this->current = this->current->right;
				while (this->current->left != nullptr)
					this->current = this->current->left;
			}
			else
			{
				while (this->current->isRightChild)
				{
					this->current = this->current->parent;
				}
				this->current = this->current->parent;
			}
			return *this;
		}

		TreeIterator operator++(int)
		{
			TreeIterator tmp(*this);
			++(*this);
			return tmp;
		}

		TreeIterator &operator--()
		{
			if (this->current == nullptr)
				return *this;
			if (this->current->left != nullptr)
			{
				this->current = this->current->left;
				while (this->current->right != nullptr)
					this->current = this->current->right;
			}
			else
			{
				if (this->current->isRightChild)
				{
					this->current = this->current->parent;
				}
			}
			return *this;
		}

		TreeIterator operator--(int)
		{
			TreeIterator tmp(*this);
			--(*this);
			return tmp;
		}

		node_ptr const &asPointer() const
		{
			return this->current;
		}

	protected:
		node_ptr current;
		node_ptr end;

		// define find end
		node_ptr findEnd(node_ptr curr) const
		{
			if (curr == nullptr)
				return nullptr;
			while (curr->parent != nullptr)
				curr = curr->parent;
			while (curr->right != nullptr)
				curr = curr->right;
			return curr;
		}
	};

	// TreeConstIterator : Binary Search Tree Const Iterator definition
	template <typename T>
	class ConstTreeIterator : public TreeIterator<T>
	{
	public:
		typedef TreeNode<T> *node_ptr;
		typedef T value_type;

		ConstTreeIterator(node_ptr pos = nullptr) : TreeIterator<T>(pos) {}

		ConstTreeIterator(ConstTreeIterator const &other) : TreeIterator<T>(other) {}

		ConstTreeIterator(TreeIterator<value_type> const &other) : TreeIterator<value_type>(other) {}

		~ConstTreeIterator() {}
	};

	// BinarySearchTree class definition
	template <typename T, class Compare = std::less<T>, class Alloc = std::allocator<TreeNode<T> > >
	class BinarySearchTree
	{
	public:
		typedef T value_type;
		typedef typename value_type::first_type key_type;
		typedef typename value_type::second_type mapped_type;
		typedef TreeNode<T> node;
		typedef TreeNode<T> *node_ptr;
		typedef size_t size_type;
		typedef Compare key_compare;
		typedef TreeIterator<value_type> iterator;
		typedef Alloc allocator_type;

		BinarySearchTree(const key_compare &comp = key_compare(),
						 const allocator_type &alloc = allocator_type()) : alloc(alloc),
																		   comp(comp),
																		   root(this->alloc.allocate(1)),
																		   end(root),
																		   size(0)
		{
			this->alloc.construct(root, node());
		}

		BinarySearchTree(const BinarySearchTree &other) : alloc(other.alloc),
														  comp(other.comp),
														  root(this->alloc.allocate(1)),
														  end(root),
														  size(0)
		{
			this->alloc.construct(root, node());
			iterator ite = other.getEnd();
			for (iterator it = other.getStart(); it != ite; ++it)
			{
				this->insert(it.asPointer()->value);
			}
		}

		~BinarySearchTree()
		{
			clear();
			this->alloc.destroy(end);
			this->alloc.deallocate(end, 1);
		}

		iterator getStart() const
		{
			return findMin(this->root);
		}

		iterator getEnd() const
		{
			return end;
		}

		size_type const &getSize() const
		{
			return size;
		}

		// define insert_left
		ft::pair<iterator, bool> insert_left(node_ptr current, value_type const &value)
		{
			current->linkLeft(new_node(value));
			this->size++;
			return ft::make_pair(iterator(current->left), true);
		}

		// define insert_right
		ft::pair<iterator, bool> insert_right(node_ptr current, value_type const &value)
		{
			current->linkRight(new_node(value));
			this->size++;
			return ft::make_pair(iterator(current->right), true);
		}

		// define build root
		ft::pair<iterator, bool> build_root(value_type const &value)
		{
			this->root = new_node(value, BLACK);
			this->size++;
			this->root->right = end;
			end->parent = root;
			return ft::make_pair(iterator(this->root), true);
		}

		// define insert
		ft::pair<iterator, bool> insert(value_type const &value)
		{
			if (this->root == end)
			{
				return build_root(value);
			}
			node_ptr current = this->root;
			while (current != nullptr)
			{
				if (!comp(value.first, current->value.first) && !comp(current->value.first, value.first))
				{
					return ft::make_pair(iterator(current), false);
				}

				else if (comp(value.first, current->value.first))
				{
					if (current->left == nullptr)
					{
						return insert_left(current, value);
					}
					current = current->left;
				}
				else
				{
					if (current->right == this->end || current->right == nullptr)
					{
						return insert_right(current, value);
					}
					current = current->right;
				}
			}
			return ft::make_pair(iterator(current), false);
		}

		// define insert with hint position
		iterator insert(iterator position, value_type const &value)
		{
			node_ptr hint = position.asPointer();
			ft::pair<iterator, bool> result;
			if (hint->left == nullptr && comp(hint->value.first, value.first))
			{
				result = insert_left(hint, value);
			}
			else if (hint->right == nullptr && comp(value.first, hint->value.first))
			{
				result = insert_right(hint, value);
			}
			else
				result = insert(value);
			return result.first;
		}

		void removeLeafNode(node_ptr node)
		{
			if (node->parent != nullptr)
			{
				if (node->isRightChild)
				{
					// case of leaf node has end as right child
					node->parent->right = node->right;
					if (node->right != nullptr)
						node->right->parent = node->parent;
				}
				else
					node->parent->left = nullptr;
			}
			if (node == this->root)
			{
				this->end->parent = nullptr;
				this->root = this->end;
			}
			this->alloc.destroy(node);
			this->alloc.deallocate(node, 1);
			this->size--;
		}

		void removeNodeWithOneChild(node_ptr node)
		{
			node_ptr child = (node->hasOnlyOneChild(end)).first;

			if (node->parent != nullptr)
			{
				if (node->isRightChild)
					node->parent->right = child;
				else
					node->parent->left = child;
				child->isRightChild = node->isRightChild;
			}
			else
			{
				findMax(child)->right = end;
				root = child;
			}
			child->parent = node->parent;
			if (node == this->root)
				this->root = child;
			this->alloc.destroy(node);
			this->alloc.deallocate(node, 1);
			this->size--;
		}

		void removeByPosition(iterator it)
		{
			node_ptr ptr = it.asPointer();
			if (size == 0 || ptr == nullptr || ptr == end)
				return;

			// case 1: leaf node
			if (ptr->isLeaf(end))
			{
				removeLeafNode(ptr);
			}

			// case 2: node with one child
			else if (ptr->hasOnlyOneChild(end).second)
			{
				removeNodeWithOneChild(ptr);
			}

			// case 3: node with two children
			else
			{
				node_ptr successor = findMin(ptr->right);
				if (successor == this->end)
					successor = findMax(ptr->left);
				node_ptr holder = alloc.allocate(1);
				alloc.construct(holder, node(successor->value));
				ptr->copyLinks(holder);
				if (ptr == this->root)
					this->root = holder;
				alloc.destroy(ptr);
				alloc.deallocate(ptr, 1);
				removeByPosition(iterator(successor));
			}
		}

		void swap(BinarySearchTree &other)
		{
			std::swap(this->root, other.root);
			std::swap(this->end, other.end);
			std::swap(this->size, other.size);
			std::swap(this->comp, other.comp);
			std::swap(this->alloc, other.alloc);
		}

		void clear()
		{
			if (size == 0)
				return;
			this->clearTree(this->root);
			end->parent = nullptr;
			this->root = end;
			this->size = 0;
		}

		size_type max_size() const
		{
			return this->alloc.max_size();
		}

		key_compare getComp() const
		{
			return comp;
		}

		iterator findByKey(const key_type &key)
		{
			node_ptr current = this->root;
			while (current != nullptr)
			{
				if (comp(key, current->value.first))
					current = current->left;
				else if (comp(current->value.first, key))
					current = current->right;
				else
					return iterator(current);
			}
			return iterator(end);
		}

	private:
		// private data members
		allocator_type alloc;
		key_compare comp;
		node_ptr root;
		node_ptr end;
		size_type size;

		// private member methods

		node_ptr new_node(value_type const &value, bool const &color = BLACK)
		{
			node_ptr newNode = this->alloc.allocate(1);
			this->alloc.construct(newNode, node(value, color));
			return newNode;
		}

		// define find min
		node_ptr findMin(node_ptr curr_root) const
		{
			if (curr_root != nullptr && curr_root != end)
			{
				while (curr_root->left != nullptr)
					curr_root = curr_root->left;
			}
			return curr_root;
		}

		// define find max
		node_ptr findMax(node_ptr curr_root) const
		{
			if (curr_root != nullptr && curr_root != end)
			{
				while (curr_root->right != nullptr && curr_root->right != end)
					curr_root = curr_root->right;
			}
			return curr_root;
		}

		void clearTree(node_ptr node)
		{
			if (node == nullptr || node == end)
				return;

			clearTree(node->left);
			clearTree(node->right);

			alloc.destroy(node);
			alloc.deallocate(node, 1);
		}
	}; // class BinarySearchTree

} // namespace ft

#endif