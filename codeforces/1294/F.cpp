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

int n;
vi G[1 << 20];
pi mx[1 << 20][3];
pair<pi, pi> ans[1 << 20];

bool fix(pi *A, pi t){
	if(A[2] >= t) return 0;
	A[2] = t;
	int i = 2;
	while(i && A[i-1] < A[i]) {
		swap(A[i-1], A[i]);
		i--;
	}
	return 1;
}

void dfs(int u, int p){
	mx[u][0] = pi(0, u);
	for(int v : G[u]) if(v != p){
		dfs(v, u);
		pi t(mx[v][0]);
		t.first++;
		fix(mx[u], t);
	}
}


void dfs(int u, int p, pi fp){
	fix(mx[u], fp);
	bool has_zero = 0;
	loop(i, 3) if(mx[u][i].second == 0) has_zero = 1;
	if(!has_zero){
		loop(i, 3) ans[u].first.first += mx[u][i].first;
		ans[u].first.second = mx[u][0].second;
		ans[u].second.first = mx[u][1].second;
		ans[u].second.second = mx[u][2].second;
	}
	
	for(int v : G[u]) if(v != p){
		loop(i, 3) if(mx[u][i].second != mx[v][0].second) {
			pi t(mx[u][i]);
			t.first++;
			dfs(v, u, t);
			break;
		}
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1, 0);
	dfs(1, 0, pi(0, 0));
	auto res = *max_element(ans + 1, ans + n + 1);
	cout << res.first.first << endl;
	cout << res.first.second << " " << res.second.first << " " << res.second.second << endl;
	return 0;
}
