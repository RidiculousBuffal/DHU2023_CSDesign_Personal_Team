#include<bits/stdc++.h>
using namespace std;
struct shuzu{
    int num;
    int index;
}child[10000];
bool cmp(shuzu a1,shuzu a2)
{
    return a1.num<a2.num;
}
int main()
{
    int n;
    cin>>n;
    int nums;
    vector<int>xulie;
    for(int i=0;i<n;i++)
    {
        cin>>nums;
        xulie.push_back(nums);
    }
    int k;
    cin>>k;
    int min=INT_MAX;
    int in_dex;
    int tmp=n-k;
    for(int i=0;i<tmp;i++)
    {
        min=INT_MAX;
        for(int j=0;j<xulie.size();j++)
        {
            if (xulie[j]<= min)
            {
                min = xulie[j];
                in_dex = j;
            }
        }
        xulie.erase(xulie.begin()+in_dex);
    }
    for(int i=0;i<xulie.size();i++)
    {
        cout<<xulie[i]<<" ";
    }
    return 0;

}
