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



int pref[1 << 20], suff[1 << 20];


int query_mex(int l, int r, int n){
	return min(l ? pref[l-1] : n, ((r+1) < n) ? suff[r+1] : n);
}

int simulate(int n, int *a, int q, int k, int s) {
	std::mt19937 gen;
	gen.seed(s);
	
	int mn = n;
	loop(i, n){
		mn = min(mn, a[i]);
		pref[i] = mn;
	}
	mn = n;
	for(int i = n-1; i >= 0; i--){
		mn = min(mn, a[i]);
		suff[i] = mn;
	}
	suff[n] = n;
	
	int last = 0;
	while (q--) {
		int op = gen() % k;
		int i = (gen() + last) % n;
		if (!op && i) {
			std::swap(a[i - 1], a[i]);
			pref[i-1] = min((i >= 2) ? pref[i-2] : n, a[i-1]);
			suff[i] = min(a[i], suff[i+1]);		
		} else {
			int j = gen() % n;
			last ^= query_mex(std::min(i, j), std::max(i, j), n);
		}
	}
	return last;
}


int A[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n, q, k, s;
	scanf("%d %d %d %d", &n, &q, &k, &s);
	loop(i, n) scanf("%d", A + i);
	printf("%d\n", simulate(n, A, q, k, s));
	return 0;
}
