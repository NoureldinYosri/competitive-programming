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


const int MAX = 200*1000 + 10;
int cnt[1 << 20],n,C,siz[MAX],mx[MAX],color[MAX],dead[MAX],parentPath;
vi G[MAX];
ll f[MAX];
char S[MAX];

int dfs(int u,int p) {
	siz[u] = 1;
	mx[u] = 0;
	for (int v : G[u]) if (v != p && !dead[v]) {
		int t = dfs(v,u);
		siz[u] += t;
		if (mx[u] < t) mx[u] = t;
	}
	return siz[u];
}
void getCenter(int u,int p,int s) {
	mx[u] = max(mx[u],s - siz[u]);
	if (mx[u] < mx[C]) C = u;
	for (int v : G[u]) if (v != p && !dead[v]) getCenter(v,u,s);
}

ll dfs(int u,int p,int msk,int root) {
	msk ^= 1 << color[u];
	ll mine = 0;
	if (popcnt(msk) <= 1) {
		mine ++;
		parentPath++;
	}
	int cmsk = msk ^ (1 << color[root]);
	mine += cnt[cmsk];
	for (int i = 0;i < 20;i++) {
		int tmsk = cmsk ^ (1 << i);
		mine += cnt[tmsk];
//            if (cnt[tmsk] > 0) System.err.println("linking " + cmsk + " with " + tmsk + " @" + u + " cnt = " + cnt[tmsk]);
	}

	ll fromChildren = 0;
	for (int v : G[u]) if (v != p && !dead[v]) fromChildren += dfs(v,u,msk,root);
	f[u] += fromChildren + mine;
//        System.err.println(root + " ---> " + u + " add " + mine + " " + fromChildren + " bcz msk = " + msk + " popcnt = " + popcnt[msk]);
	return mine + fromChildren;
}

void insert(int u,int p,int msk,int sgn,int root) {
	msk ^= 1 << color[u];
	cnt[msk] += sgn;
//        System.err.println("@[" + root + ", " + u + "] cnt[" + msk + "] += " + sgn);
	for (int v : G[u]) if (v != p && !dead[v]) insert(v,u,msk,sgn,root);
}

void DC(int u) {
	int s = dfs(u,0);
	C = u;
	getCenter(u,0,s);
	u = C;

	f[u]++;
//        cnt[1 << color[u]]++;
	for (int v : G[u]) if (!dead[v]) insert(v,u,1 << color[u],1,u);


//        cnt[1 << color[u]]--;
	ll tmp = 0;
	parentPath = 0;
	for (int v : G[u]) if (!dead[v]) {
		insert(v,u,1 << color[u],-1,u);
		tmp += dfs(v,u, 1 << color[u],u);
		insert(v,u,1 << color[u],1,u);
	}
	tmp -= parentPath;
	f[u] += parentPath;

	assert(tmp%2 == 0);
	f[u] += tmp/2;

	for (int v : G[u]) if (!dead[v]) insert(v,u,1 << color[u],-1,u);
	dead[u] = true;
	for (int v : G[u]) if (!dead[v]) DC(v);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(e,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	scanf("%s",S);
    for (int i = 1;i <= n;i++) {
        int c = S[i-1] - 'a';
        color[i] = c;
    }
    DC(1);
    for(int i = 1;i <= n;i++)
    	printf("%lld ",f[i]);

	return 0;
}
