#include<bits/stdc++.h>

using namespace std;
const int N=5e7;
vector<int> a(N+1);

void findmaxmin(vector<int>& a,int l,int r,int& maxi,int& mini){
	if(l==r){
		maxi=a[l];
		mini=a[l];
		return;
	}else{
		int max1,min1,max2,min2;
		int mid=l+(r-l)/2;
		findmaxmin(a,l,mid,max1,min1);
		findmaxmin(a,mid+1,r,max2,min2);
		maxi=max(max1,max2);
		mini=min(min1,min2);
		return;
	}
}

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	int maxi=a[0],mini=a[0];
	findmaxmin(a,0,n-1,maxi,mini);
	cout<<"max:"<<maxi<<" min:"<<mini;
}

