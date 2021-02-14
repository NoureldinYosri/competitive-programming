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
std::ostream& operator << (std::ostream& st,const std::pair<A,B> & p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
template<class T>
std::ostream& operator << (std::ostream& st, const std::vector<T> & p){
	st << "{";
	bool first = true;
	for(auto & x : p) {
		if(!first) st << ", ";
		first = false; 
		st << x;
	}
	st << "}";
	return st;
}
using namespace std;

const int mod = 998244353, p1 = 332748118, p0 = (2*p1)%mod;
const int MAXN = 100*1000 + 10, MAXM = 512;
int n, m;
vi G[MAXN];
int mex[MAXN];

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
int powmod(int a, int p){
	if(p == 0) return 1;
	int b = 1;
	for(; p > 1; p >>= 1){
		if(p & 1) b = mul(a, b);
		a = mul(a, a);
	}
	return mul(a, b);
}
int inv(int x){
	return powmod(x, mod - 2);
}


int dfs(int u){
	if(mex[u] != -1) return mex[u];
	set<int> S;
	mex[u] = 0;
	for(int v : G[u]) S.insert(dfs(v));
	while(S.count(mex[u])) mex[u]++;
	return mex[u];
}


void gauss(vector<vi> & A){
	int m = sz(A);
	vi P(m);
	iota(all(P), 0);
	loop(p, m){
		int r = -1;
		for(int i = p; i < m; i++)
			if(A[i][p]){
				r = i;
				break;
			}
		assert(r != -1);
		if(r != p){
			A[r].swap(A[p]);
			swap(P[r], P[p]);
		}
		int scaler = inv(A[p][p]);
		for(int & x : A[p]) x = mul(x, scaler);
		for(int i = p + 1; i < m; i++){
			int c = A[i][p];
			for(int j = p; j < sz(A[i]); j++)
				A[i][j] = add(A[i][j], -mul(c, A[p][j]));
		}
	}
	for(int p = m-1; p > 0; p--){
		for(int r = p-1; r >= 0; r--){
			int v = A[r][p];
			for(int c = p; c < sz(A[r]); c++)
				A[r][c] = add(A[r][c], -mul(v, A[p][c]));
		}
	}
	vector<vi> aux(m);
	loop(i, m) aux[i] = A[P[i]];
	A.swap(aux);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].push_back(b);
	}
	memset(mex, -1, sizeof mex);
	for(int i = 1; i <= n; i++) if(mex[i] == -1) mex[i] = dfs(i);
	int m = *max_element(mex + 1, mex + n + 1) + 1;
	while(m != LSOne(m)) m ++;
	vi cnt(m, 0);
	for(int i = 1; i <= n; i++)
		cnt[mex[i]]++;
		
	
	
	vector<vi> A(m, vi(m, 0));
	loop(i, m) loop(j, m) A[i][j] = cnt[i^j];
//	cerr << A << endl;
	loop(i, m) loop(j, m) A[i][j] = (n + 1)*(i == j) - A[i][j];
	
//	cerr << A << endl;
	
	loop(i, m){
		loop(j, m) A[i].push_back(0);
		A[i][m + i] = 1;
	}

	gauss(A);
	loop(i, m){
		rotate(A[i].begin(), A[i].begin() + m, A[i].end());
		A[i].resize(m);
	}
	vi B(m, 1); B[0] = 0;
	vi V(m, 0);
	loop(i, m) loop(j, m) V[i] = add(V[i], mul(A[i][j], B[j]));
	cout << V[0] << endl;
	return 0;
}
