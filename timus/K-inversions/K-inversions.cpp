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

const ll mod = 1e9;
ll dp[11][20000 + 1];
int A[20000],n,K;

void update(int p,ll v,ll *T){
	for(;p <= 20000;p += LSOne(p)) T[p] = (T[p] + v)%mod;
}

ll get(int p,ll *T){
	ll ret = 0;
	for(;p;p -= LSOne(p)) ret = (ret + T[p])%mod;
	return ret;
}

ll solve(){
	loop(i,n){
		for(int k = K;k > 1;k--){
			ll v = get(A[i] - 1,dp[k - 1]);
			update(A[i],v,dp[k]);
		}
		update(A[i],1,dp[1]);
	}	
	return get(20000,dp[K]);
}

int main(){
	scanf("%d %d",&n,&K);
	loop(i,n) scanf("%d",A + i),A[i] = n - A[i] + 1;
	printf("%lld\n",solve());
	return 0;
}
