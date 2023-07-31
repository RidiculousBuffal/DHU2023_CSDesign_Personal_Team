#include<bits/stdc++.h>
using namespace std;
bool isoperator( char op ){
    switch(op){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            return true;
        default:
            return false;
    }
}
//求运算符的优先级

int getOperPri(char op)

{
    switch(op)
    {
        case '(':
            return 1; break;
        case '+':
        case '-':
            return 2; break;
        case '*':
        case '/':
            return 3; break;
        default:
            return 0;
    }
}

template<class ElemType>

struct BinaryTreeNode
{
    ElemType data;
    BinaryTreeNode<ElemType> *LChild, *RChild;
    int vis=0;
    BinaryTreeNode() : LChild(NULL), RChild(NULL){} //构造函数1，用于构造根结点
    BinaryTreeNode(const ElemType &item, BinaryTreeNode<ElemType> *Lptr = NULL, BinaryTreeNode<ElemType> *Rptr = NULL) //构造函数2，用于构造其他结点
    //函数参数表中的形参允许有默认值，但是带默认值的参数需要放后面
    {
        LChild = Lptr;
        RChild = Rptr;
        data = item;
    }

    ElemType getData(){ return data;}  //取得结点中的数据
    void SetLChild( BinaryTreeNode<ElemType> *link ){ LChild = link; }  //修改结点的左孩子域
    void SetRChild( BinaryTreeNode<ElemType> *link ){ RChild = link; }  //修改结点的右孩子域
    void SetData( ElemType value ){ data = value; }   //修改结点的data域
    BinaryTreeNode<ElemType> * GetLChild() const{ return LChild;} //获取左孩子结点
    BinaryTreeNode<ElemType> * GetRChild() const{ return RChild;} //获取左孩子结点

};
bool visit2(BinaryTreeNode<string>*root,vector<string>&ret)
{
    if(root!=NULL)
    {
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
class BinaryTree{
private:
    BinaryTreeNode<ElemType> *root;   // 头指针
    BinaryTreeNode<ElemType>*build(BinaryTreeNode<ElemType>*root_,int k,vector<ElemType>&a,ElemType& gap)
    {
        queue<BinaryTreeNode<ElemType>*>q;
        if(a[k]!=gap)
        {
            root_=new BinaryTreeNode<ElemType>(a[k]);
            q.push(root_);
        }
        k++;
        while(!q.empty())
        {
            BinaryTreeNode<ElemType>*s=q.front();
            if(k<a.size())
            {
                if(a[k]!=gap)
                {
                    s->LChild=new BinaryTreeNode<ElemType>(a[k]);
                    q.push(s->LChild);
                }
                k++;
            }
            if(k<a.size())
            {
                if(a[k]!=gap)
                {
                    s->RChild=new BinaryTreeNode<ElemType>(a[k]);
                    q.push(s->RChild);
                }
                k++;
            }
            q.pop();
        }
        return root_;
    }

    void visit(vector<ElemType>&res,BinaryTreeNode<ElemType>*root_)
    {
        if(root_!=NULL){
            res.push_back(root_->data);
        }
    }// VISIT函数 统一存放结果至RES vector
    void Pret(vector<ElemType>&res,BinaryTreeNode<ElemType>*root_)
    {
        if(root_!=NULL)
        {
            visit(res,root_);
            Pret(res,root_->LChild);
            Pret(res,root_->RChild);
        }
    }
    void Int(vector<ElemType>&res,BinaryTreeNode<ElemType>*root_)
    {
        if(root_!=NULL)
        {
            Int(res,root_->LChild);
            visit(res,root_);
            Int(res,root_->RChild);
        }
    }
    void Pot(vector<ElemType>&res,BinaryTreeNode<ElemType>*root_)
    {
        if(root_!=NULL)
        {
            Pot(res,root_->LChild);
            Pot(res,root_->RChild);
            visit(res,root_);
        }
    }
    void add_func(BinaryTreeNode<ElemType>*root_,int&num)
    {
        if(root_!=NULL)
        {
            num++;
        }
    }
    void Pret_get_size(BinaryTreeNode<ElemType>*root_,int&num)
    {
        if(root_!=NULL)
        {
            add_func(root_,num);
            Pret_get_size(root_->LChild,num);
            Pret_get_size(root_->RChild,num);
        }
    }
public:
    //无参数的构造函数
    BinaryTree():root(NULL){}
    //带参数的构造函数
    BinaryTree(const ElemType &item){root = new BinaryTreeNode<ElemType>(item);}
    //生成树
    void makeBinaryTree( const ElemType &item, BinaryTree &left, BinaryTree &right);
    //返回二叉树结点的个数
    vector<ElemType> Create_tree_with_level(ElemType &str,ElemType&empty)
    {
        ElemType tmp;
        vector<ElemType>t;
        stringstream input_T(str);
        vector<ElemType>res;
        while(input_T>>tmp)
        {
            t.push_back(tmp);
            if(tmp!=empty)
            {
                res.push_back(tmp);
            }
        }
        root=build(root,0,t,empty);
        return res;
    }
    int BinaryTreeSize( BinaryTreeNode<ElemType> *root_)
    {
        int num=0;
        Pret_get_size(root_,num);
        return num;
    }
    //判断二叉树是否为空
    bool BinaryTreeisEmpty() const{return root == NULL;}
    int cal_height(BinaryTreeNode<ElemType>*root_)
    {
        if(root_==NULL)
        {
            return 0;
        }
        else
        {
            int hl= cal_height(root_->LChild);
            int hr= cal_height(root_->RChild);
            if(hl>hr)
            {
                return ++hl;
            }
            else
            {
                return ++hr;
            }
        }
    }
    //获取根结点元素值
    ElemType GetRootData() const{ return root->data;}
    void SetRoot(BinaryTreeNode<ElemType> * p){ root = p;}
    //获取根结点
    BinaryTreeNode<ElemType> * GetRoot() const{ return root;}
    //前序遍历
    //建立二叉树的存储结构
    BinaryTreeNode<ElemType>* CreateBinaryTree(vector<ElemType> &x, ElemType &empty, int &n);
    void get_two_degree_nodes(BinaryTreeNode<ElemType>*root_,int &sum)
    {
        if(root_!=NULL)
        {
            if(root_->LChild&&root_->RChild){sum++;}
            get_two_degree_nodes(root_->LChild,sum);
            get_two_degree_nodes(root_->RChild,sum);
        }
    }
    vector<ElemType> PreOrderTraverse(BinaryTreeNode<ElemType>*root_)
    {
        vector<ElemType>res;//存放遍历结果
        Pret(res,root_);
        return res;
    }
    vector<ElemType> InOrderTraverse(BinaryTreeNode<ElemType>*root_)
    {
        vector<ElemType>res;//存放遍历结果
        Int(res,root_);
        return res;
    }
    vector<ElemType> PostOrderTraverse(BinaryTreeNode<ElemType>*root_)
    {
        vector<ElemType>res;//存放遍历结果
        Pot(res,root_);
        return res;
    }


    BinaryTreeNode<ElemType>* Location(ElemType& x, BinaryTreeNode<ElemType>* location);
    BinaryTreeNode<ElemType>* Find_Parents(BinaryTreeNode<ElemType>*root_,ElemType &x)
    {
        if(root_!=NULL)
        {
            if(root_->RChild!=NULL)
            {
                if(root_->RChild->getData()==x)
                {
                    return root_;
                }
            }
            if(root_->LChild!=NULL)
            {
                if(root_->LChild->getData()==x)
                {
                    return root_;
                }
            }
            if(root_->LChild)//左右孩子里面找,找到了返回
                return Find_Parents(root_->LChild,x);
            if(root_->RChild)
                return Find_Parents(root_->RChild,x);
        }
        return NULL;
    }
    BinaryTreeNode<ElemType>* dfs_nearest_root(BinaryTreeNode<ElemType>*root_,string &p,string &q)
    {
        if(root_!=NULL)
        {
            if(this->Location(p,root_)&& Location(q,root_))
            {
                return root_;
            }
            else{
                if(dfs_nearest_root(root_->LChild,p,q))
                {
                    return dfs_nearest_root(root_->LChild,p,q);
                }
                if(dfs_nearest_root(root_->RChild,p,q))
                {
                    return dfs_nearest_root(root_->RChild,p,q);
                }
            }
        }
        return NULL;

    }

    bool Insert_ChildTree(BinaryTreeNode<ElemType>* parent, BinaryTreeNode<ElemType>* child, int flag);
    void BinaryTree_Revolute_Cursive(BinaryTreeNode<ElemType>* root);
    int LeafCount_Cursive(BinaryTreeNode<ElemType>* root, int& sum);
    bool InOrderRur(BinaryTreeNode<string> *root,vector<string>&ret_,bool (*visit)(BinaryTreeNode<string> *temp,vector<string>&ret)){
        if(root) {

            char temp=' ',left= ' ',right=' ';
            if(root->GetLChild() &&root->GetRChild()){
                temp = root->getData().at(0);
                left = root->GetLChild()->getData().at(0);
                right = root->GetRChild()->getData().at(0);
            }
            if(isoperator(left)
               && getOperPri(left)<getOperPri(temp)){
                ret_.push_back("(");
                InOrderRur(root->GetLChild(),ret_,visit2);
                ret_.push_back(")");
            }
            else{
                InOrderRur(root->GetLChild(),ret_,visit2);
            }
            visit2(root,ret_);
            if(isoperator(right)
               && getOperPri(right)<getOperPri(temp)){
                ret_.push_back("(");
                InOrderRur(root->GetRChild(),ret_,visit2);
                ret_.push_back(")");
            }
            else if((temp == '-' && isoperator(right)) &&(getOperPri(temp) >= getOperPri(right))){
                ret_.push_back("(");
                InOrderRur(root->GetRChild(),ret_,visit2);
                ret_.push_back(")");
            }
            else if(temp == '/' && isoperator(right)){
                ret_.push_back("(");
                InOrderRur(root->GetRChild(),ret_,visit2);
                ret_.push_back(")");
            }
            else{
                InOrderRur(root->GetRChild(),ret_,visit2);
            }
            return true;
        }
        return false;
    }
    vector<ElemType> LayerOrderTraverse(BinaryTreeNode<ElemType>* root, /*bool (*visit)(BinaryTreeNode<ElemType>* T, int& num),*/ int& num) const;
    BinaryTreeNode<ElemType>* find_brother(BinaryTreeNode<ElemType>*root_,ElemType&x)
    {
        if (root_)
        {
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
            return find_brother(root_->LChild,x);
            return find_brother(root_->RChild,x);
        }
        return NULL;
    }
};
//建立二叉树的存储结构 (外壳）
template<class ElemType>
void CreateTree(BinaryTree<ElemType> &T, ElemType &str, ElemType &empty){
    ElemType tmp;
    vector<ElemType> t;
    stringstream input_T(str);
    while(input_T >> tmp){
        t.push_back(tmp);
    }
    BinaryTreeNode<ElemType> *root;
    int num = 0;
    root = T.CreateBinaryTree(t, empty, num);
    T.SetRoot(root);
}
//建立二叉树的存储结构 (递归部分，成员函数）
template<class ElemType>
BinaryTreeNode<ElemType>* BinaryTree<ElemType>::CreateBinaryTree(vector<ElemType> &x, ElemType &empty, int &n){

    ElemType ch = x[n];
    n++;
    if (ch == empty)
    {
        return NULL;
    }
    else
    {
        BinaryTreeNode<ElemType> *Node = new BinaryTreeNode<ElemType>;
        Node->data = ch;
        Node->LChild = CreateBinaryTree(x, empty, n);
        Node->RChild = CreateBinaryTree(x, empty, n);
        return Node;
    }
}
template<class ElemType>
void print_(vector<ElemType>&res)//统一输出接口
{
    for(int i=0;i<res.size();i++)
    {
        if(i==0)
        {
            cout<<res[i];
        }
        else
        {
            cout<<","<<res[i];
        }
    }
    cout<<endl;
}
template<class ElemType>
BinaryTreeNode<ElemType>* BinaryTree<ElemType>::Location(ElemType& x, BinaryTreeNode<ElemType>* location)//寻找方位
{
    if (location == NULL) {
        return NULL;
    }
    else if (location->getData() == x) //找到了就返回这个节点所在的位置
    {
        return location;
    }
    else {
        if (Location(x, location->GetLChild())) //在左孩子里面找
        {
            return Location(x, location->GetLChild());
        }
        if (Location(x, location->GetRChild())) //在右孩子里面找
        {
            return Location(x, location->GetRChild());
        }
    }
    return NULL;
}
template<class ElemType>
bool BinaryTree<ElemType>::Insert_ChildTree(BinaryTreeNode<ElemType>* parent, BinaryTreeNode<ElemType>* child, int flag) {
    if (flag == 0) {
        if (parent->GetLChild() == NULL)
        {
            parent->SetLChild(child);//如果左孩子节点本来就为空,那么可以直接插入
        }
        else if (parent->GetLChild() != NULL && parent->GetRChild() != NULL) {
            return 0;
        }
        else {
            BinaryTreeNode<ElemType>* tmp;//左孩子节点不为空,那就先让R成为左孩子,再把原来的左孩子变成R的右孩子
            tmp = parent->GetLChild();
            parent->SetLChild(child);
            child->SetRChild(tmp);
        }
    }
    else {
        if (parent->GetRChild() == NULL) {
            parent->SetRChild(child);
        }
        else if (parent->GetLChild() != NULL && parent->GetRChild() != NULL) {
            return 0;
        }
        else {
            BinaryTreeNode<ElemType>* tmp;
            tmp = parent->GetRChild();
            parent->SetRChild(child);
            child->SetRChild(tmp);

        }
    }
    return 1;
}
template<class ElemType>
vector<ElemType> InOrderbystack(BinaryTreeNode<ElemType>*root_)
//从根节点开始检索，如果当前节点不为空，则将当前节点入栈，让当前节点成为其左孩子节点，再继续上一步的操作
//加入当前节点为空了，说明其父节点已经没有左孩子了，那么将栈顶元素出栈并输入
//判断栈顶元素是否有右孩子，如果有右孩子，则停止依次继续出栈的操作，并检索它的右孩子，重复第一步；如果没有右孩子，则继续将栈顶元素出栈
//当栈为空，并且当前节点为空时，遍历完成，退出；
{
    stack<BinaryTreeNode<ElemType>*>s;//创建栈
    vector<ElemType>res;
    BinaryTreeNode<ElemType>*tmp=root_;
    while(tmp||!s.empty())
    {
        if(tmp)
        {
            s.push(tmp);
            tmp=tmp->LChild;//
        }else
        {
            res.push_back(s.top()->data);//栈顶元素
            tmp=s.top()->RChild;//右子树
            s.pop();
        }
    }
    return res;
}
template<class ElemType>
vector<ElemType>PostOrderByStack(BinaryTreeNode<ElemType>*root_)
{
    stack<BinaryTreeNode<ElemType>*>s;
    vector<ElemType> res;
    BinaryTreeNode<ElemType>*cur;
    BinaryTreeNode<ElemType>*pre=NULL;
    s.push(root_);
    while(!s.empty())
    {
        cur=s.top();
        if((cur->LChild==NULL&&cur->RChild==NULL)||(pre!=NULL&&(pre==cur->LChild||pre==cur->RChild)))
        {
            res.push_back(cur->data);
            s.pop();
            pre=cur;
        }else{
            if(cur->RChild!=NULL){s.push(cur->RChild);}
            if(cur->LChild!=NULL){s.push(cur->LChild);}
        }
    }
    return res;
}
template<class ElemType>
///////前序遍历是根左右
//所以先push根节点
//但是因为是栈这种数据结构 是先进后出的,想要左子树比右子树先输出就需要把右子树全部入栈,把左子树叠在上面
vector<ElemType> PreOrderbystack(BinaryTree<ElemType>& T) {
    stack<BinaryTreeNode<ElemType>*>s;
    vector<ElemType>res;
    BinaryTreeNode<ElemType>* p = T.GetRoot();
    res.push_back(p->data);
    if (p->GetRChild() != NULL)
        s.push(p->GetRChild());
    if (p->GetLChild() != NULL)
        s.push(p->GetLChild());
    while (!s.empty()) {
        p = s.top();
        s.pop();
        res.push_back(p->data);
        if (p->GetRChild() != NULL) {
            s.push(p->GetRChild());
        }
        if (p->GetLChild()!=NULL) {
            s.push(p->GetLChild());
        }
    }
    return res;
}
template<class ElemType>
void BinaryTree<ElemType>::BinaryTree_Revolute_Cursive(BinaryTreeNode<ElemType>* root)//交换左右子树
{
    if (root == NULL)return;
    else {
        {
            BinaryTreeNode<ElemType> *tmp;
            tmp = root->GetLChild();
            root->SetLChild(root->GetRChild());
            root->SetRChild(tmp);
        }//作交换
        BinaryTree_Revolute_Cursive(root->GetLChild());
        BinaryTree_Revolute_Cursive(root->GetRChild());
        //对左右子树做一样的事情
    }
}
template<class ElemType>
int BinaryTree<ElemType>::LeafCount_Cursive(BinaryTreeNode<ElemType>* root, int& sum) //sum默认是0
{
    if (root == NULL)return 0;
    else if (root->GetLChild() == NULL && root->GetRChild() == NULL) {
        return sum+=1;
    }
    else {
        return LeafCount_Cursive(root->GetLChild(), sum) + LeafCount_Cursive(root->GetRChild(), sum);
    }
}
template<class ElemType>
vector<ElemType> BinaryTree<ElemType>::LayerOrderTraverse(BinaryTreeNode<ElemType>* root, /*bool (*visit)(BinaryTreeNode<ElemType>* T, int& num),*/ int& num) const {
    queue< BinaryTreeNode<ElemType>*>que;
    vector<ElemType>res;
    long long flag=0;
    que.push(root);
    while (!que.empty()) {
        if (que.front()->GetLChild()) {
            que.push(que.front()->GetLChild());
        }
        if (que.front()->GetRChild()) {
            que.push(que.front()->GetRChild());
        }
        visit(que.front(),res);
        que.pop();
        flag = 1;
    }
    return res;
}
bool check_full(BinaryTreeNode<string>*t)
{
    if(t==NULL)
    {
        return true;
    }
    int leave=0;
    queue<BinaryTreeNode<string>*>q;
    while(t!=NULL)
    {
        if(t->LChild==NULL&&t->RChild==NULL)
        {
            leave=1;
        }
        if(leave==1)
        {
            if(t->LChild||t->RChild)
            {
                return false;
            }
        }
        else
        {
            if(t->RChild!=NULL&&t->LChild==NULL)
            {
                return false;
            }
            else
            {
                if(t->LChild!=NULL)
                {
                    q.push(t->LChild);
                }
                if(t->RChild!=NULL)
                {
                    q.push(t->RChild);
                }
            }
        }
        if(!q.empty())
        {
            t=q.front();
        }
        else
        {
            return true;
        }
        q.pop();
    }

}

void dfs_zq(vector<string> s1,vector<string> s2,int &num)
{
    if(s1.empty()||s2.empty())
    {
        return ;
    }
    string s=s2[0];
    int l=0;
    for(int i=0;i<s1.size();i++)
    {
        if(s1[i]==s)
        {
            l=i;
            break;
        }
    }
    if(l>0)
    {
        dfs_zq(vector<string>(s1.begin(),s1.begin()+l),vector<string>(s2.begin()+1,s2.begin()+l+1),num);
    }
    if(s1.size()-l-1>0)
    {
        dfs_zq(vector<string>(s1.begin()+l+1,s1.end()),vector<string>(s2.begin()+l+1,s2.end()),num);
    }
    if(num==0) { cout << s; num++;}
    else{cout<<","<<s;}
}

void dfs_zh(vector<string>s1,vector<string> s2,int &num)
{
    if(s1.size()==0||s2.size()==0)
    {
        return;
    }
    string root=s2[s2.size()-1];
    int l=0;
    for(int i=0;i<s1.size();i++)
    {
        if(s1[i]==root)
        {
            l=i;
            break;
        }
    }
    if(num==0) { cout << root; num++;}
    else{cout<<","<<root;}
    dfs_zh(vector<string>(s1.begin(),s1.begin()+l),vector<string>(s2.begin(),s2.begin()+l),num);
    dfs_zh(vector<string>(s1.begin()+l+1,s1.end()),vector<string>(s2.begin()+l,s2.begin()+l+s2.size()-l-1),num);

}
int main()
{
    ///////////////////////////读入数据,建造树
    string gap;
    cin>>gap;
    string tree;
    ::getchar();
    getline(cin,tree);
    BinaryTree<string>trees;
    vector<string>res1=trees.Create_tree_with_level(tree,gap);
    vector<string>res2=trees.InOrderTraverse(trees.GetRoot());
    sort(res1.begin(),res1.end());
    print_(res2);
   
    if(res1==res2)
    {
        cout<<"true";
    }
    else
    {
        cout<<"false";
    }
    return 0;
}
