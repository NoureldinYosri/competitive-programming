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

int n,m;
int G[19][19];
bool dp[19][19][1 << 19];
int f[1 << 19];

void PRINT(int msk){
	vi cycle;
	loop(i,n) if(msk & (1 << i)) cycle.pb(i + 1);
	print(cycle,int); 
}

int main(){
	loop(i,19) f[1 << i] = i;
	scanf("%d %d",&n,&m);
	loop(i,m){
		int a,b;
		scanf("%d %d",&a,&b); a--,b--;
		G[a][b] = G[b][a] = 1;
	}	
	loop(msk,1 << n){
		if(!msk) continue;
		else if(popcnt(msk) == 1) {
			dp[f[msk]][f[msk]][msk] = 1;
			continue;
		}
		loop(u,n) if(msk & (1 << u)) {
			loop(v,n) if(v != u && (msk & (1 << v))){
				loop(t,n) if(t != u && G[u][t] && (msk & (1 << t))){
					dp[u][v][msk] |= dp[t][v][msk ^ (1 << u)]; 
				}
			} 
		}
	}
	int ans = 0;
	loop(msk,1 << n) {
		if(!msk) continue;
		if(popcnt(msk) <= 2) continue;
		int u = f[LSOne(msk)];
		int c = 0;
		loop(v,n) if(G[u][v]) ans += dp[v][u][msk];
		ans += c;
		if(c) PRINT(msk);	
	}
	cout << ans << endl;
	return 0;
}
