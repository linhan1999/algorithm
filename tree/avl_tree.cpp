#include<iostream>

using namespace std;

class avl_tree_node{
	typedef avl_tree_node node;
public:
	node(int _n):right(nullptr),left(nullptr),balance(0),key(_n){}
	node* right;
	node* left;
	int key;
	int balance;//平衡因子 -1 0 1
};

class avl_tree{
	typedef avl_tree_node node;
	typedef avl_tree tree;
public:
	tree():root(nullptr),node_num(0){}
	tree(node* _p):root(_p),node_num(1){}
	node* root;
	void tree_insert(node* p);
private:
	node* LL(node *p);	//LL平衡旋转（右单旋转） 	 1 -> 2
	node* RR(node *p);	//RR平衡旋转（左单旋转）	-1 -> -2
	node* LR(node *p);  //LR平衡旋转（先左后右双旋转）  1 -> 2
	node* RL(node *p);  //RL平衡旋转（先右后左双旋转） -1 -> -2
	
	int node_num; //结点个数	
};

//A结点的左孩子B右旋代替A的位置，A结点成为B右子树的根节点,B的原右子树成为A的左子树
node* avl_tree::LL(node *p){
	node* A = p;
	node* B = A->left;
	node* _right = B->right;	
	B->right = A;
	A->left = _right;
	return B;
}

//A结点的右孩子B左旋代替A的位置，A结点成为B左子树的根结点,B的原左子树成为A的右子树
node* avl_tree::RR(node* p){
	node* A = p;
	node* B = A->right;
	node* _left = B->left;
	B_left = A;
	A_right = _left;
	return B;
}

//A结点的左孩子B的右子树的根结点C左上旋替代B的位置，再把C右上旋替代A的位置
node* avl_tree::LR(node* p){
	node* A = p;
	node* B = A->left;
	//node* C = B->right;
	A->left = avl_tree::RR(B);
	return avl_tree::LL(A);
}

//A结点的右孩子B的左子树的根结点C右上旋替代B的位置，再把C左上旋替代A的位置
node* avl_tree::RL(node* p){
	node* A = p;
	node* B = A->right;
	//node* C = B->left;
	A->left = avl_tree::LL(B);
	return avl_tree::RR(A);
}

void avl_tree::tree_insert(node* p){
	node *parent = root;node *now = root;
	bool flag = true;
	
	while(flag){
		if(p->key < now->key){
			parent = now;
			now = now->right;			
		}
		else{	
			parent = now;
			now = now->left;
		}
	}	
}
