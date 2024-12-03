#include <iostream>
#include <queue>
#include <algorithm>
#include <bitset>
#include <fstream> // 文件读取
#include <chrono>  // 测量时间
using namespace std;
#define ll long long
const int N = 1e6 + 10;

struct object {
    ll w;
    ll v;
    int pos;
    double p;
};
bool cmp(const object &a, const object &b) {
    return a.p > b.p;
}
object oj[N];
ll n;
ll c;
ll bestv = 0;
//bitset<N> bs;

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

struct node {
    ll cw;
    ll cv;
    ll level;
    bitset<N> s;
    ll up;
    node(int cw, int cv, int level,  int up) {
        this->cw = cw;
        this->cv = cv;
        this->level = level;
//        this->s = s;
        this->up = up;
    }
};

struct nodecmp {
    bool operator()(const node &a, const node &b) const {
        return a.up < b.up;
    }
};

priority_queue<node, vector<node>, nodecmp> q;

void knap() {
    bitset<N> s;
    int init_up = bound(1, 0, 0);
    q.push(node(0, 0, 1,  init_up));
    while (!q.empty()) {
        node no = q.top();
        q.pop();
        ll cw = no.cw;
        ll cv = no.cv;
        ll level = no.level;
        if (level > n) {
            if (cv > bestv) {
                bestv = cv;
//                bs = no.s;
                break;
            }
            continue;
        }
        if (cw + oj[level].w <= c) {
//            auto left_s = no.s;
//            left_s[level] = true;
            int left_up = bound(level + 1, cw + oj[level].w, cv + oj[level].v);
            node left_node(cw + oj[level].w, cv + oj[level].v, level + 1,  left_up);
            q.push(left_node);
        }
        if (bound(level + 1, cw, cv) > bestv) {
//            auto right_s = no.s;
//            right_s[level] = false;
            int right_up = bound(level + 1, cw, cv);
            node right_node(cw, cv, level + 1, right_up);
            q.push(right_node);
        }
    }
}

int main() {
    ifstream infile("knapsack_data.txt"); // 打开文件
    if (!infile) {
        cerr << "Error: Unable to open file data.txt" << endl;
        return 1;
    }

    infile >> c >> n;
    int w, v;
    for (int i = 1; i <= n; i++) {
        infile >> w >> v;
        oj[i].w = w;
        oj[i].v = v;
        oj[i].pos = i;
        oj[i].p = (double)v / (double)w;
    }
    infile.close(); // 关闭文件

    sort(oj + 1, oj + n + 1, cmp);

    auto start = chrono::high_resolution_clock::now(); // 开始计时
    knap();
    auto end = chrono::high_resolution_clock::now(); // 结束计时

    chrono::duration<double> elapsed = end - start; // 计算时间
    cout<<"c:"<<c<<endl;
    cout<<"n:"<<n<<endl;
    cout << "Maximum value: " << bestv << endl;
    cout << "Elapsed time: " << elapsed.count() << " seconds" << endl;

    // 可选：打印选择的物品
    // for (int i = 1; i <= n; i++) {
    //     if (bs[i]) cout << oj[i].pos << " ";
    // }
    return 0;
}
