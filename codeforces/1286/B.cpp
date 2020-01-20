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

const int MAXN = 2000 + 10;
vi G[MAXN];
int siz[MAXN];
int A[MAXN],C[MAXN];
int B,n;
int dfs_in[MAXN], dfs_out[MAXN], euler[MAXN], dfs_time;


bool dfs(int u,int s,int d){
	euler[dfs_time] = u;
	dfs_in[u] = dfs_time++;
	
	siz[u] = 1;
	int e = s;
	for(int v : G[u]){
		if(!dfs(v, e, d + 1)) return 0;
		e += siz[v];
		siz[u] += siz[v];
	}
	e++;
	
	if(C[u] > siz[u]-1)
		return 0;
		
	dfs_out[u] = dfs_time;

	vi tmp(siz[u]-1);
	
	for(int i = dfs_in[u] + 1,j = 0; i < dfs_out[u];i++)
		tmp[j++] = euler[i];
		
	sort(all(tmp), [](const int & a,const int &b){
		return A[a] < A[b];
	});
	
	
	vi aux(sz(tmp));
	aux.clear();
	while(sz(tmp) > C[u]) {
		int t = tmp.back();
		tmp.pop_back();
		aux.push_back(t);
	}
	A[u] = tmp.empty() ? s*B : (A[tmp.back()] + 1);
	int offset = aux.empty() ? 0 : max(0, A[u] + 1 - A[aux.back()]);
	for(int v : aux)
		A[v] += offset;
	return 1;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	B = 3*n;
	int root = 1;
	for(int i = 1;i <= n;i++){
		int p; scanf("%d %d",&p, C+i);
		G[p].push_back(i);
		if(p == 0) root = i;
	}
	if(dfs(root, 0, 0)){
		puts("YES");
		for(int i = 1;i <= n;i++) printf("%d ",A[i] + 1);
		puts("");		
	}
	else puts("NO");
	return 0;
}
