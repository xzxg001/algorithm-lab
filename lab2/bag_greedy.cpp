#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;
#define N 1000001
typedef long long ll;
ll n;
ll c;
struct object{
	ll w;
	ll v;
	double vpw;
};
object x[N]; 
bool cmp(const object &a,const object &b){
	return a.vpw>b.vpw;
}

double bag_greedy(int c,int n,object *x){
	object x1[n+1];
	for(int i=1;i<=n;i++){
	x1[i].w=x[i].w;
	x1[i].v=x[i].v;
	x1[i].vpw=x[i].vpw;
}
	double max;
	sort(x1+1,x1+n+1,cmp);
	for(int i=1;i<=n&&c>0;i++){
		if(x1[i].w<=c){
			max+=x1[i].v;
			c-=x1[i].w;
			//cout<<x1[i].w<<endl;
		}else{
			max+=x1[i].vpw*c;
			c=0;
		}
	}
	 return max;
}
int main(){
	cin>>n>>c;
	for(int i=1;i<=n;i++){
		cin>>x[i].w>>x[i].v;
		x[i].vpw=(double)x[i].v/x[i].w;
	}
	double max=bag_greedy(c,n,x);
	cout<<fixed<<setprecision(2)<<max;
}

