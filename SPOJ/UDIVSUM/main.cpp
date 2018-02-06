#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 8000*1000;
vi primes;
bool is_compisite[MAX + 1];

void sieve(){
	for(int i = 2;i <= MAX;i++)
		if(!is_compisite[i]) {
			primes.push_back(i);
			for(ll j = i*1LL*i;j <= MAX;j += i)
				is_compisite[j] = 1;
		}
}

int bf(int n) {
	int ret = 0;
	for(int i = 1;i*i <= n;i++)
		if(n%i == 0 && __gcd(i,n/i) == 1)
			ret += i + (n/i != 1)*n/i;
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
//	sieve();
//	int T; scanf("%d",&T);
//	while(T--) {
//		ll n; scanf("%lld\n",&n);
//
//		printf("%llu\n",ans);
//	}
	for(int i = 1,sum = 0;i <= 10;i++) {
		sum += bf(i);
		printf("%d. %d\n",i,sum);
	}
	return 0;
}
