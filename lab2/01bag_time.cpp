#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
#define N 10001

int c, n; // c: capacity, n: number
int v[N], w[N]; // value weight
int m[N][N]; // max value
int x[N]; // choice

void _01bag(int c, int *v, int *w, int n, int m[N][N]) {
    for (int j = 0; j <= c; j++) m[0][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= c; j++) {
            if (j >= w[i]) m[i][j] = max(m[i - 1][j], m[i - 1][j - w[i]] + v[i]);
            else m[i][j] = m[i - 1][j];
        }
}

void _01bagchoice(int c, int *w, int n, int m[N][N], int* x) {
    for (int i = n; i > 0; i--) {
        if (m[i][c] == m[i - 1][c]) x[i] = 0;
        else {
            c -= w[i];
            x[i] = 1;
        }
    }
}

// 生成随机数据并写入文件
void generateRandomData(int itemCount, const string& filename) {
    ofstream fout(filename);
    fout << itemCount << " " << 1000 << endl; // 假设最大容量为1000
    for (int i = 0; i < itemCount; i++) {
        int weight = rand() % 100 + 1; // 随机生成重量 (1 到 100)
        int value = rand() % 100 + 1; // 随机生成价值 (1 到 100)
        fout << weight << " " << value << endl;
    }
    fout.close();
}

// 读取数据从文件
void readDataFromFile(const string& filename) {
    ifstream fin(filename);
    fin >> n >> c; // 读取物品数量和最大容量
    for (int i = 1; i <= n; i++) {
        fin >> w[i] >> v[i]; // 读取每个物品的重量和价值
    }
    fin.close();
}

int main() {
    srand(time(0)); // 初始化随机数种子
    vector<int> sizes = {10, 100, 10000}; // 三种不同规模的数据

    for (int itemCount : sizes) {
        string filename = "knapsack_data_" + to_string(itemCount) + ".txt";

        // 生成随机数据
        generateRandomData(itemCount, filename);

        // 从文件中读取数据
        readDataFromFile(filename);

        // 测量运行时间
        auto start = chrono::high_resolution_clock::now();
        _01bag(c, v, w, n, m);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        // 输出结果
        cout << "对于 " << itemCount << " 件物品，最大价值为: " << m[n][c] << endl;
        cout << "运行时间: " << duration.count() << " 毫秒。" << endl;

        // 选择的物品
        _01bagchoice(c, w, n, m, x);
//        for (int i = 1; i <= n; i++) {
//            cout << "第 " << i << " 件物品选用： " << x[i] << endl;
//        }
        cout << "-------------------------------------------" << endl;
    }

    return 0;
}
