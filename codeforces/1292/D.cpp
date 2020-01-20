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

struct node{
	map<int,pi> child;
	int cnt;
};

const int MAX = 5000 + 10;
vector<node> trie;
vi P;
int not_prime[MAX];

void sieve(){
	for(int i = 2;i < MAX;i++)
		if(not_prime[i] == 0){
			P.pb(i);
			for(int j = i*i;j < MAX;j += i)
				not_prime[j] = 1;
		}
}

void init(){
	trie.emplace_back();
	sieve();
}

vector<pi> factor(int x){
	vector<pi> ret;
	for(int p : P){
		int q = p;
		int cnt = 0;
		while (x/q){
			int ctr = x / q; q *= p;
			cnt += ctr;
		}
		if(!cnt) continue;
		ret.emplace_back(p, cnt);
	}
	return ret;
}

void insert(int x, int c){
	if(!c) return;
	auto F = factor(x);
	int cur = 0;
	while(!F.empty()){
		int p = F.back().first;
		int & e = F.back().second;
		if(!trie[cur].child.count(p)){
			trie[cur].child[p] = mp(sz(trie), e);
			trie.emplace_back();
		}
		int oe = trie[cur].child[p].second;
		assert(e >= oe);
		e -= oe;
		cur = trie[cur].child[p].first;
		if(!e) F.pop_back();
	}	
	trie[cur].cnt += c;
}

int freq[MAX];

vector<ll> f, siz;


void dfs(int u){
	assert(u < sz(trie));
	siz[u] = trie[u].cnt;
	f[u] = 0;
	for(auto p : trie[u].child){
		int v = p.second.first;
		ll w = p.second.second;
		dfs(v);
		f[u] += f[v] + w * siz[v];
		siz[u] += siz[v];
	}
//	cout << u << " " << siz[u] << " " << f[u] << endl;
}


int n;

ll dfs(int u, ll from_parent){
	f[u] += from_parent;
	ll ret = f[u];
	
	for(auto p : trie[u].child){
		int v = p.second.first;
		ll w = p.second.second;
		ret = min(ret, dfs(v, f[u] - f[v] - w * siz[v] + w * (n - siz[v])));
	}

	return ret;
}

void prtrie(int u){
	for(auto p : trie[u].child){
		int v = p.second.first;
		int w = p.second.second;
		cout << u << "," << trie[u].cnt << " " << v << "," << trie[v].cnt << " " << p.first  << "-" << w << endl;
		prtrie(p.second.first);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	scanf("%d",&n);
	loop(i, n) {
		int x; scanf("%d",&x);
		freq[x]++;
	}
	for(int x = 0; x <= 5000;x++) insert(x, freq[x]);
//	prtrie(0);
//	cout << "dfs" << endl;
	f = vector<ll>(sz(trie), 0);
	siz = vector<ll>(sz(trie), 0);
	dfs(0);
//	cout << "dfs2" << endl;
	cout << dfs(0, 0) << endl;
	return 0;
}
