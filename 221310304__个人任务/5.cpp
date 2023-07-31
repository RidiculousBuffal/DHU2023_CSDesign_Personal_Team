
#include<bits/stdc++.h>
using namespace std;
bool judge(long long num)
{
  long long low=1;
  long long  high=num;
    long long mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if((mid*mid)==num)
        {
            return true;
        }
        else if(mid*mid>num)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    return false;
}
int main()
{
    long long  num;
    cin>>num;
    if(judge(num))
    {
        cout<<"true";
    }
    else
        cout<<"false";
    return 0;

}
