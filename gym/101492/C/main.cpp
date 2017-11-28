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

const int MAXA = 500*1000,MAXN = 50*1000 + 10;
int prime[MAXA+1];
vi who[MAXA+1];
vi primes[MAXA + 1];
int A[MAXN],n;
vi ST[MAXN*4];

void sieve() {
	for(int i = 2;i <= MAXA;i++) {
		if(!prime[i]) {
			prime[i] = i;
			for(ll j = i*1LL*i;j <= MAXA;j += i)
				prime[j] = i;
		}
		for(int n = i;n > 1;) {
			int p = prime[n];
			primes[i].pb(p);
			while(n%p == 0) n /= p;
		}
	}
}

void build(int node,int s,int e) {
	for(int k = s;k <= e;k++)
		ST[node].pb(A[k]);
	sort(all(ST[node]));
	if(s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
}

bool query(int node,int s,int e,int l,int r,int val) {
	if(l <= s && e <= r) {
		auto p = lower_bound(all(ST[node]),val);
		if(p == ST[node].end()) return 0;
		else return 1;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,val);
	if(m < l) return query(right,m+1,e,l,r,val);
	return query(left,s,m,l,m,val) || query(right,m+1,e,m+1,r,val);
}

int getCnt(int target,vi & P) {
	int cnt = 0;
	for(int msk = 1;msk < (1 << sz(P));msk++){
		int p = 1,sgn = -1;
		loop(i,sz(P))
			if(msk & (1 << i))
				p *= P[i],sgn *= -1;
		int v = upper_bound(all(who[p]),target) - who[p].begin();
		cnt += sgn*v;
	}
	assert(cnt <= target);
	return cnt;
}

void insert(int x,int i) {
	for(int msk = 1;msk < (1 << sz(primes[x]));msk++){
		int p = 1;
		loop(i,sz(primes[x]))
			if(msk & (1 << i))
				p *= primes[x][i];
		who[p].pb(i);
	}
}

bool goUp(int target,int gr,vi & P) {
	int d = getCnt(target-1,P),u = getCnt(target + gr,P);
	int diff = u - d;
	int avail = gr + 1;
	return diff < avail;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	int m; scanf("%d %d",&n,&m);
	range(i,1,n) {
		int x; scanf("%d",&x);
		if(getCnt(i-1,primes[x]) < i-1) {
			int s = 0,e = i - 1;
			while(s < e) {
				int mid = s + (e - s + 1)/2;
				if(goUp(mid,i-1-mid,primes[x])) s = mid;
				else e = mid - 1;
			}
			A[i] = s;
		}
		insert(x,i);
	}

//	prArr(A+1,n,int);

	build(1,1,n);
	while(m--) {
		int l,r; scanf("%d %d",&l,&r);
		puts(query(1,1,n,l,r,l) ? "S" : "N");
	}
	return 0;
}
