#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

int n, m;
int A[1 << 20], B[1 << 20];
vector<tuple<int, int, int>> ORs;
vi adj[1 << 20];


void solve(int b) {
	fill(B, B + n, -1);
	loop(i, n) adj[i].clear();
	for(auto [i, j, v] : ORs) {
		v = (v >> b) & 1;
		if(!v) {
			B[i] = B[j] = 0;
		} else if(i == j) {
			B[i] = 1;
		} else {
			adj[i].push_back(j);
			adj[j].push_back(i);
		}
	}
	loop(i, n) if(B[i] == 0) {
		for(int j : adj[i]) {
			assert(B[j] != 0);
			B[j] = 1;
		}
	}
	loop(i, n) if(B[i] == -1) {
		bool anyZero = false;
		for(int j : adj[i]) if(B[j] == 0) {
			anyZero = true;
			break;
		}
		B[i] = anyZero;
	}
	loop(i, n) {
		A[i] |= B[i] << b;
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	ORs.resize(m);
	for(auto & [i, j, v] : ORs) {
		scanf("%d %d %d", &i, &j, &v);
		i--, j--;
	}	
	for(int b = 29; b >= 0; b--)
		solve(b);

	loop(i, n) printf("%d ", A[i]);
	puts("");
	return 0;
}
