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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 1 << 20;
vi P;
int prime_factor[MAX];
map<int,vp> dp;

void sieve(){
	for(int i = 2;i < MAX;i++)
		if(!prime_factor[i]) {
			prime_factor[i] = i;
			P.pb(i);
			for(ll j = i*1LL*i; j < MAX; j+=i)
				prime_factor[j] = i;
		}
}

vp factor(int n){
	if(dp.find(n) != dp.end()) return dp[n];
	int N = n;
	vp ret;
	int cur = 0;
	while(n >= MAX && cur < sz(P) && P[cur]*1LL*P[cur] <= n) {
		int ctr = 0;
		while (n%P[cur] == 0){
			ctr++;
			n /= P[cur];
		}
		if(ctr) ret.pb(mp(P[cur], ctr));
		cur++;
	}
	if(n < MAX) {
		while(n > 1) {
			int p = prime_factor[n],e = 0;
			while(n%p == 0) {
				e++;
				n /= p;
			}
			ret.pb(mp(p,e));
		}
	}
	if(n != 1) ret.pb(mp(n,1));
	dp[N] = ret;
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	int T; scanf("%d",&T);
	while(T--){
		int a,b; scanf("%d %d",&a,&b);
		if(a > b) swap(a,b);
		int g = __gcd(a,b);
		vp primes = factor(g);
		a /= g,b /= g;
		bool can = 1;
		for(auto it : primes){
			int p = it.xx,e = it.yy;
			int q1 = e,q2 = e;
			while(a%p == 0) a /= p,q1++;
			while(b%p == 0) b /= p,q2++;
			//cerr << p << " " << q1 << " " << q2 << endl;
			int bx = 2*q2 - q1;
			if(bx%3 || bx < 0) can = 0;
			else {
				bx /= 3;
				int ax = q2 - 2*b;
				if(ax < 0) can = 0;
			}
		}
//		cerr << a << " " << b << endl;
		if(a != 1 || b != 1) can = 0;
		puts(can ? "Yes" : "No");
//		break;
	}
	return 0;
}
