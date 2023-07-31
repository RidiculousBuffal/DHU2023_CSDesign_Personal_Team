#include <bits/stdc++.h>
using namespace std;
int vis[10001];
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    int n;
    cin>>n;

    for(int i=0;i<n;i++)
    {
        int num;
        cin>>num;
        vis[num]++;
    }
    sort(vis,vis+10001,cmp);
    int ans=0;
    int k=n/2;
    int start=0;
    while(k>0)
    {
        k-=vis[start];
        ans++;
        start++;
    }
    cout<<ans;
    return 0;
}