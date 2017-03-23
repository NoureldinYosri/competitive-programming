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

const int MAX = 100'000 + 10;
int ctr[2],color[MAX],n,m;
vi G[MAX];
int E[MAX],fr[MAX],to[MAX];
vi aux[2];

bool dfs(int u,int c){
	if(color[u] != -1) return color[u] == c;
	color[u] = c;
	aux[c].pb(u);
	for(int e : G[u]) {
		int v = fr[e] + to[e] - u;
		if(!dfs(v,c ^ E[e])) return 0;
	}
	return 1;
}

bool work(vi & V){
	memset(color,-1,sizeof color);
	V.clear();
	loop(i,m){
		aux[0].clear();
		aux[1].clear();
		int u = fr[i],v = to[i];
		if(color[u] != -1 || !E[i]) continue;
		assert(color[v] == -1);
		if(!dfs(u,0)) return 0;
		int idx = sz(aux[0]) > sz(aux[1]);
		for(int u : aux[idx]) V.pb(u);
	}
	return 1;
}

int main(){
	scanf("%d %d",&n,&m);
	int ctr = 0;
	loop(i,m){
		int a,b; char c; scanf("%d %d %c",&a,&b,&c);
		G[a].pb(i);
		G[b].pb(i);
		E[i] = c == 'R';
		fr[i] = a,to [i] = b;
		ctr += E[i];
	}	
	vi V;
	if(work(V)){
		loop(i,m) E[i] ^= 1;
		vi T;
		if(work(T)){
			if(sz(T) < sz(V)) V = T;
		}
		printf("%d\n",sz(V));
		bool first = 1;
		for(int v : V) {
			if(!first) putchar(' ');			
			printf("%d",v);
			first = 0;
		}
		puts("");
	//	print(V,int);	
	}
	else {
		loop(i,m) E[i] ^= 1;
		if(work(V)){
			printf("%d\n",sz(V));
			bool first = 1;
			for(int v : V) {
				if(!first) putchar(' '),first = 0;			
				printf("%d",v);
				first = 0;
			}
			puts("");
		//	print(V,int);		
		}
		else puts("-1");
	}
	return 0;
}
