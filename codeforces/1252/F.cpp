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

const int MAX = 4 << 10;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vi cand_base {26,29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139};
vi cand_mod {1000001273, 1000001279, 1000001311, 1000001329, 1000001333};
int base[2], mod[2], base_power[2][MAX];
int n;
vi adj[MAX];
pi f[MAX];
vector<pair<pi, int>> children[MAX];
int siz[MAX];

int add(int a, int b, int m){
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	if(a >= m || a < 0) a = (a%m + m)%m;
	return a;
}
int mul(int a, int b, int m){
	return (a*(ll)b)%m;
}

void init_hashing(){
	srand(0);
	// srand(time(0));
	shuffle(all(cand_base), rng);
	shuffle(all(cand_mod), rng);
	loop(i,2) base[i] = cand_base[i] + n;
	loop(i,2) mod[i] = cand_mod[i];
	loop(i,2) base_power[i][0] = 1;
	for(int i= 0;i < 2;i++)
		for(int j = 0;j < MAX-1;j++)
			base_power[i][j + 1] = mul(base_power[i][j],base[i],mod[i]);
}


vp Roots;

void floodfill(int u, int p){
	siz[u] = 1;
	int num = p != 0;
	for(int v : adj[u]) if(v != p){
		floodfill(v, u);
		num++;
		siz[u] += siz[v];
	}
	if(num > 1 && (n - 1)%num == 0) {
		int s = (n-1)/num;
		bool valid = true;
		if(p) valid = (n - siz[u]) == s;
		for(int v : adj[u]) if(v != p) valid &= siz[v] == s;		
		if(valid) Roots.emplace_back(num, u);
	}
}

using pl = pair<ll, ll>;


pi dfs(int u, int p){
	pi ret(0, u);
	for(int v : adj[u]) if(v != p){
		pi tmp = dfs(v, u);
		tmp.first++;
		ret = max(ret, tmp);
	}
	return ret;
}

bool lookFor(int u, int p, int t, vi & path){
	path.pb(u);
	if(u == t) return true;
	for(int v : adj[u]) {
		if(v == p) continue;
		if(lookFor(v, u, t, path)) return true;
	}
	path.pop_back();
	return false;
}

pi getHash(int u, int p){
	vp children;
	for(int v : adj[u]) if(v != p){
		pi tmp = getHash(v, u);
		children.pb(tmp);
	}
	sort(all(children));
	int H[2] = {0, 0};
	for(auto h : children){
		int aux[2] = {h.first, h.second};
		loop(i, 2){
			H[i] = mul(H[i], base[i], mod[i]);
			aux[i] = add(aux[i], 1, mod[i]);
			H[i] = add(H[i], aux[i], mod[i]);
		}
	}
//	cerr << u << " " << pi(H[0], H[1]) << endl;
	return pi(H[0], H[1]);
}

pl getHash(ll root){
	pi leaf = dfs(root, 0);
	root = leaf.second;
	leaf = dfs(root, 0);
	vi path;
	lookFor(root, 0, leaf.second, path);
	assert(sz(path) == leaf.first + 1);
	
	pl ret(-1, -1);
	vi R;
	R.pb(sz(path)/2);
	if(sz(path) > 1) R.pb(sz(path)/2 - 1);
	for(int r : R){
		r = path[r];
		//cerr << "\troot is " << r << endl;
		auto h = getHash(r, 0);
		//cerr << r << " " << h << endl;
		ll x = h.first * (1LL << 32) + h.second;
		if(ret.first == -1) ret.first = x;
		else ret.second = x;
	} 

	
	return ret;
}

bool check(int root){
	vector<pl> aux;
	for(int v : adj[root]){
		auto & V = adj[v];
		auto ptr = find(all(V), root);
		V.erase(ptr);
		aux.pb(getHash(v));
		adj[v].pb(root);
	}

	vector<ll> targets {aux[0].first, aux[0].second};
	for(ll x : targets){
		bool valid = true;
		for(auto p : aux) {
			valid &= p.first == x || p.second == x;
		}
		if(valid) return true;
	}
	
	
	
	return false;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	init_hashing();
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	floodfill(1, 0);
	sort(Roots.rbegin(), Roots.rend());
	
	for(auto [r, root] : Roots){
//		cerr << root << " " << r << endl;
		if(check(root)){
			cout << r << endl;
			return 0;
		}	
	}
	cout << -1 << endl;
	return 0;
}
