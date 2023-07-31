#include <bits/stdc++.h>

using namespace std;

////////////////////////////以下全是邻接矩阵//////////////////////////
template<class E>
vector<vector<E>>
make_weight_graph(int n, E noedgeFlag, int num_of_edge, vector<pair<int, int>> &mp, vector<E> &weight, string &kd) {
    vector<vector<E>> res(n, vector<E>(n, noedgeFlag));
    for (int i = 0; i < mp.size(); i++) {
        res[mp[i].first][mp[i].second] = weight[i];
        if (kd == "UDN") {
            res[mp[i].second][mp[i].first] = weight[i];
        }
    }
    return res;
}

template<class E>
vector<vector<E>>
make_none_weight_graph(int nums_of_ver, int nums_of_edge, E noEdgeFlag, E EdgeFlag, vector<pair<int, int>> &mp,
                       string KD) {
    vector<vector<E>> res(nums_of_ver, vector<E>(nums_of_ver, noEdgeFlag));
    for (int i = 0; i < mp.size(); i++) {
        res[mp[i].first][mp[i].second] = EdgeFlag;
        if (KD == "UDG") {
            res[mp[i].second][mp[i].first] = EdgeFlag;
        }
    }
    return res;
}
template<class V>
struct prim_struct
{
    V adj;
    V start;
    int weight;
    prim_struct(){}
    prim_struct(V adj,V start,int weight)
    {
        this->adj=adj;
        this->start=start;
        this->weight=weight;
    }
};
template<class V>
bool operator <(prim_struct<V>a1,prim_struct<V>a2)
{
    return a1.start<a2.start;
}

template<class V, class E>
class adjmartix_graph {
private:
    int Vers;//顶点数
    int Edges;//边数
    vector<vector<E>> edge;//邻接矩阵 对于无权图用1/0表示相邻否,对于戴权图,则为权值
    vector<V> ver;//存放节点值
    vector<E> weight;
    E noEdge;//邻接矩阵中无穷的值
    string GraphKind;//图的种类标志
    void dfs(int i, vector<int> &vis, vector<V> &res) {
        if (vis[i] == 0) {
            res.push_back(ver[i]);
            vis[i] = 1;
        } else {
            return;
        }
        for (int j = 0; j < edge.size(); j++) {
            if (edge[i][j] != noEdge) {
                dfs(j, vis, res);
            }
        }
    }

public:
    adjmartix_graph() {};

    adjmartix_graph(const string &kd, int vSize, vector<V> d, E noEdgeFlag)//只有节点没有边的图,图的类型,节点数,节点值,和邻接矩阵中用来表示有没有边的标记
    {
        Vers = vSize;
        ver = d;
        GraphKind = kd;
        edge.resize(vSize, vector<E>(vSize, noEdgeFlag));
        noEdge = noEdgeFlag;
        Edges = 0;
    }

    adjmartix_graph(const string &kd, int vSize, int eSize, vector<V> d, vector<vector<E>> e, E noedge)//无权图
    {
        GraphKind = kd;
        Vers = vSize;
        Edges = eSize;
        ver = d;
        edge = e;
        this->noEdge = noedge;
    }

    adjmartix_graph(const string &kd, int vSize, int eSize, E noEdgeFlag, vector<V> d, vector<vector<E>> edge,
                    vector<E> w) {
        GraphKind = kd;
        Vers = vSize;
        Edges = eSize;
        ver = d;
        this->edge = edge;
        this->weight = w;
        this->noEdge = noEdgeFlag;
    }

