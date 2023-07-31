#include <bits/stdc++.h>
#include <unordered_map>

//unorderedmap需要手动制造hash函数
using namespace std;

struct hash_func {
    hash_func() {}
    size_t operator()(const std::pair<int, int> &i) const//注意这里一定要const
    {
        return std::hash<int>()(i.first << 16) ^ std::hash<int>()(i.second);
        //hash键值对为第一pair左移12位再异或第二pair的hash,最后统一hash
    }
};

struct movie_vaild {
    int price;//第一关键字price
    int shop;//第二关键字shop
    movie_vaild() {}

    movie_vaild(int price, int shop) {
        this->price = price;
        this->shop = shop;
    }
};

bool operator<(movie_vaild x, movie_vaild y) {
    if (x.price == y.price) {
        return x.shop < y.shop;
    } else {
        return x.price < y.price;
    }
}

struct report {
    int movie;
    int shop;
    int price;

    report() {}

    report(int movie, int shop, int price) {
        this->movie = movie;
        this->shop = shop;
        this->price = price;
    }
};

bool operator<(const report x, const report y) {
    if (x.price == y.price) {
        if (x.shop == y.shop) {
            return x.movie < y.movie;
        }
        return x.shop < y.shop;
    }
    return x.price < y.price;
}

class MovieRentingSystem {
protected:
    unordered_map<pair<int, int>, int, hash_func> t_price;//通过shop 和 movie 找到电影的价格
    unordered_map<int, set<movie_vaild>> t_vaild;//可用的电影,通过电影的名字,找到价格最低的超市
    set<report> movie_report;
public:
    MovieRentingSystem() {}

    void init() {
        int n, m;
        cin >> n >> m;//商店个数,初始化行数
        for (int i = 0; i < m; i++) {
            int shop_i, movie_i, price_i;
            cin >> shop_i >> movie_i >> price_i;
            t_price[{shop_i, movie_i}] = price_i;
            t_vaild[movie_i].insert({price_i, shop_i});
        }
    }

    void search(int movie) {
        vector<int> res;
        if (!t_vaild.count(movie))//不存在这个key
        { cout << endl; }
        auto it = t_vaild[movie].begin();
        for (int i = 0; i < 5 && it != t_vaild[movie].end(); ++i, ++it) {
            cout << it->shop << " ";
        }
        cout << endl;
    }

    void rent(int shop, int movie) {
        int price = t_price[{shop, movie}];
        t_vaild[movie].erase({price, shop});//集合中删除这个电影的商店信息
        movie_report.insert({movie, shop, price});
    }

    void drop(int shop, int movie) {
        int price = t_price[{shop, movie}];
        t_vaild[movie].insert({price, shop});
        movie_report.erase({movie, shop, price});
    }

    void rep() {
        auto it = movie_report.begin();
        for (int i = 0; i < 5 && it != movie_report.end(); it++, i++) {
            cout << it->shop << " " << it->movie << " " << endl;
        }
    }
};

int main() {


    MovieRentingSystem oj_last;
    oj_last.init();
    string s;
    while (cin >> s) {
        if (s == "search") {
            int movie;
            cin >> movie;
            oj_last.search(movie);
        }
        if (s == "rent") {
            int shop, movie;
            cin >> shop >> movie;
            oj_last.rent(shop, movie);
        }
        if (s == "drop") {
            int shop, movie;
            cin >> shop >> movie;
            oj_last.drop(shop, movie);
        }
        if (s == "report") {
            oj_last.rep();
        }
    }
    return 0;

}