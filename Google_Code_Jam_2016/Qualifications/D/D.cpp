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

ll POW(ll x,int y){
	if(y == 0) return 1;
	if(y == 1) return x;
	return POW(x*x,y >> 1) * POW(x,y & 1);
}

int main(){
	int T,K,C,S;
	scanf("%d",&T);
	loop(t,T){
		scanf("%d %d %d",&K,&C,&S);
		printf("Case #%d:",t + 1);
		if(S < K){
			puts(" IMPOSSIBLE");
			continue;
		}
		ll s = 1,e = POW(K,C),M = e,step = POW(K,C - 1); int c = 0;				
		while(S && s <= M && e > 0){
			if(c == 0) {
				printf(" %lld",s);
				s += step;
				if(step != 1) s++;
			}
			else {
				printf(" %lld",e);
				e -= step;
				if(step != 1) e --;
			}
			S--;
			c ^= 1;
		}
		puts("");
	}	
	return 0;
}