    adjmartix_graph<V, E> operator=(const adjmartix_graph<V, E> &source) {

        Edges = source.Edges;
        ver = source.ver;
        GraphKind = source.GraphKind;
        edge = source.edge;
        weight = source.weight;
        Vers = source.Vers;
        noEdge = source.noEdge;
        return *this;
    }
    void prim(int u) {
        //从u的第一个有边的点开始:
        if(this->GraphKind!="UDN"){return;}
        int k;
        if(Edges==0){return;}
        for (int i = 0; i < edge.size(); i++)
        {
            if(edge[u][i]!=noEdge)
            {
                k=i;
                break;
            }
        }
       map<V,pair<V,E>>res;//存放结果
        vector<int>vis(ver.size(),0);//标记数组
         vis[k]=1;
        vector<int>has_visited;
        has_visited.push_back(k);
        while(has_visited.size()<ver.size())
        {
            V min_start;//起点
            V min_adj;//终点
            int end;
            E min_weight=noEdge;
            for(int i=0;i<has_visited.size();i++)
            {
                for(int j=0;j<edge.size();j++)
                {
                    if(edge[has_visited[i]][j]<min_weight&&vis[j]==0)
                    {
                        end=j;
                        min_start=ver[has_visited[i]];
                        min_adj=ver[j];
                        min_weight=edge[has_visited[i]][j];
                    }
                }
            }
            vis[end]=1;
            if(res.count(min_start)==1)
            {
                swap(min_start,min_adj);
            }
            res[min_start]=make_pair(min_adj,min_weight);
            has_visited.push_back(end);
        }

        for(typename std::map<V,pair<V,E> >::iterator it =res.begin();it!=res.end();it++)
        {
            if(it==res.begin())
            {
                cout<<"("<<it->second.first<<","<<it->first<<","<<it->second.second<<")";
            }
            else
            {
                cout<<",("<<it->second.first<<","<<it->first<<","<<it->second.second<<")";
            }
        }
        cout<<endl;
    }
    void print_edge() {
        for (typename vector<vector<E>>::iterator it = edge.begin(); it != edge.end(); it++) {
            for (typename vector<E>::iterator it_ = it->begin(); it_ != it->end(); it_++) {
                cout << *it_ << "\t";
            }
            cout << endl;
        }

    }

    void print_vers() {
        for (typename vector<V>::iterator it = ver.begin(); it != ver.end(); it++) {
            if (it == ver.begin()) {
                cout << *it;
            } else {
                cout << " " << *it;
            }
        }
        cout << endl;
    }

    string get_graph_type() {
        return GraphKind;
    }

    int get_nums_of_edge() {
        return Edges;
    }

