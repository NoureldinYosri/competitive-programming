/*#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 200*1000 + 10;
vi G[MAX];
int n;
int siz[MAX],player[MAX];
int idx[MAX],A[MAX],m;

void dfs(int u){
	if(G[u].empty()){
		idx[u] = m++;
		return;
	}
	for(int v : G[u]) dfs(v);
}

int solve(int u,int p){
	if(G[u].empty()) return A[idx[u]];
	int ret = p ? INT_MAX : 0;
	for(int v : G[u]){
		if(p) ret = min(ret,solve(v,p^1));
		else ret = max(ret,solve(v,p^1));
	}
	return ret;
}

void solve(){
	loop(i,m) A[i] = i + 1;
	int mn = INT_MAX,mx = 0;
	do{
		int val = solve(1,0);
		mn = min(mn,val);
		mx = max(mx,val);
	}while(next_permutation(A,A + m));
	printf("%d %d\n",mx,mn);
}

int main(){
	scanf("%d",&n);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
	}
	dfs(1);
	solve();
	return 0;
}*/
