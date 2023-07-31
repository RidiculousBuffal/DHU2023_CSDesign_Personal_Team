
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[10000];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    int target;
    int point=0;
    cin>>target;
    int low=0;
    int high=n-1;
    int mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(a[mid]==target)
        {
            cout<<mid;
            point=1;
            break;
        }
        else if(a[mid]>target)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    if(point==0)
    {
        if(target>a[n-1])
        cout<<mid+1;
        else
            cout<<mid;
    }
    return 0;

}
