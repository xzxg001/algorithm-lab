#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
typedef long long ll;

struct object {
    ll w;   // weight
    ll v;   // value
    double vpw; // value per weight (v / w)
};

// Comparator function to sort objects by value/weight ratio in descending order
bool cmp(const object &a, const object &b) {
    return a.vpw > b.vpw;
}

// Greedy algorithm for fractional knapsack problem
double bag_greedy(ll c, ll n, vector<object> &x) {
    vector<object> x1 = x;  // Create a copy of the input array
    double maxValue = 0.0;  // Initialize maximum value to 0.0

    // Sort the objects by value/weight ratio in descending order
    sort(x1.begin(), x1.end(), cmp);

    // Select items according to the greedy strategy
    for (ll i = 0; i < n && c > 0; i++) {
        if (x1[i].w <= c) {
            maxValue += x1[i].v;  // Take the full item
            c -= x1[i].w;         // Reduce capacity by the item's weight
        } else {
            maxValue += x1[i].vpw * c;  // Take fraction of the item
            c = 0;  // Knapsack is full
        }
    }

    return maxValue;
}

// Function to generate random data
void generate_random_data(ll n, ll c, vector<object> &x) {
    srand(time(0));
    for (ll i = 0; i < n; i++) {
        ll weight = rand() % 10000 + 1;  // Random weight between 1 and 10000
        ll value = rand() % 10000 + 1;   // Random value between 1 and 10000
        x[i] = {weight, value, (double)value / weight};
    }
}

int main() {
    // 三种不同规模的数据集
    vector<pair<ll, ll>> sizes = {{100, 1000}, {1000, 5000}, {100000, 1000000}};
    for (auto &size : sizes) {
        ll n = size.first;  // Number of items
        ll c = size.second; // Capacity of the knapsack

        vector<object> x(n);  // Create a vector of size n to store objects

        // Generate random data for the objects
        generate_random_data(n, c, x);

        // Measure execution time
        auto start = chrono::high_resolution_clock::now();
        double maxValue = bag_greedy(c, n, x);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        // Output the result
        cout << "问题规模: 物品数量 = " << n << "，背包容量 = " << c << endl;
        cout << "运行时间: " << duration.count() << " 毫秒。" << endl;
        cout << "-------------------------------------------" << endl;
    }

    return 0;
}
