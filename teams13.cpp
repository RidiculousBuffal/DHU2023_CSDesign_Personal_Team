#include<bits/stdc++.h>

using namespace std;

struct c {
    int queue_time;
    int index_;
    int wait_time;

    c() {}

    c(int queue_time, int index_, int wait_time) {
        this->queue_time = queue_time;
        this->index_ = index_;
        this->wait_time = wait_time;
    }
};

bool operator<(c c1, c c2) {
    if (c1.queue_time == c2.queue_time) {
        if (c1.wait_time == c2.wait_time) {
            return c1.index_ < c2.index_;
        }
        return c1.wait_time < c2.wait_time;
    }
    return c1.queue_time < c2.queue_time;
}

struct processing//任务队列
{
    int index_;
    int wait_time;

    processing() {}

    processing(int index_, int wait_time) {
        this->index_ = index_;
        this->wait_time = wait_time;
    }
};

bool operator<(processing a1, processing a2) {
    if (a1.wait_time == a2.wait_time) {
        return a1.index_ < a2.index_;
    }
    return a1.wait_time < a2.wait_time;
}

int main() {
    int n;
    cin >> n;
    multiset<c> CPU;
    for (int i = 0; i < n; ++i) {
        int queue_time;
        int wait_time;
        cin >> queue_time;
        cin >> wait_time;
        CPU.insert({queue_time, i, wait_time});
    }
    multiset<processing> go;
    int Time = CPU.begin()->queue_time;//开始时间直接快进到第一个事件的等待时间
    std::set<c>::iterator it = CPU.begin();
    while (it != CPU.end()) {
        while (it != CPU.end() && Time >= it->queue_time) {
            go.insert({it->index_, it->wait_time});
            it++;
        }
        if (!go.empty()) {
            cout << go.begin()->index_ << " ";//输出第一个
            Time += go.begin()->wait_time;
            go.erase(go.begin());
        } else {
            if (++it != CPU.end())//判断一下是不是越界了
            {
                Time = it->queue_time;
            } else {
                break;
            }
        }
    }
    while (!go.empty()) {
        cout << go.begin()->index_ << " ";//输出第一个
        Time += go.begin()->wait_time;
        go.erase(go.begin());
    }
    return 0;

}