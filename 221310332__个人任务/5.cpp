#include <bits/stdc++.h>
using namespace std;
template<class T>
struct chainNode
{
    T element;
    chainNode <T>*next;//下一个节点的指针
    chainNode<T> *fa;//上一个节点的指针
    chainNode(T element,chainNode<T>*fa,chainNode<T>*next)
    {
        this->element=element;
        this->fa=fa;
        this->next=next;
    }
    chainNode(chainNode<T>*fa,chainNode<T>*next)
    {
        this->fa=fa;
        this->next=next;
    }
};

template<class T>
class deque_chain
{
protected:
    chainNode <T>*headNode;
    chainNode  <T>*tailNode;
    int listSize;
public:
    deque_chain()
    {
        headNode=new chainNode<T>(nullptr,nullptr);
        tailNode=headNode;
        listSize=0;
    }
    deque_chain(deque_chain <T>&b)
    {
        headNode=new chainNode<T>(nullptr,nullptr);
        tailNode=nullptr;
        listSize=0;
        //复制构造函数
        listSize=b.listSize;
        chainNode<T>*p=b.headNode->next;
        chainNode<T> *t=headNode;
        t->next=new chainNode<T>(p->element,headNode,nullptr);
        t=t->next;
        p=p->next;
        while(p)
        {
            t->next=new chainNode<T>(p->element,t,nullptr);
            p=p->next;
            t=t->next;
        }
        tailNode=t;
    }
    template<class H>
    bool  solve_oj_3(int n,deque_chain<T>&res);
    explicit deque_chain(vector<T>&a)
    {
        headNode=new chainNode<T>(nullptr,nullptr);
        tailNode=nullptr;
        listSize=0;
        if(a.size()==0)
        {
            listSize=a.size();
            return ;
        }
        else if(a.size()==1)
        {
            listSize=1;
            headNode->next=new chainNode<T>(a[0],headNode,nullptr);
            tailNode=headNode->next;
        }
        else
        {
            listSize=a.size();
            chainNode<T>*p=headNode;
            for(int i=0;i<a.size();i++)
            {
                p->next=new chainNode<T>(a[i],p,nullptr);
                p=p->next;
            }
            tailNode=p;

        }
    }
    void print()
    {
        if(listSize==0){cout<<endl;return;}
        chainNode<T>*p=headNode->next;
        // cout<<"head-->";
        cout<<p->element;
        p=p->next;
        while(p)
        {
            cout<<"->"<<p->element;


            p=p->next;
        }
//        cout<<"tail";
        cout<<endl;
    }
    int get_size()
    {
        return listSize;
    }
    friend vector<int>distance(deque_chain<int>&a);
    void push_front(T element)
    {
        if(listSize==0)
        {
            headNode->next=new chainNode<T>(element,headNode,nullptr);
            tailNode=headNode->next;
            listSize++;
        }
        else
        {
            headNode->next=new chainNode<T>(element,headNode,headNode->next);
            listSize++;
        }
    }
    void insert_by_index(int index,T element)
    {
        if(index<0||index>listSize)
        {
            return ;
        }
        chainNode<T>*p=headNode;
        for(int i=0;i<index-1;i++)
        {
            p=p->next;
        }
        p->next=new chainNode<T>(element,p,p->next);
        if(p->next==nullptr)
        {
            //更新尾节点
            tailNode=p;
        }
        listSize++;
    }
    void renew_tail()//防止自己不知道哪里没更新尾节点
    {
        chainNode<T>*p=tailNode;
        while(p->next!=nullptr)
        {
            p=p->next;
        }
        tailNode=p;
    }
    void erase(chainNode<T>*node)
    {
        chainNode<T>*p=node;
        p->fa->next=p->next;
        p->next->fa=p->fa;
        delete p;
        listSize--;
    }
    void erase(int index)
    {
        if(index<0||index>=listSize)
        {
            return ;
        }
        else
        {
            chainNode<T>*p=headNode;
            for(int i=0;i<index-1;i++)
            {
                p=p->next;
            }
            chainNode<T>*g=p->next;
            p->next=g->next;
            g->next->fa = p;
            delete g;
        }
    }
    void push_back(T element)
    {
        if(listSize==0)
        {
            headNode->next=new chainNode<T>(element,headNode,nullptr);
            tailNode=headNode->next;
            listSize++;
        }
        else
        {
            while(tailNode->next!=NULL)
            {
                tailNode=tailNode->next;
            }
            tailNode->next=new chainNode<T>(element,tailNode,nullptr);
            tailNode=tailNode->next;
            listSize++;
        }
    }
    void reverse()
    {
        chainNode<T>*p=headNode->next;
        while(p)
        {
            chainNode<T>*g=p->next;
            move_to_head(p);
            p=g;
        }
    }
    T merge_with_out_purge(deque_chain<T>&b)
    {
        int n=0;
        int y=listSize+b.listSize;
        chainNode<T>*p=nullptr;
        if(listSize>0) { p = headNode->next; }
        chainNode<T>*g=nullptr;
        if(b.listSize>0) { g = b.headNode->next; }
        if(listSize==0)
        {
            n++;
            if((y)/2==n)
                return g->element;
            while(g)
            {
                push_back(g->element);
                g=g->next;
            }

        }
        else
        {
            while(p&&g)
            {
                if(g->element<=p->element)
                {
                    n++;
                    if((y)/2==n)
                        return g->element;
                    insert_front_node(p,g->element);
                    g=g->next;

                }
                else
                {
                    n++;
                    if((y)/2==n)
                        return p->element;
                    p=p->next;

                }
            }
            while(g)
            {
                n++;
                if((y)/2==n)
                    return g->element;
                push_back(g->element);
                g=g->next;

            }
        }

    }
    chainNode<T>*gethead()
    {
        return headNode;
    }
    chainNode<T>*getlast()
    {
        return tailNode;
    }
    void even_odd()
    {
        if(headNode->next==nullptr||headNode->next->next==nullptr)
        {
            return;
        }
        chainNode<T>*odd=headNode->next;
        chainNode<T>*even=headNode->next->next;
        chainNode<T>*even_head=headNode->next->next;
        while(even!=nullptr&&even->next!=nullptr)
        {
            odd->next=even->next;
            odd=odd->next;
            even->next=odd->next;
            even=even->next;
        }
        odd->next=even_head;
    }
    void move_to_head(chainNode<T>*node)
    {
        if(node==headNode->next){return;}
        chainNode<T>*g=node;
        g->fa->next=g->next;
        if(g->next!=nullptr)
        {
            g->next->fa=g->fa;
        }
        g->next=headNode->next;
        g->fa=headNode;
        headNode->next=g;
    }
    chainNode<T>* find_the_min()
    {
        chainNode<T>*p=headNode->next;
        chainNode<T>*min=p;
        while(p)
        {
            if(p->element<min->element)
            {
                min=p;
            }
            p=p->next;
        }
        return min;
    }
    void insert_front_node(chainNode<T>*node,T element)
    {
        chainNode<T>*tmp=new chainNode<T>(element,node->fa,node);
        node->fa->next=tmp;
        node->fa=tmp;

        listSize++;
    }
    void insert_after_node(chainNode<T>*node,T element)
    {
        node->next=new chainNode<T>(element,node,node->next);
        chainNode<T>*g=node->next;
        if(g->next==nullptr)
        {
            tailNode=g;
        }
        listSize++;
    }
    void move_small()
    {
        chainNode<T>*p=find_the_min();
        move_to_head(p);
    }
    void clear()
    {
        chainNode<T>*t=headNode->next;
        while(t)
        {
            chainNode<T>*g=t;
            t=t->next;
            g->fa=nullptr;
            g->next=nullptr;
            delete g;
        }
        headNode->next=nullptr;
        tailNode=nullptr;
        listSize=0;
    }
    friend int word_count(deque_chain<char>&a);
    void only_merge(deque_chain<T>&b)
    {
        chainNode<T>*p=nullptr;
        if(listSize>0) { p = headNode->next; }
        chainNode<T>*g=nullptr;
        if(b.listSize>0) { g = b.headNode->next; }
        while(g)
        {
            push_back(g->element);
            g=g->next;
        }
    }

