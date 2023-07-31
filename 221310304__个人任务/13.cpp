#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<int>nums;
    int num;
    for(int i=0;i<n;i++)
    {
        cin>>num;
        nums.push_back(num);
    }
    int k;
    cin>>k;
    int sum=0;
    sort(nums.begin(),nums.end());
    for(int i=0;i<n;i++)
    {
        if(nums[i]<0)
        {
            nums[i]=-nums[i];
            k--;
        }
        if(k<=0)
        {
            break;
        }
    }
    sort(nums.begin(),nums.end());
    if(k==0)
    {
        for(int i=0;i<n;i++)
        {
            sum=sum+nums[i];
        }
        cout<<sum;
    }
    else if(k>0)
    {
        if(k%2==0)
        {
            for(int i=0;i<n;i++)
            {
                sum=sum+nums[i];
            }
            cout<<sum;
        }
        else
        {
            for(int i=0;i<n;i++)
            {
                sum=sum+nums[i];
            }
            sum=sum-2*nums[0];
            cout<<sum;
        }
    }


    return 0;
}