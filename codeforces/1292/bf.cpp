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
int state[3][MAX];
bool vis[3][MAX];
int n;

bool dfs(int r, int c){
	if(r < 1 || c < 1) return 0;
	if(r > 2 || c > n) return 0;
//	cout << r << " " << c << " " << n << endl;
	
	if(state[r][c]) return 0;
	if(r == 2 && c == n) return 1;
	if(vis[r][c]) return 0;
	vis[r][c] = 1;
	for(int i = -1;i <= 1;i++)
		for(int j = -1; j<= 1; j++)
			if(abs(i) + abs(j) == 1)
				if(dfs(r+i, c + j))
					return 1;
	return 0;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif

	int m;
	cin >> n >> m;
	while(m--){
		int r,c; cin >> r >> c;
		state[r][c] ^= 1;
		memset(vis, 0, sizeof vis);
		puts(dfs(1,1) ? "YES" : "NO");
	}
	return 0;
}
