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


int A, B, C, D;


ll solve(int z, int B, int C){
	ll u = max(B - (z - C), 0);
	ll v = max(C - (z - B), 0);
	ll d_area = u*v;
	if(d_area == 0) return 0;
	ll p = u + v - 1 + v + 1;
	ll tmp = d_area - p + 2;
//	cerr << z << ": " << u << " " << v << " " << d_area << " " << p << endl;
	assert(tmp%2 == 0);
	assert(tmp >= 0);
	tmp >>= 1;
	tmp += u + v - 1;
//	cerr << u << " " << v << " " << u + v << " -> " << tmp << endl;
	return tmp;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> A >> B >> C >> D;
	ll ans = 0;
	for(int z = C; z <= D; z++)
		ans += solve(z, B, C) - solve(z, A-1, C) - solve(z, B, B-1) + solve(z, A-1, B-1);
	cout << ans << endl;
	return 0;
}
