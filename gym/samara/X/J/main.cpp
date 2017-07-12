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
#define popcnt(x) __builtin_popcount(x)
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
vi G[MAX],aux[MAX];
int n;
int branch[MAX];
bool found = 0;

void dfs(int u,int p){

	for(int v : G[u]) if(v != p){
		dfs(v,u);
		branch[u] += branch[v] ? branch[v] : 1;
		aux[u].pb(branch[v]);
	}

}


void dfs(int u,int p,int from_parent){
//	cerr << u << " " << branch[u] << " " << from_parent << endl;
	branch[u] += from_parent;
	if(branch[u] >= 5) {
		found = 1;
		return;
	}
	for(int v : G[u]) if(v != p){
		int t = branch[u] - (branch[v] ? branch[v] : 1);
		dfs(v,u,t ? t : 1);
		if(found) break;
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);

	#endif
	int n; scanf("%d",&n);
	loop(i,n - 1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	int mx = 0;
	range(i,1,n) mx = max(mx,sz(G[i]));
	if(mx >= 5) puts("NO");
	else{
		dfs(1,0);
		dfs(1,0,0);
		puts(found ? "NO" : "YES");
	}

	return 0;
}
