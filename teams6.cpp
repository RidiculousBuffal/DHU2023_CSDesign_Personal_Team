#include <bits/stdc++.h>

using namespace std;

////////////////////////////以下全是邻接矩阵//////////////////////////
template<class E>
struct edgeNode {
    int data;//就是连到那个点的序号
    E weight;
    edgeNode<E> *next;

    edgeNode() {
        next = NULL;
        weight = 0;
    }

    edgeNode(const int &d, edgeNode<E> *ptr = NULL) //构造函数，用于构造其他结点（无权图）
    //函数参数表中的形参允许有默认值，但是带默认值的参数需要放后面
    {
        next = ptr;
        data = d;
    }

    edgeNode(const int &d, const E &w, edgeNode<E> *ptr = NULL) //构造函数，用于构造其他结点（带权图）
    //函数参数表中的形参允许有默认值，但是带默认值的参数需要放后面
    {
        next = ptr;
        data = d;
        weight = w;
    }

    int getData() { return data; }  //取得结点的序号（顶点集）
    E getWeight() { return weight; }  //取得边集中对应边的权值
    void SetLink(edgeNode<E> *link) { next = link; }  //修改结点的next域
    void SetData(int value) { data = value; }   //修改结点的序号（顶点集）
    void SetWeight(E value) { weight = value; }   //修改边集中对应边的权值
};

template<class V, class E>
struct Kruskal_struct {
    V start;
    V end;
    E weight;
    int index;

    Kruskal_struct() {}

    Kruskal_struct(V start, V end, E weight, int index = 0) {
        this->start = start;
        this->end = end;
        this->weight = weight;
        this->index = index;
    }
};

template<class V, class E>
bool operator<(Kruskal_struct<V, E> a1, Kruskal_struct<V, E> a2) {
    if (a2.weight == a1.weight) {
        return a1.index < a2.index;
    } else {
        return a1.weight < a2.weight;
    }
}

template<class V, class E>
class adjlist_graph {
private:
    int Vers;//顶点数
    int Edges;//边数
    vector<edgeNode<E> *> verList;//一个顶点映射到一条边组
    vector<V> ver;//顶点集,定位序号,映射map,也可以直接搞Map的
    string GraphKind;//类型标志
    void dfs_graph(int a, vector<V> &res, vector<int> &vis) {
        if (vis[a] == 0) {
            res.push_back(ver[a]);
            vis[a] = 1;
        }
        edgeNode<E> *p = verList[a]->next;
        while (p) {
            dfs(p->data, res, vis);
            p = p->next;
        }

    }

    void find_m_path(vector<int> vis, vector<V> paths, vector<vector<V>> &result, int n, int m, int s) {
        if (m == s) {
            paths.push_back(ver[n]);
            result.push_back(paths);
            return;
        } else {
            if (vis[n] == 0) {
                paths.push_back(ver[n]);
                vis[n] = 1;
            }
            edgeNode<E> *p = verList[n]->next;
            while (p) {
                find_m_path(vis, paths, result, p->data, m, ++s);
                s--;
                p = p->next;
            }
        }

    }

    V find_set(V x) {
        if (x != fa[x]) {
            fa[x] = find_set(fa[x]);
        }
        return fa[x];
    }

    void Union(V u, V v) {
        if (fa[u] == u) {
            fa[u] = fa[v];
            return;
        } else if (fa[u] == fa[v]) {
            return;
        } else {
            Union(fa[u], v);
            fa[u] = fa[v];//父节点统一;
            return;
        }

    }

public:
    vector<Kruskal_struct<V, E>> kru;
    map<V, V> fa;

    adjlist_graph<V, E>();

    adjlist_graph<V, E>(int v, int e, vector<edgeNode<E> *> &vl, vector<V> &ver, string &gk) {
        this->Vers = v;
        this->Edges = e;
        this->verList = vl;
        this->ver = ver;
        this->GraphKind = gk;
    }

    void printList() {
        for (int i = 0; i < ver.size(); i++) {
            cout << ver[i];
            edgeNode<E> *p = verList[i]->next;
            while (p) {
                cout << "->" << p->data << "(" << p->weight << ")";
                p = p->next;
            }
            cout << endl;
        }
        cout << endl;
    }

