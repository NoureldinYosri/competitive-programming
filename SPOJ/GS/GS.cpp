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
vector<vp> G;

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

matrix gauss(matrix & A){
	cerr << A << endl;
	int n = sz(A);
	loop(i, n){
		A[i].resize(2*n, 0);
		A[i][i + n] = 1;
	}
	loop(pivot, n){
		int r = -1;
		for(int i = pivot; i < n; i++) {
			if(A[i][pivot]){
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
			for(int c = pivot; c < 2*n; c++){
				A[i][c] -= s * A[pivot][c];
			}
		}
	}
	for(int pivot = n-1; pivot >= 0; pivot--){
		for(int r = pivot - 1; r >= 0; r--){
			ld s = A[r][pivot];
			for(int c = pivot; c < 2*n; c++)
				A[r][c] -= s * A[pivot][c];
		}
	}
	matrix iA(n, row(n, 0));
	loop(i, n) loop(j, n) iA[i][j] = A[i][j + n];
	return iA;
}

void tc(){
	int n, src, snk; scanf("%d %d %d", &n, &src, &snk);
	src--, snk--;
	G.clear();
	G.resize(n);
	vi name(n);
	iota(all(name), 0);
	if(snk != n-1) swap(name[snk], name[n-1]);
	loop(e, n-1){
		int a, b, c; scanf("%d %d %d", &a, &b, &c);
		a--, b--;
		a = name[a];
		b = name[b];
		G[a].emplace_back(b, c);
		G[b].emplace_back(a, c);
	}
	matrix A(n-1, row(n-1, 0.0));
	loop(i, n-1) {
		ld s = 0;
		for(auto [j, w] : G[i]){
			if(j != n-1) A[i][j] = w;
			s += w;
		}
		for(auto & x : A[i]) x /= s;
	}
	loop(i, n-1) loop(j, n-1) A[i][j] = (i == j) - A[i][j];
	auto iA = gauss(A);
	double ans = accumulate(all(iA[name[src]]), 0.0);
	printf("%.5f\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
