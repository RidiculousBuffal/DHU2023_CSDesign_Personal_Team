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
    vector<int>s;
    for(int i=0;i<n;i++)
    {
        int tmp;
        cin>>tmp;
        s.push_back(tmp);
    }
    int k;
    cin>>k;
    sort(s.begin(),s.end());
    for(int i=0;i<s.size();i++)
    {
        if(s[i]<0)
        {
            s[i]=-s[i];
            k--;
        }
        if(k<=0){break;}
    }
    sort(s.begin(),s.end());
    if(k==0)
    {
        cout<<accumulate(s.begin(),s.end(),0);
    }
    else if(k>0)
    {
        if(k%2==0)
        {
            cout<<accumulate(s.begin(),s.end(),0);
        }
        else
        {
            cout<<accumulate(s.begin(),s.end(),0)-2*s[0];
        }
    }

    return 0;

}