#include<bits/stdc++.h>
using namespace std;
template<class T>
struct chainNode
{
    T element;
    chainNode <T>*next;//下一个节点的指针
    chainNode<T> *fa;//上一个节点的指针
    chainNode(T element,chainNode<T>*fa=NULL,chainNode<T>*next=NULL)
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
    chainNode()
    {
        fa=NULL,next=NULL;
    }
};

template<class T>
class deque_chain//双向链表
{
protected:
    chainNode <T>*headNode;
    chainNode  <T>*tailNode;
    int listSize;
public:
    deque_chain()
    {
        headNode=new chainNode<T>(nullptr,nullptr);
        tailNode=nullptr;
        listSize=0;
    }
    deque_chain(deque_chain <T>&b)//拷贝构造函数
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
    explicit deque_chain(vector<T>&a)//独一无二的，将数组转换为双向链表
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

    virtual void print()
    {
        if(listSize==0){cout<<endl;return;}
        chainNode<T>*p=headNode->next;
        // cout<<"head-->";
        cout<<p->element;
        p=p->next;
        while(p)
        {
            cout<<" "<<p->element;


            p=p->next;
        }
        cout<<endl;
    }
    int getsize()
        {
            return listSize;
        }
    friend vector<int>distance(deque_chain<int>&a);
    void push_front(T element)//向链表的最前面插入元素
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
    void insert_by_index(int index,T element)//特定位置插入
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

    virtual void erase(chainNode<T>*node)
    {
        chainNode<T>*p=node;
        p->fa->next=p->next;
        if(p->next!=NULL)
            p->next->fa=p->fa;
       else
           tailNode=p->fa;
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
            if(g->next!=NULL)
                g->next->fa = p;
            else
                tailNode=g->fa;
            delete g;
            listSize--;
        }
    }
    virtual void push_back(T element)//从尾部插入
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
    void reverse()//倒置
    {
        chainNode<T>*p=headNode->next;
        while(p)
        {
            chainNode<T>*g=p->next;
            move_to_head(p);
            p=g;
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
    void move_to_head(chainNode<T>*node)//把节点移到头上
      {
          if(node==headNode->next){return;}
          if(node==tailNode){tailNode=tailNode->fa;}
          chainNode<T>*g=node;
          g->fa->next=g->next;
          if(g->next!=nullptr)
          {
              g->next->fa=g->fa;
          }
          g->next=headNode->next;
          g->fa=headNode;
          headNode->next->fa=g;
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
  //  friend void print_p(deque_chain<polynomial>&a);
    friend void solve_problem (string &a,string&a_xi,string &b,string&b_xi,int k);
};
template<class T>
class circular_deque_chain:public deque_chain<T>
{
public:
    circular_deque_chain(int n,T k)
    {
        if(n<=0)return;
        this->headNode=new chainNode<T>(NULL,NULL);
        this->listSize=n;
        chainNode<T>*p=this->headNode;
        for(int i=0;i<n;i++)
        {
            //构建N个含k的节点
            p->next=new chainNode<T>(k,p,NULL);
            p=p->next;
        }
        this->tailNode=p;
        this->tailNode->next=this->headNode->next;
    }
    circular_deque_chain()
    {
        this->headNode=new chainNode<T>(nullptr,nullptr);
        this->tailNode=this->headNode;
        this->listSize=0;
    }
    circular_deque_chain(vector<T>&a)
    {
        if(a.size()==0)
        {
            this->headNode=new chainNode<T>(nullptr,nullptr);
            this->tailNode=this->headNode;
            this->listSize=0;
        }
       else
        {
            this->listSize=a.size();
            this->headNode=new chainNode<T>(nullptr,nullptr);
            this->tailNode=this->headNode;
            chainNode<T>*p=this->headNode;
            for(int i=0;i<a.size();i++)
            {
                p->next=new chainNode<T>(a[i],p,NULL);
                p=p->next;
            }
            p->next=this->headNode->next;
            this->tailNode=p;
            this->headNode->next->fa=this->tailNode;
        }

    }
    void push_back(T element) override
    {
        if(this->listSize==0)
        {
            this->headNode->next=new chainNode<T>(element,this->headNode,nullptr);
            this->tailNode=this->headNode->next;
            this->tailNode->next=this->headNode->next;
            this->headNode->fa=this->tailNode;
            this->listSize++;
        }
        else
        {

            this->tailNode->next=new chainNode<T>(element,this->tailNode,nullptr);
            this->tailNode=this->tailNode->next;
            this->tailNode->next=this->headNode->next;
            this->headNode->next->fa=this->tailNode;
            this->listSize++;
        }
    }
    void erase(chainNode<T>*node)override
    {
        chainNode<T>*p=node;
        if(p==this->tailNode){this->tailNode=this->tailNode->fa;}
        p->fa->next=p->next;
        p->next->fa=p->fa;
        delete p;
        this->listSize--;
    }
    void print()override
    {
        chainNode<T>*p=this->headNode->next;
        cout<<"(1,"<<p->element<<")";
        p=p->next;
        for(int i=2;i<=this->listSize;i++)
        {
            cout<<"->("<<i<<","<<p->element<<")";
            p=p->next;
        }
    }

   
};
void arrange(deque_chain<int>&a)
{
    chainNode<int>*p=a.gethead()->next;
    chainNode<int>*q=a.getlast();
    int len=0,height=a.getsize()-1;
    while(len<height)
    {
        if(q->element<0)
        {
            if(p->element>=0)
            {
                swap(p->element,q->element);
                p=p->next;
                q=q->fa;
                len++;
                height--;
                a.print();
                continue;
            }
            else
            {
                p=p->next;
                len++;
                continue;
            }
        }else
        {
            q=q->fa;
           height--;
            continue;
        }
    }
}
int main()
{
    int n;
       cin>>n;
       vector<int>nums;
       for(int i=0;i<n;i++)
       {
           int num;
           cin>>num;
           nums.push_back(num);
       }
       deque_chain<int>nums1(nums);
       nums1.print();
       cout<<endl;
       arrange(nums1);
       return 0;
}
