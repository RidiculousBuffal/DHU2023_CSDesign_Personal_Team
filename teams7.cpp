#include<bits/stdc++.h>
using namespace std;
template<class ElemType>
struct BinaryTreeNode {
    ElemType data;
    BinaryTreeNode<ElemType> *LChild, *RChild;
    int vis = 0;

    BinaryTreeNode() : LChild(NULL), RChild(NULL) {} //构造函数1，用于构造根结点
    BinaryTreeNode(const ElemType &item, BinaryTreeNode<ElemType> *Lptr = NULL,
                   BinaryTreeNode<ElemType> *Rptr = NULL) //构造函数2，用于构造其他结点
    //函数参数表中的形参允许有默认值，但是带默认值的参数需要放后面
    {
        LChild = Lptr;
        RChild = Rptr;
        data = item;
    }

    ElemType getData() { return data; }  //取得结点中的数据
    void SetLChild(BinaryTreeNode<ElemType> *link) { LChild = link; }  //修改结点的左孩子域
    void SetRChild(BinaryTreeNode<ElemType> *link) { RChild = link; }  //修改结点的右孩子域
    void SetData(ElemType value) { data = value; }   //修改结点的data域
    BinaryTreeNode<ElemType> *GetLChild() const { return LChild; } //获取左孩子结点
    BinaryTreeNode<ElemType> *GetRChild() const { return RChild; } //获取左孩子结点

};

bool visit2(BinaryTreeNode<string> *root, vector<string> &ret) {
    if (root != NULL) {
//        if(root->data.at(0)=='-'&&root->data!="-")
//        {
//            cout<<"("<<root->data<<")";
//        }
        //else
        ret.push_back(root->data);
        return true;
    }
    return false;
}

//二叉树
template<class ElemType>
class BinaryTree {
private:
    BinaryTreeNode<ElemType> *root;   // 头指针
    BinaryTreeNode<ElemType> *build(BinaryTreeNode<ElemType> *root_, int k, vector<ElemType> &a, ElemType &gap) {
        queue<BinaryTreeNode<ElemType> *> q;
        if (a[k] != gap) {
            root_ = new BinaryTreeNode<ElemType>(a[k]);
            q.push(root_);
        }
        k++;
        while (!q.empty()) {
            BinaryTreeNode<ElemType> *s = q.front();
            if (k < a.size()) {
                if (a[k] != gap) {
                    s->LChild = new BinaryTreeNode<ElemType>(a[k]);
                    q.push(s->LChild);
                }
                k++;
            }
            if (k < a.size()) {
                if (a[k] != gap) {
                    s->RChild = new BinaryTreeNode<ElemType>(a[k]);
                    q.push(s->RChild);
                }
                k++;
            }
            q.pop();
        }
        return root_;
    }

    void visit(vector<ElemType> &res, BinaryTreeNode<ElemType> *root_) {
        if (root_ != NULL) {
            res.push_back(root_->data);
        }
    }// VISIT函数 统一存放结果至RES vector


public:
    //无参数的构造函数
    BinaryTree() : root(NULL) {}

    //带参数的构造函数
    BinaryTree(const ElemType &item) { root = new BinaryTreeNode<ElemType>(item); }
    //生成树

    //返回二叉树结点的个数
    void Int(vector<ElemType> &res, BinaryTreeNode<ElemType> *root_) {
        if (root_ != NULL) {
            Int(res, root_->LChild);
            visit(res, root_);
            Int(res, root_->RChild);
        }
    }
    vector<ElemType> Create_tree_with_level(ElemType &str, ElemType &empty) {
        ElemType tmp;
        vector<ElemType> t;
        stringstream input_T(str);
        vector<ElemType> res;
        while (input_T >> tmp) {
            t.push_back(tmp);
            if (tmp != empty) {
                res.push_back(tmp);
            }
        }
        root = build(root, 0, t, empty);
        return res;
    }

    void SetRoot(BinaryTreeNode<ElemType> *p) { root = p; }

    //获取根结点
    BinaryTreeNode<ElemType> *GetRoot() const { return root; }

    //前序遍历
    //建立二叉树的存储结构
    BinaryTreeNode<ElemType> *CreateBinaryTree(vector<ElemType> &x, ElemType &empty, int &n);

    vector<ElemType> InOrderTraverse(BinaryTreeNode<ElemType> *root_) {
        vector<ElemType> res;//存放遍历结果
        Int(res, root_);
        return res;
    }

    BinaryTreeNode<ElemType> *find_brother(BinaryTreeNode<ElemType> *root_, ElemType &x) {
        if (root_) {
            {
                if (root_->LChild != nullptr) {
                    if (root_->LChild->data == x) {
                        return root_->RChild;
                    }
                }
                if (root_->RChild != nullptr) {
                    if (root_->RChild->data == x) {
                        return root_->LChild;
                    }
                }
            }//康康一个根节点的左右孩子
            return find_brother(root_->LChild, x);
            return find_brother(root_->RChild, x);
        }
        return NULL;
    }
};

//建立二叉树的存储结构 (递归部分，成员函数）
template<class ElemType>
BinaryTreeNode<ElemType> *BinaryTree<ElemType>::CreateBinaryTree(vector<ElemType> &x, ElemType &empty, int &n) {

    ElemType ch = x[n];
    n++;
    if (ch == empty) {
        return NULL;
    } else {
        BinaryTreeNode<ElemType> *Node = new BinaryTreeNode<ElemType>;
        Node->data = ch;
        Node->LChild = CreateBinaryTree(x, empty, n);
        Node->RChild = CreateBinaryTree(x, empty, n);
        return Node;
    }
}

template<class ElemType>
void print_(vector<ElemType> &res)//统一输出接口
{
    for (int i = 0; i < res.size(); i++) {
        if (i == 0) {
            cout << res[i];
        } else {
            cout << "," << res[i];
        }
    }
    cout << endl;
}

int main() {
    ///////////////////////////读入数据,建造树
    string gap;
    cin >> gap;
    string tree;
    ::getchar();
    getline(cin, tree);
    BinaryTree<string> trees;
    vector<string> resLevelOrder = trees.Create_tree_with_level(tree, gap);
    vector<string> resInOrder ;
    trees.Int(resInOrder,trees.GetRoot());
    sort(resLevelOrder.begin(), resLevelOrder.end());
    print_(resInOrder);
    if (resLevelOrder == resInOrder) {
        cout << "true";
    } else {
        cout << "false";
    }
    return 0;
}
