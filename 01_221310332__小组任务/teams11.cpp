#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
bool operator <(pair<int,int>a1,pair<int,int>a2)
{
    return a1.first<a2.first;
}
class LRU
{
protected:
    long long capacity;
    map<int,int>key_to_time;
    map<pair<int,int>,int>time_to_key;//第一个是time,第二个是key
    int start;
public:
    LRU(int capacity)
    {
        this->capacity=capacity;
        this->start=0;
    }
    void put(int a,int b)
    {
        if(time_to_key.count({key_to_time[a],a})==1)
        {
            //先删除
            time_to_key.erase({key_to_time[a],a});
            start++;
            key_to_time[a]=start;
            time_to_key[{start,a}]=b;
            return;
        }
        if(time_to_key.size()==capacity)
        {
            time_to_key.erase(time_to_key.begin());
            start++;
            key_to_time[a]=start;
            time_to_key[{start,a}]=b;
            return;
        }
        else
        {
            start++;
            time_to_key[{start,a}]=b;
            key_to_time[a]=start;
        }
    }
    void get(int a)
    {
        if(time_to_key.count({key_to_time[a],a})==0)
        {
            cout<<"-1"<<endl;
        }
        else
        {
            cout<<time_to_key[{key_to_time[a],a}]<<endl;
            int val=time_to_key[{key_to_time[a],a}];
            time_to_key.erase({key_to_time[a],a});
            start++;
            key_to_time[a]=start;
            time_to_key[{key_to_time[a],a}]=val;
        }
    }
};
int main()
{
//    get_oj_case();
  //  ifstream cin("in.txt");
   int start=0;
   int capacity;
   cin>>capacity;
   string s;
   LRU lru(capacity);
   while(cin>>s)
   {
       if(s=="put")
       {
           int a,b;
           cin>>a>>b;
           lru.put(a,b);
       }
       else
       {
           int a;
           cin>>a;
           lru.get(a);
       }
   }

   return 0;

}