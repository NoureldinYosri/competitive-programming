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

const int MAX = 1e5 + 1e2;
vi U[MAX],V[MAX];
int D[MAX],P1[MAX],P2[MAX],n;
vi L1[MAX],L2[MAX];
vi F[MAX],G[MAX];

int bfs(int root,vi *T,vi *L,int *P,int c = 0){
	queue<int> q; q.push(root);
	memset(D,0,sizeof D); 
	int r = D[root] = 1; P[root] = 0;
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(c) L[D[u]].pb(u);
		for(int v : T[u]) if(v != P[u]) {
			r = D[v] = D[u] + 1;
			P[v] = u;			
			q.push(v);
		}
	}
	return r;
}

vi get_roots(vi *T){
	vi deg(n + 1);
	range(i,1,n) deg[i] = sz(T[i]);
	queue<int> q,p;
	range(i,1,n) if(deg[i] == 1) q.push(i);
	while(!q.empty()){
		int u = q.front(); q.pop();
		p.push(u); if(sz(p) > 2) p.pop();
		for(int v : G[u]) {
			deg[v]--;
			if(deg[v] == 1) q.push(v);
		}
	}
	vi ret;
	while(!p.empty()){
		ret.pb(p.front());
		p.pop();
	}
//	assert(sz(ret));
	return ret;
}

bool clear(int c){
	loop(i,n+1) L1[i].clear(),L2[i].clear(),F[i].clear(),G[i].clear();
	return c;
}

bool valid(int c1,int c2){
	int r = bfs(c1,U,L1,P1,1);
	int r2 = bfs(c2,V,L2,P2,1);
	if(r != r2) return clear(0);

	for(;r;r--){
		if(sz(L1[r]) != sz(L2[r])) return clear(0);
		sort(all(L1[r]),[](const int & a,const int & b){
			return F[a] < F[b];
		});
		sort(all(L2[r]),[](const int & a,const int & b){
			return G[a] < G[b];		
		});
		int m = sz(L1[r]);
		loop(i,m) if(F[L1[r][i]] != G[L2[r][i]]) return clear(0);
		int k = 0;
		loop(i,m){
			int j = i;
			while(j < m && F[L1[r][i]] == F[L1[r][j]]) {
				F[P1[L1[r][j]]].pb(k);
				G[P2[L2[r][j]]].pb(k);
				j++;
			}
			k++;
			i = j - 1;
		}
	}
	return clear(1);
}

char buffer[6000];

int read_tree(vi *T){
	memset(P1,0,sizeof P1);	
	int m = 1,cur = 1;
	for(char *p = buffer;*p == '0' || *p == '1';p++){
		if(*p == '0'){
			T[cur].pb(++m);	
			T[m].pb(cur);
			P1[m] = cur;
			cur = m;
		}
		else cur = P1[cur];
	}	
	memset(P1,0,sizeof P1);	
	return m;
}

int main(){
	int T; scanf("%d\n",&T);
	while(T--){
		fgets(buffer,6000,stdin); 
		n = read_tree(U);
		fgets(buffer,6000,stdin); 
		int m = read_tree(V);
		if(n != m) {
			loop(i,max(n,m)+1) U[i].clear(),V[i].clear();
			puts("different");
			continue;
		}
		if(n == 1){
			loop(i,n+1) U[i].clear(),V[i].clear();
			puts("same");
			continue;
		}	
		vi C1 = get_roots(U),C2 = get_roots(V);
		bool ans = 0;
		for(int c1 : C1) for(int c2 : C2) ans |= valid(c1,c2);
		puts(ans ? "same" : "different");
		loop(i,n+1) U[i].clear(),V[i].clear();
	}	
	
	
	return 0;
}
