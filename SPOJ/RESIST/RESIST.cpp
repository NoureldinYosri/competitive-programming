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
 
ld gauss(matrix & A){
	int n = sz(A);
	ld det = 1;
	loop(pivot, n){
		int r = -1;
		for(int i = pivot; i < n; i++) {
			if(abs(A[i][pivot]) > eps){
				r = i;
				break;
			}
		}
		assert(r != -1);
		if(r != pivot) {
			A[pivot].swap(A[r]);
			det = -det;
		}
		ld s = A[pivot][pivot];
		det *= s;
		for(auto & x : A[pivot]) x /= s;
		for(int i = pivot + 1; i < n; i++){
			s = A[i][pivot];
			for(int c = pivot; c < sz(A[i]); c++){
				A[i][c] -= s * A[pivot][c];
			}
		}
	}

	return det;
}





int n, m;

void tc(){
	matrix iR(n, row(n, 0.0));
	loop(e, m){
		int a, b, c; scanf("%d %d %d", &a, &b, &c);
		a--, b--;
		iR[a][b] += 1/(ld)c;
		iR[b][a] += 1/(ld)c;
	}
	matrix L(n, row(n, 0.0));
	loop(i, n) L[i][i] = accumulate(all(iR[i]), (ld)0.0);
	loop(i, n) loop(j, n) L[i][j] -= iR[i][j];
	
	matrix A(n - 2, row(n - 2, 0.0));
	loop(i, n-2) loop(j, n-2) A[i][j] = L[i + 1][j + 1];
	matrix B(n - 1, row(n - 1, 0.0));
	loop(i, n-1) loop(j, n-1) B[i][j] = L[i][j];

	ld R = gauss(A) / gauss(B);
	
	R = abs(R);
	printf("%.2f\n", (double)R);
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	while(scanf("%d %d", &n, &m) == 2) tc();
	return 0;
}
