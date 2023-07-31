#include<bits/stdc++.h>
using namespace std;
struct node
{
    int index_;
    int num;
    node(){}
    node(int index_,int num)
    {
        this->index_=index_;
        this->num=num;
    }
};
bool operator <(node a1,node a2)
{
    if(a1.num==a2.num)
    {
        return a1.index_<a2.index_;
    }
    return a1.num>a2.num;
}
set<node>op;
int main() {
    int n;
    cin>>n;
    list<int>jjj;
    for(int i=0;i<n;i++)
    {
        int tmp;
        cin>>tmp;
        jjj.push_back(tmp);
    }
    int k;
    cin>>k;
    for(int i=0;i<n-k;i++)
    {
        jjj.erase(min_element(jjj.begin(),jjj.end()));
    }
    for(auto it = jjj .begin();it!=jjj.end();it++)
    {
        cout<<*it<<" ";
    }

   return 0;
}
