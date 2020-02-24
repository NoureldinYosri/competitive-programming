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


char S[1 << 20];

int freq[128];
vi IDX[128];

ll solve(vi & A, vi & B){
	ll ret = 0;
	for(int i : A){
		auto ptr = upper_bound(all(B), i);
		ret += B.end() - ptr;
	}
/*	if(ret){
		print(A, int);
		print(B, int);
		cerr << ret << endl;
			
	}
*/	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%s", S);
	int n = strlen(S);
	loop(i, n) {
		freq[S[i] - 'a']++;
		IDX[S[i] - 'a'].pb(i);
	}
	ll ans = 0;
	loop(c, 26)
		ans = max(ans, freq[c] + 0LL);
	
	loop(i, 26) loop(j, 26) {
		ans = max(ans, solve(IDX[i], IDX[j]));
	}
	cout << ans << endl;
	return 0;
}
