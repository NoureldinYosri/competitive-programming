#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int MAX = 1 << 20;
vi tris[MAX];
vi members[MAX];
int deg[MAX];
int n;
queue<int> q;
vi P,Q;
vi C[MAX],bad[MAX];
int vis[MAX];

void dfs(int u){
	vis[u] = 1;
	P.push_back(u);
	sort(all(bad[u]));
	for(int v : C[u]){
		if(vis[v] || binary_search(all(bad[u]),v)) continue;
		dfs(v);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i = 1;i <= n;i++){
			tris[i].clear(),deg[i] = 0;
			C[i].clear();
			bad[i].clear();
		}
		for(int i = 1;i <= n-2;i++){
			members[i].clear();
			loop(j,3){
				int x; scanf("%d",&x);
				members[i].push_back(x);
				deg[x]++;
				tris[x].push_back(i);
			}
		}
	//	prArr(deg+1,n,int);
		P.clear();
		Q.clear();
		for(int i = 1;i <= n;i++){
			if(deg[i] == 1)
				q.push(i);
		}
		while(!q.empty()){
			int u = q.front(); q.pop();
			P.push_back(u);
//			cout << "u is " << u;
			if(tris[u].empty()) continue;
			int t = tris[u][0];
//			cout << u << " " << t << endl;
			Q.push_back(t);
			vi tmp(members[t]);
			tmp.erase(find(all(tmp),u));
			for(int v : tmp){
				C[v].push_back(u);
				C[u].push_back(v);
			}
			if(n-sz(P) >= 3){
				int a = tmp[0],b = tmp[1];
				bad[a].push_back(b);
				bad[b].push_back(a);				
			}
			
			for(int v : members[t]){
				deg[v]--;
				tris[v].erase(find(all(tris[v]),t));
				if(deg[v] == 1)
					q.push(v);
			}
		}
		P.clear();
		fill(vis,vis + n + 1,0);
		dfs(1);
		
		for(int x : P) printf("%d ",x);
		puts("");
		for(int x : Q) printf("%d ",x);
		puts("");
	}
	
	return 0;
}
