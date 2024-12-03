//https://zhuanlan.zhihu.com/p/670544975
#include<iostream>
#include<vector>
using namespace std;
#define ll long long

int lengthOfLIS(vector<ll> a){
	int size=0;
	vector<ll> q(a.size()+1);
	int i,j;
	for(int x:a){
		i=0,j=size;
		while(i<j){
			int m=i+(j-i)/2;
			if(q[m]<x)i=m+1;
			else j=m;
		}
		q[i]=x;
		size=max(i+1,size);
	}
	return size;
}
int main(){
	ll n;
	cin>>n;
	vector<ll> a(n+1);
	for(int i=0;i<n;i++)cin>>a[i];
	ll ans=lengthOfLIS(a);
	cout<<ans<<endl;
}
