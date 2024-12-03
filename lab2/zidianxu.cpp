#include<bits/stdc++.h>

using namespace std;
#define N 10001
typedef long long ll;

ll f[N];
int permRank(int n,int *pi){
	int r=0;
	int rp[n+1];
	for(int i=1;i<=n;i++)rp[i]=pi[i];
	for(int i=1;i<=n;i++){
		r+=(rp[i]-1)*f[n-i];
		for(int j=i+1;j<=n;j++)if(rp[j]>rp[i])rp[j]--;
	}
	return r;
}

void permUnrank(int n,int r,int *pi){
	int d=0;
	pi[n]=1;
	for(int i=1;i<n;i++){
		d=(r%f[i+1])/f[i];
		r-=d*f[i];
		pi[n-i]=d+1;
		for(int j=n-i+1;j<=n;j++)if(pi[j]>d)pi[j]++;
	}
} 
int main(){
	f[0]=1;
	for(int i=1;i<=N;i++)f[i]=f[i-1]*i;
	int n;
	int pi1[n+1],pi2[n+1];
	int r1,r2;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>pi1[i];
	r1=permRank(n,pi1);
	cout<<r1<<endl;
	r2=r1+1;
	permUnrank(n,r2,pi2);
	for(int i=1;i<=n;i++)cout<<pi2[i]<<" ";
	
}

