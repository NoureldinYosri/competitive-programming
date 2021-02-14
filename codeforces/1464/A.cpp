#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

vp V;
vi nxt;
vector<bool> vis;

int solve(){
	int m = sz(V);
	map<int, int> col2index;
	loop(i, m) {
		col2index[V[i].second] = i;
	}
	nxt.resize(m);
	loop(i, m){
		int x = V[i].first;	
		if(col2index.count(x)) nxt[i] = col2index[x];
		else nxt[i] = -1;
	}
	vis.resize(m);
	fill(all(vis), false);
//	print(nxt, int);
	int ans = 0;
	loop(i, m) if(!vis[i]){
		int j = i;
		int ctr = 0;
		while(j != -1 && !vis[j]) {
			vis[j] = true;
			ctr++;
			j = nxt[j];
		}
		ans += ctr;
		ans += j == i;
	}	
	return ans;
}
void tc(){
	int n, m; scanf("%d %d", &n, &m);
	V.clear();
	loop(i, m){
		int x, y; scanf("%d %d", &x, &y);
		if(x == y) continue;
		V.emplace_back(x, y);
	}
	m = sz(V);
	int ans = solve();
	for(auto & [x, y] : V) swap(x, y);
	ans = min(ans, solve());
	
	printf("%d\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