    void cross_merge(deque_chain<T>&b)
    {
        chainNode<T>*p=nullptr;
        if(listSize>0) { p = headNode->next; }
        chainNode<T>*g=nullptr;
        if(b.listSize>0) { g = b.headNode->next; }
        if(listSize==0)
        {
            while(g)
            {
                push_back(g->element);
                g=g->next;
            }
        }
        else
        {
            while(p&&g)
            {
                chainNode<T>*a=p->next;
                chainNode<T>*d=g->next;
                p->next=g;
                g->fa=p;
                g->next=a;
                if(a!=NULL)
                    a->fa=g;


                p=a;
                g=d;
            }
            while(g)
            {
                push_back(g->element);
                g=g->next;
            }

        }
    }
    void pruge()
    {
        chainNode<T>*p=headNode->next;
        while(p)
        {
            chainNode<T>*g=p->next;
            while(g)
            {
                chainNode<T>*k=g->next;
                if(g->element==p->element)
                {
                    del(g);
                }
                g=k;
            }
            p=p->next;
        }
    }
    chainNode<T>* get_head()
    {
        return headNode;
    }
    chainNode<T>*get_tail()
    {
        return tailNode;
    }
    void del(chainNode<T>*k)
    {
        chainNode<T>*tmp=k;
        if(k==tailNode)
        {
            tailNode=k->fa;
        }
        k->fa->next=k->next;
        if(k->next!=NULL)
        {
            k->next->fa=k->fa;
        }
        delete tmp;
    }

};

