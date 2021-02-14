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

 
using ld = long double;
using row = vector<ld>;
using matrix = vector<row>;
const ld eps = 1e-12;
 
ostream& operator << (ostream& os, const matrix & A) {
	os << "[";
	bool firstRow = true;
	for(auto R : A){
		if(!firstRow) {
			os << "; ";
		}
		firstRow = false;
		bool firstItem = true;
		for(auto x : R) {
			if(!firstItem) os << " ";
			os << x;
			firstItem = false;
		}
	}
	os << "]";
	return os;
}
 
void gauss(matrix & A){
	int n = sz(A);
	loop(pivot, n){
		int r = -1;
		for(int i = pivot; i < n; i++) {
			if(abs(A[i][pivot]) > eps){
				r = i;
				break;
			}
		}
		assert(r != -1);
		if(r != pivot) A[pivot].swap(A[r]);
		ld s = A[pivot][pivot];
		for(auto & x : A[pivot]) x /= s;
		for(int i = pivot + 1; i < n; i++){
			s = A[i][pivot];
			for(int c = pivot; c < sz(A[i]); c++){
				A[i][c] -= s * A[pivot][c];
			}
		}
	}
	for(int pivot = n-1; pivot >= 0; pivot--){
		for(int r = pivot - 1; r >= 0; r--){
			ld s = A[r][pivot];
			for(int c = pivot; c < sz(A[r]); c++)
				A[r][c] -= s * A[pivot][c];
		}
	}
}

void inv_matrix(matrix & A){
	int n = sz(A);
	loop(i, n){
		A[i].resize(2*n, 0);
		A[i][i + n] = 1;
	}
	gauss(A);
	loop(i, n){
		rotate(A[i].begin(), A[i].begin() + n, A[i].end());
		A[i].resize(n);
	}
}




vi V;
vector<bool> vis;
int n, m;
vector<vp> G;

void dfs(int u){
	if(vis[u]) return;
	vis[u] = true;
	V.push_back(u);
	for(auto [v, _] : G[u]) dfs(v);
}

void tc(){
	G.clear();
	G.resize(n);
	loop(e, m){
		int a, b, c; scanf("%d %d %d", &a, &b, &c);
		a--, b--;
		G[a].emplace_back(b, c);
		G[b].emplace_back(a, c);
	}
	if(n == 2){
		ld R = 0;
		for(auto [_, r] : G[0]){
			R += 1.0/r;
		}
		R = 1.0/R;
		printf("%.02f\n", (double)R);
		return;
	}
	V.clear();
	vis.resize(n);
	fill(all(vis), false);
	dfs(0);
	sort(all(V));
	assert(V.back() == n-1);
	int N = sz(V) - 2;
	matrix A(N, row(N, 0.0));
	row B(N, 0.0);
	loop(i, N){
		int u = V[i + 1];
		ld scaler = 0;
		for(auto [v, r] : G[u]){
			if(v == 0 || v == n-1){
				B[i] += (v == 0)/(ld)r;
			} else {
				A[i][lower_bound(all(V), v) - V.begin() - 1] += 1.0/r;
			}
			scaler += 1.0/r;
		}
		for(auto & x : A[i]) x /= scaler;
		B[i] /= scaler;
	}
	loop(i, N) loop(j, N) A[i][j] = (i == j) - A[i][j];
	inv_matrix(A);
	row Volt(N, 0.0);
	loop(i, N) loop(j, N) Volt[i] += A[i][j] * B[j];
	ld current = 0;
	for(auto [v, r] : G[0]){
		if(v == n-1){
			current += 1.0/r;
		} else {
			int j = lower_bound(all(V), v) - V.begin() - 1;
			ld dv = 1 - Volt[j];
			current += dv / r;			
		}
	}
	ld resistance = 1.0/current;
	printf("%.2f\n", (double)resistance);
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	while(scanf("%d %d", &n, &m) == 2) tc();
	return 0;
}
