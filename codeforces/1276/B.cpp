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

const int MAXN = 200*1000 + 10;

vi G[MAXN];
int n,m;
int type[MAXN];
int a,b;
bool vis[MAXN];

void init(){
	loop(i,n+1) G[i].clear(),type[i] = 0;
}

void dfs(int u,int forbidden,int val){
	if(vis[u]) return ;
	if(u == forbidden) return;
	type[u] |= val;
	vis[u] = 1;
	for(int v : G[u]) dfs(v,forbidden,val);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d %d %d",&n,&m,&a,&b);
		init();
		loop(e,m){
			int f,t; scanf("%d %d",&f,&t);
			G[f].push_back(t);
			G[t].push_back(f);
		}
		fill(vis,vis + n + 1,0);
//		prArr(type+1,n,int);
		dfs(a,b,1);
		fill(vis,vis + n + 1,0);
		dfs(b,a,2);
//		prArr(type+1,n,int);
		ll one = 0,two = 0;
		for(int i = 1;i <= n;i++){
			one += type[i] == 1;
			two += type[i] == 2;
		}
//		cout << one << " "<< two << endl;
		one--;
		two--;
		printf("%lld\n",one*two);
	}
	return 0;
}
