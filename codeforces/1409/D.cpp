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


void tc(){
	ll n; int ts;
	scanf("%lld %d", &n, &ts);
	string N = "0" + to_string(n);
	int s = 0;
	for(char c : N) s += c - '0';
	if(s <= ts) {
		puts("0");
	} else {
		ll ans = 0;
		ll p10 = 1;
		for(int i = sz(N)-1; i > 0; i--, p10 *= 10){
			int d = N[i] - '0';
			ans += (10 - d)*p10;
			N[i] = '0';
			s = 0;
			for(int j = i-1; j >= 0; j--){
				if(N[j] == '9') N[j] = '0';
				else {
					N[j]++;
					break;
				}
			}
			loop(j, i) s += N[j] - '0';
			if(s <= ts){
				printf("%lld\n", ans);
				return;
			}
		}
		assert(0);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
