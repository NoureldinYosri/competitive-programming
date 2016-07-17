#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int MAX = 1e5 + 1e2;
double ans[MAX];
vi G[MAX];
int SZ[MAX],n;

int dfs(int u){
	SZ[u] = 1;
	for(int v : G[u]) SZ[u] += dfs(v);
	return SZ[u];
}


void dfs(int u,double exp){
	ans[u] = exp;
	int S = SZ[u] - 1;
	for(int v : G[u]) dfs(v,exp + (S - SZ[v])*0.5 + 1);
}

int main(){
	scanf("%d",&n);
	int a;
	loop(i,n - 1){
		scanf("%d",&a);
		G[a - 1].pb(i + 1);
	}
	dfs(0);
	dfs(0,1);
	loop(i,n) printf("%.15f%c",ans[i]," \n"[i == n - 1]);
	return 0;
}
