#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int MAX = 200000 + 1e2;
const int MAXLG = 20;
int N,K;
int head[MAX][2],nxt[MAX << 1][2],to[MAX << 1][2],weight[MAX << 1][2],edgeCnt[2];
int LCAPOS[MAX],vertex[MAX << 1],level[MAX << 1],RMQ[MAX << 1][MAXLG],lg[MAX << 1];
ll HEIGHT[MAX],DEPTH[MAX];
int CenterLevel[MAX],vis[MAX];

void init(){
	memset(head,-1,sizeof head);
	
}

void add_edge(int a,int b,int c = 0,int q = 1){
	int & pos = edgeCnt[q];
	to[pos][q] = b;
	weight[pos][q] = c;
	nxt[pos][q] = head[a][q];
	head[a][q] = pos++;
}

void addBiEdge(int a,int b,int c){
	add_edge(a,b,c,0);
	add_edge(b,a,c,0);
}

inline void record(int u,ll depth,ll height,int & idx){
	vertex[idx] = u;
	level[idx] = height;
	HEIGHT[u] = height;
	DEPTH[u] = depth;
	LCAPOS[u] = idx++;
}

void dfsLCA(int u,int p,ll depth,ll height,int & idx){
	record(u,depth,height,idx);
	for(int e = head[u][0]; ~e ;e = nxt[e][0]){
		int v = to[e][0],w = weight[e][0];
		if(v != p){
			dfsLCA(v,u,depth + 1,height + w,idx);
			record(u,depth,height,idx);
		}
	}
}

inline int get_min(int a,int b){
	return (level[a] < level[b]) ? a : b;		
}

void BuildRMQ(int n){
	lg[0] = -1;
	loop(i,n) lg[i + 1] = lg[i] + ((i + 1) == LSOne(i + 1));
	loop(i,n) RMQ[i][0] = i;
	loop(k,MAXLG - 1) loop(i,n) {
		RMQ[i][k + 1] = RMQ[i][k];
		if(i + (1 << k) < n) RMQ[i][k + 1] = get_min(RMQ[i][k],RMQ[i + (1 << k)][k]);
	}
}

void BuildLCA(){
	int idx = 0;
	dfsLCA(1,0,0,0,idx);
	BuildRMQ(idx);
}


void get_spacing(int a,int b,ll & depth,ll & height){
	int na = a,nb = b;	
	a = LCAPOS[a],b = LCAPOS[b];
	if(a > b) swap(a,b);
	int l = lg[b - a + 1];
	int p = vertex[get_min(RMQ[a][l],RMQ[b - (1 << l) + 1][l])];
	depth = DEPTH[na] + DEPTH[nb] - 2*DEPTH[p];
	height = HEIGHT[na] + HEIGHT[nb] - 2*HEIGHT[p];
}

int dfsCenCnt(int u,int p){
	int ret = 1;
	for(int e = head[u][0]; ~e ;e = nxt[e][0]) {
		int v = to[e][0];
		if(v != p && !CenterLevel[v]) ret += dfsCenCnt(v,u);
	}
	return ret;
}

int dfsCen(int u,int p,int & center,int & parent,int tot){
	vis[u] = 1;
	int is_feasable = 1,subtreesize = 1,tmp;	
	for(int e = head[u][0]; ~e ;e = nxt[e][0]) {
		int v = to[e][0];
		if(v != p && !CenterLevel[v]) {
			tmp = dfsCen(v,u,center,parent,tot);
			is_feasable &= tmp <= (tot/2);
			subtreesize += tmp;
		}
		else if(CenterLevel[v] && CenterLevel[v] > CenterLevel[parent]) parent = v; 
	}
	is_feasable &= (tot - subtreesize) <= (tot/2);
	if(is_feasable) center = u;
	return subtreesize;
}

void CentroidDecomposition(int & tot,int depth){
	if(tot == N) return;
	fill(vis,vis + N + 1,0);
	range(u,1,N) 
		if(!vis[u] && !CenterLevel[u]){
			int subtreesize = dfsCenCnt(u,0),center = u,parent = 0;
			dfsCen(u,0,center,parent,subtreesize);
			CenterLevel[center] = depth;
			add_edge(parent,center);
			tot++;
		}
	CentroidDecomposition(tot,depth + 1);
}

int solve(int u,vi & subtree){
	int ret = INT_MAX,v;
	vi tmpSubTree; vector<pl> vals;
	for(int e = head[u][1]; ~e ; e = nxt[e][1]) {
		v = to[e][1]; tmpSubTree.clear();
		ret = min(ret,solve(v,tmpSubTree));
		for(int t : tmpSubTree) {
			subtree.pb(t);
			ll a,b;
			get_spacing(u,t,a,b);
			vals.pb({b,a});
		}
	}	
	subtree.pb(u); vals.pb(mp(0,0));
	sort(all(vals));
	loop(i,sz(vals)){
		auto p = lower_bound(vals.begin() + i + 1,vals.end(),mp(K - vals[i].xx,-1LL));
		if(p != vals.end() && p->xx == K-vals[i].xx) ret = min(ret + 0LL,p->yy + vals[i].yy);
	}
	return ret;
}

int main(){
	init();
	scanf("%d %d",&N,&K);
	loop(i,N - 1){
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		a++,b++;
		addBiEdge(a,b,c);
	}	
	BuildLCA();
	int tot = 0;
	CentroidDecomposition(tot,1);
	vi t; 
	int ret = solve(to[0][1],t);
	ret = (ret == INT_MAX) ? -1 : ret;
	printf("%d\n",ret);
	return 0;
}
