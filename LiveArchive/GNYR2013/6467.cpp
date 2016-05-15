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
using namespace std;

vi G[1 << 10];

int dfs(int u){
	if(sz(G[u]) == 0) return 1;
	int best = 0,ctr = 0;	
	loop(i,sz(G[u])){
		int v = G[u][i];
		int f = dfs(v);
		if(f > best) best = f,ctr = 1;
		else if(f == best) ctr++;
	}
	return best + (ctr > 1);
}

int main(){
	pre();
	int T,K,N,M,a,b;	
	cin >> T;
	while(T--){
		cin >> K >> N >> M;
		fill(G,G + N,vi());
		loop(i,M){
			cin >> a >> b;
			G[b].pb(a);
		}
		cout << K << " " << dfs(N) << endl;
	}
	return 0;
}
