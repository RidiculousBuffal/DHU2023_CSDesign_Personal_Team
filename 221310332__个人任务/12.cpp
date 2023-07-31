#include <bits/stdc++.h>
using namespace std;
int vis[10001];
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
bool operator < (node a1,node a2)
{
    return a1.num>a2.num;
}
set<node>x;
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++) {
        int num;
        cin >> num;
        x.insert({i,num});
    }
    if(x.size()==1)
    {
        cout<<"0";
        return 0;
    }
    auto it=x.begin();
    it++;
    if(x.begin()->num>=it->num*2)
    {
        cout<<x.begin()->index_;
    }
    else
    {
        cout<<"-1";
    }
    return 0;

}