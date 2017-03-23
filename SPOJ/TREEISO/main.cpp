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
//vi F[MAX],G[MAX];
pi F[MAX],G[MAX];
int base1,base2;
int mod1,mod2;
vi P{179424691,179425033,179425601,179426083,179424697,179425063,179425619,179426089,179424719,179425069,179425637,179426111,179424731,179425097,179425657,179426123,179424743,179425133,179425661,179426129,179424779,179425153,179425693,179426141,179424787,179425171,179425699,179426167,179424793,179425177,179425709,179426173,179424797,179425237,179425711,179426183,179424799,179425261,179425777,179426231,179424821,179425319,179425811,179426239,179424871,179425331,179425817,179426263,179424887,179425357,179425819,179426321,179424893,179425373,179425823,179426323,179424899,179425399,179425849,179426333,179424907,179425403,179425859,179426339,179424911,179425423,179425867,179426341,179424929,179425447,179425879,179426353,179424937,179425453,179425889,179426363,179424941,179425457,179425907,179426369,179424977,179425517,179425943,179426407,179424989,179425529,179425993,179426447,179425003,179425537,179426003,179426453,179425019,179425559,179426029,179426491,179425027,179425579,179426081,179426549};
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

int mul(int x,int y,int mod){
	return (x*1LL*y)%mod;
}

int add(int x,int y,int mod){
	x += y;
	if(x >= mod) x -= mod;
	return x;
}

vi get_roots(vi *T){
	vi deg(n + 1);
	range(i,1,n) deg[i] = sz(T[i]);
	queue<int> q,p;
	range(i,1,n) if(deg[i] == 1) q.push(i);
	while(!q.empty()){
		int u = q.front(); q.pop();
		p.push(u); if(sz(p) > 2) p.pop();
		for(int v : T[u]) {
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
	loop(i,n+1) L1[i].clear(),L2[i].clear();
	loop(i,n+1) F[i] = G[i] = mp(0,0);
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
		int k = 1;
		loop(i,m){
			int j = i;
			while(j < m && F[L1[r][i]] == F[L1[r][j]]) {
				F[P1[L1[r][j]]].xx = add(mul(F[P1[L1[r][j]]].xx,base1,mod1),k,mod1);
				G[P2[L2[r][j]]].xx = add(mul(G[P2[L2[r][j]]].xx,base1,mod1),k,mod1);
				F[P1[L1[r][j]]].yy = add(mul(F[P1[L1[r][j]]].yy,base2,mod2),k,mod2);
				G[P2[L2[r][j]]].yy = add(mul(G[P2[L2[r][j]]].yy,base2,mod2),k,mod2);
				j++;
			}
			k++;
			i = j - 1;
		}
	}
	return clear(1);
}

int main(){
	srand(time(0));
	int T; scanf("%d",&T);
	while(T--){
		base1 = rand()%100;
		base2 = rand()%100;
		mod1 = P[rand()%sz(P)];
		mod2 = P[rand()%sz(P)];
		scanf("%d",&n);
		if(n == 1){
			puts("YES");
			continue;
		}
		loop(i,n-1){
			int a,b; scanf("%d %d",&a,&b);
			U[a].pb(b);
			U[b].pb(a);
		}
		loop(i,n-1){
			int a,b; scanf("%d %d",&a,&b);
			V[a].pb(b);
			V[b].pb(a);
		}
		vi C1 = get_roots(U),C2 = get_roots(V);
		bool ans = 0;
		for(int c1 : C1) for(int c2 : C2) ans |= valid(c1,c2);
		puts(ans ? "YES" : "NO");
		loop(i,n+1) U[i].clear(),V[i].clear();
	}	
	
	
	return 0;
}
