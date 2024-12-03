#include "iostream"
#include "string"
#include "iomanip"
#include "fstream"
#include <chrono>  // 引入时间库来记录运行时间

using namespace std;

/*
正则表达式可选字符集的排列顺序先为‘*’，‘？’，操作文件名序列中出现的所有字符按其频率递减的次序随后

大体思路：
正则表达式为s，当前考察文件为f

match(i, j)为s[1,i]与f[1,j]匹配情况
如果match(i-1, j-1) = 1, s[i] = '?'
    match(i-1, j-1) = 1, s[i] = f[j]
    match(i-1, k) = 1,   s[i] = '*'
match(i, j) = 1
否则 match(i, j) = 0
*/

const int MAXN = 250;  // 最大文件数
const int MAXL = 8;  // 最大文件名长度
const int MAXP = 62; // 大写字母 + 小写字母 + 数字
int minlen;  // 最优正则表达式长度
int maxmat;  // 最优正则表达式所能匹配的操作文件数
int curmat;  // 当前正则式所能匹配的操作文件数
string f[MAXN + 1];  // 操作文件 + 非操作文件
string k[MAXN + 1];  // 非操作文件
int n[2];  // n[0]为操作文件数，n[1]为非操作文件数
int p[MAXP];  // p[len-1] 存储 s[len]可选字符数
char s[MAXP];  // 存储临时正则表达式
char minmat[MAXP];  // 最优正则表达式
int match[MAXP][MAXN + 1][MAXP];  // match[len][i][j]表示正则表达式的第len个字符与第i个文件的第j个字符的匹配情况

struct Cha {
    char c;  // 字符
    int f;   // 字符出现的频率
};

Cha cha[MAXN][MAXP]; // cha[len][i]表示正则表达式长度为len时的字符排序情况

// 对操作文件名中出现的字符按出现频率排序存储，以加快搜索进程
void save(char c, int len) {
    int i, j;
    for (i = 1; i <= p[len]; i++)
        if (cha[len][i].c == c) {
            cha[len][i].f++;
            cha[len][0] = cha[len][i];
            j = i;
            while (cha[len][j - 1].f < cha[len][0].f) { // 将频率小于当前字符频率的字母后移
                cha[len][j] = cha[len][j - 1];
                j--;
            }
            cha[len][j] = cha[len][0];  // 将当前字母放到适当位置
            return;
        }
    // 如果p[len] = 0，或者字符c第一次出现，则增加一个字符
    cha[len][++p[len]].c = c;
    cha[len][p[len]].f = 1;
}

// 计算当前匹配情况
bool check(int len) {
    int i, j, t, k = 0;
    curmat = 0;
    for (i = 1; i <= n[0]; i++) { // 遍历操作文件
        for (j = 0; j < MAXP; j++)
            match[len][i][j] = 0; // 初始化匹配表
        if (len == 1 && s[1] == '*') // 如果是*且正则长度为1，匹配全部
            match[len][i][0] = 1;
        for (j = 1; j <= f[i].length(); j++) { // 操作文件的每个字符
            switch (s[len]) {
            case '*': // 匹配任意长度的子串
                for (t = 0; t <= j; t++)
                    if (match[len - 1][i][t] == 1) {
                        match[len][i][j] = 1; // 正则表达式的第len个字符与第i个文件的第j个字符的匹配情况
                        break;
                    }
                break; // 此处的break不能省略！
            case '?': // 匹配单个字符
                match[len][i][j] = match[len - 1][i][j - 1];
                break;
            default:
                if (s[len] == f[i][j - 1]) // 精准字符匹配
                    match[len][i][j] = match[len - 1][i][j - 1];
                break;
            }
        }
        // 检查当前文件是否完全匹配
        for (j = f[i].length(); j >= 1; j--) {
            if (match[len][i][j] == 1) {
                k++;
                if (j == f[i].length()) // 说明第i个文件与正则表达式匹配
                    curmat++;
                break;
            }
        }
    }
    // 如果当前匹配情况比历史最佳情况差，返回false
    if (k < maxmat || k == maxmat && len >= minlen)
        return false;
    p[len] = 0; // 更新字符频率
    for (i = 1; i <= n[0]; i++) // 对与正则表达式匹配的文件中的字符重新排序，以便正则式下次扩展
        for (j = 1; j < f[i].length(); j++)
            if (match[len][i][j] == 1)
                save(f[i][j], len);
    return true;
}

