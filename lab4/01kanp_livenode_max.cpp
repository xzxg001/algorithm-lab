#include<iostream>
#include<queue>
#include<algorithm>
#include<bitset>
using namespace std;
#define ll long long
const int N=1e6+10;
//const int N=1e6+10;
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
ll bestv=0;
bitset<N> bs;
int bound(int i, int cw, int cv){
	ll cleft=c-cw;
	ll nv=cv;
	int j=i;
	for(;j<=n&&oj[j].w<=cleft;j++){
		cleft-=oj[j].w;
		nv+=oj[j].v;
	}
	if(j<=n)nv+=oj[j].v*(double)cleft/oj[j].w;
	return nv;
}
struct node{
	ll cw;
	ll cv;
	ll level;
	bitset<N> s; 
	ll up;
	node(int cw,int cv,int level,bitset<N> s,int up){
		this->cw=cw;
		this->cv=cv;
		this->level=level;
		this->s=s;
		this->up=up;
	}

};
struct nodecmp{
	bool operator()(const node &a,const node &b)const{
		return a.up<b.up;
	}
};
priority_queue<node,vector<node>,nodecmp> q;
void knap(){
	bitset<N> s;
	int init_up=bound(1,0,0);
	q.push(node(0,0,1,s,init_up));
	while(!q.empty()){
		node no=q.top();
		q.pop();
		ll cw=no.cw;
		ll cv=no.cv;
		ll level=no.level;
		if(level>n){
			if(cv>bestv){
			bestv=cv;
			bs=no.s;
			break;
			}
			
			continue;
		}
		if(cw+oj[level].w<=c){
			auto left_s=no.s;
			left_s[level]=true;
			int left_up=bound(level+1,cw+oj[level].w,cv+oj[level].v);
			node left_node(cw+oj[level].w,cv+oj[level].v,level+1,left_s,left_up);
			q.push(left_node);
		}
		if(bound(level+1,cw,cv)>bestv){
			auto right_s=no.s;
			right_s[level]=false;
			int right_up=bound(level+1,cw,cv);
			node right_node(cw,cv,level+1,right_s,right_up);
			q.push(right_node);
		}
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
	knap();
	cout<<bestv<<endl;
//	for(int i=1;i<=n;i++)
//		if(bs[i])cout<<oj[i].pos<<" ";
}
