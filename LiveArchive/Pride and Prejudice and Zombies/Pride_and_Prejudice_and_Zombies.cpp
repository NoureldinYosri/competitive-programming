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

ll n,p10[12];
int q;

bool solve(int i,int & x,int & y,int l1,int l2,int *ctr){
	if(i == q) return x*1LL*y == n;
	loop(d1,10){
		if(d1 == 0 && l1 == 0) continue;
		ctr[d1]--;
		loop(d2,10){
			if(d2 == 0 && l2 == 0) continue;
			if(i == 9 && (d1 == 0 || d2 == 0)) continue;
			ctr[d2]--;
			if(ctr[d1] >= 0 && ctr[d2] >= 0){
				x = d1*p10[i] + x;
				y = d2*p10[i] + y;
				ll p = x*1LL*y;				
				if(n%p10[i + 1] == p%p10[i + 1]){
					if(solve(i + 1,x,y,d1,d2,ctr)) return 1;
				}
				x -= d1*p10[i];
				y -= d2*p10[i];
			}
			ctr[d2]++;
		}
		ctr[d1]++;
	}
	return 0;
}

int main(){
	int x,y;
	p10[0] = 1;
	loop(i,11) p10[i + 1] = p10[i] * 10;
	while(scanf("%lld",&n) == 1 && n){
		q = x = y = 0;
		int ctr[10]; fill(ctr,ctr + 10,0);
		ll m = n;
		while(m) ctr[m%10]++,m /= 10,q++;
		q >>= 1;
		printf("%lld: %s\n",n,solve(0,x,y,-1,-1,ctr) ? "yes" : "no");
	}
	return 0;
}
