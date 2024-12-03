#include <bits/stdc++.h>

using namespace std;
const int N = 21;
#define ll long long

int e[21][21];

struct node {
    int lcost; // 下界
    int cw; // 当前费用
    int s; // 根节点到当前路径，用于标记当前节点的位置 
    int x[21]; // 记录路径

    node(int l, int c, int s, const int x[21]) : lcost(l), cw(c), s(s) {
        for (int i = 0; i < 21; ++i) {
            this->x[i] = x[i];
        }
    }   
};

struct nodecmp {
    bool operator()(const node& a, const node& b) {
        return a.lcost > b.lcost;
    }
};

int n; // 顶点数
int minout = 0;
int bestc = INT_MAX; // 最小费用
int bc[21];

priority_queue<node, vector<node>, nodecmp> q;

int main() {
    cin >> n;
    int minarr[n];
    fill_n(minarr, n, INT_MAX); // 初始化为INT_MAX
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            e[i][j] = INT_MAX;
        }
    }
    int ac;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> ac;
            e[i][j] = ac;
            if (i != j && ac < minarr[i]) {
                minarr[i] = ac;
            }
        }
    }
    for (int i = 0; i < n; i++) { // 计算minarr数组和minout值
        if (minarr[i] == INT_MAX) {
            cout << "NoEdge" << endl;
            return 0;
        }
        minout += minarr[i];   
    }
    int t[21];
    for (int i = 0; i < n; i++) t[i] = i;
    q.push(node(minout, 0, 0, t));
    while (!q.empty()) {
        auto no = q.top();
        q.pop();
        int lcost = no.lcost; // 下界
        int cw = no.cw; // 当前费用
        int s = no.s; // 根节点到当前路径，用于标记当前节点的位置 
        int x[21];
        for (int i = 0; i < 21; ++i) {
            x[i] = no.x[i];
        }
        if (s >= n - 1) {
            bestc = cw;
            for (int i = 0; i < n; ++i) {
                bc[i] = x[i];
            }
            break;
        }
        if (s == n - 2) {
            if (e[x[n - 2]][x[n - 1]] != INT_MAX && e[x[n - 1]][0] != INT_MAX &&
                cw + e[x[n - 2]][x[n - 1]] + e[x[n - 1]][0] < bestc) {
                ll nlcost = cw + e[x[n - 2]][x[n - 1]] + e[x[n - 1]][0];
                q.push(node(nlcost, nlcost, s + 1, x));
            } else continue;
        } else {
            for (int i = s + 1; i < n; i++) {
                if (e[x[s]][x[i]] != INT_MAX) {
                    int ncw = cw + e[x[s]][x[i]];
                    int nlcost = lcost - minarr[x[s]] + e[x[s]][x[i]];
                    if (nlcost < bestc) {
                        int tmp[21];
                        for (int j = 0; j < 21; ++j) {
                            tmp[j] = x[j];
                        }
                        swap(tmp[s + 1], tmp[i]);
                        q.push(node(nlcost, ncw, s + 1, tmp));
                    }
                }
            }
        }
    }
    cout << bestc << endl;
    // for (int i = 0; i < n; i++) {
    //     cout << bc[i] << " ";
    // }
    return 0;
}