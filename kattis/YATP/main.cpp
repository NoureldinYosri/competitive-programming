#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAXN = 200*1000 + 10,MAXX = 1000000;

int pen[MAXN],n;
vi E[MAXN];
int fr[MAXN],to[MAXN],W[MAXN];
int siz[MAXN],mx[MAXN];
ll sum_weight[MAXN],ans[MAXN];
bool dead[MAXN];

int floodFill(int u,int p) {
	siz[u] = 1;
	mx[u] = 0;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p || dead[v]) continue;
		siz[u] += floodFill(v,u);
		mx[u] = max(mx[u],siz[v]);
	}
	return siz[u];
}

int getCenter(int u,int p,int s) {
	mx[u] = max(mx[u],s - siz[u]);
	int c = u;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p || dead[v]) continue;
		int g = getCenter(v,u,s);
		if(mx[g] < mx[c]) c = g;
	}
	return c;
}


typedef pair<ll,ll> line;

struct node{
	node *left,*right;
	line L;
};

auto f = [](const line & g,const int ll & x) {
	return g.first*x + g.second;
};




node* insert(node *root,int s,int e,line nL) {
	if(!root) {
		root = new node();
		root->L = nL;
		return root;
	}
	if(s == e) {
		if(f(nL,s) < f(root->L,s)) root->L = nL;
		return root;
	}
	int m = (s + e)/2 + 1;
	bool lef = f(nL,s) < f(root->L,s);
	bool mid = f(nL,m) < f(root->L,m);
	if(mid) swap(root->L,nL);
	if(s == e) return root;
	if(lef != mid) root->left = insert(root->left,s,m-1,nL);
	else root->right = insert(root->right,m,e,nL);
	return root;
}

//vector<line> lines;
//
//ll bf(ll x) {
//	ll ans = LLONG_MAX;
//	for(line L : lines)
//		ans = min(ans,f(L,x));
//	return ans;
//}
ll query(node *root,int s,int e,int x) {
	if(!root) return LLONG_MAX;
	ll ret = f(root->L,x);
	if(s == e) return ret;
	int m = (s + e) >> 1;
	if(x <= m) ret = min(ret,query(root->left,s,m,x));
	else ret = min(ret,query(root->right,m+1,e,x));
	return ret;
}

void dfsOptain(int u,int p,ll sum_path,node *root,int w) {
	ll tmp = query(root,1,MAXX,pen[u]);
//	cerr << w << " " << u << ": " << tmp << " vs " << bf(pen[u]) << endl;
//	assert(tmp == bf(pen[u]));
	tmp += sum_path;
	ans[u] = min(ans[u],tmp);
	ans[w] = min(ans[w],pen[w]*(ll)pen[u] + sum_path);
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p || dead[v]) continue;
		dfsOptain(v,u,sum_path + W[e],root,w);
	}
}

node* dfsInsert(int u,int p,ll sum_path,node *root) {
	root = insert(root,1,MAXX,mp(pen[u],sum_path));
//	lines.emplace_back(pen[u],sum_path);
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p || dead[v]) continue;
		root = dfsInsert(v,u,sum_path + W[e],root);
	}
	return root;
}

void DC(int u,int d = 0) {
	static vi aux;
//	cerr << ++d << " " << u << endl;
	int s = floodFill(u,0);
	u = getCenter(u,0,s);
	node *root = 0;
	aux.clear();
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dead[v]) continue;
		aux.push_back(e);
	}
	root = insert(0,1,MAXX,mp(pen[u],0LL));
//	lines.emplace_back(pen[u],0);
	for(int e : aux) {
		int v = fr[e] + to[e] - u;
		dfsOptain(v,u,W[e],root,u);
		root = dfsInsert(v,u,W[e],root);
	}
	reverse(all(aux));
	root = insert(0,1,MAXX,mp(pen[u],0LL));
//	lines.clear();
//	lines.emplace_back(pen[u],0);
	for(int e : aux) {
		int v = fr[e] + to[e] - u;
		dfsOptain(v,u,W[e],root,u);
		root = dfsInsert(v,u,W[e],root);
	}
//	lines.clear();

	dead[u] = 1;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dead[v]) continue;
		assert(v <= n);
		assert(v >= 1);
		DC(v,d+1);
	}
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	for(int u = 1;u <= n;u++){
		scanf("%d",pen + u);
		ans[u] = pen[u]*(ll)pen[u];
	}

	for(int e = 0;e < n-1;e++) {
		scanf("%d %d %d",fr + e,to + e,W + e);
		assert(fr[e] <= n);
		assert(to[e] <= n);
		E[fr[e]].push_back(e);
		E[to[e]].push_back(e);
	}
	DC(1);
//	prArr(ans+1,n,ll);
	ll res = 0;
	for(int u = 1;u <= n;u++)
		res += ans[u];
	printf("%lld\n",res);
	return 0;
}
