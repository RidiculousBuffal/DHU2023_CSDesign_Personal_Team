#include<bits/stdc++.h>
using namespace std;
struct node
{
    int index_;
    int level;
    node(){}
    node(int index_,int level)
    {
        this->index_=index_;
        this->level=level;
    }
};
bool operator <(node a1,node a2)
{
    if(a1.level==a2.level){return a1.index_<a2.index_;}
    return a1.level<a2.level;
}
multiset<node>person;
multiset<node>op;
int main()
{
    int x=0;
    int num;
    while(cin>>num)
    {
        if(x==0)
        {
            cout<<"("<<x<<","<<num<<")";
        }
        else
        {
            cout<<","<<"("<<x<<","<<num<<")";
        }
        if(num<50)
        {
            op.insert({x,num});
        }
        else if(50<=num&&num<=255)
        {
            person.insert({x,num});
        }
        x++;
    }
    cout<<endl;
    cout<<endl;
    if(op.empty()){cout<<"none";}
    else {
        for (std::set<node>::iterator it = op.begin(); it != op.end(); it++) {
                cout<<it->index_<<" ";
        }
    }
    cout<<endl;
    if(person.empty()){cout<<"none";}
    else {
        for (std::set<node>::iterator it = person.begin(); it != person.end(); it++) {
            cout<<it->index_<<" ";
        }
    }
    return 0;
}