#include<bits/stdc++.h>
using namespace std;
int nums[10002];
int main()
{
    int m,n;
    cin>>m>>n;
   
    int num;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>num;
            
            nums[num]++;
        }
    }
    int sum=0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>num;
         
            if(nums[num]!=0)
            {
                nums[num]--;
            }
            else
            {
                sum++;
            }
        }
    }
    cout<<sum;
    return 0;
}
