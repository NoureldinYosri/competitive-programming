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



void gauss(vector<vector<double>> & A){
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
		double scaler = 1/A[p][p];
		for(double & x : A[p]) x *= scaler;
		for(int i = p + 1; i < m; i++){
			double c = A[i][p];
			for(int j = p; j < sz(A[i]); j++)
				A[i][j] -= c * A[p][j];
		}
	}
	for(int p = m-1; p > 0; p--){
		for(int r = p-1; r >= 0; r--){
			double v = A[r][p];
			for(int c = p; c < sz(A[r]); c++)
				A[r][c] -= v * A[p][c];
		}
	}
	vector<vector<double>> aux(m);
	loop(i, m) aux[i] = A[P[i]];
	A.swap(aux);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; 
	scanf("%d", &n);

	vector<vector<double>> A(n, vector<double>(n + 1, 0.0));
	loop(i, n) loop(j, n + 1) scanf("%lf", &A[i][j]);
	gauss(A);
	loop(i, n) printf("%0.5f\n", A[i].back());
	return 0;
}
