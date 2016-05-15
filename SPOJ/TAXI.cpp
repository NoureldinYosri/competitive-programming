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

int C[1000][1000];
int Z[1000][1000];
vi G[1000];
int m,n;
pair<ll,ll> People[1000],TAXI[1000];
int V[1000];

bool bfs(vi & P){
	P.clear();
	fill(V,V + n + m + 10,-2);	
	V[0] = -1;
	queue<int> q;
	q.push(0);
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(u == n + m + 1) {
			while(u != -1){
				P.pb(u);
				u = V[u];
			}
			reverse(all(P));
			return 1;
		}
		for(int v : G[u])
			if(C[u][v] && V[v] == -2){
				V[v] = u;
				q.push(v);
			}
	}
	return 0;
}

int solve(){
	int f = 0;
	vi P;
	while(bfs(P)){
		++f;
		loop(i,sz(P) - 1){
			int u = P[i],v = P[i + 1];
			C[u][v]--;
			C[v][u]++;
		}
	}
	return f;
}

void add_edge(int a,int b){
	G[a].pb(b);  C[a][b] = Z[a][b] = 1;
	G[b].pb(a);  C[b][a] = Z[b][a] = 0;
}

int main(){
	int T;
	ll s,c;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %lld %lld",&m,&n,&s,&c);
		loop(i,m + n + 3) G[i].clear();	
		loop(i,m) {
			scanf("%lld %lld",&People[i + 1].xx,&People[i + 1].yy);
			add_edge(0,i + 1);
		}
		loop(i,n){
			scanf("%lld %lld",&TAXI[i + m + 1].xx,&TAXI[i + m + 1].yy);
			loop(j,m){
				ll dist = abs(TAXI[i + m + 1].xx - People[j + 1].xx) + abs(TAXI[i + m + 1].yy - People[j + 1].yy);
				dist *= 200;			
				if(dist <= c*1LL*s) add_edge(j + 1,i + m + 1);
			}
			add_edge(i + m + 1,n + m + 1);
		}
		printf("%d\n",solve());
	}
	return 0;
}
