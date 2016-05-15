#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

pair<int,ll> P[1 << 20]; int n;
int A[1 << 20];

ll solve(int s,int e){
	cerr << s << " " << e << endl;
	int m = (s + e) >> 1;
	ll d = 1LL << 60;
	if(m - s >= 1 && e - m - 1 >= 1) d = min(solve(s,m),solve(m + 1,e));
	bool c = 0;
	while(s <= e && abs(P[s].xx - P[m].xx) >= d) s++,c = 1;
	while(s <= e && abs(P[e].xx - P[m].xx) >= d) e--,c = 1;
	if(c && s < e)
		for(;s <= e;s++) 
			for(int i = s + 1;i <= e;i++) 
				d = min(d,(P[s].xx - P[i].xx)*(P[s].xx - P[i].xx)+(P[s].yy - P[i].yy)*(P[s].yy - P[i].yy));
	return d;
}

int main(){
	  while(scanf("%d",&n) == 1){
		loop(i,n){
			scanf("%d",A + i);
			P[i].xx == i + 1;
			P[i].yy = (i ? P[i - 1].yy : 0) + A[i];
		}
		printf("%lld\n",solve(0,n - 1));
	}
	return 0;
}
