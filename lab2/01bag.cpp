#include<iostream>
#include<cmath>
using namespace std;
#define N 10001

int c,n;//c:capacity n:number
int v[N],w[N];//value weight
int m[N][N];//maxvalue
int x[N];//choice

void _01bag(int c,int *v,int *w,int n,int m[N][N]){
	for(int j=0;j<=c;j++)m[0][j]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=c;j++){
			
			if(j>=w[i])m[i][j]=max(m[i-1][j],m[i-1][j-w[i]]+v[i]);
			else m[i][j]=m[i-1][j];
		}
}

void _01bagchoice(int c,int *w,int n,int m[N][N],int* x){
	for(int i=n;i>0;i--){
		if(m[i][c]==m[i-1][c])x[i]=0;
		else{
			c-=w[i];
			x[i]=1;
		}
	}
}

//void _01bag(int c, int *v, int *w, int n) {
//    for (int j = 0; j <= c; j++) m[j] = 0;
//    for (int i = 1; i <= n; i++) {
//        for (int j = c; j >= w[i]; j--) {
//            m[j] = max(m[j], m[j - w[i]] + v[i]);
//        }
//    }
//}
//
//void _01bagchoice(int c, int *w, int n) {
//    int current_c = c;
//    for (int i = n; i > 0; i--) {
//        if (m[current_c] == m[current_c - w[i]]) x[i] = 0;
//        else {
//            x[i] = 1;
//            current_c -= w[i];
//        }
//    }
//}

int main(){
	cin>>n;
	cin>>c;
	for(int i=1;i<=n;i++)cin>>w[i]>>v[i];
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)m[i][j]=0;
	_01bag(c,v,w,n,m);
	cout<<m[n][c];
	_01bagchoice(c,w,n,m,x);
	for(int i=1;i<=n;i++)cout<<"第"<<i<<"件物品选用："<<x[i]<<endl; 
}

