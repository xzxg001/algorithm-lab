#include <iostream>
#include <time.h> 
#include <stdlib.h>
#include<algorithm>
using namespace std;


template<class Type>
Type select(Type a[], int n,int l, int r, int k){//左边界，右边界，第k位元素
	if(k<1||k>n){
		printf("Index out of bounds\n");
		exit(0);
	}
	n=n-1;
	while (true){
		if (l >= r)return a[l];
		//随机选择划分基准
		int i = l, j = l + rand() % (r - l + 1);//j选择为l到r的任意值[l,r]
		swap(a[i], a[j]);//与首元素交换位置
		j = r + 1;
		Type pivot = a[l];
		//以划分基准为轴做元素交换
		while (true){
			while (i<r&&a[++i] < pivot);
			while (j>l&&a[--j] > pivot);
			if (i >= j){
				break;
			}
			swap(a[i], a[j]);
		}
		//如果最后基准元素在第k个元素的位置，则找到了第k小的元素 
		if (j - l + 1 == k){
			return pivot;
		}	
		//a[j]必然小于pivot,做最后一次交换，满足左侧比pivot小，右侧比pivot大
		a[l] = a[j];
		a[j] = pivot;		
		//对子数组重复划分过程
		if (j - l + 1 < k){
			k = k - (j - l + 1);//基准元素右侧,求出相对位置 
			l = j + 1;
		}else{//基准元素左侧 
			r = j - 1;
		}
	}
}
 
//template <class Type>
//Type Select(Type a[],int n,int k){
//	
//	return select(a,0,n-1,k);		
//}
 
int main(){
	int n,k,r;
	while(cin>>n){
		cin>>k;
		int a[n];
		for(int i=0;i<n;i++)
			cin>>a[i];
		r=select<int> (a,n,0,n-1,k);
		cout<<r<<endl;
	}
	return 0; 
}