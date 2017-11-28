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

const int MAX = 100000 + 10,MAXA = 100000 + 10;
vi E[MAX];
int n;
int fr[MAX],to[MAX],C[MAX];
ll ans;
int prime[MAXA];
vi divs[MAXA];

void sieve(){
	int f = 0;
	divs[1].pb(1);
	for(int i = 2;i < MAXA;i++){
		if(prime[i] == 0) {
			prime[i] = i;
			for(ll j = i*1LL*i;j < MAXA;j += i)
				prime[j] = i;
		}
		int p = prime[i],e = 0,N = i;
		while(N%p == 0) N /= p,e ++;
		divs[i].reserve(sz(divs[N])*(e+1));
		for(int x : divs[N])
			for(int j = 0,q = 1;j <= e;j++,q *= p)
				divs[i].pb(x*q);
		int g = 0;
		for(int x : divs[i])
			g += sz(divs[x]);
		f = max(f,g);
	}
	cout << "max = " << f << endl;
}

void clean(){
	range(i,1,n) E[i].clear();
}

map<int,int> dfs(int u,int p) {
	map<int,int> f;
	f[0] = 0;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		map<int,int> tmp = dfs(v,u);
		for(auto p : tmp) {
			int a = p.xx;
			int b = __gcd(a,C[e]);
			f[b] = max(f[b],tmp[a] + 1);
		}
	}
	for(auto p : f)
		ans = max(ans,p.xx*1LL*f[p.yy]);
	return f;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	return 0;
}
