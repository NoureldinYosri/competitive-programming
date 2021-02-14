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


int n, m;
vector<vi> G;
vector<bool> vis;

void tc(){
	static vi ans;
	scanf("%d %d", &n, &m);
	G.clear();
	G.resize(n + 1);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	vis.resize(n + 1);
	fill(all(vis), false);
	ans.clear();
	set<int> V;
	V.insert(1);
	while(!V.empty()){
		if(!V.empty()){
			int u = *V.begin(); V.erase(V.begin());
			vis[u] = true;
			ans.push_back(u);
			for(int v : G[u]) if(!vis[v]) {
				vis[v] = true;
				for(int t : G[v]) if(!vis[t]) V.insert(t);
			}
		}		
		while(!V.empty() && vis[*V.begin()]) V.erase(V.begin());
	}
	if(find(vis.begin() + 1, vis.end(), false) == vis.end()){
		puts("YES");
		printf("%d\n", sz(ans));
		for(int x : ans) printf("%d ", x);
		puts("");
	} else {
		puts("NO");
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
