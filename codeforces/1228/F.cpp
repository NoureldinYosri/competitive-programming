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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 1 << 20;
vi G[MAX];
int n;

pi dfs(int u,int p,int d = 0) {
	pi ret(d,u);
	for(int v : G[u]) if(v != p) ret = max(ret,dfs(v,u,d+1));
	return ret;
}

int dfsRoot(int u,int p,int rem) {
	if(!rem) return u;
	for(int v : G[u]){
		if(v == p) continue;
		int c = dfsRoot(v,u,rem-1);
		if(c != -1) return c;
	}
	return -1;
}



void bf(){

}

bool correct = 1;
vi ans;

void handle1(int u,int d,int D) {
	if(d == D) return;
	correct = 0;
}
void handle2(int u,int d,int D) {
	if(d == 0) return;
	if(d == D-1) {
		ans.push_back(u);
		return;
	}
	correct = 0;
}

void handle3(int u,int d,int D) {
	if(d == 0 || d == D-1) {
		ans.push_back(u);
		return;
	}
	correct = 0;
}

void handle4(int u,int d,int D) {
	if(d > 0 && d < D-1) {
		ans.push_back(u);
		return;
	}
	correct = 0;
}

void solve(int u,int p,int D,int d = 0) {
	if(sz(G[u]) > 4) {
		correct = 0;
		return;
	}
	if(sz(G[u]) == 1) handle1(u,d,D);
	if(sz(G[u]) == 2) handle2(u,d,D);
	if(sz(G[u]) == 3) handle3(u,d,D);
	if(sz(G[u]) == 4) handle4(u,d,D);
	for(int v : G[u]) if(v != p){
		solve(v,u,D,d+1);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	if(n <= 5) {
		bf();
		return 0;
	}
	int m = (1 << n) - 3;
	loop(e,m) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	int root = dfs(1,0).second;
	root = dfs(root,0).second;
	int D = dfs(root,0).first;
	if(D != 2*n) {
		puts("0");
		return 0;
	}
	D >>= 1;
	root = dfsRoot(root,0,D);
	solve(root,0,D);
	if(!correct || sz(ans) > 1) ans.clear();
	printf("%d\n",sz(ans));
	for(int p : ans) printf("%d ",p);
	return 0;
}
