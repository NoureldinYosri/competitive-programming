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

inline int POW(int x,int p,int mod){
	if(!p) return 1;
	int y = 1,debug = x == 8 && p == 99;
	for(;p > 1;p >>= 1){
		if(p & 1) y = (x*1LL*y)%mod;
		x = (x*1LL*x)%mod;
	}
	x = (x*1LL*y)%mod;
	return x;
}

int main(){
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
	int n,k;
	scanf("%d %d",&n,&k);
	int ans = 0,K = k;
	vector<pair<pi,int> > fact;
	for(int i = 2;i*i <= k;i++) if(k%i == 0) {
		int p = i,q = 1,e = 0;		
		while(k%i == 0){
			q *= p;
			k /= i;
			e++;
		}
		fact.pb(mp(mp(p,q),e));
	}
	if(k != 1) fact.pb(mp(mp(k,k),1));
	for(auto pr : fact){
		int p = pr.xx.xx,q = pr.xx.yy,e = pr.yy;
		if(p == 2){
			// 2^n >= e
			int lg = 0;
			while((1 << lg) < e) lg++;
			if(n >= lg) continue;
		}
		int phi = q - q/p;
		int ex = POW(2,n,phi);
		int a = POW(2,ex,q);
		a = (a*1LL*(K/q))%K;
		a = (a*1LL*POW(K/q,phi - 1,q))%K;
		ans += a;
		if(ans >= K) ans -= K;
	}
	ans ++; if(ans == K) ans = 0;
	cerr << ans << endl;
	return 0;
}
