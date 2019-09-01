#ifdef ACTIVE
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

const int MAX = 200000;
vi G[MAX];
int n;

int ask(int u) {
	cout << "? 2 " << u << endl;
	fflush(stdout);
	int v; cin >> v;
	if(v == -1) exit(0);
	return v;
}

bool dead[MAX];
int siz[MAX],mx[MAX];

int floodFill(int u,int p) {
	siz[u] = 1;
	mx[u] = 0;
	for(int v : G[u]) {
		if(v == p || dead[v]) continue;
		int s = floodFill(v,u);
		siz[u] += s;
		mx[u] = max(mx[u],s);
	}
	return siz[u];
}

int getCenter(int u,int p,int s) {
	mx[u] = max(mx[u],s - siz[u]);
	int c = u;
	for(int v : G[u]) {
		if(v == p || dead[v]) continue;
		int g = getCenter(v,u,s);
		if(mx[g] < mx[c]) c = g;
	}
	return c;
}

void DC(int u){
	int s = floodFill(u,0);
	u = getCenter(u,0,s);
	int v = ask(u);
	if(v == 0) {
		cout << "! " << u << endl;
		return;
	}
	dead[u] = 1;
	DC(v);
}

int main(){
	scanf("%d",&n);
	loop(e,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	DC(1);
	return 0;
}
#endif