    void find_path(int start, int m) {
        vector<int> vis(ver.size(), 0);
        vector<V> paths;
        vector<vector<V>> results;
        find_m_path(vis, paths, results, start, m, 0);
        if (results.empty()) { cout << "0" << endl; }
        else {
            for (int i = 0; i < results.size(); i++) {
                for (int j = 0; j < results[i].size(); j++) {
                    if (j == 0) { cout << results[i][j]; }
                    else {
                        cout << "->" << results[i][j];
                    }
                }
                cout << endl;

            }
            cout << results.size();
        }


    }

    bool delete_edge(int u, int v) {
        if (u >= 0 && v >= 0 && u < verList.size() && v < verList.size()) {
            edgeNode<E> *p = verList[u];
            while (p) {
                if (p->next && p->next->data == v) {
                    edgeNode<E> *g = p->next;
                    p->next = p->next->next;
                    Edges--;
                    delete g;//删除边
                    break;
                }
                p = p->next;
            }
            if (!p) { return false; }
            if (GraphKind == "UDG" || GraphKind == "UDN") {
                edgeNode<E> *f = verList[v];
                while (f) {
                    if (f->next && f->next->data == u) {
                        edgeNode<E> *j = f->next;
                        f->next = f->next->next;
                        delete j;//删除边
                        break;
                    }
                    f = f->next;
                }
                if (!f) { return false; }
            }

            return true;
        }
        return false;
    }

    void printList_no_weight() {
        for (int i = 0; i < ver.size(); i++) {
            cout << ver[i];
            edgeNode<E> *p = verList[i]->next;
            while (p) {
                cout << "->" << p->data;
                p = p->next;
            }
//            cout << "->nullptr" << endl;
            cout << endl;
        }
        cout << endl;
    }

    pair<vector<Kruskal_struct<V, E>>, E> Kruskal()//第一形参保存过程,第二形参保存求和
    {
        E sum = 0;
        vector<Kruskal_struct<V, E>> res;
        for (int i = 0; i < kru.size(); i++) {
            if (find_set(kru[i].start) != find_set(kru[i].end)) {
                res.push_back({kru[i].start, kru[i].end, kru[i].weight});
                Union(kru[i].start, kru[i].end);
                sum += kru[i].weight;
            }
        }
        return make_pair(res, sum);
    }

    void print_vers() {
        for (typename vector<V>::iterator it = ver.begin(); it != ver.end(); it++) {
            if (it == ver.begin()) { cout << *it; }
            else { cout << " " << *it; }
        }
        cout << endl;
    }

    adjlist_graph<V, E> operator=(const adjlist_graph<V, E> &others) {
        this->Vers = others.Vers;
        this->Edges = others.Edges;
        this->verList = others.verList;
        this->ver = others.ver;
        this->GraphKind = others.GraphKind;
        return *this;
    }

    string get_graph_type() {
        return GraphKind;
    }

    bool del_one_ver(int a) {
        if (a > 0 && a < ver.size()) {
            ver.erase(ver.begin() + a);//删除节点
            Vers--;//减去一个
            if (GraphKind == "DG") {
                edgeNode<E> *p = verList[a];
                while (p->next) {
                    Edges--;
                    p = p->next;
                }
            }//有向图的话要多减去自己拥有的边
            verList.erase(verList.begin() + a);//移出这个顶点
            for (auto it = verList.begin(); it != verList.end(); it++) {
                //修改数字
                edgeNode<E> *p = *it;
                while (p) {

                    if (p->next && p->next->data > a) { p->next->data--; }
                    if (p->next && p->next->data == a) {
                        edgeNode<E> *g = p->next;
                        p->next = p->next->next;
                        delete g;
                        Edges--;
                    }
                    p = p->next;
                }
            }
            return true;
        }
        return false;
    }

    int get_nums_of_edges() {
        return Edges;
    }

    int get_nums_of_vers() {
        return Vers;
    }

    int get_location_of_a_ver(V a) {
        for (int i = 0; i < ver.size(); i++) {
            if (ver[i] == a) {
                return i;
            }
        }
        return -1;
    }

    int get_location_of_first_ver(int a) {
        if (verList[a]->next != NULL) {
            return verList[a]->next->data;
        } else {
            return -1;
        }
    }

    int get_out_degree(int a) {
        int ans = 0;
        if (a < 0 || a >= ver.size()) { return -1; }
        edgeNode<E> *p = verList[a]->next;
        while (p) {
            ans++;
            p = p->next;
        }
        return ans;
    }

    int get_in_degree(int a) {
        int ans = 0;
        if (a < 0 || a >= ver.size()) { return -1; }
        for (int i = 0; i < verList.size(); i++) {
            edgeNode<E> *p = verList[i]->next;
            while (p) {
                if (p->data == a) {
                    ans++;
                }
                p = p->next;
            }
        }
        if (GraphKind == "UDG") { return -1; }
        return ans;
    }

