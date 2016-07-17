#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

const int MAX = 200000;
vi G[MAX];
int n,idx[MAX],P[MAX],L[MAX],E[MAX << 2],Q[MAX << 2],F[MAX],lg[MAX << 4],ctr;
int RMQ[MAX << 2][30];
int ST[MAX << 2];

void dfs(){
	int u = 0; ctr = 0; L[0] = 0; P[0] = -1;
	while(u != -1){
		//cerr << u << " " << ctr << " " << L[u] << endl;
		F[u] = ctr;
		E[ctr] = L[u];
		Q[ctr] = u;
		++ctr;
		if(idx[u] == sz(G[u])){
			u = P[u];
			continue;	
		}
		int v = G[u][idx[u]];
		if(v != P[u]){
			P[v] = u;
			L[v] = L[u] + 1;
		}
		else v = u;
		idx[u]++;
		u = v;
	}
}

void build(int node,int s,int e){
	ST[node] = -1;
	if(s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m + 1,e);
}

void init(){
	build(1,0,n-1);
	dfs();
	loop(i,ctr) RMQ[i][0] = i;//,cerr << E[i] << " ";
	//cerr << endl;
	loop(i,lg[ctr] + 1){		
		loop(j,ctr){
			int a = RMQ[j][i],b = RMQ[min(j + (1 << i),ctr - 1)][i];
			RMQ[j][i + 1] = a;
			if(E[b] < E[a]) RMQ[j][i + 1] = b;
	//		cerr << E[RMQ[j][i+1]] << " ";
		}
	//	cerr << endl;
	}/*
	loop(j,ctr){
		cerr << j << ": ";	
		loop(i,lg[ctr] + 2)
			cerr << E[RMQ[j][i]] << " " ;
		cerr << endl;
	}*/
}

int LCA(int a,int b){
	if(a == -1) return b;
	if(b == -1) return a;
	if(a == b) return a;
	int x = F[a],y = F[b]; if(y < x) swap(x,y);
	int l = lg[y - x + 1];
	a = RMQ[x][l];
	b = RMQ[y  - (1 << l) + 1][l];
	if(E[a] > E[b]) a = b;
	return Q[a];
}

void update(int node,int s,int e,int i){	
	if(s == e){
		if(ST[node] == s) ST[node] = -1;
		else ST[node] = s;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(i <= m) update(left,s,m,i);
	else update(right,m+1,e,i);
	ST[node] = LCA(ST[left],ST[right]);
	//cerr << ST[left] << " " << ST[right] << " -> " << ST[node] << endl;
}

int main(){
	lg[1] = 0;
	loop(i,MAX << 4){
		if(i <= 1) continue;
		lg[i] = lg[i - 1];
		if(i == (i & (-i))) lg[i]++;
	}
	int T,Z; char s[5]; int x;
	scanf("%d",&T);
	while(T--){
		loop(i,n + 1){
			G[i].clear();
			idx[i] = 0;
		}
		scanf("%d",&n);
		loop(i,n - 1){
			int a,b;
			scanf("%d %d",&a,&b);
			G[a].pb(b);
			G[b].pb(a);
		}
		init();
		scanf("%d",&Z);
		while(Z--){
			scanf("%s %d",s,&x);
			update(1,0,n - 1,x);
			printf("%d\n",ST[1]);
		}
	}
	return 0;
}
