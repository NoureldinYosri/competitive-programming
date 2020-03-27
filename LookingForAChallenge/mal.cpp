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

const int MAX = 200* 1000 + 10;
int L[MAX], R[MAX], n;
int ans[MAX];
bool on_floor[MAX];

void dfs(int u, int p){
	if(L[u] != -1 && L[u] != p) dfs(L[u], u);
	else L[u] = -1;
	if(R[u] != -1 && R[u] != p) dfs(R[u], u);
	else R[u] = -1;
}

int Q[2*MAX], q_size;

void do_kill(int u, int t){
	q_size = 0;
	int cur = 0;
	Q[q_size++] = u;
	while(cur < q_size){
		u = Q[cur++];
		if(u == -1 || on_floor[u]) continue;
		on_floor[u] = 1;
		ans[u] = t;
		if(L[u] != -1) Q[q_size++] = L[u];
		if(R[u] != -1) Q[q_size++] = R[u];
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n;i ++) {
		scanf("%d %d", L + i, R + i);
		ans[i] = -1;
	}
	dfs(1, 0);
	for(int t = 1; t <= m; t++){
		int u, h; scanf("%d %d", &u, &h);
		do_kill((h == 1) ? L[u] : R[u], t);
	}
	for(int i = 1; i <= n;i ++) printf("%d\n", ans[i]);
	return 0;
}
