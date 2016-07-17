#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

const int MAXN = 100010,MAXA = 2000000;
int head[MAXN],nxt[MAXN << 1],to[MAXN << 1],edgeCnt = 1;
int prime_factor[MAXA + 1],factors[70],numFactors;
int value[MAXN],nodeTime[MAXN],dfs_time = 0;
int n,m;
vector<pi> nodes[MAXA + 1];
int ansDepth[MAXN],ans[MAXN];

void sieve(){
	loop(i,MAXA + 1) prime_factor[i] = i;
	for(ll i = 2;i <= MAXA;i++)
		if(prime_factor[i] == i){
			for(ll j = i*i;j <= MAXA;j += i)
				prime_factor[j] = i;
		}
}

void factorize(int n){
	numFactors = 0;
	while(n > 1){
		int p = prime_factor[n];
		factors[numFactors++] = p;
		while(n%p == 0) n /= p;
	}
}

void add_edge(int a,int b){
	to[edgeCnt]  = b;
	nxt[edgeCnt] = head[a];
	head[a] = edgeCnt++;
}

void addBiEdge(int a,int b){
	add_edge(a,b);
	add_edge(b,a);
}

void dfs(int u,int p = 0,int depth = 0){
	ans[u] = ansDepth[u] = -1;
	factorize(value[u]);
	loop(i,numFactors) {
		if(!nodes[factors[i]].empty()) if(ansDepth[u] < nodes[factors[i]].back().xx) 
			ans[u] = nodes[factors[i]].back().yy,ansDepth[u] = nodes[factors[i]].back().xx;	
		nodes[factors[i]].pb(mp(depth,u));		
	}
	for(int e = head[u];e;e = nxt[e]) if(to[e] != p) dfs(to[e],u,depth + 1);
	factorize(value[u]);
	loop(i,numFactors) nodes[factors[i]].pop_back();
}


int main(){
	sieve();
	int a,b,type,u,v;
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",value + i + 1);
	loop(i,n - 1){
		scanf("%d %d",&a,&b);
		addBiEdge(a,b);
	}	
	dfs(1);
	while(m--){
		scanf("%d %d",&type,&u);
		if(type == 2){
			scanf("%d",&v);
			value[u] = v;
			dfs(1);
		}
		else printf("%d\n",ans[u]);
	}
	return 0;
}
