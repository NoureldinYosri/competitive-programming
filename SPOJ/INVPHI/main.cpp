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

const int MAXA = 100*1000*1000 + 1;
int prime[MAXA + 1];
map<int,ll> mem;

void sieve(){
	for(int i = 2;i <= MAXA;i++)
		if(prime[i] == 0) {
			prime[i] = i;
			for(ll j = i*1LL*i;j <= MAXA;j += i)
				prime[j] = i;
		}
}

ll solve(int n,vi & divs){
	if(n == 1) return 1;
	if(mem.find(n) != mem.end()) return mem[n];
	ll & ret = mem[n];
	int N = n;
	if(divs.empty()) {
		divs.push_back(1);
		while(n > 1) {
			int p = prime[n],e = 0;
			while(n%p == 0) n /= p,e++;
			for(int i = 0,L = sz(divs);i < L;i++){
				int q = 1;
				for(int j = 1;j <= e;j++) {
					q *= p;
					divs.push_back(q*divs[i]);
				}
			}
		}
	}

	ret = -1;
	for(int d : divs) if(N%d == 0){
		int p = d + 1;
		if(prime[p] == p) {
			int m = N/d;
			ll q = p;
			ll tmp = (m == N) ? -1 : solve(m,divs);
			if(tmp > 0 && tmp%p && (ret == -1 || tmp*q < ret)) ret = tmp*q;
			while(m%p == 0) {
				m /= p;
				q *= p;
				tmp = solve(m,divs);
				if(tmp < 0 || tmp%p == 0) continue;
				if(ret == -1 || tmp*q < ret) ret = tmp*q;
			}
		}
	}

	return ret;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	int T; scanf("%d",&T);
	while(T--) {
		int n ; scanf("%d",&n);
		vi divs;
		printf("%lld\n",solve(n,divs));
	}

	return 0;
}
