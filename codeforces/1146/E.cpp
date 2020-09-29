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

const int MAX = 1 << 21;
int ST[MAX];
int n, m;
int A[MAX];
vi V;
vi who[MAX];

void update(int cur, int v){
	ST[cur] = v;
}

void push_down(int cur){
	if(ST[cur] == -1) return;
	int left = 2*cur + 1, right = left + 1;
	update(left, ST[cur]);
	update(right, ST[cur]);
	ST[cur] = -1;
}

void update(int cur, int s, int e, int l, int r, int v){
	if(l <= s && e <= r) return update(cur, v);
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) update(left, s, m, l, r, v);
	else if(m < l) update(right, m+1, e, l, r, v);
	else {
		update(left, s, m, l, m, v);
		update(right, m+1, e, m+1, r, v);
	}
}

void dfs(int cur, int s, int e){
	if(s == e){
		cerr << V[s] << " is " << ST[cur] << endl;
		int sgn = 2*(ST[cur] == 1) - 1;
		for(int i : who[s])
			A[i] = sgn*V[s];
		return;
	}
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	dfs(left, s, m);
	dfs(right, m+1, e);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%d", A + i), V.pb(A[i]), V.pb(-A[i]);
	sort(all(V));
	V.resize(unique(all(V)) - V.begin());
	memset(ST, -1, sizeof ST);
	update(0, 0, sz(V)-1, 0, sz(V)-1, 0);
	loop(i, n) {
		int x = A[i];
		int k = lower_bound(all(V), x) - V.begin();
		update(0, 0, sz(V)-1, k, k, 1);
		who[lower_bound(all(V), x) - V.begin()].pb(i);
	}
	
	while(m--){
		char c; int v;
		scanf(" %c %d", &c, &v);
		cerr << c << " " << v << endl;
		if(c == '<'){
			int k = lower_bound(all(V), v) - V.begin();
			k--;
			if(k >= 0){
				int x = V[k];
				int kd = lower_bound(all(V), -x) - V.begin();				
				update(0, 0, sz(V)-1, 0, k, 0);
				update(0, 0, sz(V)-1, kd, sz(V)-1, 1);
			}
		}
		else {
			int k = upper_bound(all(V), v) - V.begin();
			cerr << "k is " << k << endl;
			print(V, int);
			if(k < sz(V)){
				int x = V[k];
				int kd = lower_bound(all(V), -x) - V.begin();				
				cerr << "kd is " << kd << endl;
				update(0, 0, sz(V)-1, k, sz(V)-1, 0);
				dfs(0, 0, sz(V)-1);
				cerr << "set " << V[0] << " to " << V[kd] << " to 1" << endl;
				update(0, 0, sz(V)-1, 0, kd, 1);
			}			
		}
		dfs(0, 0, sz(V)-1);
		prArr(A, n, int);
	}
//	dfs(0, 0, sz(V)-1);
//	prArr(A, n, int);
	return 0;
}
