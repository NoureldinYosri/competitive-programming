#pragma GCC optimize ("O3")
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

int dfs(int u,int pl = 0){
	siz[u] = sz(G[u]) == 0;
	player[u] = pl;
	for(int v : G[u])
		siz[u] += dfs(v,pl ^ 1);
	return siz[u];
}

int maximize(int u){
	if(G[u].empty()) return 1;
	vi aux_t,aux_loss;
	for(int v : G[u]){
		int t = maximize(v);
		aux_t.pb(t);
		aux_loss.pb(siz[v] - t);
	}
	sort(all(aux_t));
	sort(all(aux_loss));
	vi val;
	int cur = siz[u];
	for(auto x : aux_loss){
		val.pb(cur - x);
		cur -= x + 1;
	}
	int ret = player[u] ? val.back() : val[0];
	return ret;
}
int minimize(int u){
	if(G[u].empty()) return 1;
	vi aux_t,aux_loss;
	for(int v : G[u]){
		int t = minimize(v);
		aux_t.pb(t-1);
		aux_loss.pb(siz[v] - t);
	}
	sort(all(aux_t));
	sort(all(aux_loss));
	vi val;
	int cur = 1;
	for(auto x : aux_t){
		val.pb(cur + x);
		cur += x + 1;
	}
	int ret = player[u] ? val[0] : val.back();
//	cerr << "u = " << u << " player = " << player[u] << " ret = " << ret << endl;
	return ret;
}
int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	scanf("%d",&n);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
	}
	dfs(1);
	cout << maximize(1) << " ";
	cout << minimize(1) << endl;
	//cerr << maximize(1) << " ";
	//cerr << minimize(1) << endl;
	return 0;
}
