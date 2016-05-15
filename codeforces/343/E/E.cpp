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

const int MAX = 3e5;
int P[MAX][22],dfs_P[MAX],IDX[MAX],NUM[MAX],D[MAX],NUM2[MAX];
ll SUM[MAX],SUM2[MAX];
vi G[MAX];
int n,m;
pi fr[MAX];

void bfs(){
	queue<int> q;
	q.push(1);
	while(!q.empty()){
		int u = q.front();	q.pop();
		for(int v : G[u])
			if(v != P[u][0]){
				P[v][0] = u;
				D[v] = D[u] + 1;
				loop(i,21) P[v][i + 1] = P[P[v][i]][i];
				q.push(v);
			}
	}
}

int lca(int a,int b){
	int k = 0;
	while(a != b){			
		if(D[a] > D[b]) swap(a,b);
		while(D[P[b][k]] > D[a]) k++;
		while(k && D[P[b][k]] <= D[a]) k--;
		while(k && P[b][k] == 0) k--;
		b = P[b][k];
	}
	return a;
}

int dist(int a,int b){
	int p = lca(a,b);
	return D[a] + D[b] - 2*D[p];
}

void dfs(){
	int u = 1;
	while(u){
		if(IDX[u] == sz(G[u])){
			int p = dfs_P[u];
			NUM[u]++;
			SUM[p] += SUM[u] + NUM[u];
			NUM[p] += NUM[u];
			u = p;
			continue;
		}
		int v = G[u][IDX[u]++];
		if(v == dfs_P[u]) continue;
		dfs_P[v] = u;
		u = v;
	}
}

void bfs2(){
	queue<int> q;
	q.push(1);
	NUM2[1] = 1;				
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : G[u]){
			if(v != P[u][0]){
				NUM2[v] = NUM2[u] + NUM[u] - NUM[v];				
				SUM2[v] = SUM2[u] + SUM[u] - SUM[v] - NUM[v] + NUM2[v] - 1;
				q.push(v);
			}
		}
	}
}

int f(int x){
	int i = 0;
	while(x != (1 << i)) i++;
	return i;
}

int get2(int a,int d){
	while(d){
		a = P[a][f(LSOne(d))];
		d -= LSOne(d);
	}
	return a;
}

int main(){		
	scanf("%d %d",&n,&m);
	int a,b;	
	loop(i,n - 1){
		scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}	
	loop(i,m) scanf("%d %d",&fr[i].xx,&fr[i].yy);
	bfs();
	dfs();
	bfs2();
	loop(i,m){
		a = fr[i].xx,b = fr[i].yy;
		int p = lca(a,b);
		if(p == a || p == b){
			if(p == b) swap(a,b);			
			double ans = 1 + dist(a,b);
			ans += SUM[b]*1.0/NUM[b];
			a = get2(b,D[b] - D[a] - 1);	
			ll tmp_sum = SUM[p] + SUM2[p] - SUM[a] - NUM[a];
			ll tmp_num = NUM[p] + NUM2[p] - NUM[a] - 1;
			ans += tmp_sum*1.0/tmp_num;
			printf("%.9f\n",ans);	
		}
		else{
			double ans = 1 + dist(a,b);
			ans += SUM[a]*1.0/NUM[a];
			ans += SUM[b]*1.0/NUM[b];;
			printf("%.9f\n",ans);
		}
	}
	return 0;
}

