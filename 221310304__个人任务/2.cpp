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
        cout<<p->element<<" ";
        p=p->next;
        while(p)
        {
            cout<<p->element<<" ";


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
    chainNode<T>*gethead()
    {
        return headNode;
    }
    chainNode<T>*getlast()
    {
        return tailNode;
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
    void pop_back()
    {
        if(this->listSize==0)
        {
            return;
        }
        else
        {
            listSize--;
            if(tailNode==headNode->next)
            {
                chainNode<T>*p=headNode->next;
                delete p;
            }
            else
            {
                chainNode<T>*g=tailNode;

                tailNode->fa->next=NULL;
                tailNode=tailNode->fa;
                delete g;
            }
        }
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
void Rearrange(deque_chain<int>&a)
{
    chainNode<int>*p=a.get_head()->next;
    chainNode<int>*q=a.get_tail();
    int l=0,h=a.get_size()-1;
    while(l<h)
    {
        if(q->element<0)
        {
            if(p->element>=0)
            {
                swap(p->element,q->element);
                p=p->next;
                q=q->fa;
                l++;
                h--;
                a.print();
                continue;
            }
            else
            {
                p=p->next;
                l++;
                continue;
            }
        }else
        {
            q=q->fa;
           h--;
            continue;
        }
    }
}
void Delete(deque_chain<int>&a,int num)
{
    chainNode<int>*p=a.get_head()->next;
    chainNode<int>*q=a.get_tail();
    int l=0,h=a.get_size()-1;
    while(l<h)
    {
        if(p->element==num)
        {
            if(q->element!=num)
            {
                swap(q->element,p->element);
                l++;
                h--;
                p=p->next;
                q=q->fa;
                a.pop_back();

            }
            else
            {

                q=q->fa;
                a.pop_back();
                h--;
            }
        }
        else
        {
            p=p->next;
            l++;
        }
    }
    if(a.get_tail()->element==num)
    {
        a.pop_back();
    }
}
int main()
{
   int n;
   cin>>n;
   int num;
   vector<int>data;
   for(int i=0; i<n;i++)
   {
       cin>>num;
       data.push_back(num);
   }
   int nums;
   cin>>nums;
   deque_chain<int>data1(data);
   data1.print();
   cout<<endl;
    Delete(data1,nums);
    if(data1.get_size()==0)
    {
        cout<<"empty";
    }
    else
    {
        data1.print();
    }

    return 0;
}