    void dfs(int a) {
        vector<int> vis(ver.size(), 0);
        vector<V> res;
        dfs_graph(a, res, vis);
        for (int k = 0; k < res.size(); k++) {
            if (k == 0) {
                cout << res[k];
            } else {
                cout << "->" << res[k];
            }
        }
        cout << endl;
    }

    void bfs(int a) {
        vector<int> vis(ver.size(), 0);
        vector<V> res;
        res.push_back(ver[a]);
        vis[a] = 1;
        queue<edgeNode<E> *> nodes;
        nodes.push(verList[a]);
        while (!nodes.empty()) {
            edgeNode<E> *p = verList[nodes.front()->data];
            if (!nodes.empty()) { nodes.pop(); }

            while (p) {
                if (vis[p->data] == 0) {
                    nodes.push(p);
                    vis[p->data] = 1;
                }
                p = p->next;
            }
            if (!nodes.empty()) {
                res.push_back(ver[nodes.front()->data]);
            }
        }
        for (int i = 0; i < res.size(); i++) {
            if (i == 0) {
                cout << res[i];
            } else {
                cout << "->" << res[i];
            }
        }
    }

    bool check_vers(int u, int v) {
        if (u >= 0 && v >= 0 && u < ver.size() && v < ver.size()) {
            edgeNode<E> *p = verList[u]->next;
            while (p) {
                if (p->data == v) {
                    return true;
                }
                p = p->next;
            }

        }
        return false;
    }

    bool check_circle() {
        vector<int> has_visited;
        queue<int> que;
        vector<int> vis(ver.size(), 0);
        vector<int> degree(ver.size(), 0);
        for (int i = 0; i < ver.size(); i++) {
            int k = get_in_degree(i);
            degree[i] = k;
            if (!k) {
                que.push(i);
                has_visited.push_back(i);
                vis[i] = 1;
            }
        }
        while (!que.empty()) {
            edgeNode<E> *p = verList[que.front()]->next;
            while (p) {
                degree[p->data]--;
                if (degree[p->data] == 0 && !vis[p->data])//康康有没有被访问过
                {
                    que.push(p->data);
                    has_visited.push_back(p->data);
                    vis[p->data] = 1;
                }
                p = p->next;
            }
            que.pop();
        }
        if (has_visited.size() == ver.size()) {
            return false;
        } else {
            return true;
        }
    }

    void AOE() {
        if (this->GraphKind != "DN") {
            return;
        }
        if (this->check_circle()) {
            return;
        }
        if (Edges == 0) {
            for (int i = 0; i < ver.size(); i++) {
                cout << ver[i] << "\t" << "0" << "\t" << "0" << endl;
            }
            return;
        }
        vector<int> ve(Vers, 0);//初始化最早发生时间

        for (int i = 0; i < verList.size(); i++) {
            edgeNode<int> *p = verList[i]->next;
            while (p) {
                ve[p->data] = max(ve[p->data], ve[i] + p->weight);
                p = p->next;
            }
        }
        //
        vector<int> vl(Vers, ve[Vers - 1]);//初始化最晚发生时间
        vl[Vers - 1] = ve[Vers - 1];
        for (int i = verList.size() - 1; i >= 0; i--) {
            edgeNode<int> *p = verList[i]->next;
            while (p) {
                { vl[i] = min(vl[i], vl[p->data] - p->weight); }
                p = p->next;
            }
        }
        //活动ai开始的最早时间
        map<pair<int, int>, int> e;
        //活动ai开始的最晚发生时间
        map<pair<int, int>, int> l;
        vector<pair<int, int>> tmp;
        for (int i = 0; i < verList.size(); i++) {
            edgeNode<int> *p = verList[i]->next;
            while (p) {
                e[make_pair(i, p->data)] = ve[i];
                tmp.push_back({i, p->data});
                p = p->next;
            }
        }
        for (int i = 0; i < verList.size(); i++) {
            edgeNode<int> *p = verList[i]->next;
            while (p) {
                l[make_pair(i, p->data)] = vl[p->data] - p->weight;
                p = p->next;
            }
        }
        ///////print;
        for (int i = 0; i < vl.size(); i++) {
            cout << ver[i] << "\t" << ve[i] << "\t" << vl[i] << endl;
        }
        cout << endl;
        for (int i = 0; i < e.size(); i++) {
            cout << "<" << ver[tmp[i].first] << "," << ver[tmp[i].second] << ">" << "\t" << e[tmp[i]] << "\t"
                 << l[tmp[i]] << endl;
        }
        cout << endl;
        int t = 0;
        for (int i = 0; i < e.size(); i++) {
            if (e[tmp[i]] == l[tmp[i]]) {
                if (t == 0) {
                    cout << "(" << ver[tmp[i].first] << "," << ver[tmp[i].second] << ")";
                    t++;
                } else {
                    cout << "->(" << ver[tmp[i].first] << "," << ver[tmp[i].second] << ")";
                }
            }
        }
    }
};

