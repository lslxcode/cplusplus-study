#include <iostream>
#include <stack>

namespace std{

    /**
     * @brief 
     * 结点信息
     */
    struct TreeNode{
        TreeNode *left;
        TreeNode *right;
        int val;
        TreeNode() : left(NULL),right(NULL),val(0){
        }
    };

    /**
     * @brief 
     * 1. 反向中序遍历
     */
    void dfs_test1(TreeNode *root){
        if(root){
            dfs_test1(root->right);
            cout << root->val << endl;
            dfs_test1(root->left);
        }
    }

    /**
     * @brief 
     * 2. 堆栈前序遍历
     * 		1. 先把头结点放入栈中，
	 *		2. 每次从栈中弹出结点，记为cur，并打印cur->val
	 *		3. cur如果有左孩子则压入左孩子
	 *		4. cur如果有右孩子则压入右孩子
     *          重复到2，直到栈为空
     */
    void dfs_preOrder(TreeNode *root){
        if(root){
            stack<TreeNode *> stk;
            stk.push(root);
            while(!stk.empty()){
                root = stk.top();
                stk.pop();
                cout << root->val << endl;
                if(root->left){
                    stk.push(root->left);
                }
                if(root->right){
                    stk.push(root->right);
                }
            }
        }
    }

    /**
     * @brief 
     * 2. 堆栈中序遍历
     * 		a. 准备一个栈
	 *  	b. 每棵子树的整个树左边界进栈
	 *	    c. 依次弹出的过程中，先打印，对弹出结点的右树的左边界进栈
	 *	    d. 周而复始c，直到栈为空，或者结点为空
     */
    void dfs_inOrder(TreeNode *root){
        if(root){
            stack<TreeNode *> stk;
            while(!stk.empty() || root != NULL){
               if(!stk.empty()){
                   stk.push(root);
                   root = root->left;
               }else{
                   root = stk.top();
                   stk.pop();
                   cout << root->val << endl;
                   root = root->right;
               }
            }
        }
    }


    /**
     * @brief 
     * 2. 堆栈后续遍历
	 *		1. 准备两个栈，将头结点放入栈1中，
	 *		2. 弹出栈1的顶部元素记为cur，放入栈2，
	 *		3. cur如果有左孩子则在栈1压入左孩子
	 *		4. cur如果有右孩子则在栈2压入右孩子
	 *		5. 重复到2，直到栈1为空并且
     *        遍历打印栈2内容
     */
    void dfs_posOrder(TreeNode *root){
        if(root){
            stack<TreeNode *> stk1;
            stack<TreeNode *> stk2;
            stk1.push(root);
            while(!stk1.empty()){
                root = stk1.top();
                stk1.pop();
                stk2.push(root);
                if(root->left){
                    stk1.push(root->left);
                }
                if(root->right){
                    stk1.push(root->right);
                }
            }

            while(!stk2.empty()){
                cout << stk2.top()->val << endl;
                stk2.pop();
            }
        }
    }

    /**
     * @brief 
     * Morris遍历
     * 	c. 先序遍历：
     *		a. 只有第一次来到节点打印，第二次不打印
     *	d. 中序遍历：
     *       只能遍历到一次的节点，直接打印，能遍历二次的节点，第二次打印，第一次不打印
     *	e. 后序遍历：
     *		a. 第二次来到某一结点时，逆序打印此节点左树的右边界
     *		b. 等整个树遍历完成时，逆序单独打印整个树的由边界
     */

    //中序遍历
    void morrisInOrder(TreeNode *root){
        if(root){
            TreeNode *cur = root;
            TreeNode *cur1 = NULL;
            while(cur != NULL){
                cur1 = cur->left;
                if(cur1){
                    while(cur1->right && cur1->right != cur){
                        cur1 = cur1->right;
                    }
                    if(cur1->right == NULL){
                        cur1->right = cur;
                        cur = cur->left;
                        continue;
                    }
                    if(cur1->left == cur){
                        cur1->right = NULL;
                    }
                }
                cout << cur->val << endl;
                cur = cur->right;
            }
        }
    }

//前序遍历
    void morrisPreOrder(TreeNode *root){
        if(root){
            TreeNode *cur = root;
            TreeNode *cur1 = NULL;
            while(cur != NULL){
                cur1 = cur->left;
                if(cur1){//如果有左子树
                    while(cur1->right && cur1->right != cur){
                        cur1 = cur1->right;
                    }
                    if(cur1->right == NULL){//第一次遍历cur，
                        cur1->right = cur;
                        cout << cur->val << endl;
                        cur = cur->left;
                        continue;
                    }
                    //cur1第二次遍历，将右指针调回去，执行70行cur向右移动
                    if(cur1->left == cur){
                        cur1->right = NULL;
                    }
                }else{//没有左子树情况，打印节点
                    cout << cur->val << endl;
                }
                //cur向右移动
                cur = cur->right;
            }
        }
    }


//后序遍历
 TreeNode* reverseEdge(TreeNode *root){
        TreeNode *cur = NULL;
        TreeNode *pre = NULL;
        while(root){
            cur = root->right;
            root->right = pre;
            pre = root;
            root = cur;
        }
        return cur;
    }
    void printEdge(TreeNode *root){
        TreeNode *tail = reverseEdge(root);
        TreeNode *cur = tail;
        while(cur){
            cout << cur->val << endl;
            cur = cur->right;
        }
        reverseEdge(tail);
    }
void morrisPosOrder(TreeNode *root){
    if(root){
        TreeNode *cur = root;
        TreeNode *cur1 = NULL;
        while(cur != NULL){
            cur1 = cur->left;
            if(cur1){
                while(cur1->right && cur1->right != cur){
                    cur1 = cur1->right;
                }
                if(cur1->right == NULL){
                    cur1->right = cur;
                    cur = cur->left;
                    continue;
                }
                if(cur1->left == cur){
                    cur1->right = NULL;
                }
            }
            printEdge(cur);
            cur = cur->right;
        }
    }
}
   


}

int main(){
    return 0;
}