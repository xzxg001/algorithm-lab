#include<bits/stdc++.h>

using namespace std;
#define ll long long 
const int N=1e4+10;
vector<vector<int>> e(N,vector<int>(N,INT_MAX));

struct node{
	ll lcost;//下界
	ll cw;//当前费用
	ll s;//根节点到当前路径，用于标记当前节点的位置 
	vector<int> x;//记录路径
	node(ll lcost,ll cw,ll s,vector<int> x){
		this->lcost=lcost;
		this->cw=cw;
		this->s=s;
		this->x=x;
	}	
};

struct nodecmp{
	bool operator()(const node& a,const node& b){
		return a.lcost > b.lcost;
	}
};

ll n,m;//顶点数和边数
ll u,v,w;
ll minout;

ll bestc=INT_MAX;//最小费用
vector<int> bc;
priority_queue<node,vector<node>,nodecmp> q;
int main(){
	cin>>n>>m;
	vector<ll> minarr(n+1,INT_MAX);
	for(int i=0;i<m;i++){
		cin>>u>>v>>w;
		e[u][v]=w;
		e[v][u]=w;
		if(w<minarr[u])minarr[u]=w;
		if(w<minarr[v])minarr[v]=w; 
	}
	for(int i=1;i<=n;i++){//计算minarr数组和minout值
		if(minarr[i]==INT_MAX){
			cout<<"NoEdge"<<endl;
			return 0;
		}
		minout+=minarr[i];	
	}
	vector<int> t(n);
	for(int i=0;i<n;i++)t[i]=i+1;
	q.push(node(minout,0,0,t));
	while(!q.empty()){
		auto no=q.top();
		q.pop();
		ll lcost=no.lcost;//下界
		ll cw=no.cw;//当前费用
		ll s=no.s;//根节点到当前路径，用于标记当前节点的位置 
		auto x=no.x;//记录路径
		if(s==n-1){
				bestc=cw+e[x[n-2]][x[n-1]]+e[x[n-1]][1];
				bc=x;
				break;
		}
		if(s==n-2){
			if(e[x[n-2]][x[n-1]]!=INT_MAX&&e[x[n-1]][1]!=INT_MAX&&
			cw+e[x[n-2]][x[n-1]]+e[x[n-1]][1]<bestc){
				ll ncw=cw+e[x[n-2]][x[n-1]]+e[x[n-1]][1];
				q.push(node(ncw,ncw,s+1,x));
			}else continue;
		}else{
			for(int i=s+1;i<=n;i++){
				if(e[x[s]][x[i]]!=INT_MAX){
					ll ncw=cw+e[x[s]][x[i]];
					ll nlcost=lcost-minarr[x[s]]+e[x[s]][x[i]];
					if(nlcost<bestc){
						auto tmp=x;
						swap(tmp[s+1],tmp[i]);
						q.push(node(nlcost,ncw,s+1,tmp));
					}
				}
			}
		}
	}
	cout<<bestc<<endl;
	for(int i=1;i<=n;i++){
		cout<<bc[i]<<" ";
	}
}