    bool delete_one_edge(int a, int b) {
        if (a < edge.size() && b < edge.size() && a >= 0 && b >= 0) {
            if (edge[a][b] == noEdge) {
                return false;
            } else {
                Edges--;
                edge[a][b] = noEdge;
                if (GraphKind == "UDG" || GraphKind == "UDN") {
                    edge[b][a] = noEdge;
                }
                return true;
            }
        }
    }
//   pair<int,deque<V>> dji (int a,int b)
//    {
//        if(a<0||a>=Vers)
//        {
//           exit(0);
//        }
//        int start=a;
//        vector<int>s;
//        s.push_back(a);
//        vector<int>u;
//        vector<int>vis(ver.size(),0);
//        vis[start]=1;
//        for(int i=0;i<ver.size();i++)
//        {
//            if(i!=a)
//            {
//                u.push_back(i);
//            }
//        }
//        vector<int>dist=edge[a];//初始化
//        std::vector<int>::iterator smallest ;
//
//        vector<int>path(ver.size(),-1);
//
//        for(int i=0;i<ver.size();i++)
//        {
//            if(dist[i]!=noEdge){path[i]=start;}
//        }
//        int Min_=INT32_MAX;
//        for(int i=0;i<dist.size();i++)
//        {
//            if(vis[i]!=1&&dist[i]!=noEdge&&dist[i]<Min_)
//            {
//                smallest=dist.begin();
//                smallest+=i;
//                Min_=dist[i];
//            }
//        }
//        while(!u.empty())
//        {
//            //先把最小的放入s;
//            int pos=distance(dist.begin(),smallest);
//            s.push_back(pos);vis[pos]=1;
//            int pre=pos;
//            for(int i=0;i<u.size();i++)
//            {
//                if(u[i]==pos)
//                {
//                    u.erase(u.begin()+i);
//                    break;
//                }
//            }
//            for(int i=0;i<edge[pos].size();i++)
//            {
//                if(edge[pre][i]!=noEdge&&vis[i]!=1)
//                {
//                    int w=dist[pre]+edge[pre][i];
//                    if(w<dist[i]||dist[i]==noEdge)
//                    {
//                        dist[i]=w;
//                        path[i]=pre;
//                    }
//                }
//            }
//            int Min=INT32_MAX;
//            for(int i=0;i<dist.size();i++)
//            {
//                if(vis[i]!=1&&dist[i]!=noEdge&&dist[i]<Min)
//                {
//                    smallest=dist.begin();
//                    smallest+=i;
//                    Min=dist[i];
//                }
//            }
//        }
//        deque<V>res;
//        int p=b;
//        while(p!=a)
//        {
//            res.push_front(ver[p]);
//            p=path[p];
//        }
//        pair<int,deque<V>>res_=make_pair(dist[b],res);
//        return res_;
//    }
//    map<V,pair<int,int>>get_all_vers_in_and_out_degree()
//    {
//        //入度
//        map<V,pair<int,int>>res;
//        for(int p=0;p<ver.size();p++) {
//            int cnt=0;
//            for (int i = 0; i < edge.size(); i++) {
//                if(edge[i][p]!=noEdge)
//                {
//                    cnt++;
//                }
//            }
//            res[ver[p]].first=cnt;
//        }
//        //出度
//        for(int p=0;p<ver.size();p++) {
//            int cnt=0;
//            for (int i = 0; i < edge.size(); i++) {
//                if(edge[p][i]!=noEdge)
//                {
//                    cnt++;
//                }
//            }
//            res[ver[p]].second=cnt;
//        }
//        return res;
//    }
    void dfs_graph(int i) {
        vector<int> vis(Vers, 0);
        vector<V> res;
        dfs(i, vis, res);

        for (int k = 0; k < res.size(); k++) {
            if (k == 0) {
                cout << res[k];
            } else {
                cout << "->" << res[k];
            }
        }
    }

    void bfs_graph(int i) {
        vector<V> res;
        vector<int> vis(Vers, 0);
        list<int> que;
        que.push_back(i);
        while (!que.empty()) {
            i = que.front();
            if (vis[i] != 1) {
                res.push_back(ver[i]);
                vis[i] = 1;
            }
            que.pop_front();
            //将从顶点i可以走道的顶点加入队列
            for (int j = 0; j < edge.size(); j++) {
                if (edge[i][j] != noEdge && vis[j] != 1) {
                    que.push_back(j);
                }
            }
        }
        for (int k = 0; k < res.size(); k++) {
            if (k == 0) {
                cout << res[k];
            } else {
                cout << "->" << res[k];
            }
        }
    }

    int get_location_of_ver(V &c) {
        for (int i = 0; i < ver.size(); i++) {
            if (ver[i] == c) {
                return i;
            }
        }
        return -1;
    }

    void insert_one_ver(V c) {
        ver.push_back(c);
        for (int i = 0; i < edge.size(); i++) {
            edge[i].push_back(noEdge);
        }
        Vers++;
        edge.push_back(vector<E>(Vers, noEdge));
    }

