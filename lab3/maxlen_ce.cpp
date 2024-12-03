#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;
#define ll long long

// 求解最长递增子序列的长度
int lengthOfLIS(vector<ll> &a) {
    int size = 0;
    vector<ll> q(a.size() + 1);
    int i, j;
    for (int x : a) {
        i = 0, j = size;
        while (i < j) {
            int m = i + (j - i) / 2;
            if (q[m] < x)
                i = m + 1;
            else
                j = m;
        }
        q[i] = x;
        size = max(i + 1, size);
    }
    return size;
}

// 生成测试数据
void generate_test_data(const string &filename, ll size, ll max_value) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    out << size << "\n"; // 输出数组大小
    for (ll i = 0; i < size; i++) {
        out << rand() % max_value + 1 << " "; // 随机生成 [1, max_value] 范围内的数字
    }
    out.close();
    cout << "Generated data for " << filename << " with size " << size << ".\n";
}

// 测试数据
void test_data(const string &filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    ll n;
    in >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        in >> a[i];
    }
    in.close();

    // 测试算法并计时
    clock_t start_time = clock();
    ll ans = lengthOfLIS(a);
    clock_t end_time = clock();

    // 输出结果
    cout << "Test for " << filename << ":\n";
    cout << "Longest Increasing Subsequence Length: " << ans << "\n";
    cout << "Time taken: " << double(end_time - start_time) / CLOCKS_PER_SEC << " seconds\n\n";
}

int main() {
    srand(time(0)); // 设置随机种子

    // 生成测试数据
    generate_test_data("lis_small.txt", 10, 100);       // 小规模
    generate_test_data("lis_medium.txt", 1000, 10000); // 中规模
    generate_test_data("lis_large.txt", 1000000, 1000000); // 大规模

    cout << "\nData generation complete.\n\n";

    // 测试小规模数据
    test_data("lis_small.txt");

    // 测试中规模数据
    test_data("lis_medium.txt");

    // 测试大规模数据
    test_data("lis_large.txt");

    return 0;
}
