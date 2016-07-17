#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

const int MAX = 1e5 + 1e3;

int n;
vector<pi> G[MAX];
int A[MAX];
int SZ[MAX];

int dfs0(int u,int p){
	int ret = 1;
	for(auto e : G[u]) if(p != e.xx) ret += dfs0(e.xx,u);
	return SZ[u] = ret;
}


int dfs1(int u,int p,ll d){
	if(d > A[u]) return SZ[u];
	int ret = 0;
	for(auto e : G[u]) if(p != e.xx) ret += dfs1(e.xx,u,max(e.yy + d,0LL));
	return ret;
}

int main(){
	int a,b;
	scanf("%d",&n);
	if(n == 1){
		puts("0");
		return 0;
	}
	loop(i,n) scanf("%d",A + i);
	loop(i,n - 1) {
		scanf("%d %d",&a,&b); a--;
		G[a].pb(mp(i+1,b));
		G[i+1].pb(mp(a,b));
	}
	dfs0(0,-1);
	cout << dfs1(0,-1,0) << endl;
	return 0;
}
