#include <bits/stdc++.h>

using namespace std;
int vis[10001];

int main() {
    int n;
    cin >> n;
    int index_;
    for (int i = 0; i < n; i++) {
        int num;cin >> num;
        if (vis[num] == 1) {
            index_ = num;}
        vis[num] = 1;}
    cout << index_ << " ";
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {cout << i << " ";
            return 0;}}
    return 0;
}