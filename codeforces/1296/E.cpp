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


set<int> IDX[128];
bool vis[MAX];
vi ord;
string s;
int n;

void dfs(int u){
	if(vis[u]) return;
	vis[u] = 1;
	int c = s[u];
	for(int z = 'z'; z > c; z--){
		while(!IDX[z].empty() && *IDX[z].begin() < u){
			int v = *IDX[z].begin();
			IDX[z].erase(IDX[z].begin());
			dfs(v);
		}
	}
	ord.pb(u);
}

int color[MAX];
set<int> S[26];
int mix[26];


bool found(int x, int z){
	for(int c = z; c < 26; c++)
		if(S[c].count(x))
			return 1;
	return 0;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> s;
	loop(i, n){
		int c = s[i];
		IDX[c].insert(i);
	}
	
	loop(i, n) if(!vis[i]) dfs(i);
	
	int k = 0;
	loop(i, n){
		int c = s[i] - 'a';
		k = max(k, color[i] = mix[c]);
		S[c].insert(color[i]);
		
		for(int z = 0;z <= c;z++){
			while(found(mix[z], z+1)) mix[z]++;
		}
//		prArr(mix, 26, int);
						
	}
	k++;
	printf("%d\n", k);
	loop(i, n) printf("%d ", color[i] + 1);
	puts("");
	return 0;
}
