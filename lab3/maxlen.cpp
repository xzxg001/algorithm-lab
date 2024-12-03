#include<bits/stdc++.h>

using namespace std;
#define ll long long
const int N=1e6+10; 

ll n;
ll lengthOfLIS(vector<ll> a){
	int n=a.size();
	vector<ll> b(n);
	ll max=0;
	b[0]=1;
	for(ll i=0;i<n;i++){
		ll k=0;
		for(ll j=0;j<i;j++){
			if(b[j]>k&&a[i]>a[j])k=b[j];
		}
		b[i]=k+1;
		if(b[i]>max)max=b[i];
	}
	
	return max;
}
int main(){
	cin>>n;
	vector<ll> a(n);
	for(int i=0;i<n;i++)cin>>a[i];
	ll ans=lengthOfLIS(a);
	cout<<ans<<endl;
}
