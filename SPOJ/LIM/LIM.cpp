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

map<int, vi> G;
int visId[500], visNum;
vi V;

void dfs(int u){
	if(visId[u] == visNum) return;
	visId[u] = visNum;
	V.push_back(u);
	for(int v : G[u]) dfs(v);
}

double solve(){
	V.clear();
	visNum++;
	dfs(0);
	if(find(all(V), 300) == V.end()) return 0;
	map<int, int> id;
	sort(all(V));
	while(V.back() > 290) V.pop_back();
	int n = sz(V);
	loop(i, n) id[V[i]] = i;
	matrix A(n, row(n, 0.0));
	row B(n, 0.0);
	loop(i, n) {
		int u = V[i];
		ld x = 1.0/sz(G[u]);
		for(int v : G[u]){
			if(v == 300){
				B[i] = x;
			} else if(v <= 290){
				A[i][id[v]] = x;
			}
		}
	}
	loop(i, n) loop(j, n) A[i][j] = (i == j) - A[i][j];
	auto iA = gauss(A);
	double ans = 0;
	loop(i, n) ans += iA[0][i] * B[i];
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	for(int m; scanf("%d", &m) == 1 && m; ){
		G.clear();
		loop(i, m){
			int a, b; scanf("%d %d", &a, &b);
			G[a].push_back(b);
			G[b].push_back(a);
		}
		printf("%.3f\n", min(max(0.0, solve()), 1.0));
	}
	return 0;
}
