#include <bits/stdc++.h>

using namespace std;

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

int cal(string s) {
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
int main() {
	int n=0;
	cin>>n;
	while(n--) {
		string s;
		cin >> s;
		cout<<cal(s)<<endl;
	}
}
