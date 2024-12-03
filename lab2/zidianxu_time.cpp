#include <bits/stdc++.h>
using namespace std;
#define N 500
typedef long long ll;

ll f[N];

// 计算排列的秩
int permRank(int n, int *pi) {
    int r = 0;
    int rp[n + 1];
    for (int i = 1; i <= n; i++) rp[i] = pi[i];
    for (int i = 1; i <= n; i++) {
        r += (rp[i] - 1) * f[n - i];
        for (int j = i + 1; j <= n; j++)
            if (rp[j] > rp[i]) rp[j]--;
    }
    return r;
}

// 根据秩计算排列
void permUnrank(int n, int r, int *pi) {
    pi[n] = 1;
    for (int i = 1; i < n; i++) {
        int d = (r % f[i + 1]) / f[i];
        r -= d * f[i];
        pi[n - i] = d + 1;
        for (int j = n - i + 1; j <= n; j++)
            if (pi[j] > d) pi[j]++;
    }
}

// 生成随机排列并写入文件
void generateRandomPermutation(int n, const string& filename) {
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1); // 生成 [1, 2, ..., n]
    random_shuffle(perm.begin(), perm.end()); // 随机打乱
    ofstream fout(filename);
    fout << n << endl;
    for (int num : perm) {
        fout << num << " ";
    }
    fout << endl;
    fout.close();
}

// 从文件读取排列
void readPermutationFromFile(const string& filename, int *pi, int &n) {
    ifstream fin(filename);
    fin >> n;
    for (int i = 1; i <= n; i++) {
        fin >> pi[i];
    }
    fin.close();
}

int main() {
    // 预计算阶乘
    f[0] = 1;
    for (int i = 1; i <= N; i++) f[i] = f[i - 1] * i;

    vector<int> sizes = {6, 10, 12}; // 三种不同规模的排列
    for (int n : sizes) {
        // 生成随机排列并写入文件
        string filename = "random_permutation_" + to_string(n) + ".txt";
        generateRandomPermutation(n, filename);

        // 从文件中读取排列
        int pi[N], pi2[N];
        readPermutationFromFile(filename, pi, n);

        // 测量 permRank 和 permUnrank 运行时间
        auto start = chrono::high_resolution_clock::now();
        int r1 = permRank(n, pi);      // 计算排列的秩
        permUnrank(n, r1 + 1, pi2);    // 计算下一个排列
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        // 输出结果
        cout << "排列大小: " << n << endl;
        cout << "运行时间: " << duration.count() << " 毫秒。" << endl;
        cout << "-------------------------------------------" << endl;
    }

    return 0;
}