template<class E>
void insert_node(int data, E weight, edgeNode<E> *root) {
    edgeNode<E> *p = root;
    p->next = new edgeNode<E>(data, weight, p->next);
}

template<class E>
void insert_node(int data, edgeNode<E> *root) {
    edgeNode<E> *p = root;
    p->next = new edgeNode<E>(data, p->next);
}

template<class E>
vector<edgeNode<E> *>
make_weight_adjlist_graph_map(string &kd, vector<pair<int, int>> &edges, int nums_of_vers, int num_of_edges,
                              vector<E> &weight) {
    vector<edgeNode<E> *> res(nums_of_vers);
    for (int i = 0; i < nums_of_vers; i++) {
        res[i] = new edgeNode<E>();
    }

    for (int j = 0; j < num_of_edges; j++) {
        insert_node(edges[j].second, weight[j], res[edges[j].first]);
        if (kd == "UDN") {
            insert_node(edges[j].first, weight[j], res[edges[j].second]);
        }
    }
    return res;
}

template<class E>
vector<edgeNode<E> *>
make_none_weight_adjlist_graph_map(string &kd, vector<pair<int, int>> &edges, int nums_of_vers, int nums_of_edges) {
    vector<edgeNode<E> *> res(nums_of_vers);
    for (int i = 0; i < nums_of_vers; i++) {
        res[i] = new edgeNode<E>(i, NULL);
    }
    for (int j = 0; j < nums_of_edges; j++) {
        insert_node(edges[j].second, res[edges[j].first]);
        if (kd == "UDG") {
            insert_node(edges[j].first, res[edges[j].second]);
        }
    }
    return res;
}

template<class V, class E>
adjlist_graph<V, E> make_weight_adjlist_graph() {
    string KD;
    cin >> KD;
    int Vers;
    cin >> Vers;
    vector<V> v;
    for (int i = 0; i < Vers; i++) {
        V tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    int Edges;
    cin >> Edges;
    vector<pair<int, int>> e;
    for (int i = 0; i < Edges; i++) {
        int a, b;
        cin >> a >> b;
        e.push_back(make_pair(a, b));
    }
    vector<E> weight;
    for (int i = 0; i < Edges; i++) {
        E tmp;
        cin >> tmp;
        weight.push_back(tmp);
    }
    vector<edgeNode<E> *> res = make_weight_adjlist_graph_map(KD, e, Vers, Edges, weight);
    adjlist_graph<V, E> res1(Vers, Edges, res, v, KD);
    for (int i = 0; i < Edges; i++) {
        res1.kru.push_back({v[e[i].first], v[e[i].second], weight[i], i});
        res1.fa[v[e[i].first]] = v[e[i].first];
        res1.fa[v[e[i].second]] = v[e[i].second];//开始自己是自己的祖先
    }
    return res1;
}

template<class V, class E>
adjlist_graph<V, E> make_none_weight_adjlist_graph() {
    string kd;
    cin >> kd;
    int nums_of_vers;
    cin >> nums_of_vers;
    vector<V> v;
    for (int i = 0; i < nums_of_vers; i++) {
        V tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    int nums_of_edge;
    cin >> nums_of_edge;
    vector<pair<int, int>> e;
    for (int i = 0; i < nums_of_edge; i++) {
        int a, b;
        cin >> a >> b;
        e.push_back(make_pair(a, b));
    }
    vector<edgeNode<E> *> res = make_none_weight_adjlist_graph_map<E>(kd, e, nums_of_vers, nums_of_edge);
    adjlist_graph<V, E> res1(nums_of_vers, nums_of_edge, res, v, kd);
    return res1;
}

template<class V>
void solve_team_6() {
    adjlist_graph<V, int> res1 = make_weight_adjlist_graph<V, int>();
    res1.print_vers();
    res1.printList();

    res1.AOE();

}

int main() {
    solve_team_6<string>();
    return 0;
}