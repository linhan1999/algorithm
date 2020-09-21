/*
算法是使用辅助递归函数，辅助函数需要记录前序数组的起点和中点，数组均使用前闭后闭约定。

中序左子数的区间为[inStart,inRoot-1],中序右子数的区间为[inRoot+1,inEnd]

前序左子数的区间为[preStart+1,preStart+(inRoot-1-inStart)+1]      // 由前序左子数的个数等于中序左子树计算得到

前序右子数的区间为[preStart+(inRoot-inStart)+1,preEnd],*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, int preStart,int preEnd, vector<int>& inorder,int inStart, int inEnd){
        if(preStart>preEnd)
            return NULL;
        
        int rootVal = preorder[preStart];
        TreeNode* root = new TreeNode(rootVal);
        int inRoot = inStart;
        while(inRoot<inEnd && inorder[inRoot]!=rootVal)
            inRoot++;
        
        root->left = buildTree(preorder, preStart+1,preStart+inRoot-inStart,inorder,inStart,inRoot-1);
        root->right = buildTree(preorder,preStart+inRoot-inStart+1,preEnd,inorder,inRoot+1,inEnd);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder,0,preorder.size()-1, inorder,0,inorder.size()-1);
    }
};

/*
对于后序遍历

中序左子数的区间为[inStart,inRoot-1],中序右子数的区间为[inRoot+1,inEnd]

后序左子数的区间为[posStart,posStart+inRoot-1-inStart],

后序右子数的区间为[posStart+inRoot-inStart,posEnd-1]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, int inStart, int inEnd, vector<int> postorder, int posStart, int posEnd){
        if(inStart>inEnd)
            return NULL;
        
        int rootVal = postorder[posEnd];
        TreeNode* root = new TreeNode(rootVal);
        int inRoot = inStart;
        while(inRoot<inEnd && inorder[inRoot]!=rootVal)
            inRoot++;
        
        root->left = buildTree(inorder,inStart,inRoot-1,postorder,posStart, posStart+inRoot-1-inStart);
        root->right = buildTree(inorder,inRoot+1,inEnd,postorder, posStart+inRoot-inStart,posEnd-1);
        return root;
        
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return buildTree(inorder,0,inorder.size()-1,postorder,0,postorder.size()-1);
    }
};
