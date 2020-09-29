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


vi primes;

bool is_prime(int x){
	for(int p : primes)
		if(x%p == 0)
			return 0;
	return x > 1;
}

set<int> F[111];

bool check(const set<int> & A, const set<int> & B){
	for(int x : A) if(B.count(x)) return 0;
	return 1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; cin >> n;
	int m = n/2;
	
	for(int x = 2; sz(primes) < 150; x++)
		if(is_prime(x))
			primes.pb(x);
	


	for(int i = 1, k = 0, cnt = 0; i <= n;i ++){
		for(int j = i+1; j <= n; j++) if(check(F[i], F[j])) {
			if(cnt == 0) F[i].insert(k), cnt++;
			F[j].insert(k);
			cnt++;
			if(cnt == m) {
				k++;
				cnt=  0;
			}
		}
		k += cnt != 0;
		cnt = 0;
	}
	
	int mx=  0;
	for(int i = 1; i <= n;i++) {
		mx = max(mx, sz(F[i]));
	}
	cout << mx << endl;
	
//	for(int i = 1; i <= n;i++) printf("%lld\n", F[i]);

	return 0;
}
