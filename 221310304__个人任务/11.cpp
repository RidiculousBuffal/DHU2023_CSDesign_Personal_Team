#include<bits/stdc++.h>
using namespace std;
int shuzu[10001];
int vis[10001];
int main()
{
    int n;
    cin>>n;
 //   cout<<n<<endl;
    int num;
    for(int i=1;i<=n;i++)
    {
        cin>>num;
   //     cout<<num<<" ";
        if(num!=i)
        {
            cout<<num<<" "<<i<<" ";
        }
    }
    return 0;
}
