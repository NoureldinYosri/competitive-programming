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
#define pl pair<ll,ll>
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
pi ST[MAX << 2];
pi A[MAX],B[MAX];
int f[MAX],g[MAX],h[MAX],n;
int dfs_in[MAX],dfs_out[MAX],dfs_time,euler[MAX];
vi G[MAX];

void clean(){
	range(i,1,n) G[i].clear();
	dfs_time = 0;
}

void dfs(int u,int p){
	euler[dfs_time] = u;
	dfs_in[u] = dfs_time++;
	for(int v : G[u]) if(v != p) dfs(v,u);
	dfs_out[u] = dfs_time - 1;
}

bool contains(int u,int v){
	if(!u || !v) return 0;
	return dfs_in[u] <= dfs_in[v] && dfs_in[v] <= dfs_out[u];
}

void build(int node,int s,int e){
	ST[node] = mp(0,0);
	if(s == e) {
		f[euler[s]] = 0;
		ST[node].xx = euler[s];
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
}


pi choose(pi A,pi B){
	int aux [] = {A.xx,A.yy,B.xx,B.yy};
	sort(aux,aux + 4,[](const int & a,const int & b){
		return f[a] > f[b];
	});
	vi V;
	loop(i,3) V.pb(aux[3-i]);
	while(!V.empty() && (contains(aux[0],V.back() || contains(V.back(),aux[0])))) V.pop_back();
	return mp(aux[0],V.empty() ? 0 : V.back());
}

void update(int node,int s,int e,int p){
	if(s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p);
	else update(right,m+1,e,p);
	ST[node] = choose(ST[left],ST[right]);
}

pi query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	pi a = query(left,s,m,l,m),b = query(right,m+1,e,m+1,r);
	return choose(a,b);
}



int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		loop(i,n-1){
			int a,b; scanf("%d %d",&a,&b);
			G[a].pb(b);
			G[b].pb(a);
		}
		dfs(1,0);
		assert(dfs_time == n);
		build(1,0,n-1);
		range(u,1,n) {
			f[u] = f[query(1,0,n-1,dfs_in[u],dfs_out[u]).xx] + 1;
			update(1,0,n-1,dfs_in[u]);
		}
		range(u,1,n) {
			A[u] = mp(0,0);
			if(dfs_in[u] != dfs_out[u]) A[u] = query(1,0,n-1,dfs_in[u]+1,dfs_out[u]);
			A[u] = choose(A[u],mp(u,0));
		}
		copy(f,f+n+1,g);
		build(1,0,n-1);
		for(int u = n;u >= 1;u--){
			f[u] = f[query(1,0,n-1,dfs_in[u],dfs_out[u]).xx] + 1;
			update(1,0,n-1,dfs_in[u]);
		}
		range(u,1,n) {
			B[u] = mp(0,0);
			if(dfs_in[u] != dfs_out[u]) B[u] = query(1,0,n-1,dfs_in[u]+1,dfs_out[u]);
			B[u] = choose(B[u],mp(u,0));
		}
		copy(f,f+n+1,h);
//		range(u,1,n) cerr << u << " " << g[u] -1<< " " << h[u] - 1<< endl;
		int ans = 0;
		range(u,1,n) {
			int a[2] = {A[u].xx,A[u].yy};
			int b[2] = {B[u].xx,B[u].yy};
//			prArr(a,2,int);
//			prArr(b,2,int);

			loop(i,2) loop(j,2) {
				int v = a[i],t = b[j];
				if((contains(v,t) || contains(t,v)) && (v!=u && t!=u))  continue;
				ans = max(ans,g[v] + h[t] - (v==t && v==u));
			}
		}
		printf("%d\n",ans);
		clean();
	}
	return 0;
}
