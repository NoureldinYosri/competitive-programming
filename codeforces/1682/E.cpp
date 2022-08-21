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


int n, m;
int P[1 << 20], A[1 << 20], B[1 << 20];
vi E[1 << 20];
bool vis[1 << 20];
pi cutAt[1 << 20];
map<int, vi> need[1 << 20];

pi dfs(int u, int p) {
	vis[u] = true;
	set<int> have, want;
	want.insert(u);
	have.insert(P[u]);
	for(int e : E[u]) {
		int v = A[e] + B[e] - u;
		if(v == p) continue;
		A[e] = u;
		B[e] = v;
		auto [h, w] = dfs(v, u);
		cutAt[e] = pi(w, h);
		have.insert(h);
		want.insert(w);
	}
	int ctr[2] = {0, 0};
	int h = 0, w = 0;
	for(int ch : have) if(!want.count(ch)) {
		h = ch;
		ctr[0]++;
	}
	for(int cw : want) if(!have.count(cw)) {
		w = cw;
		ctr[1]++;
	}

	assert(ctr[0] == ctr[1] && ctr[0] <= 1);
	return pi(h, w);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", P + i);
	loop(e, m) {
		scanf("%d %d", A + e, B + e);
		E[A[e]].push_back(e);
		E[B[e]].push_back(e);
	}
	for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, 0);
	loop(e, m) {
		int a = A[e], b = B[e];
		auto [w, h] = cutAt[e];
		need[a][w].push_back(e);
		need[b][h].push_back(e);
	}

	queue<int> q;
	vi ans;
	loop(e, m) if(cutAt[e] == pi(P[A[e]], P[B[e]])) {
		q.push(e);
	}

	// loop(e, m) {
	// 	cerr << pi(A[e], B[e]) << ": " << cutAt[e] << endl;
	// }

	while(!q.empty()) {
			int e = q.front(); q.pop();
			ans.push_back(e);
			swap(P[A[e]], P[B[e]]);
			for(int t : need[A[e]][P[A[e]]]) {
				if(cutAt[t] == pi(P[A[t]], P[B[t]])) {
					q.push(t);
				}
			}
			for(int t : need[B[e]][P[B[e]]]) {
				if(cutAt[t] == pi(P[A[t]], P[B[t]])) {
					q.push(t);
				}
			}
	}

	for(int e : ans) printf("%d ", e + 1);
	puts("");
	return 0;
}
