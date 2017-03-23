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
vector<string> essay;
string X[MAX],Y[MAX],XY[MAX*4];
int n,m;
char buffer[MAX * 10];
vi G[MAX*4],rG[MAX*4],nG[MAX*4];
int ord[MAX*4],vis[MAX*4],dfs_time,cmp_cnt;
pi F[MAX*4],psi[MAX*4];
int cmp[MAX*4];

void dfs(int u){
	vis[u] = 1;
	for(int v : rG[u]) if(!vis[v]) dfs(v);
	ord[dfs_time++] = u; 
}

void dfs(int u,int id){
	vis[u] = 1;
	psi[id] = min(psi[id],F[u]);
	cmp[u] = id;
	for(int v : G[u]) if(!vis[v]) dfs(v,id);
}

pi dfs2(int u){
	if(vis[u]) return psi[u];
	vis[u] = 1;
	for(int v : nG[u]) psi[u] = min(psi[u],dfs2(v));
	return psi[u];
}

int main(){
	scanf("%d",&m);
	loop(i,m){
		scanf("%s",buffer);
		essay.pb(string(buffer));
		for(char & c : essay.back()) c = tolower(c);
	}
	scanf("%d",&n);
	loop(i,n){
		scanf("%s",buffer); X[i] = string(buffer);
		scanf("%s",buffer); Y[i] = string(buffer);
		for(char & c : X[i]) c = tolower(c);
		for(char & c : Y[i]) c = tolower(c);
		XY[2*i] = X[i];
		XY[2*i + 1] = Y[i];
	}	
	int k = 2*n;
	loop(i,m) XY[k++] = essay[i];
	sort(XY,XY + k);
	k = unique(XY,XY + k) - XY;
	loop(i,k){
		F[i].xx = count(all(XY[i]),'r');
		F[i].yy = sz(XY[i]);
	}
	loop(i,n) {
		int x = lower_bound(XY,XY + k,X[i]) - XY;
		int y = lower_bound(XY,XY + k,Y[i]) - XY;
		G[x].pb(y);	
		rG[y].pb(x);
	}
	loop(i,k) if(!vis[i]) dfs(i);
	memset(vis,0,sizeof vis);
	assert(dfs_time == k);
	reverse(ord,ord + k);
	loop(j,k) if(!vis[ord[j]]) {
		int i = ord[j];
		psi[cmp_cnt] = F[i];
		dfs(i,cmp_cnt++);
	}
	loop(u,k) for(int v : G[u]){
		nG[cmp[u]].pb(cmp[v]);
	}
	memset(vis,0,sizeof vis);
	loop(i,cmp_cnt) dfs2(i);
	int x = 0; ll y = 0;
	loop(i,m) {
		int q = lower_bound(XY,XY + k,essay[i]) - XY;
		x += psi[cmp[q]].xx,y += psi[cmp[q]].yy;
	}
	cout << x << " " << y << endl;
	cerr << x << " " << y << endl;
	return 0;
}
