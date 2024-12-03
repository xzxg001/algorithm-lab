#include<iostream>
#include<climits>
#include<vector>
#include<queue>
using namespace std;
#define ll long long 
const int N=1e6+10;
const int M=5e6+10;
struct Edge{
	ll v;
	ll w;
	Edge(int v,int w){
		this->v=v;
		this->w=w;
	}
};
vector<Edge> e[N];

struct node{
	int dis;
	int pos;
	node(int dis,int pos){
		this->dis=dis;
		this->pos=pos;
	}
	bool operator()(const node &a,const node &b)const{
	return a.dis>b.dis;
}
};
struct cmp {
    bool operator()(const node& a, const node& b) {
        return a.dis > b.dis; 
    }
};
priority_queue<node, vector<node>, cmp> q;
bool book[N];
ll n,m,st;//顶点数，边数，起始节点
ll dis[N];//最短距离
ll pre[N];//该顶点的前序顶点
inline void dijkstra(){
	fill(dis, dis + N, INT_MAX); 
	dis[st]=0;
	q.push(node(0,st));
	while(!q.empty()){
		node t=q.top();
		q.pop();
		ll d=t.dis;
		int p=t.pos;
		if(book[p])continue;
		book[p]=1;
		int v;
		ll w;
		for(auto edge:e[p]){
			v=edge.v;
			w=edge.w;
			if(dis[p]+w<dis[v]){
				dis[v]=dis[p]+w;
				q.push(node(dis[v],v));
				pre[v]=p;
			}
		}	
	}
}


int main(){
	cin>>n>>m>>st;
	ll u,v,w;
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;
		e[u].push_back(Edge(v,w));
	}
	dijkstra();
	for(int i=1;i<=n;i++){
		if(dis[i]==INT_MAX)cout<<INT_MAX<<" ";
		else cout<<dis[i]<<" ";
	}
	cout<<"输入查询的节点路径：";
    int x=0;
    cin>>x;
    for(;x!=0;){
    	if(x==st){cout<<x;break;
		}
    	cout<<x<<"<-";
    	x=pre[x];
	}
	
}
