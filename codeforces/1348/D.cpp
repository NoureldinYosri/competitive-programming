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

ll N;

ll f(int D){
	ll ret = 1;
	ll cnt = 1;
	for(int d = 0;d <= D; d++){
		cnt <<= 1;
		ret += cnt*(1LL << (D - d));
	}
	return ret;
}

void solve(){
	//1001
	int D = 1;
	while(((1LL << (D + 1))-1) < N) D++;
	printf("%d\n", D);
	N--;
	ll population = 1;
	for(int d = 0; d < D; d++){
		ll effect = D-d;
		ll people = min(population, max(N/effect - population, 0LL));
//		cerr << N << " " << population << " " << people << " " << effect << endl;
		population += people;
		printf("%lld ", people);
		N -= population;
	}
	puts("");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%lld", &N);
		solve();
	}
	return 0;
}


// 1 -> 0.5*2 -> 2*1.5
// 2*1.5 -> 4*0.75 -> 4*1.75 -> 7
// 4*1.75 -> 8*0.875 -> 8.1.875 -> 15