    bool check_route(int a, int b) {
        if (a >= 0 && b >= 0 && a < edge.size() && b < edge.size()) {
            if (edge[a][b] != noEdge) {
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    int get_next_ver(int a, int b) {
        for (int j = b + 1; j < edge.size(); j++) {
            if (edge[a][j] != noEdge) {
                return j;
            }
        }
        return -1;
    }

    int get_first_ver(int a) {
        for (int j = 0; j < edge.size(); j++) {
            if (edge[a][j] != noEdge) {
                return j;
            }
        }
        return -1;
    }
};

template<class V, class E>
adjmartix_graph<V, E> make_adjmartix_graph() {
    string KD;
    cin >> KD;

    int n;
    cin >> n;
    vector<V> ver;
    for (int i = 0; i < n; i++) {
        V tmp;
        cin >> tmp;
        ver.push_back(tmp);
    }
    E noFlagtype;
    cin >> noFlagtype;
    int num_of_edge;
    cin >> num_of_edge;

    vector<pair<int, int>> mp;
    for (int i = 0; i < num_of_edge; i++) {
        int a, b;
        cin >> a >> b;
        pair<int, int> tmp = make_pair(a, b);
        mp.push_back(tmp);
    }
    vector<E> weight;
    for (int i = 0; i < num_of_edge; i++) {
        E tmp;
        cin >> tmp;
        weight.push_back(tmp);
    }
    vector<vector<E>> matrix = make_weight_graph(n, noFlagtype, num_of_edge, mp, weight, KD);
    adjmartix_graph<V, E> res(KD, n, num_of_edge, noFlagtype, ver, matrix, weight);
//    cout << KD << endl;
//
//    for (int i = 0; i < n; i++) {
//        if (i == 0) {
//            cout << ver[i];
//        } else {
//            cout << " " << ver[i];
//        }
//    }
//    cout << endl;
//    cout << num_of_edge << endl;
    return res;
}

template<class V, class E>
adjmartix_graph<V, E> make_none_weight_graph(E noEdgeFlag, E EdgeFlag) {
    string KD;
    cin >> KD;
    int nums_of_ver;
    cin >> nums_of_ver;
    vector<V> vers;
    for (int i = 0; i < nums_of_ver; i++) {
        V tmp;
        cin >> tmp;
        vers.push_back(tmp);
    }
    int num_of_edge;
    cin >> num_of_edge;
    vector<pair<int, int>> mp;
    for (int i = 0; i < num_of_edge; i++) {
        int a, b;
        cin >> a >> b;
        pair<int, int> tmp = make_pair(a, b);
        mp.push_back(tmp);
    }
    vector<vector<E>> martix = make_none_weight_graph(nums_of_ver, nums_of_ver, noEdgeFlag, EdgeFlag, mp, KD);
    adjmartix_graph<V, E> res(KD, nums_of_ver, num_of_edge, vers, martix, noEdgeFlag);
    return res;
}

void solve_oj_1() {
    adjmartix_graph<int, int> a = make_adjmartix_graph<int, int>();
    cout << endl;
    a.print_edge();
}

template<class V>
void solve_oj_2() {
    adjmartix_graph<V, int> res1 = make_none_weight_graph<V, int>(0, 1);
    res1.print_vers();
    cout << res1.get_nums_of_edge() << endl;
    res1.print_edge();
    int a, b;
    cin >> a >> b;

    if (res1.delete_one_edge(a, b)) {
        cout << "true" << endl;
        cout << res1.get_nums_of_edge() << endl;
        res1.print_edge();
    } else {
        cout << "false" << endl;
        cout << res1.get_nums_of_edge() << endl;
        res1.print_edge();
    }
}

template<class V>
void solve_oj_3() {
    adjmartix_graph<V, int> res1 = make_none_weight_graph<V, int>(0, 1);
    V C;
    cin >> C;
    res1.print_vers();
    cout << res1.get_location_of_ver(C);
}

template<class V, class E>
void solve_oj_4() {
    adjmartix_graph<V, E> res1 = make_adjmartix_graph<V, E>();
    int a, b;
    res1.print_edge();

    cin >> a >> b;
    if (res1.delete_one_edge(a, b)) {
        cout << "true" << endl;
        cout << res1.get_nums_of_edge() << endl;
        res1.print_edge();
    } else {
        cout << "false" << endl;
        cout << res1.get_nums_of_edge() << endl;
        res1.print_edge();
    }
}

template<class V>
void solve_oj_5() {
    adjmartix_graph<V, int> res1 = make_none_weight_graph<V, int>(0, 1);
    V c;
    cin >> c;
    cout << res1.get_graph_type() << endl;
    res1.print_vers();

    cout << endl;
    res1.print_edge();

    res1.insert_one_ver(c);
    res1.print_vers();
    cout << endl;
    res1.print_edge();
    cout << endl;
}

template<class V>
void solve_oj_6() {
    adjmartix_graph<V, int> res1 = make_none_weight_graph<V, int>(0, 1);
    res1.print_vers();
    cout << endl;
    res1.print_edge();
    int i;
    cin >> i;
    res1.dfs_graph(i);
}

template<class V>
void solve_oj_7() {
    adjmartix_graph<V, int> res1 = make_none_weight_graph<V, int>(0, 1);
    res1.print_vers();
    cout << endl;
    res1.print_edge();
    int a, b;
    cin >> a >> b;

    if (res1.check_route(a, b)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
}

template<class V>
void solve_oj_8() {
    adjmartix_graph<V, int> res1 = make_none_weight_graph<V, int>(0, 1);
    res1.print_vers();
    cout << endl;
    res1.print_edge();
    int i;
    cin >> i;
    res1.bfs_graph(i);
}

template<class V>
void solve_oj_9() {
    adjmartix_graph<V, int> res1 = make_none_weight_graph<V, int>(0, 1);
    res1.print_vers();
    cout << endl;
    res1.print_edge();
    int a, b;
    cin >> a >> b;
    cout << res1.get_next_ver(a, b);
}

template<class V>
void solve_oj_10() {
    adjmartix_graph<V, int> res1 = make_none_weight_graph<V, int>(0, 1);
    res1.print_vers();
    cout << endl;
    res1.print_edge();
    int a;
    cin >> a;
    cout << res1.get_first_ver(a) << endl;
}
template <class V>
void solve_teams_3()
{
    adjmartix_graph<V,double>res1=make_adjmartix_graph<V,double>();
    int u;cin>>u;
    cout<<res1.get_graph_type()<<endl;
    res1.print_vers();
    cout<<endl;
    res1.print_edge();

    res1.prim(u);
}
////////////////////////////以上全是邻接矩阵//////////////////////////
///////////////////////////以下全是邻接表////////////////////////////
template<class E>
struct edgeNode {
    int data;//就是连到那个点的序号
    E weight;
    edgeNode<E> *next;

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
   void find_m_path(vector<int>vis,vector<V>paths,vector<vector<V>>&result,int n,int m,int s)
    {
        if(m==s){paths.push_back(ver[n]);result.push_back(paths);return;}
        else
        {
            if(vis[n]==0)
            {
                paths.push_back(ver[n]);
                vis[n]=1;
            }
            edgeNode<E>*p=verList[n]->next;
            while(p)
            {
                find_m_path(vis,paths,result,p->data,m,++s);
                s--;
                p=p->next;
            }
        }

    }
public:
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
            cout << "->nullptr" << endl;
        }
        cout << endl;
    }
void find_path(int start,int m)
    {
        vector<int>vis(ver.size(),0);
        vector<V>paths;
        vector<vector<V>>results;
       find_m_path(vis,paths,results,start,m,0);
        if(results.empty()){cout<<"0"<<endl;}
        else{for(int i=0;i<results.size();i++)
        {
            for(int j=0;j<results[i].size();j++)
            {
                if(j==0){cout<<results[i][j];}
                else
                {
                    cout<<"->"<<results[i][j];
                }
            }
            cout<<endl;

        }
        cout<<results.size();}


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
cout<<endl;
        }
        cout << endl;
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
        res[i] = new edgeNode<E>(i, NULL);
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
void solve_oj_mid_1() {
    adjlist_graph<V, int> res1 = make_weight_adjlist_graph<V, int>();
    cout << res1.get_graph_type() << endl;
    res1.print_vers();
    res1.printList();
}

template<class V>
void solve_oj_mid_2() {
    adjlist_graph<V, int> res1 = make_none_weight_adjlist_graph<V, int>();
    int a;
    cin >> a;
    cout << res1.get_graph_type() << endl;
    res1.print_vers();
    cout << res1.get_nums_of_vers() << endl;
    cout << res1.get_nums_of_edges() << endl;
    res1.printList_no_weight();

    res1.del_one_ver(a);
    res1.print_vers();
    cout << res1.get_nums_of_vers() << endl;
    cout << res1.get_nums_of_edges() << endl;
    res1.printList_no_weight();
}

template<class V>
void solve_oj_mid_3() {
    adjlist_graph<V, int> res1 = make_none_weight_adjlist_graph<V, int>();
    int a;
    cin >> a;
    res1.print_vers();
    res1.printList_no_weight();
    cout << res1.get_location_of_first_ver(a);
}

template<class V>
void solve_oj_mid_4() {
    adjlist_graph<V, int> res1 = make_none_weight_adjlist_graph<V, int>();
    int a;
    cin >> a;
    res1.print_vers();
    res1.printList_no_weight();
    cout << res1.get_out_degree(a);
}

template<class V>
void solve_oj_mid_5() {
    adjlist_graph<V, int> res1 = make_none_weight_adjlist_graph<V, int>();
    int a, b;
    cin >> a >> b;
    res1.print_vers();
    cout << res1.get_nums_of_edges() << endl;
    res1.printList_no_weight();

    if (res1.delete_edge(a, b)) {
        cout << "true" << endl;
        res1.print_vers();
        cout << res1.get_nums_of_edges() << endl;
        res1.printList_no_weight();
    } else {
        cout << "false" << endl;
        res1.print_vers();
        cout << res1.get_nums_of_edges() << endl;
        res1.printList_no_weight();
    }
}

template<class V>
void solve_oj_mid_6() {
    adjlist_graph<V, int> res1 = make_none_weight_adjlist_graph<V, int>();
    int a;
    cin >> a;
    res1.print_vers();
    res1.printList_no_weight();
    cout << res1.get_in_degree(a);
}

template<class V>
void solve_oj_mid_7() {
    adjlist_graph<V, int> res1 = make_none_weight_adjlist_graph<V, int>();
    cout << res1.get_graph_type() << endl;
    res1.print_vers();
    res1.printList_no_weight();
}

template<class V>
void solve_oj_mid_8() {
    adjlist_graph<V, int> res1 = make_none_weight_adjlist_graph<V, int>();
    V A;
    cin >> A;
    cout << res1.get_graph_type() << endl;
    res1.print_vers();
    res1.printList_no_weight();
    cout << res1.get_location_of_a_ver(A);
}

template<class V>
void solve_oj_mid_9() {
    adjlist_graph<V, int> res1 = make_none_weight_adjlist_graph<V, int>();
    int a;
    cin >> a;
    res1.print_vers();
    res1.printList_no_weight();
    res1.bfs(a);
}

template<class V>
void solve_oj_mid_10() {
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
    int nums_of_edge = 0;
    vector<pair<int, int>> e(0);
    vector<edgeNode<int> *> res = make_none_weight_adjlist_graph_map<int>(kd, e, nums_of_vers, nums_of_edge);
    adjlist_graph<V, int> res1(nums_of_vers, nums_of_edge, res, v, kd);
    cout << res1.get_graph_type() << endl;
    res1.print_vers();
    res1.printList_no_weight();
}

template<class V>
void solve_oj_mid_11() {
    adjlist_graph<V, int> res1 = make_none_weight_adjlist_graph<V, int>();
    int a, b;
    cin >> a >> b;
    res1.print_vers();
    res1.printList_no_weight();
    if (res1.check_vers(a, b)) {
        cout << "true";
    } else {
        cout << "false";
    }
}
template<class V>
void solve_oj_teams2()
{
    adjlist_graph<V, int> res1 = make_none_weight_adjlist_graph<V, int>();
    int a, b;
    cin >> a >> b;
    res1.print_vers();
    res1.printList_no_weight();
    res1.find_path(a,b);
}
void get_test_cases() {
    //获取OJ测试用例
    string k;
    cin >> k;
    cout << k << endl;
    int a;
    cin >> a;
    cout << a << endl;
    for (int i = 0; i < a; i++) {
        string s;
        cin >> s;
        cout << s << " ";
    }
    int b;
    cin >> b;
    cout << b << endl;
    for (int i = 0; i < b; i++) {
        int t1, t2;
        cin >> t1 >> t2;
        cout << t1 << " " << t2 << endl;
    }
    int j;
    cin >> j;
    cout << j << endl;
}
//////////////////////////////////////以上全是邻接表///////
/////////////////////////////////////以下全是LEETCODE/////
vector<vector<int>>adjmartix_init(int n, vector<pair<int,int>>&init)
{
    vector<vector<int>>res(n,vector<int>(n,0));
    for(int i=0;i<n-1;i++)
    {
        res[init[i].first][init[i].second]=1;
    }
    return res;
}
vector<vector<int>>re_adjmartix_init(int n, vector<pair<int,int>>&init)
{
    vector<vector<int>>res(n,vector<int>(n,0));
    for(int i=0;i<n-1;i++)
    {
        res[init[i].second][init[i].first]=1;
    }
    return res;
}
pair<vector<vector<int>>,vector<vector<int>>>init_leetcode_graph(int n)
{

    vector<pair<int,int>>init;
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        init.push_back(make_pair(a,b));
    }
    return make_pair(adjmartix_init(n,init), re_adjmartix_init(n,init));
};
void solve_leetcode_1()
{
    int n;
    cin>>n;
    pair<vector<vector<int>>,vector<vector<int>>>k=init_leetcode_graph(n);
    vector<vector<int>> &graph1=k.first;
    vector<vector<int>> &graph2=k.second;
    vector<bool> vis(n);
    int cnt=0;
    queue<int>q;
    q.push(0);
    //从城市0 BFS搜索其他城市
    while (!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=true;
        for(auto& v:graph1[u])
        {
            if(!vis[v])
            {
                q.push(v);
            }
        }
        for(auto&v:graph2[u])
        {
            if(!vis[v])
            {
                q.push(v);
                cnt++;
            }
        }
    }
    cout<<n-cnt;
}
//template<class V,class E>
//void discreate_math_get_degrees()
//{
//    adjmartix_graph<V, int> a = make_adjmartix_graph<V, int>();
//    a.print_edge();
//    map<V,pair<int,int>>res=a.get_all_vers_in_and_out_degree();
//    for(std::map<V,pair<int,int>>::iterator it=res.begin();it!=res.end();it++)
//    {
//        cout<<"The degree "<<it->first<<"'s indegree is: "<<it->second.first<<", outdegree is "<<it->second.second<<endl;
//    }
//}
//template<class V,class E>
//void discreate_math_dij()
//{
//    adjmartix_graph<V, int> a = make_adjmartix_graph<V, int>();
//    int c,d;
//    cin>>c>>d;
//    pair<int, deque<V>>res=a.dji(c,d);
//    cout<<"the min weight is"<<res.first<<endl;
//    cout<<"the path is:";
//    for(int i=0;i<res.second.size();i++)
//    {
//        if(i==0)
//        {
//            cout<<res.second[i];
//        }
//        else{
//            cout<<"->"<<res.second[i];
//        }
//    }
//}

int main() {
    solve_teams_3<string>();
    return 0;
}