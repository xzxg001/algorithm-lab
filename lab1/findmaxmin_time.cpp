#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

const int N = 5e7;  // ����ģ��������
vector<int> a(N+1);

// �������ֵ����Сֵ�ĵݹ麯��
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

// ����������ɲ�д���ļ�
void generateRandomData(int n, const string& filename, int minRange, int maxRange) {
    ofstream fout(filename);
    srand(time(0)); // ��ʼ�����������
    for (int i = 0; i < n; i++) {
        fout << minRange + rand() % (maxRange - minRange + 1) << " "; // ����ָ����Χ�������
    }
    fout.close();
}

// ���ļ��ж�ȡ����
void readDataFromFile(vector<int>& a, const string& filename, int n) {
    ifstream fin(filename);
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }
    fin.close();
}

int main() {
    vector<int> sizes = {10, 1000, 1000000}; // ���ֲ�ͬ��ģ�����ݣ�С���С���
    int minRange = 0;    // ���������Сֵ
    int maxRange = 1000000; // ����������ֵ

    for (int size : sizes) {
        string filename = "findmaxmin" + to_string(size) + ".txt";

        // 1. ����������ݲ�д���ļ�
        generateRandomData(size, filename, minRange, maxRange);

        // 2. ���ļ��ж�ȡ����
        readDataFromFile(a, filename, size);

        // 3. ������ݹ�ģ��Ϣ
        cout << "Data size: " << size << " numbers." << endl;

        // 4. �������ֵ����Сֵ���ҵ�ִ��ʱ��
        int maxi = a[0], mini = a[0];
        auto start = high_resolution_clock::now();
        findmaxmin(a, 0, size - 1, maxi, mini);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        // 5. ������
        cout << "Max: " << maxi << ", Min: " << mini << endl;
        cout << "Time taken to find max and min: " << duration.count() << " milliseconds." << endl;
        cout << "-------------------------------------------" << endl;
    }

    return 0;
}

