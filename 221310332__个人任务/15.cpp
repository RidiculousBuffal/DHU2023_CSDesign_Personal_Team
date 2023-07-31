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
    int k,n;
    cin>>k>>n;
    priority_queue<int,vector<int>,greater<int>> s;
    for (int i = 0; i < n; ++i) {
        int tmp;
        cin>>tmp;
        s.push(tmp);
        if(s.size()>k)
        {
            s.pop();
        }
    }
    string j;
    while(cin>>j)
    {
        int p;
        cin>>p;
        s.push(p);
        if(s.size()>k)
        {
            s.pop();
        }
        cout<<s.top()<<endl;
    }
    return 0;

}