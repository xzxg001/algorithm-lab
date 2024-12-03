#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
#include <ctime>

using namespace std;
#define ll long long
const int N = 1e4 + 10;

struct Object {
    ll w;    // 重量
    ll v;    // 价值
    int pos; // 编号
    double p; // 单位价值
};

// 数据排序规则（按单位价值降序）
bool cmp(const Object &a, const Object &b) {
    return a.p > b.p;
}

Object oj[N];
ll n, c;          // 物品数量和背包容量
ll bestv = 0;      // 当前最优价值
bitset<N> bs;      // 记录选择的物品

// 计算上界
int bound(int i, int cw, int cv) {
    ll cleft = c - cw;
    ll nv = cv;
    int j = i;
    for (; j <= n && oj[j].w <= cleft; j++) {
        cleft -= oj[j].w;
        nv += oj[j].v;
    }
    if (j <= n) nv += oj[j].v * (double)cleft / oj[j].w;
    return nv;
}

// 定义节点结构
struct Node {
    ll cw, cv;        // 当前重量和价值
    ll level;         // 当前层数
    bitset<N> s;      // 当前选择状态
    ll up;            // 当前节点的上界

    Node(int cw, int cv, int level, bitset<N> s, int up)
        : cw(cw), cv(cv), level(level), s(s), up(up) {}
};

// 优先队列比较规则
struct NodeCmp {
    bool operator()(const Node &a, const Node &b) const {
        return a.up < b.up; // 按上界从大到小排列
    }
};

// 分支限界法
priority_queue<Node, vector<Node>, NodeCmp> q;
void knap() {
    bitset<N> s;
    int init_up = bound(1, 0, 0);
    q.push(Node(0, 0, 1, s, init_up));
    while (!q.empty()) {
        Node no = q.top();
        q.pop();
        ll cw = no.cw;
        ll cv = no.cv;
        ll level = no.level;
        if (level > n) {
            if (cv > bestv) {
                bestv = cv;
                bs = no.s;
                break;
            }
            continue;
        }
        // 左分支
        if (cw + oj[level].w <= c) {
            auto left_s = no.s;
            left_s[level] = true;
            int left_up = bound(level + 1, cw + oj[level].w, cv + oj[level].v);
            q.push(Node(cw + oj[level].w, cv + oj[level].v, level + 1, left_s, left_up));
        }
        // 右分支
        if (bound(level + 1, cw, cv) > bestv) {
            auto right_s = no.s;
            right_s[level] = false;
            int right_up = bound(level + 1, cw, cv);
            q.push(Node(cw, cv, level + 1, right_s, right_up));
        }
    }
}

// 生成测试数据
void generate_test_data(const string &filename, ll num_items, ll max_weight, ll max_value, ll capacity) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    out << capacity << " " << num_items << "\n"; // 背包容量和物品数量
    for (ll i = 0; i < num_items; i++) {
        ll weight = rand() % max_weight + 1;   // 随机重量
        ll value = rand() % max_value + 1;     // 随机价值
        out << weight << " " << value << "\n";
    }

    out.close();
    cout << "Generated data for " << filename << " with " << num_items << " items.\n";
}

// 数据测试函数
void test_data(const string &filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // 加载数据
    in >> c >> n;
    for (ll i = 1; i <= n; i++) {
        in >> oj[i].w >> oj[i].v;
        oj[i].p = (double)oj[i].v / oj[i].w;
        oj[i].pos = i;
    }
    in.close();

    // 排序物品
    sort(oj + 1, oj + n + 1, cmp);

    // 测试分支限界算法
    clock_t start_time = clock();
    knap();
    clock_t end_time = clock();

    // 输出结果
    cout << "Test for " << filename << ":\n";
    cout << "Maximum value: " << bestv << "\n";
    cout << "Time taken: " << double(end_time - start_time) / CLOCKS_PER_SEC << " seconds\n\n";
}

int main() {
    srand(time(0)); // 设置随机种子

    // 生成测试数据
    generate_test_data("01knap_livenode_small.txt", 10, 100, 200, 500);      // 小规模
    generate_test_data("01knap_livenode_medium.txt", 10000, 500, 1000, 10000); // 中规模
    generate_test_data("01knap_livenode_large.txt", 1000000, 1000, 2000, 1000000); // 大规模
    cout << "\nData generation complete.\n\n";

    // 测试小规模数据
    test_data("01knap_livenode_small.txt");

    // 测试中规模数据
    test_data("01knap_livenode_medium.txt");

    // 测试大规模数据
    test_data("01knap_livenode_large.txt");

    return 0;
}
