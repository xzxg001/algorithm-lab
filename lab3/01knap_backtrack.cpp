#include<bits/stdc++.h>

using namespace std;
#define ll long long
const int N=1e6+10;
struct object{
	ll w;
	ll v;
};
object oj[N];
ll n;
ll c;
ll cw=0,cv=0;
ll bestv=0;
int bound(int i){
	ll nv=cv;
	for(int j=i;j<=n;j++){
		nv+=oj[j].v;
	}
	return nv;
}
void backtrack(int i){
	if(i>n){
		bestv=cv;
		return;
	}
	if(cw+oj[i].w<=c){
		cw+=oj[i].w;
		cv+=oj[i].v;
		backtrack(i+1);
		cw-=oj[i].w;
		cv-=oj[i].v;
	}
	if(bound(i+1)>bestv){
		backtrack(i+1);
	}
}

int main(){
	cin>>c>>n;
	int w,v;
	for(int i=1;i<=n;i++){
		cin>>w>>v;
		oj[i].w=w;
		oj[i].v=v;
	}
	backtrack(1);
	cout<<bestv<<endl;
}