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

int T,L,M,N,D;
int A[1 << 20];

bool can(ll t){
	ll ctr = 0;
	loop(i,N){
		if(t/A[i] >= L - ctr) return 1;
		ctr += t / A[i];
	}
	return 0;
}

int main(){
	scanf("%d",&T);
	loop(t,T){
		scanf("%d %d %d %d",&L,&N,&M,&D); M = min(M,L);
		loop(i,N) scanf("%d",A + i);
		sort(A,A + N);
		ll s = 0,e = LLONG_MAX;
		while(s < e){
			ll m = s + ((e - s) >> 1);
			if(can(m)) e = m;
			else s = m + 1;
		}
		multiset<ll> dryers; int tot = 0;
		vector<ll> machines;		
		loop(i,M) dryers.insert(0LL);
		loop(i,N){
			int m = min(s/A[i],L - tot + 0LL); tot += m;
			loop(j,m) machines.pb(A[i] * (j + 1LL));
		}
		ll ans = 0;
		sort(all(machines));
		for(ll t : machines){
			auto p = dryers.begin();
			ll tx = max(t,*p) + D;
			ans = max(tx,ans);
			dryers.erase(p);
			dryers.insert(tx);
		}
		printf("Case #%d: %lld\n",t+1,ans);
	}
	return 0;
}
