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

const int MAXN = 3 << 10;
int A[MAXN], n;
vi freq;
vector<vector<ll>> cnt2, cnt3;

void tc(){
	scanf("%d", &n);
	loop(i, n) {
		scanf("%d", A + i);
		A[i]--;
	}
	freq.clear();
	cnt2.clear();
	cnt3.clear();
	freq.resize(n, 0);
	cnt2.resize(n, vector<ll>(n, 0));
	cnt3.resize(n, vector<ll>(n, 0));
	ll ans = 0;
	loop(i, n){
		int x = A[i];
		loop(i, n) ans += cnt3[i][x];
		loop(i, n) cnt3[x][i] += cnt2[x][i];
		loop(i, n) cnt2[i][x] += freq[i];
		freq[x]++;
	}
	printf("%lld\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
