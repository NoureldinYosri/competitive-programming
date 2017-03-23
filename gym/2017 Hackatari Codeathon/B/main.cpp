#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 100'010;
vi T1[MAX],T2[MAX];
int n,m;
vi U[2],V[2];

void dfs(int u,int p,int c,vi *T,vi *aux){
	if(sz(T[u]) == 1) aux[c].pb(u);
	for(int v : T[u]) if(v != p) dfs(v,u,c^1,T,aux);
}

int main(){
	scanf("%d",&n);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		T1[a].pb(b);
		T1[b].pb(a);
	}
	scanf("%d",&m);
	loop(i,m-1){
		int a,b; scanf("%d %d",&a,&b);
		T2[a].pb(b);
		T2[b].pb(a);
	}
	dfs(1,0,0,T1,U);
	dfs(1,0,0,T2,V);
	if(sz(V[1]) == sz(U[0])) V[0].swap(V[1]);
	printf("%d\n",2 + (sz(U[0]) != sz(V[0])));	
	if(sz(U[0]) != sz(V[0])){
		while(sz(V[0]) > sz(U[0])){
			V[1].pb(V[0].back());
			V[0].pop_back();
		}
		while(sz(V[1]) > sz(U[1])){
			V[0].pb(V[1].back());
			V[1].pop_back();
		}
	}
	loop(i,sz(U[0])) printf("%d %d\n",U[0][i],V[0][i]);
	loop(i,sz(U[1])) printf("%d %d\n",U[1][i],V[1][i]);
	return 0;
}
