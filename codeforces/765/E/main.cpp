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

const int MAX = 200'010;
vi G[MAX];
vi fail[MAX];
set<int> H[MAX];

int ans = INT_MAX;

int get_val(int h){
	assert(h > 0);
	while(h%2 == 0) h >>= 1;
	return h;
}

bool dfs(int u,int p){
	int ret = 1;	
	for(int v : G[u]) if(v != p) {
		if(dfs(v,u)) H[u].insert((H[v].empty() ? 0 : *H[v].begin()) + 1);
		else fail[u].pb(v),ret = 0;
	}
	ret &= sz(H[u]) <= 1;
	return ret;
}

void dfs(int u,int p,int h){
	if(h != -1) H[u].insert(h + 1);
	if(fail[u].empty()){
		if(H[u].empty()) ans = 0;
		if(sz(H[u]) == 1) ans = get_val(*H[u].begin());
		if(sz(H[u]) == 2) ans = get_val(*H[u].begin() + *H[u].rbegin());
	}
	if(sz(H[u]) <= 1 && sz(fail[u]) == 1){
		int h = H[u].empty() ? 0 : *H[u].begin();
		for(int v : fail[u])
			dfs(v,u,h);
	}
}

int main(){
	int n; scanf("%d",&n);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	dfs(1,0,-1);
	if(ans == INT_MAX) ans = -1;
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
