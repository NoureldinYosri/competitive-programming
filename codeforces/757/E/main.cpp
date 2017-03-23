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

const int MAX = 1e6 + 1e2,mod = 1e9 + 7;
int f[MAX*2],inv[MAX*2];
int prime[MAX];

int mul(int x,int y){
	return (x*1LL*y)%mod;
}

void sieve(){
	range(i,2,MAX-1)
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*1LL*i;j < MAX;j += i)
				prime[j] = i;
		}
}

int POW(int x,int p){
	if(!p) return 1;
	int y = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}

int main(){
	f[0] = inv[0] = 1;
	loop(i,MAX*2-1) {
		f[i+1] = mul(f[i],i+1);
		inv[i+1] = POW(f[i+1],mod - 2);	
	}
	sieve();
	int q; scanf("%d",&q);
	while(q--){
		int r,n; scanf("%d %d",&r,&n);
		int ans = 1;
		while(n > 1){
			int p = prime[n],e = 0;
			while(n%p == 0){
				n /= p;
				e++;
			}
			int tmp = mul(f[r + e - 1],r+2*e);
			tmp = mul(tmp,inv[e]);
			tmp = mul(tmp,inv[r]);
			ans = mul(ans,tmp);
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
