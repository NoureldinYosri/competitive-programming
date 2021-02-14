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

vi children[22];
int n;
vi path[22];

void dfs(int u){
	if(u > 1) path[u].push_back(u);
	for(int v : children[u]) {
		dfs(v);
		int s = sz(path[u]);
		int one = u > 1;
		int parity = 1;
		for(int t : path[v]){
			path[u].push_back(t);
			if(parity){
				for(int i = 0; i + one < s; i++)
					path[u].push_back(path[u][s - 1 - i]);				
			} else {
				for(int i = one; i < s; i++)
					path[u].push_back(path[u][i]);
			}
			parity ^= 1;
		}
		path[v].clear();
	}
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	for(int i = 2; i <= n; i++){
		int p; scanf("%d", &p);
		children[p].push_back(i);
	}
	dfs(1);
	printf("%d\n", sz(path[1]));
	for(int v : path[1]) printf("%d ", v);
	puts("");
	return 0;
}
