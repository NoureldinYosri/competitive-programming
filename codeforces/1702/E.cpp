#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

int n;
vector<vi> adj;
vi color, ctr, who;

bool dfs(int u, int c, int & diff) {
	if(color[u] != -1) return color[u] == c;
	color[u] = c;
	diff += 2*c - 1;
	for(int v : adj[u]) if(!dfs(v, 1 - c, diff)) return false;
	return true;
}

void init() {
	adj.clear();
	adj.resize(n);

	color.clear();
	color.resize(n, -1);

	ctr.clear();
	ctr.resize(n, 0);

	who.clear();
	who.resize(n, -1);
}

void tc() {
	scanf("%d", &n);
	init();
	loop(i, n) {
		loop(t, 2) {
				int v; scanf("%d", &v); v--;
				ctr[v]++;
				if(who[v] != -1) {
					int j = who[v];
					adj[i].push_back(j);
					adj[j].push_back(i);
				}
				who[v] = i;
		}
	}
	loop(i, n) if(ctr[i] != 2) {
		puts("NO");
		return;
	}
	loop(i, n) if(color[i] == -1) {
		int diff = 0;
		if(!dfs(i, 0, diff)) {
			puts("NO");
			return;
		}
	}
	puts("YES");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
