#include<iostream>
#include<vector>
#include<climits>
using namespace std;
#define ll long long
const int N=2e3+1;
bool book[N];
ll dis[N];
ll pre[N];
vector<vector<int>> e(N,vector<int>(N,INT_MAX));
ll n,m;//顶点个数,边条数
ll st; //起始点
int main(){
    cin>>n>>m;
    cin>>st;
    int u,v,w;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)if(i==j)e[i][j]=0;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        e[u][v]=w;
    }
    for(int i=1;i<=n;i++)dis[i]=INT_MAX;
    dis[st]=0;
    book[st]=1;
    for(int j=1;j<=n;j++)if(e[st][j]>=0)dis[j]=e[st][j];
    ll min1;
    int mini;
    for(int i=1;i<=n-1;i++){
        min1=INT_MAX;
        for(int j=1;j<=n;j++){
            if(dis[j]<min1&&book[j]==0){
                min1=dis[j];
                mini=j;
            }
        }
        book[mini]=1;
        for(int j=1;j<=n;j++){
            if(dis[mini]+e[mini][j]<dis[j]&&e[mini][j]<INT_MAX){
                dis[j]=dis[mini]+e[mini][j];
                pre[j]=mini;
            }
        }
    }
    for(int i=1;i<=n;i++)cout<<dis[i]<<" ";
    cout<<"输入查询的节点路径：";
    int x=0;
    cin>>x;
    for(;x!=0;){
    	if(x==st)cout<<x;
    	cout<<x<<"<-";
    	x=pre[x];
	}
}