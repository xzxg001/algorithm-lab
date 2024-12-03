#include <iostream>
#include <chrono> // 使用高精度时间测量的头文件
#include<vector>

using namespace std;
using namespace std::chrono; // 使用 chrono 命名空间

const int N=5e7;
vector<int> a(N+1);
void merge(vector<int>& a,int l,int mid,int r) {
	int i=l,j=mid+1,k=0;
	vector<int> tmp(r-l+1);
	while(i<=mid&&j<=r) {
		if(a[i]<=a[j])tmp[k++]=a[i++];
		else tmp[k++]=a[j++];
	}
	while(i<=mid)tmp[k++]=a[i++];
	while(j<=r)tmp[k++]=a[j++];
	for(int k=0; k<tmp.size(); k++)a[l+k]=tmp[k];
}


void mergesort(vector<int>& a,int l,int r) {
	if(l>=r)return;
	int mid=l+(r-l)/2;
	mergesort(a,l,mid);
	mergesort(a,mid+1,r);
	merge(a,l,mid,r);
}

int main() {
	int n=0;
	cin>>n;
	//int a[10]= {4,5,2,8,6,3,4,9,88,45};
	for(int i=0; i<n; i++)cin>>a[i];

    mergesort(a, 0, n - 1);
    for (int i = 0; i < n; i++)cout << a[i] << " ";

    return 0;

}

