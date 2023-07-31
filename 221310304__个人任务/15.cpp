#include<bits/stdc++.h>
using namespace std;
int nums[10001];
int main()
{
    int k;
    cin>>k;
    int n;
    cin>>n;
    int num;
    string s;
    int add;
    priority_queue<int,vector<int>,greater<int>>nums;
    for(int i=0;i<n;i++)
    {
        cin>>num;
        nums.push(num);
        if(nums.size()>k)
        {
            nums.pop();
        }
    }
    while(cin>>s)
    {
        cin>>add;
        nums.push(add);
        if(nums.size()>k)
        {
            nums.pop();
        }
        cout<<nums.top()<<endl;
    }
    return 0;
}