void solve_oj_2()
{
    int n;
    cin>>n;
    vector<int>quick(n,0);
    for(int i=0;i<n;i++)
    {
        int tmp;
        cin>>tmp;
        quick[i]=tmp;
    }
    int i;
    cin>>i;
    for(int j=0;j<quick.size();j++)
    {
        cout<<quick[j]<<" ";
    }
    cout<<endl;
    cout<<endl;
    int k1=0,k2=quick.size()-1;
    while(k1<k2)
    {
        if(quick[k1]==i)
        {
            if(quick[k2]!=i) {
                swap(quick[k1], quick[k2]);
                k1++;
                k2--;
                continue;
            }
            else
            {
                k2--;
                continue;
            }
        }
        k1++;
    }
    for(int p=0;p<quick.size();p++)
    {
        if(quick[p]!=i)
            cout<<quick[p]<<" ";
        else
        {
            if(p==0)
            {
                cout<<"empty"<<endl;
            }
          return;
        }
    }
}

void solve_oj_1()
{
    int n;
    cin>>n;
    vector<int>res(n,0);
    for(int i=0;i<n;i++)
    {
        int tmp;
        cin>>tmp;
        res[i]=tmp;
    }
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            cout<<res[i];
        }
        else
        {
            cout<<" "<<res[i];
        }
    }
    cout<<endl;
    cout<<endl;
    int low=0,high=res.size()-1;
    while(low<high)
    {
        if(res[low]<0)
        {
            low++;
            continue;
        }
        else if(res[low]>0)
        {
            if(res[high]<0)
            {
                swap(res[low],res[high]);
                for(int i=0;i<n;i++)
                {
                    if(i==0)
                    {
                        cout<<res[i];
                    }
                    else
                    {
                        cout<<" "<<res[i];
                    }
                }
                cout<<endl;
                low++;
                high--;
                continue;
            }
            else
            {
                high--;
                continue;
            }
        }

    }
}
template<class T>
bool solve_oj_3(int n,deque_chain<T>&res)
{

    chainNode<T>*s=res.get_head()->next;
    chainNode<T>*p=res.get_head()->next;
    int y=0;
    if(n<res.get_size())
    {
        while(p!=NULL&&y<n-1)
        {
            p=p->next;
            y++;
        }
        int j=0;
        while(j<n/2)
        {
            if(s->element!=p->element)
            {
                return false;
            }
            j++;
            s=s->next;
            p=p->fa;
        }
    }
    else
    {
        int j = 0;
        while (j < res.get_size() / 2) {
            if (s->element != p->element) {
                return false;
            }
            j++;
            s = s->next;
            p = p->fa;
        }
    }
    return true;
}
int Find(vector<int>&n,int num)
{
    int low=0;
    int high=n.size()-1;
    int mid=(low+high)/2;
    while(low<high)
    {
        if(n[mid]==num)
        {
            return mid;
        }
        else
        {
            if(n[mid]>num)
            {
                high=mid-1;
                mid=(low+high)/2;
            }
            else
            {
                low=mid+1;
                mid=(low+high)/2;
            }
        }
    }
    return mid+1;
}
void solve_oj_4()
{
    int n;
    cin>>n;
    vector<int>res(n,0);
    for(int i=0;i<n;i++)
    {
        int tmp;
        cin>>tmp;
        res[i]=tmp;
    }
    int num;
    cin>>num;
    cout<<Find(res,num);
}
void solve_oj_5()
{
    int num;
    cin>>num;
    int left = 0, right = num;
    cout<<"OUT:"<<endl;
    while (left <= right) {
        if(left==right&&num!= sqrt(num)* sqrt(num)){break;}
        long long mid = (right + left) / 2 ;
        long long square = mid * mid;
        if (square < num) {
            left = mid + 1;
        } else if (square > num) {
            right = mid - 1;
        } else {
            cout<<"true";
            return;
        }
    }
    cout<<"false";
    return;
}
int main()
{
    cout<<"IN:"<<endl;
    solve_oj_5();
//    int n;
//    cin>>n;
//    switch (n) {
//        case 0:
//        {
//            int j;
//            cin>>j;
//            vector<int>a;
//            //vector<int>b;
//            string a1;
//            //string b1;
//            getchar();
//            getline(cin,a1);
//           // getline(cin,b1);
//            stringstream in1(a1);
//            //stringstream in2(b1);
//            int num;
//            while(in1>>num)
//            {
//                a.push_back(num);
//            }
////            while(in2>>num)
////            {
////                b.push_back(num);
////            }
//            deque_chain<int>a_(a);
//            a_.print();
////            deque_chain<int>b_(b);
////            b_.print();
//            cout<<endl;
////            a_.only_merge(b_);
////            a_.print();
//            if(solve_oj_3(j,a_))
//            {
//                cout<<"true";
//            }
//            else
//            {
//                cout<<"false";
//            }
//            break;
//        }
//        case 1:
//        {
//            int j;
//            cin>>j;
//            vector<double>a;
//            vector<double>b;
//            string a1;
//            string b1;
//            getchar();
//            getline(cin,a1);
//           // getline(cin,b1);
//            stringstream in1(a1);
//           // stringstream in2(b1);
//            double num;
//            while(in1>>num)
//            {
//                a.push_back(num);
//            }
////            while(in2>>num)
////            {
////                b.push_back(num);
////            }
//            deque_chain<double>a_(a);
//            a_.print();
////            deque_chain<double>b_(b);
////            b_.print();
//            cout<<endl;
//            if(solve_oj_3(j,a_))
//            {
//                cout<<"true";
//            }
//            else
//            {
//                cout<<"false";
//            }
//            break;
//        }
//        case 2:
//        {
//            int j;
//            cin>>j;
//            vector<char>a;
//            vector<char>b;
//            string a1;
//            string b1;
//            getchar();
//            getline(cin,a1);
//           // getline(cin,b1);
//            stringstream in1(a1);
//          //  stringstream in2(b1);
//            char num;
//            while(in1>>num)
//            {
//                a.push_back(num);
//            }
////            while(in2>>num)
////            {
////                b.push_back(num);
////            }
//            deque_chain<char>a_(a);
//            a_.print();
////            deque_chain<char>b_(b);
////            b_.print();
//            cout<<endl;
//
//            if(solve_oj_3(j,a_))
//            {
//                cout<<"true";
//            }
//            else
//            {
//                cout<<"false";
//            }
//            break;
//        }
//        case 3:
//        {
//            int j;
//            cin>>j;
//            vector<string>a;
//            vector<string>b;
//            string a1;
//            string b1;
//            getchar();
//            getline(cin,a1);
//         //   getline(cin,b1);
//            stringstream in1(a1);
//           // stringstream in2(b1);
//            string num;
//            while(in1>>num)
//            {
//                a.push_back(num);
//            }
////            while(in2>>num)
////            {
////                b.push_back(num);
////            }
//            deque_chain<string>a_(a);
//            a_.print();
////            deque_chain<string>b_(b);
////            b_.print();
//               cout<<endl;
////            a_.only_merge(b_);
////            a_.print();
//            if(solve_oj_3(j,a_))
//            {
//                cout<<"true";
//            }
//            else
//            {
//                cout<<"false";
//            }
//            break;
//        }
//        default:
//        {
//            cout<<"err";
//        }
//
//    }
//    //system("pause");
//    return 0;
}