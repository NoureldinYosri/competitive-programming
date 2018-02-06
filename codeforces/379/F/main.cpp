#pragma GCC optimize ("O3")
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

const int MAX = 2*500*1000 + 10;
int siz[MAX],mx[MAX],depth[MAX],ID[MAX];
int ans[MAX],n;
int lst[MAX],nxt[MAX],head[MAX];

int fr[MAX*2],to[MAX*2],H[MAX*2],e_cnt;
int vhead[MAX],enxt[MAX*2];


inline void add_edge(int f,int t) {
	enxt[e_cnt] = vhead[f];
	vhead[f] = e_cnt;
	to[e_cnt] = t;
	e_cnt++;
}

inline void add_bi_edge(int f,int t) {
	add_edge(f,t);
	add_edge(t,f);
}

int get_size(int u,int p) {
	siz[u] = 1;
	mx[u] = 0;
	depth[u] = depth[p] + 1;
	for(int e = vhead[u],v;~e;e = enxt[e]) {
		v = to[e];
		if(v != p) {
			int s = get_size(v,u);
			mx[u] = max(mx[u],s);
			siz[u] += s;
		}
	}
	return siz[u];
}

void get_center(int u,int p,int s,int & c) {
	mx[u] = max(mx[u],s - siz[u]);
	if(mx[u] < mx[c]) c = u;
	for(int e = vhead[u],v;~e;e = enxt[e]) {
		v = to[e];
		if(v != p) get_center(v,u,s,c);
	}
}

void mark(int u,int p,int id) {
	depth[u] = depth[p] + 1;
	ID[u] = id;
	for(int e = vhead[u],v;~e;e = enxt[e]) {
		v = to[e];
		if(v != p) mark(v,u,id);
	}
}





void DC(int u = 1,int st = 1,int p = 0) {
	int prv = -1;
	for(int e = vhead[u];~e;e = enxt[e]) {
		if(to[e] != p){
			if(prv == -1) vhead[u] = e;
			else enxt[prv] = e;
			prv = e;
		}
		else if(e == vhead[u]) vhead[u] = -1;
	}
	if(prv != -1) enxt[prv] = -1;


	int s = get_size(u,0);
	get_center(u,0,s,u);


	depth[0] = -MAX;
	depth[u] = 0;
	ID[u] = 0;
	for(int e = vhead[u],v;~e;e = enxt[e]) {
		v = to[e];
		mark(v,u,v);
		lst[v] = 0;
	}


	int best[2] = {-MAX,-MAX};
	int src[2] = {-2,-1};

	for(int v = st;v;v = nxt[v]) {
		for(int i = 0;i < 2;i++)
			if(src[i] != ID[v]){
				ans[v] = max(ans[v],depth[v] + best[i]);
				break;
			}

		if(lst[ID[v]]) nxt[lst[ID[v]]] = v;
		else head[ID[v]] = v;
		lst[ID[v]] = v;

		if(src[0] == ID[v]) best[0] = max(best[0],depth[v]);
		else if(best[1] < depth[v]) {
			best[1] = depth[v];
			src[1] = ID[v];
			if(best[0] < best[1]) {
				swap(best[0],best[1]);
				swap(src[0],src[1]);
			}
		}
		assert(src[0] != src[1]);
	}
	for(int e = vhead[u],v;~e;e = enxt[e]) {
		v = to[e];
		nxt[lst[v]] = 0;
		H[e] = head[v];
	}


	for(int e = vhead[u],v;~e;e = enxt[e]) {
		v = to[e];
		DC(v,H[e],u);
	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
//		freopen("out.out","w",stdout);
	#endif
	int Q;
	scanf("%d",&Q);
	n = 4;
	memset(vhead,-1,sizeof vhead);
	for(int i = 2;i <= 4;i++)
		add_bi_edge(1,i);

	while(Q--) {
		int p; scanf("%d",&p);
		add_bi_edge(p,++n);
		add_bi_edge(p,++n);
	}

	for(int i = 1;i < n;i++)
		nxt[i] = i + 1;

	DC();
	int dia = 2;
	for(int u = 6;u <= n;u += 2)
		printf("%d\n",dia = max(dia,ans[u]));
	return 0;
}
