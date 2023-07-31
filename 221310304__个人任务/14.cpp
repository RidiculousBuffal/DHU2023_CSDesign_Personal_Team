#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int nums[10001];
    int num;
    for(int i=0;i<n;i++)
    {
        cin>>num;
        nums[num+1000]=1;
    }
    for(int i=0;i<4000;i++)
    {
        if(nums[i+1000]==1&&nums[2*i+1000]==1)
        {
            cout<<"true"<<endl;
            return 0;
        }
    }
    cout<<"false";
    return 0;
}
