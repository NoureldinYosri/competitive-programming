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


int A[3];

ll solve(int k){
	if(k == 3){
		ll ret = 0;
		loop(i,3) loop(j,i) ret += abs(A[i] - A[j]);
		return ret;
	}
	int v = A[k];
	ll ret = LLONG_MAX;
	for(int dv = -1;dv <= 1;dv++){
		A[k] = v + dv;
		ret = min(ret,solve(k+1));
	}
	A[k] = v;
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		loop(i,3) scanf("%d",A + i);
		printf("%lld\n",solve(0));
	}
	
	return 0;
}
