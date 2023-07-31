#include<bits/stdc++.h>

using namespace std;

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
    if (a1.num == a2.num) {
        return a1.index_ < a2.index_;
    }
    return a1.num < a2.num;
}

set<node> op;

int main() {
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        int s = 0;
        for (int j = 0; j < n; j++) {
            int p = 0;
            cin >> p;
            if (p == 1) {
                s++;
            }
        }
        op.insert({i, s});
    }
    int ppppp;
    cin >> ppppp;
    int t = 0;
    for (std::set<node>::iterator it = op.begin(); it != op.end(); it++) {
        if (t >= ppppp) {
            return 0;
        }
        cout << it->index_ << " ";
        t++;
    }
    return 0;
}
