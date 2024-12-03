#include<bits/stdc++.h>

using namespace std;
#define ll long long
const int N=1e6+10;
struct object{
	ll w;
	ll v;
	int pos;
	double p;
};
bool cmp(const object &a,const object &b){
	return a.p>b.p;
}
object oj[N];
ll n;
ll c;
ll cw=0,cv=0;
ll bestv=0;
vector<int> bs,s;
int bound(int i){
	ll cleft=c-cw;
	ll nv=cv;
	int j=i;
	for(;j<=n&&oj[j].w<=cleft;j++){
		cleft-=oj[j].w;
		nv+=oj[j].v;
	}
	if(j<=n)nv+=oj[j].v*cleft/oj[j].w;
	return nv;
}
void backtrack(int i){
	if(i>n){
		bestv=cv;
		bs=s;
		return;
	}
	if(cw+oj[i].w<=c){
		cw+=oj[i].w;
		cv+=oj[i].v;
		s.push_back(i);
		backtrack(i+1);
		cw-=oj[i].w;
		cv-=oj[i].v;
		s.pop_back();
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
		oj[i].pos=i;
		oj[i].p=(double)v/(double)w;
	}
	sort(oj+1,oj+n+1,cmp);
	backtrack(1);
	cout<<bestv<<endl;
	for(int i:bs){
		cout<<oj[i].pos<<" ";
	}
}
