#include <bits/stdc++.h>
using namespace std;
vector<int>arr;
vector<int>kthSmallestPrimeFraction(int k)
{
    int n=arr.size();
   struct my_cmp
   {
       bool operator ()(const pair<int,int>&x,const pair<int,int>&y)
       {
           return arr[x.first]*arr[y.second]>arr[x.second]*arr[y.first];
       }
   };
   priority_queue<pair<int,int>,vector<pair<int,int>>,my_cmp>que;
   //这里面每一个pair存的是在arr数组中的两个位序,而不是真是的分数
   for(int j=1;j<n;j++)
   {
       que.emplace(0, j);//这个0和j是遵循排序规则arr[0]/arr[j]>arr[0]/arr[j+1]
   }
   for(int z=1;z<k;z++)
   {
       pair<int,int>tmp=que.top();
       que.pop();
       if(tmp.first+1<tmp.second)
       {
           que.emplace(tmp.first+1,tmp.second);
       }
   }
   return{arr[que.top().first],arr[que.top().second]};
}
int main()
{
    int j;
    cin>>j;
    for (int i = 0; i < j; ++i) {
        int tmp;
        cin>>tmp;
        arr.push_back(tmp);
    }
    int k;
    cin>>k;
    vector<int>res= kthSmallestPrimeFraction(k);
    cout<<res[0]<<" "<<res[1]<<endl;
}