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


const int MAX = 1024;
int n, m;
vi G[MAX];
int knows[MAX];
bool dead[MAX];

int k;


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
		knows[a]++;
		knows[b]++;
	}
	knows[0] = INT_MAX;
	k = n/3;
	while(1){
		int i = min_element(knows, knows + n + 1) - knows;
		if(knows[i] >= k-1) break;
		knows[i] = INT_MAX;
		dead[i] = 1;
		for(int v : G[i])
			knows[v]--;
	}
	for(int i = 1; i <= n && k; i++) if(!dead[i]) {
		printf("%d ", i);
		k--;
	}
	return 0;
}
