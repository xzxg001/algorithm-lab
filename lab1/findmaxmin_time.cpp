#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

const int N = 5e7;  // 最大规模的数据量
vector<int> a(N+1);

// 查找最大值和最小值的递归函数
void findmaxmin(vector<int>& a, int l, int r, int& maxi, int& mini) {
    if (l == r) {
        maxi = a[l];
        mini = a[l];
        return;
    } else {
        int max1, min1, max2, min2;
        int mid = l + (r - l) / 2;
        findmaxmin(a, l, mid, max1, min1);
        findmaxmin(a, mid + 1, r, max2, min2);
        maxi = max(max1, max2);
        mini = min(min1, min2);
        return;
    }
}

// 随机数据生成并写入文件
void generateRandomData(int n, const string& filename, int minRange, int maxRange) {
    ofstream fout(filename);
    srand(time(0)); // 初始化随机数种子
    for (int i = 0; i < n; i++) {
        fout << minRange + rand() % (maxRange - minRange + 1) << " "; // 生成指定范围的随机数
    }
    fout.close();
}

// 从文件中读取数据
void readDataFromFile(vector<int>& a, const string& filename, int n) {
    ifstream fin(filename);
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }
    fin.close();
}

int main() {
    vector<int> sizes = {10, 1000, 1000000}; // 三种不同规模的数据：小、中、大
    int minRange = 0;    // 随机数的最小值
    int maxRange = 1000000; // 随机数的最大值

    for (int size : sizes) {
        string filename = "findmaxmin" + to_string(size) + ".txt";

        // 1. 生成随机数据并写入文件
        generateRandomData(size, filename, minRange, maxRange);

        // 2. 从文件中读取数据
        readDataFromFile(a, filename, size);

        // 3. 输出数据规模信息
        cout << "Data size: " << size << " numbers." << endl;

        // 4. 测量最大值和最小值查找的执行时间
        int maxi = a[0], mini = a[0];
        auto start = high_resolution_clock::now();
        findmaxmin(a, 0, size - 1, maxi, mini);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        // 5. 输出结果
        cout << "Max: " << maxi << ", Min: " << mini << endl;
        cout << "Time taken to find max and min: " << duration.count() << " milliseconds." << endl;
        cout << "-------------------------------------------" << endl;
    }

    return 0;
}

