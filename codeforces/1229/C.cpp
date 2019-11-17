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

const int MAX = 100*1000 + 10;
const int B = sqrt(MAX),S = (MAX + B - 1)/B;

unordered_set<int> adj[MAX];
int n,m;
int val[MAX],lst_update[MAX];
int blkVal[MAX];
ll smaller[MAX],bigger[MAX];
ll ans;
ll change[MAX];

void read(){
	scanf("%d %d",&n,&m);
	loop(e,m){
		int a,b;scanf("%d %d",&a,&b);
		adj[a].insert(b);
		adj[b].insert(a);
	}
}

void prepare(){
	ans = 0;
	for(int u = 1;u <= n;u++) {
		blkVal[u] = val[u];
		for(int v : adj[u]){
			smaller[u] += val[v] < val[u];
			bigger[u] += val[v] > val[u];
		}
		ans += smaller[u]*bigger[u];
	}
}


int V[MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	read();
	for(int u = 1;u <= n;u++) val[u] = u,lst_update[u] = -1;
	prepare();
	printf("%lld\n",ans);
	int Q; scanf("%d",&Q);
	for(int q = 0;q < Q;q++) scanf("%d",V + q);

	for(int q = 0;q < Q;q++) {
		int u = V[q];
		int s = q - q%B;
		if(lst_update[u] >= s)
			ans -= change[u];
		ll old = smaller[u]*bigger[u];
		int was_smaller = 0,was_bigger = 0;
		val[u] = n + q + 1;
		for(int i = s;i < q;i++) {
			int v = V[i];
			if(!adj[u].count(v)) continue;
			cout << "v is " << val[v] << " was " << blkVal[v] << endl;
			ll sgn = (val[v] - blkVal[v])*(ll)(val[u] - blkVal[u]);
			if(sgn > 0) continue;
			if(blkVal[v] < blkVal[u]) was_smaller++;
			else was_bigger++;
		}
		cout << u << ": " << was_smaller << " " << was_bigger << endl;
		ll new_val = (smaller[u] - was_smaller + was_bigger)*(bigger[u] - was_bigger + was_smaller);
		change[u] = new_val - old;
		lst_update[u] = q;
		ans += change[u];
		printf("%lld\n",ans);
		if(q%B == B-1) prepare();
	}
	return 0;
}
