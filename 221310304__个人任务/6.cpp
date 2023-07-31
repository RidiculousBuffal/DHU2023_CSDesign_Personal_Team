 #include<bits/stdc++.h>
using namespace std;
int main()
{
    int len;
    char letters[10000];
    char target;
    cin>>len;
    for(int i=0;i<len;i++)
    {
        cin>>letters[i];
    }
    cin>>target;
    int i=0;
    for(i=0;i<len;i++)
    {
        if(letters[i]>target) {
            cout << letters[i];
            break;
        }
    }
    if(i==len)
    {
        cout<<letters[0];
    }
    return 0;

}
