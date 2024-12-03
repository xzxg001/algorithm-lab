#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// 第一个算法实现：组合数方法
int C(int n, int m) {
    int sum1 = 1, sum2 = 1;
     
    for (int i = 2; i < m + 1; ++i)
        sum2 *= i;
    for (int i = n; i > n - m; --i)
        sum1 *= i;
     
    return sum1 / sum2;
}

int cal1(string code) {
    int len = code.length(), sum = 0;
    int code_num[len];
     
    // 1. 将字符串进行编码
    for (int i = 0; i < len; ++i)
        code_num[i] = code[i] - 96;
     
    // 2. 统计位数小于len的个数
    for (int i = 1; i < len; ++i)
        sum += C(26, i);
     
    // 3. 统计位数等于len的字符串到所求之间的个数
    int start = 1;               // 第 x 位的起点，初始化为1
    for (int i = 0; i < len; ++i) {
        for (int j = start; j < code_num[i]; ++j) {
            sum += C(26 - j, len - i - 1);
            // 26 - j 表示剩下还有多少字母可以选择
            // len - i - 1 表示剩下多少位置可以放字母
        }
        start = code_num[i] + 1; // 更新下一位的起点，因为升序，所以至少 + 1
    }
    
    return sum+1;
}

// 第二个算法实现：递归和备忘录方法
vector<vector<int>> memoF(27, vector<int>(7, -1)); // f(i, k)
vector<int> memoG(7, -1); // g(k)

int f(int i, int k) {
    if (k == 1) return 1;
    if (memoF[i][k] != -1) return memoF[i][k];
    int l = 0;
    for (int j = i + 1; j <= 26; j++) {
        l += f(j, k - 1);
    }
    return memoF[i][k] = l;
}

int g(int k) {
    if (memoG[k] != -1) return memoG[k];
    int l = 0;
    for (int i = 1; i <= 26; i++) {
        l += f(i, k);
    }
    return memoG[k] = l;
}

int cal2(string s) {
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
    return all + 1;
}

// 随机生成升序字符串
string generateRandomAscendingString(int maxLength) {
    int len = rand() % maxLength + 1; // 随机生成长度 1 到 maxLength
    string s;
    for (int i = 0; i < len; ++i) {
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

int main() {
    srand(time(0)); // 随机数种子

    // 测试用例数量
    int testCases = 100;
    
    // 最大字符串长度
    int maxLength = 6;

    for (int i = 0; i < testCases; ++i) {
        string s = generateRandomAscendingString(maxLength);

        // 分别用两种算法计算结果
        int result1 = cal1(s);
        int result2 = cal2(s);

        // 输出测试字符串和两个算法的结果
        cout << "测试字符串: " << s << endl;
        cout << "算法1结果: " << result1 << ", 算法2结果: " << result2 << endl;

        // 比较两个结果是否一致
        if (result1 != result2) {
            cout << "结果不一致！" << endl;
            break;
        } else {
            cout << "结果一致！" << endl;
        }
        cout << "-----------------------------------" << endl;
    }

    return 0;
}
