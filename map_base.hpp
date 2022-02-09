#ifndef __MAP_BASE_HPP__
#define __MAP_BASE_HPP__

namespace ft
{
	template <typename T>
	struct	lstNode
	{
		T			data;
		lstNode		*next;
		lstNode		*prev;

		lstNode(const T &src = T()) : data(src), next(this), prev(this) {};
	};

	template <typename T>
	struct	mapNode
	{
		private:
		bool _unused;
		#if __APPLE__ == 0
			int _unused_for_linux;
		#endif

		public:
		T			data;
		mapNode		*parent;
		mapNode		*left;
		mapNode		*right;

		mapNode(const T &src = T()) : \
			data(src), parent(NULL), left(NULL), right(NULL) {};
	};

	template <typename T>
	mapNode<T>	*farRight(mapNode<T> *node) {
		while (node->right != NULL)
			node = node->right;
		return (node);
	}

	template <typename T>
	mapNode<T>	*farLeft(mapNode<T> *node) {
		while (node->left != NULL)
			node = node->left;
		return (node);
	}
}

#endif