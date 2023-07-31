#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int nums[10001];
    int num;
    int max=0;
    int index;
    for(int i=0;i<n;i++)
    {
        cin>>num;
        nums[i]=num;
        if(num>=max)
        {
            max=num;
            index=i;
        }
    }
    for(int i=0;i<n;i++)
    {
        if(max>=nums[i]*2&&i!=index)
        {
            continue;
        }
        if(max<nums[i]*2&&i!=index)
        {
            cout << "-1";
            break;
        }
        cout<<index;
    }

    return 0;
}