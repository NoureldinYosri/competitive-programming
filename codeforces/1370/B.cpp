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

const int MAXN = 1024 << 2;
int A[MAXN], n;
vi parity[2];
vp pairs;

void solve(){
	loop(r, 2) parity[r].clear();
	loop(i, 2*n) parity[A[i]&1].pb(i);
	
	pairs.clear();
	loop(r, 2){
		while(sz(parity[r]) > 1){
			int a = parity[r].back(); parity[r].pop_back();
			int b = parity[r].back(); parity[r].pop_back();
			pairs.emplace_back(a+1, b+1);
		}		
	}
	if(sz(pairs) == n) pairs.pop_back();
	for(auto [a, b] : pairs) printf("%d %d\n", a, b);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		loop(i, 2*n) scanf("%d", A + i);
		solve();
	}
	return 0;
}
