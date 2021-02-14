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

ld gauss(matrix & A){
	int n = sz(A);
	ld det = 1;
	loop(p, n){
		int r = -1;
		for(int i = p; i < n; i++)
			if(abs(A[i][p]) > eps){
				r = i;
				break;
			}
		if(r == -1) return 0;
		if(r != p){
			A[p].swap(A[r]);
			det *= -1;
		}
		ld s = A[p][p];
		det *= s;
		for(auto & x : A[p]) x /= s;
		for(int i = p + 1; i < n; i++){
			s = A[i][p];
			for(int c = p; c < sz(A[i]); c++)
				A[i][c] -= s * A[p][c];
		}
	}
	return det;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	for(int n; scanf("%d", &n) == 1 && n; ){
		matrix A(n, row(n, 0));
		loop(i, n) loop(j, n) {
			int x; scanf("%d", &x);
			A[i][j] = x;
		}
		printf("%.0f\n", (double)gauss(A));
	}
	puts("*");
	return 0;
}
