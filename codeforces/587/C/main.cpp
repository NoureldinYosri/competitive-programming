#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 100*1000 + 10;

struct node {
	int siz;
	node *l,*r;
};

node* build(int s,int e){
	node *ret = new node();
	if(s == e) return ret;
	int m = (s + e) >> 1;
	ret->l = build(s,m);
	ret->r = build(m+1,e);
	return ret;
}

node* update(node *root,int s,int e,int p){
	node *ret = new node();
	*ret = *root;
	ret->siz++;
	if(s == e) return ret;
	int m = (s + e) >> 1;
	if(p <= m) ret->l = update(root->l,s,m,p);
	else ret->r = update(root->r,m+1,e,p);
	return ret;
}



const int MAXLG = 20;

node *T[MAX];
vi IDs[MAX],G[MAX],ans;
int n,m;
int P[MAX][MAXLG];
int depth[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time;

void dfs(int u,int p){
	depth[u] = depth[p] + 1;
	P[u][0] = p;
	loop(i,MAXLG-1) P[u][i + 1] = P[P[u][i]][i];
	dfs_in[u] = dfs_time++;
	T[u] = T[p];
	for(int x : IDs[u])
		T[u] = update(T[u],1,m,x);
	for(int v : G[u]) if(v != p) dfs(v,u);
	dfs_out[u] = dfs_time - 1;
}

void query(node *u,node *v,node *p,node *pp,int s,int e,int cnt){
	if(s == e) {
		int cur = u->siz + v->siz - p->siz - pp->siz;
		if(cur) ans.pb(s);
		return ;
	}
	int m = (s + e) >> 1;
	int left_cnt = u->l->siz + v->l->siz - p->l->siz - pp->l->siz;
	if(left_cnt >= cnt) query(u->l,v->l,p->l,pp->l,s,m,cnt);
	else {
		query(u->l,v->l,p->l,pp->l,s,m,left_cnt);
		query(u->r,v->r,p->r,pp->r,m+1,e,cnt - left_cnt);
	}
}

bool inSubTree(int a,int b){
	return dfs_in[b] <= dfs_in[a] && dfs_in[a] <= dfs_out[b];
}

int lca(int a,int b){
	if(depth[a] > depth[b]) swap(a,b);
	if(inSubTree(b,a)) return a;
	int k = MAXLG - 1;
	while(a != b){
		if(depth[a] > depth[b]) swap(a,b);
		while(k && inSubTree(a,P[b][k])) k--;
		b = P[b][k];
	}
	return a;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int q;
	scanf("%d %d %d",&n,&m,&q);
	loop(i,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	range(i,1,m) {
		int x; scanf("%d",&x);
		IDs[x].pb(i);
	}
	T[0] = build(1,m);
	dfs(1,0);
	dfs_out[0] = n;
	while(q--){
		int u,v,a; scanf("%d %d %d",&u,&v,&a);
		ans.clear();
		int p = lca(u,v);
		int pp = P[p][0];
		query(T[u],T[v],T[p],T[pp],1,m,a);
		printf("%d",sz(ans));
		for(int x : ans) printf(" %d",x);
		puts("");
	}
	return 0;
}
