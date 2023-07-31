#include <bits/stdc++.h>
using namespace std;
bool cmp(pair<int,int>a1,pair<int,int>a2)
{
    return a1.first*a2.second<a1.second*a2.first;
}
vector<int>solve(vector<int>&arr,int k)
{
    int n=arr.size();
    vector<pair<int,int>>frac;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            frac.push_back({arr[i],arr[j]});
        }
    }
    sort(frac.begin(),frac.end(),cmp);
    return {frac[k-1].first,frac[k-1].second};
}
int main()
{
    int len;
    cin>>len;
    vector<int>arr(len,0);
    for(int i=0;i<len;i++)
    {
        int tmp;
        cin>>tmp;
        arr[i]=tmp;
    }
    int k;
    cin>>k;
    vector<int>res= solve(arr,k);
    cout<<res[0]<<" "<<res[1];
}