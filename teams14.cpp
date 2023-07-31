#include<bits/stdc++.h>

using namespace std;

class MyCalendar {
public:
    map<int, int> mp;

    MyCalendar() {
    }

    bool book(long long start, long long end) {
        mp[start]++;mp[end]--;long long ans = 0;
        //想象一辆公交车，按时间有人上车，有人下车。对于这一题，车上的乘客不能多于一个人。
        for (std::map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
            ans += it->second;
            if (ans >= 2) {mp[start]--;mp[end]++;return false;}}
        return true;}
};

int main() {
    MyCalendar cal;
    ifstream cin("in_14.txt");
    string s;
    while (cin >> s) {
        long long a, b;
        cin >> a >> b;
        if (cal.book(a, b)) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
    return 0;
}