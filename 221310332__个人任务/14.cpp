#include <bits/stdc++.h>

using namespace std;
int vis[10001];

struct node {
    int index_;
    int num;

    node() {}

    node(int index_, int num) {
        this->index_ = index_;
        this->num = num;
    }
};

bool operator<(node a1, node a2) {
    return a1.num > a2.num;
}

set<node> x;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        vis[tmp + 2000] = 1;
    }
    for (int i = -1001; i <= 1001; i++) {
        if (vis[i + 2000] == 1 && vis[2 * i + 2000] == 1) {
            cout << "true" << endl;
            return 0;
        }
    }
    cout << "false";
    return 0;

}