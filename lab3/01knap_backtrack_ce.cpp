#include <bits/stdc++.h>
#include <chrono> // 引入 chrono 库
using namespace std;
#define ll long long

const int N = 1e6 + 10;
struct Object {
    ll weight, value, index;
    double ratio;
};
bool compare(const Object &a, const Object &b) {
    return a.ratio > b.ratio;
}

Object objects[N];
ll c, n, current_weight = 0, current_value = 0, best_value = 0;
vector<ll> best_solution, temp_solution;

// 生成测试数据
void generate_test_data(const string &filename, ll num_items, ll max_weight, ll max_value, ll capacity) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    out << capacity << " " << num_items << "\n"; // 背包容量和物品数量
    for (ll i = 0; i < num_items; i++) {
        ll weight = rand() % max_weight + 1;   // 随机重量
        ll value = rand() % max_value + 1;     // 随机价值
        out << weight << " " << value << "\n";
    }

    out.close();
    cout << "Generated data for " << filename << " with " << num_items << " items.\n";
}

// 计算上界
ll calculate_bound(ll i) {
    ll remaining_capacity = c - current_weight;
    ll potential_value = current_value;
    ll j = i;
    for (; j <= n && objects[j].weight <= remaining_capacity; j++) {
        remaining_capacity -= objects[j].weight;
        potential_value += objects[j].value;
    }
    if (j <= n) {
        potential_value += objects[j].value * remaining_capacity / objects[j].weight;
    }
    return potential_value;
}

// 回溯搜索
void backtrack(ll i) {
    if (i > n) {
        best_value = current_value;
        best_solution = temp_solution;
        return;
    }
    if (current_weight + objects[i].weight <= c) {
        current_weight += objects[i].weight;
        current_value += objects[i].value;
        temp_solution.push_back(objects[i].index);
        backtrack(i + 1);
        current_weight -= objects[i].weight;
        current_value -= objects[i].value;
        temp_solution.pop_back();
    }
    if (calculate_bound(i + 1) > best_value) {
        backtrack(i + 1);
    }
}

// 测试数据
void test_data(const string &filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // 加载数据
    in >> c >> n;
    for (ll i = 1; i <= n; i++) {
        in >> objects[i].weight >> objects[i].value;
        objects[i].index = i;
        objects[i].ratio = (double)objects[i].value / objects[i].weight;
    }
    in.close();

    // 排序物品
    sort(objects + 1, objects + n + 1, compare);

    // 计时并运行算法
    auto start_time = chrono::high_resolution_clock::now();
    backtrack(1);
    auto end_time = chrono::high_resolution_clock::now();

    // 输出结果
    cout << "Test for " << filename << ":\n";
    cout << "Best value: " << best_value << "\n";
    cout << "Time taken: "
         << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count()
         << " milliseconds\n\n";
}

int main() {
    srand(time(0)); // 设置随机种子

    // 生成测试数据
    generate_test_data("01knap_backtrack_small.txt", 10, 100, 200, 500);      // 小规模
    generate_test_data("01knap_backtrack_medium.txt", 10000, 500, 1000, 10000); // 中规模
    generate_test_data("01knap_backtrack_large.txt", 1000000, 1000, 2000, 1000000); // 大规模
    cout << "\nData generation complete.\n\n";

    // 测试小规模数据
    test_data("01knap_backtrack_small.txt");

    // 测试中规模数据
    test_data("01knap_backtrack_medium.txt");

    // 测试大规模数据
    test_data("01knap_backtrack_large.txt");

    return 0;
}
