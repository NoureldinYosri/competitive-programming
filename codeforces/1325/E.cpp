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
int prime[MAX];

void sieve(){
	for(int i = 2; i < MAX; i++){
		if(prime[i]) continue;
		prime[i] = i;
		for(ll j = i*(ll)i; j < MAX; j+=i)
			prime[j] = i;
	}
}


int n;
int A[1 << 20];
vi G[1 << 20];
int state[1 << 20];
int cnt[1 << 20];

int remove_squares(int x){
	int y = 1;
	while(x > 1){
		int p = prime[x], e = 0;
		while(x%p == 0){
			x /= p;
			e++;
		}
		if(e&1) y *= p;
	}
	return y;
}


void scratch(){
	set<int> S, C;
	
	for(int n = 1; n <= 1000*1000; n++){
		int s = 1, r = 1, c = 0;
		for(int m = n; m > 1; ){
			int p = prime[m];
			int e = 0;
			while(m%p == 0){
				m /= p;
				e++;
			}
			s *= e + 1;
			if(e & 1) r *= p, c++;
		}
		if(s > 7) continue;
		S.insert(r);
		C.insert(c);
	}
	print(C, int);
	set<int> P;
	for(int x : S){
		if(x == 1) continue;
		if(x == prime[x]) continue;
		P.insert(prime[x]);
		P.insert(x/prime[x]);
	}
	cerr << sz(P) << endl;
	
}

const int oo = 1 << 29;
int depth[MAX], par[MAX];
int ctr[MAX];
bool vis[MAX];


pi dfs(int u){
	int ret = oo;
	int D = oo;
	if(state[u]) D = 0;
	
	vis[u] = 1;
	for(int v : G[u]){
		if(vis[v]) continue;
		if(par[v] == u) {
			pi aux = dfs(v);
			ret = min(ret, aux.first);
			int d = aux.second + 1;
			ret = min(ret, d + D + 2);
			D = min(D, d);
		}
		else ret = min(ret, depth[u] + depth[v] + 1);
	}
	return pi(ret, D);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	//scratch();
	
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	loop(i, n) A[i] = remove_squares(A[i]);
	
	loop(i, n) if(A[i] == 1){
		puts("1");
		return 0;
	}
	
	loop(i, n) {
		int x = A[i];
		cnt[x]++;
		if(cnt[x] == 2) {
			puts("2");
			return 0;
		}
	}
		
	
	loop(i, n){
		int x = A[i];
		if(x == prime[x]){
			state[x] = 1;
			continue;
		}
		int a = prime[x], b = x/a;
		G[a].pb(b);
		G[b].pb(a);
	}
	
	
	vi PQ;
	loop(i, n) if(prime[A[i]] != A[i]) PQ.pb(A[i]);
	
	if(PQ.empty()){
		puts("-1");
		return 0;
	}
	
	int M = *max_element(all(PQ));
	
/*	loop(i, n) if(prime[A[i]] == A[i]) cout << A[i] << endl;
	for(int x : PQ){
		cout << prime[x] << " " << x/prime[x] << endl;
	}
*/	
	vi V;
	for(int i = 2; i*i <= M; i++)
		if(cnt[i] || sz(G[i]))
			V.pb(i);
	
//	print(V, int);
	
	vi cand(V);
	reverse(all(cand));
	
	queue<int> Q;
	int ans = oo;
	
	while(!cand.empty()){
		
		memset(depth, -1, sizeof depth);
		memset(par, -1, sizeof par);
		int root = cand.back(); cand.pop_back();
		
		while(!Q.empty()) Q.pop();
		Q.push(root);
		depth[root] = 0;
		par[root] = 0;
		
		while(!Q.empty()){
			int p = Q.front(); Q.pop();
			for(int q : G[p]) {
				if(depth[q] == -1){
					depth[q] = depth[p] + 1;
					Q.push(q);
					par[q] = p;
				}
			}
		}
	
		memset(vis, 0, sizeof vis);
		ans = min(ans, dfs(root).first);

//		cerr << root << " " << ans << endl;
	}
	
	if(ans >= oo) ans = -1;

	cout << ans << endl;
	
	return 0;
}

