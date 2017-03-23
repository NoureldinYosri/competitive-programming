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


const int MAX = 1 << 20;

vi G[MAX],rG[MAX];
string name[MAX];
int n,m;
int ord[MAX],dfs_time;
int id[MAX];
int f[MAX],vis[MAX];

int NOT(int a){
	if(a < m) return a + m;
	else return a - m;
}

void add_edge(int a,int b){
	G[a].pb(b);
	rG[b].pb(a);
}

void add_sat_edge(int a,int b){
	add_edge(NOT(a),b);
	add_edge(NOT(b),a);	
}

void build_graph(){
	for(int i = 0;i < m;i += 2){
		add_sat_edge(i,i + 1);
		add_sat_edge(NOT(i),NOT(i + 1));
	}
	for(int i = 0;i < m;i++)
		for(int j = 0;j < m;j++)
			if(name[i] == name[j] && i != j) 
				add_sat_edge(NOT(i),NOT(j));
	for(int i = 0;i < m;i += 2)
		for(int j = 0;j < m;j += 2)
			if(name[i] == name[j] && i != j){
				add_sat_edge(NOT(i),NOT(j + 1));
			}
}

void dfs(int u){
	vis[u] = 1;
	for(int v : G[u]) if(!vis[v]) dfs(v);
	ord[dfs_time++] = u;
}

void dfs(int u,int k){
	id[u] = k;
	vis[u] = 1;
	for(int v : rG[u]) if(!vis[v]) dfs(v,k);
}

int main(){
	scanf("%d",&n);
	loop(i,n){
		string u,v; cin >> u >> v;
		name[2*i] = u.substr(0,3);
		name[2*i + 1] = u.substr(0,2) + v.substr(0,1);
	}
	m = 2*n;
	build_graph();
	dfs_time = 0;
	for(int i = 0;i < 2*m;i++) if(!vis[i]) dfs(i);
//	assert(dfs_time == 2*m);
	reverse(ord,ord + dfs_time);
	int ctr = 0;
	memset(vis,0,sizeof vis);
	for(int i = 0;i < 2*m;i++) if(!vis[ord[i]]) dfs(ord[i],ctr++);
	
	for(int i = 0;i < m;i++) if(id[i] == id[i + m]) {
		puts("NO");
		return 0;
	}
	for(int i = 0;i < m;i++)
		if(id[i] < id[i + m]) f[i] = 0;
		else f[i] = 1;

	puts("YES");
	for(int i = 0;i < n;i++){
	//	assert(f[2*i] != -1 && f[2*i + 1] != -1);
	//	assert(f[2*i] ^ f[2*i + 1]);
		if(f[2*i]) printf("%s\n",name[2*i].c_str());
		else printf("%s\n",name[2*i + 1].c_str());
	}	
	return 0;
}
