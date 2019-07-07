#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
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
using namespace std;

const int MAX = 100*1000 + 10,mod = 1000000007;
int n,X;
vi G[MAX];
int val[MAX];

int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a,int b) {
	return (a*(ll)b)%mod;
}


int floodFill(int u,int p) {
	for(int v : G[u])
		if(v != p)
			val[u] ^= floodFill(v,u);
	return val[u];
}

bool isLeaf(int u,int p) {
	if(sz(G[u]) != 1) return 0;
	return p != 0;
}

pi cross(pi f,pi tmp) {
	int A[2] = {f.first,f.second};
	int B[2] = {tmp.first,tmp.second};
	int C[2] = {0};
	loop(i,2) loop(j,2) C[i^j] = add(C[i^j],mul(A[i],B[j]));
	return mp(C[0],C[1]);
}


pi dfs(int u,int p){
	pi ret(1,0);
	for(int v : G[u]) if(v != p) {
		pi tmp = dfs(v,u);
		tmp.first = add(tmp.first,1);
//		cerr << "\t" << u ;
//		prp(ret);
//		cerr << " X ";
//		prp(tmp);
		ret = cross(ret,tmp);
//		cerr << " = " ;
//		prp(ret);
//		cerr << endl;
	}

	ret.first = add(ret.first,-1);

	if(val[u] == X) ret.second = add(1,add(ret.second,ret.first));
	else if(val[u] == 0 && !isLeaf(u,p)) {
		ret.first = add(ret.first,ret.second);
	}
//	cerr << u << " " << ret.first << " " << ret.second << endl;
	return ret;
}

int solve(int u,int p) {
	int p2 = 1;
	int ctr = 0;
	for(int i = 1;i <= n;i++)
		if(val[i] == 0)
			ctr++;
	ctr--;
	for(int i = 0;i < ctr;i++)
		p2 = add(p2,p2);
	return p2;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&X);
	for(int i = 1;i <= n;i++)
		scanf("%d",val + i);
	loop(e,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	int root = 1;
	floodFill(root,0);
	pi res = dfs(root,0);
//	prp(res);
	int ans = 0;
	if(X == val[root]) ans = add(1,res.first);
	else if(val[root] == 0) ans = res.second;
	if(X == 0 && val[root] == 0)
		ans = solve(root,0);
	printf("%d\n",ans);
	return 0;
}
