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
    void Erase()
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
                       erase(g);
                   }
                   g=k;
               }
               p=p->next;
           }
       }
    bool judge1()
    {
        chainNode<T>*p1=headNode->next;
        chainNode<T>*p2=tailNode;
        while(p1->next!=p2)
        {
            if(p1->element==p2->element)
            {
                p1=p1->next;
                p2=p2->fa;
            }
            else
                return 0;
            break;
        }
        return 1;
    }
    bool judge2(int n)
    {
        chainNode<T>*p1=headNode->next;
        chainNode<T>*p2=headNode->next;
        for(int i=0;i<n-1;i++)
        {
            p2=p2->next;
        }
        while(p1->next!=p2)
        {
            if(p1->element==p2->element)
            {
                p1=p1->next;
                p2=p2->fa;
            }
            else
            {
                return 0;
                break;
            }
        }
        return 1;
    }
    int get_size()
    {
        
        return listSize;
    }
    void erase(chainNode<T>*k)
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
    virtual void print()
    {
        if(listSize==0){cout<<endl;return;}
        chainNode<T>*p=headNode->next;
        cout<<p->element;
        p=p->next;
        while(p)
        {
            cout<<"->"<<p->element;
            p=p->next;
        }
        cout<<endl;
    }
};

int main()
{
    int x;
    cin>>x;
    int n;
    cin>>n;
    switch (x) {
        case 0:
        {
            vector<int>a;
            string a1;
            getchar();
            getline(cin,a1);
            stringstream in1(a1);
            int num;
            while(in1>>num)
            {
                a.push_back(num);
            }
            deque_chain<int>a_(a);
            a_.print();
            cout<<endl;
            if(a_.get_size()<=n)
            {
               if( a_.judge1()||n==1)
               {
                   cout<<"true";
               }
                else
                    cout<<"false";
                
            }
            if(a_.get_size()>n)
            {
                if( a_.judge2(n)||n==1)
                {
                    cout<<"true";
                }
                 else
                     cout<<"false";
                 
            }
            break;
        }
        case 1:
        {
            vector<double>a;
            string a1;
            getchar();
            getline(cin,a1);
            stringstream in1(a1);
            double num;
            while(in1>>num)
            {
                a.push_back(num);
            }
            deque_chain<double>a_(a);
            a_.print();
            cout<<endl;
            if(a_.get_size()<=n)
            {
               if( a_.judge1()||n==1)
               {
                   cout<<"true";
               }
                else
                    cout<<"false";
                
            }
            if(a_.get_size()>n)
            {
                if( a_.judge2(n)||n==1)
                {
                    cout<<"true";
                }
                 else
                     cout<<"false";
                 
            }
            break;
        }
        case 2:
        {
            vector<char>a;
            string a1;
            getchar();
            getline(cin,a1);
            stringstream in1(a1);
            char num;
            while(in1>>num)
            {
                a.push_back(num);
            }
            deque_chain<char>a_(a);
            a_.print();
            cout<<endl;
            if(a_.get_size()<=n)
            {
               if( a_.judge1()||n==1)
               {
                   cout<<"true";
               }
                else
                    cout<<"false";
                
            }
            if(a_.get_size()>n)
            {
                if( a_.judge2(n)||n==1)
                {
                    cout<<"true";
                }
                 else
                     cout<<"false";
                 
            }
            break;
        }
        case 3:
        {
            vector<string>a;
            string a1;
            getchar();
            getline(cin,a1);
            stringstream in1(a1);
            string num;
            while(in1>>num)
            {
                a.push_back(num);
            }
            deque_chain<string>a_(a);
            a_.print();
            cout<<endl;
            if(a_.get_size()<=n)
            {
               if( a_.judge1()||n==1)
               {
                   cout<<"true";
               }
                else
                    cout<<"false";
                
            }
            if(a_.get_size()>n)
            {
                if( a_.judge2(n)||n==1)
                {
                    cout<<"true";
                }
                 else
                     cout<<"false";
                 
            }
            break;
        }
        default:
        {
            cout<<"err";
        }
        return 0;
    }
}
