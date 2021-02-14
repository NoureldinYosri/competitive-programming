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

ostream& operator <<(ostream& os, const matrix & A){
	bool firstRow = true;
	os << "[";
	for(auto & R : A){
		if(!firstRow){
			os << "; ";
		}
		firstRow = false;
		bool firstItem = true;
		for(auto & x : R){
			if(!firstItem){
				os << " ";
			}
			firstItem = false;
			os << x;
		}
	}
	os << "]";
	return os;
}

void gauss(matrix & A){
//	cerr << A << endl;
	int n = sz(A);
	loop(p, n){
		int r = -1;
		for(int i = p; i < n; i++)
			if(abs(A[i][p]) > eps) {
				r = i;
				break;
			}
		assert(r != -1);
		if(r != p) A[p].swap(A[r]);
		ld s = A[p][p];
		for(auto & x : A[p]) x /= s;
		for(int i = p + 1; i < n; i++){
			ld s = A[i][p];
			for(int c = p; c < sz(A[i]); c++)
				A[i][c] -= s * A[p][c];
		}
	}
//	cerr << A << endl;
	for(int p = n-1; p > 0; p--){
		for(int i = p-1; i >= 0; i--){
			ld s = A[i][p];
			for(int c = p; c < sz(A[i]); c++)
				A[i][c] -= s * A[p][c];
		}
	}
//	cerr << A << endl;
}


void inv_matrix(matrix & A){
	int n = sz(A);
	loop(i, n){
		A[i].resize(2*n);
		A[i][i + n] = 1;
	}
	gauss(A);
	loop(i, n){
		rotate(A[i].begin(), A[i].begin() + n, A[i].end());
		A[i].resize(n);
	}
}


int fail[1 << 20];

int getLen(int l, int c, const string & s){
	static map<int, int> mem[26];
	if(mem[c].count(l)) return mem[c][l];
	int t = l;
	char target = c + 'a';
	while(t && s[t] != target) t = fail[t - 1];
	t += s[t] == target;
	return mem[c][l] = t;
}

void buildFail(const string & s){
	int l = 0;
	for(int i = 1; i < sz(s); i++)
		fail[i] = l = getLen(l, s[i] - 'a', s);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int m; string s;
	cin >> m >> s;
	buildFail(s);
	int n = sz(s);
	matrix A(n, row(n, 0.0));
	loop(i, n){
		loop(c, m) {
			int j = getLen(i, c, s);
			if(j < n){
				A[i][j]++;
			}
		}
		loop(j, n) A[i][j] = (i == j) - A[i][j]/m;
	}
	inv_matrix(A);
	
	double E = accumulate(all(A[0]), 0.0);
	
	cout << floor(E + eps) << endl;

	return 0;
}
