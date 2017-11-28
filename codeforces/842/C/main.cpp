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

const int MAX = 200*1000 + 10;
int prime[MAX],A[MAX],n;
vi divs[MAX],G[MAX],primes[MAX];
int cnt[MAX],ans[MAX],g[MAX];

void sieve(){
	divs[1].pb(1);
	for(int i = 2;i < MAX;i++){
		if(!prime[i]) {
			prime[i] = i;
			for(ll j = i*1LL*i;j < MAX;j += i)
				prime[j] = i;
		}
		int p = prime[i],q = 0,n = i,pe = 1;
		while(n%p == 0) n /= p,q++,pe *= p;
		divs[i] = divs[n];
		primes[i] = primes[n];
		primes[i].pb(pe);
		int s = 0,e = sz(divs[n]);
		while(q--) {
			for(;s < e;s++) divs[i].pb(divs[i][s]*p);
			e += sz(divs[n]);
		}
	}
}


void dfs(int u,int p,int depth = 0,int zeros = 0){
	for(int div : divs[A[u]]) cnt[div]++;
	zeros += A[u] == 0;
	for(int div : divs[A[u]]){
		if(cnt[div] + zeros >= depth) ans[u] = max(ans[u],div);
	}
	for(int div : divs[A[p]]){
		if(cnt[div] + zeros >= depth) ans[u] = max(ans[u],div);
	}
	for(int v : G[u]) if(v != p) dfs(v,u,depth + 1,zeros);
	for(int div : divs[A[u]]) cnt[div]--;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	scanf("%d",&n);
	range(i,1,n) scanf("%d",A + i);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	range(i,1,n) printf("%d ",ans[i]);
	return 0;
}
