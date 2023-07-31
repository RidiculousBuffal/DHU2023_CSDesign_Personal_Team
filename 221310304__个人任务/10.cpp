#include<bits/stdc++.h>
using namespace std;
int nums[10001];
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    int n;
    cin>>n;
    int num;
    vector<int>questions;
    for(int i=0;i<n;i++)
    {
            cin>>num;
            questions.push_back(num);
            nums[num]++;
    }
    sort(nums,nums+10001,cmp);
    int k=n/2;
    int sum=0;
    int start=0;
    while(k>0)
    {
        sum++;
        k=k-nums[start];
        start++;
    }
    cout<<sum;
    return 0;
}
