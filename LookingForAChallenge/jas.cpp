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

const int MAXN = 50*1000 + 10;
set<int>* F[MAXN];
vi G[MAXN];
int n;

void dfs(int u, int p){
	int t = -1;
	for(int v : G[u]) if(v != p){
		dfs(v, u);
		if(t == -1 || F[v]->size() > F[t]->size())
			t = v;
	}
	if(t == -1) F[u] = new set<int>();
	else F[u] = F[t];
	int a = -1;
	for(int v : G[u]) if(v != p && v != t){
		for(int x : *F[v]) {
			if(F[u]->count(x)) a = max(a, x);
			else F[u]->insert(x);
		}
	}
	int b = a+1;
	while(F[u]->count(b)) b++;
	while(!F[u]->empty() && *F[u]->begin() < b) F[u]->erase(F[u]->begin());
	F[u]->insert(b);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1, 0);
	cout << *F[1]->rbegin() << endl;
	return 0;
}
