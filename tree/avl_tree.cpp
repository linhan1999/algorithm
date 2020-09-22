template <class K, class V>
class AVLNode {
public:
	K _key;
	V _value;
	int _bf;
	AVLNode<K, V>* _left;
	AVLNode<K, V>* _right;
	AVLNode<K, V>* _parent;

	AVLNode(const K& key, const V& value)
		:_key(key), _value(value), _bf(0), _left(NULL), _right(NULL), _parent(NULL)
	{

	}
};
/*
1.每个节点都有一个平衡因子，大小为右子树高度-左子树的高度。
2.平衡因子可能为-1,0,1，高度差绝对值不能超过1，超过1说明不平衡，需要旋转。
3.树中每个左右子树都为AVL。
*/

template <class K, class V>
class AVLTree {
	typedef AVLNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	void Insert(const K& key, const V& value)
	{
		if (_root == NULL) {
			_root = new Node(key, value);
			return;
		}

		Node* cur = _root;
		Node* parent = NULL;
		while (cur) {
			if (key < cur->_key) {
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				return;
			}
		}

		cur = new Node(key, value);
		if (key < parent->_key) {
			parent->_left = cur;
			cur->_parent = parent;
		}
		if (key > parent->_key) {
			parent->_right = cur;
			cur->_parent = parent;
		}


		//插入结束，需要更新一下平衡因子，再判断是否需要旋转
		//更新平衡因子，需要从parent开始往跟上遍历,平衡因子 = 右 - 左;
		while (parent) {
			if (parent->_left == cur)//如果parent的左边插入，那么parent的平衡因子要-1
				--parent->_bf;
			else//(parent->_right == cur)//如果parent的右边插入，那么parent的平衡因子要+1
				++parent->_bf;

			if (parent->_bf == 0) {
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1) {
				cur = parent;
				parent = parent->_parent;
			}
			else {//2或-2
				if (parent->_bf == 2) {
					if (cur->_bf == 1) {
						RotateLeft(parent);
					}
					else {//cur->_bf == -1
						RotateRL(parent);
					}
				}
				else {//parent->_bf == -2
					if (cur->_bf == 1) {
						RotateLR(parent);
					}
					else {//cur->_bf == -1
						RotateRight(parent);
					}
				}
				parent->_bf = 0;
				cur->_bf = 0;
				break;
			}

		}
	}

private:
	void RotateRight(Node* parent)//parent->_bf == -2 && cur->_bf == -1
	{
		Node* cur = parent->_left;//cur

		Node* right = cur->_right;//把cur的right给parent的左
		if (right != NULL) {
			parent->_left = right;
			right->_parent = parent;
		}

		Node* node = parent->_parent;//先记录一下parent原来的父节点
		cur->_right = parent; //把parent给cur的右
		parent->_parent = cur;//更新parent的父节点

							  //把cur与parent之前的父节点连接
		if (parent == _root)//如果之前的parent就是根，直接把根变成cur
		{
			_root = cur;
			_root->_parent = NULL;
		}
		else//如果之前的parent有父节点，那么就要连接
		{
			if (node->_left == parent)
			{
				node->_left = cur;

			}
			else
			{
				node->_right = cur;
			}
			cur->_parent = node;

			node->_bf = 0;
			cur->_bf = 0;
		}
	}

	void RotateLeft(Node* parent)//parent->_bf == 2 && cur->_bf == 1
	{
		Node* cur = parent->_right;
		Node* left = cur->_left;

		if (left != NULL) {
			parent->_right = left;
			left->_parent = parent;
		}

		Node* node = parent->_parent;
		cur->_left = parent;
		parent->_parent = cur;

		if (parent == _root) {
			_root = cur;
			_root->_parent = NULL;
		}
		else {
			if (node->_left == parent) {
				node->_left = cur;
			}
			else {
				node->_right = cur;
			}
			cur->_parent = node;
		}
	}

	void RotateRL(Node* parent)//parent->_bf == 2 && cur->_bf == -1
	{
		RotateRight(parent->_right);
		RotateLeft(parent);
	}

	void RotateLR(Node* parent)//parent->_bf == -2 && cur->_bf == 1
	{
		RotateLeft(parent->_left);
		RotateRight(parent);
	}

private:
	Node* _root;
};
