#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

ll A,B,T,N;
ll S[1 << 20],C[1 << 20];

double f(ll Z){
	ll s = S[N - 1]; double ans = 0.0;
	if(Z < s){
		loop(i,N){
			if(Z < S[i]) {
				if(i) Z -= S[i - 1];
				return ans + Z*Z/2.0;
			}
			ans += C[i]*C[i]/2.0;
		}
		return Z*Z/2.0;
	}	
	loop(i,N) ans += C[i]*C[i] / 2.0;
	return ans * (Z/s) + f(Z%s);
}

int main(){
	scanf("%lld",&T); 
	loop(t,T){
		scanf("%lld %lld %lld",&N,&A,&B);
		loop(i,N) scanf("%lld",S + i),C[i] = S[i];
		loop(i,N) S[i] += i ? S[i - 1] : 0;
		printf("Case #%d: %.9lf\n",t + 1,(f(B) - f(A))/(B - A + 0.0));
	}
	return 0;
}