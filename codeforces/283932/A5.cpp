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

const int MAXN = 55;
ll L[MAXN], R[MAXN];
int n;
ll K;

ll get(int v){
	ll ret = 0;
	loop(i, n) if(v >= L[i]) {
		if(v <= R[i]) ret += v - L[i] + 1;
		else ret += R[i] - L[i] + 1;
	}
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %lld", &n, &K);
	loop(i, n) scanf("%lld %lld", L + i, R + i);
	ll s = *min_element(L, L + n), e = *max_element(R, R + n);
	K++;
	while(s < e){
		ll m = s + (e-s)/2;
		if(get(m) >= K) e = m;
		else s = m+1;
	}
	cout << s << endl;
	return 0;
}