// 判断是否匹配非操作文件
bool ok(int len) {
    int i, j, l, t;
    for (l = 1; l <= len; l++) {
        for (i = n[0] + 1; i <= n[0] + n[1]; i++) {
            for (j = 0; j < MAXP; j++)
                match[l][i][j] = 0; // 初始化匹配表
            if (s[1] == '*' && l == 1)
                match[l][i][0] = 1;
            for (j = 1; j <= f[i].length(); j++) {
                switch (s[l]) {
                case '*':
                    for (t = 0; t <= j; t++)
                        if (match[l - 1][i][t] == 1) {
                            match[l][i][j] = 1;
                            break;
                        }
                    break;
                case '?':
                    match[l][i][j] = match[l - 1][i][j - 1];
                    break;
                default:
                    if (s[l] == f[i][j - 1])
                        match[l][i][j] = match[l - 1][i][j - 1];
                    break;
                }
            }
        }
    }
    // 如果正则表达式匹配到非操作文件，返回false
    for (i = n[0] + 1; i <= n[0] + n[1]; i++)  // 如果正则表达式与非操作文件匹配
        if (match[len][i][f[i].length()] == 1)
            return false;
    return true;
}

// 求最优匹配的回溯法
// len 为当前正则表达式长度
// 正则表达式可选字符集的排列顺序先为‘*’，‘？’，操作文件名序列中出现的所有字符按其频率递减的次序随后
void search(int len) {
    // 如果当前正则表达式更优(匹配更多文件名/有更短表达式），更新最优解
    if ((curmat > maxmat || (curmat == maxmat && len < minlen)) && ok(len)) {
        maxmat = curmat;
        minlen = len;
        for (int i = 0; i <= minlen; i++)
            minmat[i] = s[i];
    }
    len++;
    // 尝试添加?和*
    if (len == 1 || s[len - 1] != '*') {
        s[len] = '?';
        if (check(len))
            search(len);
        s[len] = '*';
        if (check(len))
            search(len);
    }
    // 尝试添加其他字符
    for (int i = 1; i <= p[len - 1]; i++) {
        s[len] = cha[len - 1][i].c;
        if (check(len))
            search(len);
    }
}

int main() {
    ifstream fin("data.txt");  // 修改为读取 "data.txt"
    if (!fin) {
        cerr << "无法打开文件 data.txt" << endl;
        return 1;
    }

    cout << "输入文件：" << endl;
    n[0] = 0;
    n[1] = 0;
    p[0] = 0;
    string str;
    char ch;
    
    // 记录开始时间
    auto start = chrono::high_resolution_clock::now();

    while (!fin.eof()) { // 读入
        fin >> str >> ch;

        if (ch == '+') {
            f[++n[0]] = str;
            cout << f[n[0]] << " " << ch << endl;
            save(f[n[0]][0], 0);
        } else {
            k[++n[1]] = str;
            cout << k[n[1]] << " " << ch << endl;
        }
    }

    for (int i = 1; i <= n[1]; i++)
        f[n[0] + i] = k[i];

    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n[0] + n[1]; i++)
        match[0][i][0] = 1;

    maxmat = 0;
    minlen = 255;

    search(0);

    // 记录结束时间
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;  // 计算程序运行时间

    cout << "匹配最多文件数：" << maxmat << endl;
    cout << "正则表达式为：";
    for (int i = 0; i <= minlen; i++)
        cout << minmat[i];
    cout << endl;

    cout << "程序运行时间： " << duration.count() << " 秒" << endl;

    fin.close();
    return 0;
}
