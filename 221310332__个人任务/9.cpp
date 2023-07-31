#include <bits/stdc++.h>
using namespace std;
int vis[10001];
int main()
{
    int m,n;
    cin>>m>>n;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            int num;
            cin>>num;
            vis[num]++;
        }
    }
    int ans=0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            int num;
            cin>>num;
            if(vis[num]>0)
            {
                vis[num]--;
            }
            else
            {
                ans++;
            }
        }
    }
    cout<<ans;
    return 0;
}