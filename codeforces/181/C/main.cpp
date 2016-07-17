#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,L = (n);i < L;i++)
#define range(i,a,b) for(int i = (a),L = (b);i <= L;i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int mod = 1e9 + 7;
const int MAX = 1000000;
int F[MAX + 1],inv[MAX + 1],n,a,b;
vector<int> good;

int POW(int v,int p){
	int t = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) t = (t*1LL*v)%mod;
		v = (v*1LL*v)%mod;
	}
	return (t*1LL*v)%mod;
}

void init(){
	F[0] = inv[0] = 1;
	range(i,1,MAX){
		F[i] = (F[i - 1]*1LL*i)%mod;
		inv[i] = POW(F[i],mod - 2);
	}
}

int main(){
	init();
	scanf("%d %d %d",&a,&b,&n); if(a < b) swap(a,b);
	range(l,1,8){	
		loop(msk,1 << l){
			int M = 0;
				loop(i,l) 
					if(msk & (1 << i)) M = M*10 + a;
					else M = M*10 + b;
			good.pb(M);			
		}
	}
	int ans = 0,ctr = 10;
	for(int m : good){
		int t = m - b*n;
		if (t >= 0 && t%(a - b) == 0 && t/(a - b) <= n){
			int x = t/(a - b);
			int tmp = (F[n]*1LL*inv[x])%mod;
			tmp = (tmp*1LL*inv[n - x])%mod;
			ans += tmp;
			if(ans >= mod) ans -= mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
