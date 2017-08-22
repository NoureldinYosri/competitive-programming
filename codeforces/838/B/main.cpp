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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 2*(200*1000 + 10),MAXLG = 20;

vi E[MAX];
int Forward[MAX],back[MAX],n;
int fr[MAX],to[MAX],weight[MAX];
int siz[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time;
int parent[MAX][MAXLG],depth[MAX];
ll A[MAX],B[MAX];
ll ST[2][MAX << 2],LA[2][MAX << 2];

void dfs(int u,int p,ll w){
	A[dfs_time] = w;
	B[dfs_time] = w + back[u];
	dfs_in[u] = dfs_time++;
	siz[u] = 1;
	depth[u] = depth[p] + 1;
	parent[u][0] = p;
	loop(k,MAXLG - 1) parent[u][k + 1] = parent[parent[u][k]][k];
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		assert(to[e] == v);
		dfs(v,u,w + weight[e]);
		siz[v] += siz[u];
	}
	dfs_out[u] = dfs_time - 1;
}


void build(int node,int s,int e,ll *A,ll *ST){
	if(s == e) {
		ST[node] = A[s];
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m,A,ST);
	build(right,m+1,e,A,ST);
	ST[node] = min(ST[left] , ST[right]);
}

void update(int node,ll v,ll *ST,ll *LA){
	ST[node] += v;
	LA[node] += v;
}

void push(int node,ll *ST,ll *LA){
	if(!LA[node]) return;
	int left = node << 1,right = left | 1;
	update(left,LA[node],ST,LA);
	update(right,LA[node],ST,LA);
	LA[node] = 0;
}

void update(int node,int s,int e,int l,int r,ll v,ll *ST,ll *LA){
	if(l <= s && e <= r) return update(node,v,ST,LA);
	push(node,ST,LA);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,v,ST,LA);
	else if(m < l) update(right,m+1,e,l,r,v,ST,LA);
	else update(left,s,m,l,m,v,ST,LA),update(right,m+1,e,m+1,r,v,ST,LA);
	ST[node] = min(ST[left],ST[right]);
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
		while(k && inSubTree(a,parent[b][k])) k--;
		b = parent[b][k];
	}
	return a;
}

ll query(int node,int s,int e,int pos,ll *ST,ll *LA){
	if(s == e) return ST[node];
	push(node,ST,LA);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(pos <= m) return query(left,s,m,pos,ST,LA);
	else return query(right,m+1,e,pos,ST,LA);
}
ll query(int node,int s,int e,int l,int r,ll *ST,ll *LA){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	push(node,ST,LA);
	if(r <= m) return query(left,s,m,l,r,ST,LA);
	if(m < l) return query(right,m+1,e,l,r,ST,LA);
	return min(query(left,s,m,l,m,ST,LA),query(right,m+1,e,m+1,r,ST,LA));
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int q; scanf("%d %d",&n,&q);
	range(e,1,n-1){
		scanf("%d %d %d",fr + e,to + e,weight + e);
		E[fr[e]].pb(e);
		Forward[to[e]] = weight[e];
	}
	range(e,n,2*n-2){
		scanf("%d %d %d",fr + e,to + e,weight + e);
		assert(to[e] == 1);
		back[fr[e]] = weight[e];
	}
	dfs(1,0,0);
	dfs_out[0] = n;
	build(1,0,n-1,A,ST[0]);
	build(1,0,n-1,B,ST[1]);
/*	prArr(dfs_in,n,int);
	prArr(dfs_out,n,int);
	prArr(A,n,ll);
	prArr(B,n,ll);
*/	loop(i,q){
		int type,a,b; scanf("%d %d %d",&type,&a,&b);
		if(type == 1){
			int e = a;
			ll diff = b - weight[e];
			weight[e] = b;
			if(e < n) {
				int u = to[e],l = dfs_in[u],r = dfs_out[u];
				update(1,0,n-1,l,r,diff,ST[0],LA[0]);
				update(1,0,n-1,l,r,diff,ST[1],LA[1]);
			}
			else {
				int u = fr[e],pos = dfs_in[u];
				update(1,0,n-1,pos,pos,diff,ST[1],LA[1]);
			}
		}
		else {
			int p = lca(a,b);
			if(p == a) {
				int l = dfs_in[a],r = dfs_in[b];
				ll tb = query(1,0,n-1,r,ST[0],LA[0]);
				ll ta = query(1,0,n-1,l,ST[0],LA[0]);
				printf("%lld\n", tb - ta );
			}
			else {
				ll x = query(1,0,n-1,dfs_in[a],dfs_out[a],ST[1],LA[1]),
						y = query(1,0,n-1,dfs_in[a],ST[0],LA[0]);
				ll up = x - y;
				ll down = query(1,0,n-1,dfs_in[b],ST[0],LA[0]);
//				cerr << "lca (" << a << " ," << b << ") = " << p << endl;
//				cerr << "up is " << x << " - " << y << " ,down = " << down << endl;
				printf("%lld\n",up + down);

			}
		}
	}
	return 0;
}
