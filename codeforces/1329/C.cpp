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

const int MAXN = 1 << 23;
int A[MAXN];
int siz[MAXN], is_leaf[MAXN], depth[MAXN];
int H, G, n;
vi ans;

void dfs(int u, int d){
	depth[u] = d;
	is_leaf[u] = d == H;
	if(!is_leaf[u]) {
		dfs(2*u, d+1);
		dfs(2*u+1, d+1);
	}
}

int get_val(int u){
	if(u > n) return 0;
	return A[u];
}


bool is_safe(int u){
	if(u > n) return 1;
	if(depth[u] > G) return 1;
	int left = 2*u, right = 2*u + 1;
	if(get_val(left) == 0 && get_val(right) == 0)
		return 0;
	if(get_val(left) > get_val(right))
		return is_safe(left);
	else
		return is_safe(right);
}

void f(int u){
	if(u > n) return ;
	int left = 2*u, right = 2*u+1;
	int vl = get_val(left), vr = get_val(right);
	if(vl == 0 && vr == 0){
		A[u] = 0;
		return;
	}
	if(vl > vr){
		A[u] = vl;
		f(left);
	}
	else {
		A[u] = vr;
		f(right);
	}
}

void work(int u){
	if(u > n || depth[u] > G) return;
	int left = 2*u, right = 2*u + 1;
	while(is_safe(u)) {
		ans.pb(u);
		f(u);
	}
	
	work(left);
	work(right);
}

ll get_res(int u){
	if(depth[u] > G) return 0;
	return A[u] + get_res(2*u) + get_res(2*u+1);
}

ll solve(){
	ans.clear();
	dfs(1, 1);
	work(1);
	return get_res(1);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &H, &G);
		n = (1 << H) - 1;
		for(int i = 1; i <= n; i++) scanf("%d", A + i);
		printf("%lld\n", solve());
		for(int x : ans) printf("%d ", x);
		puts("");
	}
	return 0;
}
