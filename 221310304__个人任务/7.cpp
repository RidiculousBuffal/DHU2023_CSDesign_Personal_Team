#include<bits/stdc++.h>
using namespace std;
struct Fight{
    int sum=0;
    int index;
}fight[100];
bool cmp(Fight a1,Fight a2)
{
    if(a1.sum==a2.sum){return a1.index<a2.index;}
    else
    {
        return a1.sum<a2.sum;
    }
}
int fighter[102][102];
int main()
{
    int m,n;
    cin>>m>>n;

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>fighter[i][j];
        }
    }
    int k;
    cin>>k;

    for(int i=0;i<m;i++)
    {
        fight[i].index=i;
        for(int j=0;j<n;j++)
        {
            if (fighter[i][j] != 0) {
                fight[i].sum++;
            }
        }
    }
    sort(fight,fight+m,cmp);
    for(int p=0;p<k;p++)
    {
        cout<<fight[p].index<<" ";
    }
    return 0;

}
