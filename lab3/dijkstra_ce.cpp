#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <chrono>
using namespace std;
#define ll long long

const int N = 1e6 + 10;
struct Edge {
    ll v, w;
    Edge(ll v, ll w) : v(v), w(w) {}
};

vector<Edge> e[N];
struct Node {
    ll dis, pos;
    Node(ll dis, ll pos) : dis(dis), pos(pos) {}
    bool operator>(const Node &a) const { return dis > a.dis; }
};

priority_queue<Node, vector<Node>, greater<Node>> q;
bool book[N];
ll n, m, st; // 顶点数，边数，起始节点
ll dis[N];   // 最短距离
ll pre[N];   // 前序顶点

// 生成测试数据
void generate_test_data(const string &filename, ll num_nodes, ll num_edges, ll max_weight) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    out << num_nodes << " " << num_edges << " " << 1 << "\n"; // 顶点数，边数，起始节点固定为 1
    for (ll i = 0; i < num_edges; i++) {
        ll u = rand() % num_nodes + 1; // 随机起点
        ll v = rand() % num_nodes + 1; // 随机终点
        while (u == v) v = rand() % num_nodes + 1; // 避免自环
        ll w = rand() % max_weight + 1; // 随机权重
        out << u << " " << v << " " << w << "\n";
    }

    out.close();
    cout << "Generated data for " << filename << " with " << num_nodes << " nodes and " << num_edges << " edges.\n";
}

// Dijkstra 算法
void dijkstra() {
    fill(dis, dis + n + 1, LLONG_MAX); // 初始化为无穷大
    fill(book, book + n + 1, false);  // 重置访问标记
    dis[st] = 0;
    q.push(Node(0, st));
    while (!q.empty()) {
        Node t = q.top();
        q.pop();
        ll d = t.dis, p = t.pos;
        if (book[p]) continue;
        book[p] = true;
        for (auto edge : e[p]) {
            ll v = edge.v, w = edge.w;
            if (dis[p] + w < dis[v]) {
                dis[v] = dis[p] + w;
                pre[v] = p;
                q.push(Node(dis[v], v));
            }
        }
    }
}

// 测试数据
void test_data(const string &filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // 加载数据
    in >> n >> m >> st;
    for (ll i = 1; i <= n; i++) e[i].clear(); // 清空邻接表
    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        in >> u >> v >> w;
        e[u].push_back(Edge(v, w));
    }
    in.close();

    // 测试算法并计时
    auto start_time = chrono::high_resolution_clock::now();
    dijkstra();
    auto end_time = chrono::high_resolution_clock::now();

    // 输出结果
    cout << "Test for " << filename << ":\n";
    cout << "Actual edges: " << m << "\n";
    cout << "Time taken: "
         << chrono::duration<double>(end_time - start_time).count()
         << " seconds\n\n";
}

int main() {
    srand(time(0)); // 设置随机种子

    // 生成测试数据
    generate_test_data("dijkstra_small.txt", 10, 20, 100);       // 小规模
    generate_test_data("dijkstra_medium.txt", 1000, 5000, 1000); // 中规模
    generate_test_data("dijkstra_large.txt", 1000000, 5000000, 10000); // 大规模

    cout << "\nData generation complete.\n\n";

    // 测试小规模数据
    test_data("dijkstra_small.txt");

    // 测试中规模数据
    test_data("dijkstra_medium.txt");

    // 测试大规模数据
    test_data("dijkstra_large.txt");

    return 0;
}
