#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

const int N = 5e7; // �������ݵ����ֵ
vector<int> a(N+1);

// �ϲ�������������
void merge(vector<int>& a, int l, int mid, int r) {
    int i = l, j = mid + 1, k = 0;
    vector<int> tmp(r - l + 1);
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (int k = 0; k < tmp.size(); k++) a[l + k] = tmp[k];
}

 //�鲢����
void mergesort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergesort(a, l, mid);
    mergesort(a, mid + 1, r);
    merge(a, l, mid, r);
}

//void mergesort(vector<int>& a,int l,int r){
//	int step=1;
//	int n=a.size();
//	while(step<n){
//	for(int i=0;i<n;i+=2*step){
//		int l=i;
//		int mid=min(i+step-1,n-1);
//		int r=min(i+2*step-1,n-1);
//		merge(a,l,mid,r);
//	}
//	step*=2;
//}
//}


// ����������ɣ����� minRange �� maxRange �����������ݷ�Χ
void generateRandomData(int n, const string& filename, int minRange, int maxRange) {
    ofstream fout(filename);
    srand(time(0)); // ��ʼ�����������
    for (int i = 0; i < n; i++) {
        fout << minRange + rand() % (maxRange - minRange + 1) << " "; // ����ָ����Χ�ڵ������
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
    vector<int> sizes = {10, 10000, 1000000}; // ���ֲ�ͬ��ģ������
    int minRange = 0; // ��Сֵ
    int maxRange = 1000000; // ���ֵ (���Կ������ݵķ�Χ��С)

    for (int size : sizes) {
        string filename = "mergesort" + to_string(size) + ".txt";

        // 1. ����������ݲ�д���ļ����������ݷ�ΧΪ [minRange, maxRange]
        generateRandomData(size, filename, minRange, maxRange);

        // 2. ���ļ��ж�ȡ����
        readDataFromFile(a, filename, size);

        // 3. ��������Ϣ�����ݹ�ģ
        cout << "Data size: " << size << " numbers"<<endl;
		cout<<"Random Range: [" << minRange << ", " << maxRange << "]." << endl;

        // 4. �����鲢�����ִ��ʱ��
        auto start = high_resolution_clock::now();
        mergesort(a, 0, size - 1);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        // 5. �������ʱ��
        cout << "Sorting " << size << " numbers took: " << duration.count() << " milliseconds." << endl;
        cout << "-------------------------------------------" << endl;
    }

    return 0;
}

