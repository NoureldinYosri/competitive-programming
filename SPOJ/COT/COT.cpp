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

struct node{
	int size;
	node *left,*right;
public:
	node():size(0),left(0),right(0){}
};

const int MAX = 100000 << 2;
vi G[MAX];
int E[MAX << 2],L[MAX << 2],H[MAX],P[MAX],D[MAX],IDX[MAX],idx,n,mx;
int lg[MAX << 2],RMQ[MAX << 2][23],value[MAX],tmp[MAX];
node *T[MAX];

inline void insert(int u,int & p,int *E,int *L){
	E[p] = u;
	L[p] = D[u];
	p++;
}

void dfs(int root,vi *G,int *E,int *H,int *L){
	int u = root; 
	P[u] = -1; D[u] = 0;
	idx = 0;
	while(u != -1){
		if(IDX[u] == 0) H[u] = idx;
		insert(u,idx,E,L);
		if(IDX[u] == sz(G[u])){
			u = P[u];
			continue;	
		}
		int v = G[u][IDX[u]++];
		if(v == P[u]) continue;
		P[v] = u;
		D[v] = D[u] + 1;
		u = v;
	}
}

void build_RMQ(int *L){
	loop(i,idx) RMQ[i][0] = i;
	loop(k,22){
		loop(i,idx){
			RMQ[i][k + 1] = RMQ[i][k];
			if(i + (1 << k) < idx && L[RMQ[i + (1 << k)][k]] < L[RMQ[i][k]]) 
				RMQ[i][k + 1] = RMQ[i + (1 << k)][k]; 
		}
	}
}

void init(int root,vi *G,int *E,int *H,int *L){
	fill(IDX,IDX + n,0);
	
	dfs(root,G,E,H,L);
	lg[0] = -1;
	range(i,1,(n << 2) - 1){
		lg[i] =  lg[i - 1];
		if(i == LSOne(i)) lg[i]++;
	}	
	build_RMQ(L);
}

int get_RMQ(int a,int b){
	if(a > b) swap(a,b);
	int l = lg[b - a + 1];
	int u = RMQ[a][l] , v = RMQ[b - (1 << l) + 1][l];
	if(L[v] < L[u]) u = v;
	return u;
}


int LCA(int a,int b) {return E[get_RMQ(H[a],H[b])];}


node* init_PST(int l,int r){
	node *root = new node();
	if(l == r) return root;
	int m = (l + r) >> 1;
	root->left = init_PST(l,m);
	root->right = init_PST(m + 1,r);
	return root;
}

node* update(node *root,int s,int e,int v){
	node *nr = new node(); *nr = *root;
	nr->size++;
	if(s == e) return nr;
	int m = (s + e) >> 1;
	if(v <= m) nr->left = update(root->left,s,m,v);
	else nr->right = update(root->right,m + 1,e,v);
	return nr;
}

int query(node *pp,node *p,node *u,node *v,int s,int e,int k){
	if(s == e) return s;
	int m = (s + e) >> 1;
	int q = v->left->size + u->left->size - p->left->size - pp->left->size;
	//cerr << s << " " << e << " " << q << " " << k << " ... ";
	//cerr << u->left->size << " " << v->left->size << " " << p->left->size << endl;	
	if(q >= k) return query(pp->left,p->left,u->left,v->left,s,m,k);
	else return query(pp->right,p->right,u->right,v->right,m + 1,e,k - q); 
}

void build_PSTs(){
	T[0] = init_PST(0,mx);
	queue<int> q;
	q.push(1); P[1] = 0;
	while(!q.empty()){
		int u = q.front(); q.pop();
		T[u] = update(T[P[u]],0,mx,value[u]);
		loop(i,sz(G[u])){
			int v = G[u][i];
			if(v == P[u]) continue;
			P[v] = u;
			q.push(v);
		}
	}
}

int main(){
	int m,a,b,c;
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",value + i + 1);
	value[0] = INT_MAX; n++;
	
	// compress
	copy(value,value + n,tmp);
	sort(tmp,tmp + n);
	a = unique(tmp,tmp + n) - tmp;
	loop(i,n) value[i] = lower_bound(tmp,tmp + a,value[i]) - tmp;
	mx = a - 2;
	
	// read tree
	loop(i,n - 2){
		scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	
	// build LCA and PST
	init(1,G,E,H,L);
	build_PSTs();

	while(m--){
		scanf("%d %d %d",&a,&b,&c);
		int p = LCA(a,b);
		int ans = query(T[P[p]],T[p],T[a],T[b],0,mx,c);
		printf("%d\n",tmp[ans]);
	}
	return 0;
}
