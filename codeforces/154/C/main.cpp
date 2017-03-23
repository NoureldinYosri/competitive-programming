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

const int MAX = 1000*1000;
vi G[MAX + 1];
int deg[MAX + 1],n;
int ord[MAX + 1];
int XOR[MAX + 1],cnt[MAX + 1];
ll h[MAX + 1],h2[MAX + 1],mod = 1e9 + 7,base = 2;
vl H[MAX + 1];

int main(){
	int m; scanf("%d %d",&n,&m);
	while(m--){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
		deg[a]++;
		deg[b]++;
		XOR[a] ^= b;
		XOR[b] ^= a;
		h[a] += b;
		h[b] += a;
	}
	range(i,1,n) {sort(all(G[i]));}
	range(u,1,n){
		ll mul = base;
		for(int v : G[u]){
			h2[u] = (v*mul + h2[u])%mod;
			H[u].pb(h2[u]);
			mul <<= 1;
			if(mul >= mod) mul -= mod;
		}
	}
	loop(i,n) ord[i] = i + 1;
	sort(ord,ord + n,[](const int & a,const int & b){
		return tie(deg[a],XOR[a],h[a],G[a]) < tie(deg[b],XOR[b],h[b],G[b]);
	});

	
	ll ans = 0;
	loop(i,n){
		int j = i;
		while(j < n && deg[ord[j]] == deg[ord[i]] && XOR[ord[j]] == XOR[ord[i]] && h[ord[j]] == h[ord[i]] && h2[ord[j]] == h2[ord[i]]) j++;
		// O(blk*log(blk)*deg)
		// blk < n/deg
		// O(n/deg * log(n)*deg -> O(n log n)
		/*for(;i < j;){
			int k = i;
			while(k < j && G[ord[i]] == G[ord[k]]) k++;
			int len = k - i;
			ans += len*(len - 1LL)/2; 
			i = k;
		}*/
		ans += (j - i)*(j - i - 1LL)/2;
		i = j;
		i--;
	}

	for(int u = 1;u <= n;u++){
		for(int v : G[u])
			if(u < v && deg[u] == deg[v] && XOR[u]^v == XOR[v]^u && h[u] - v == h[v] - u && cnt[u] == cnt[v]){
				int i = lower_bound(all(G[u]),v) - G[u].begin();
				int j = lower_bound(all(G[v]),u) - G[v].begin();
				ll x = H[u].back() - H[u][i],y = H[v].back() - H[v][j];
				if(x < 0) x += mod;
				if(y < 0) y += mod;
				x = (x*500000004)%mod;
				y = (y*500000004)%mod;
				x += i ? H[u][i - 1] : 0;
				y += j ? H[u][j - 1] : 0;
				if(x >= mod) x -= mod;
				if(y >= mod) y -= mod;
				ans += x == y;
			}
		for(int v : G[u]) cnt[v]++;	
	}

	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
