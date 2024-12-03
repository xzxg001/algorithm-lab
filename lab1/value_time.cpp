#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace chrono;

// 备忘录数组
vector<vector<int>> memoF(27, vector<int>(7, -1)); // f(i, k)
vector<int> memoG(7, -1); // g(k)

// 计算 f(i, k)
int f(int i, int k) {
    if (k == 1) return 1;
    if (memoF[i][k] != -1) return memoF[i][k]; // 如果已计算，直接返回
    int l = 0;
    for (int j = i + 1; j <= 26; j++) {
        l += f(j, k - 1);
    }
    return memoF[i][k] = l; // 存储计算结果
}

// 计算 g(k)
int g(int k) {
    if (memoG[k] != -1) return memoG[k]; // 如果已计算，直接返回
    int l = 0;
    for (int i = 1; i <= 26; i++) {
        l += f(i, k);
    }
    return memoG[k] = l; // 存储计算结果
}

int cal(const string &s) {
    int n = s.size();
    int all = 0; // 初始化 all
    for (int i = 1; i < n; i++) {
        all += g(i);
    }
    for (int i = 0, temp = 0; i < n; i++) {
        int l = s[i] - 'a' + 1;
        for (int j = temp + 1; j < l; j++) {
            all += f(j, n - i);
        }
        temp = l;
    }
    return all + 1; // +1 for the empty string
}

// 生成随机升序字符串
string generateAscendingString(int length) {
    string s;
    for (int i = 0; i < length; i++) {
        char ch = 'a' + rand() % 26;
        if (s.empty() || ch > s.back()) {
            s.push_back(ch);
        } else {
            ch = s.back() + 1;
            if (ch <= 'z') s.push_back(ch);
        }
    }
    return s;
}

// 生成测试数据并写入文件
void generateTestData(const string &filename, int n) {
    ofstream fout(filename);
    fout << n << endl;
    for (int i = 0; i < n; i++) {
        int len = rand() % 6 + 1; // 随机生成字符串长度 1-6
        string s = generateAscendingString(len);
        fout << s << endl;
    }
    fout.close();
}

// 从文件读取数据
vector<string> readTestData(const string &filename) {
    ifstream fin(filename);
    int n;
    fin >> n;
    vector<string> data(n);
    for (int i = 0; i < n; i++) {
        fin >> data[i];
    }
    fin.close();
    return data;
}

int main() {
    srand(time(0)); // 初始化随机种子

    // 数据规模
    vector<int> sizes = {10, 1000, 1000000}; // 三种不同规模的数据
    for (int dataSize : sizes) {
        string filename = "ascending_strings_" + to_string(dataSize) + ".txt";

        // 生成测试数据并写入文件
        generateTestData(filename, dataSize);

        // 从文件读取数据
        vector<string> data = readTestData(filename);

        // 计时
        auto start = high_resolution_clock::now();
        for (const string &s : data) {
            int result = cal(s); 
        }
        auto end = high_resolution_clock::now();

        // 记录运行时间
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "处理 " << dataSize << " 个升序字符串的运行时间为: " 
             << duration.count() << " 毫秒" << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}
