#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1e5 + 1e2,mod = 1e9 + 7;
int prime[MAX + 1];
int P[MAX],cnt;
int dp[MAX + 1],id[MAX + 1];
int t;

void sieve(){
	for(int i = 2;i <= MAX;i++)
		if(!prime[i]){
			prime[i] = i; P[cnt++] = i;
			for(ll j = i*1LL*i;j <= MAX;j += i)
				prime[j] = i;
		}	
}

int POW(int x,int k){
	if(!k) return 1;
	int y = 1;
	for(;k > 1;k >>= 1){
		if(k & 1) y = (y*1LL*x)%mod;
		x = (x*1LL*x)%mod;
	}
	return (x*1LL*y)%mod;
}

#define mul(x,y) (((x%mod)*1LL*(y%mod))%mod)


int func(int tmp,int p,int ctr,int k){
	if(id[tmp] == t) return dp[tmp];
	id[tmp] = t;
	int r = POW(p,k);
	int q = POW(r,ctr + 1) - 1; if(q < 0) q += mod;
	r--; if(r < 0) r += mod; r = POW(r,mod - 2);
	return dp[tmp] = mul(q,r);
}

int G(int n,int k){
	int ret = 0;
	loop(i,cnt){
		if(P[i] > n) break;
		int p = P[i],pk = POW(p,k),pke = pk,pe = p;
		int sum = 1,sgn = 1;
		while(pe <= n){
			sum += pke; if(sum >= mod) sum -= mod;
			int tmp = mul(sum,(n/pe - n/(pe * 1LL * p)));
			ret += (2*sgn - 1)*tmp;
			if(ret >= mod) ret -= mod;
			if(ret < 0) ret += mod;
			pke = mul(pke,pk);
			if(pe <= n/p) pe *= p;
			else break;
		//	sgn ^= 1;
		}
		cerr << p << " " << ret << endl;
	}
	ret ++;
	if(ret >= mod) ret -= mod;
	return ret;
}


int main(){
	sieve();/*
	int T; scanf("%d",&T);
	for(t = 1;t <= T;t++){
		int a,b,k,ans = 0; scanf("%d %d %d",&a,&b,&k);
		int x = G(b,k),y = G(a-1,k);
		x -= y;
		if(x < 0) x += mod;
		printf("%d\n",x);
	}	*/
	cerr << G(6,1) << endl;
	
	
	return 0;
}
