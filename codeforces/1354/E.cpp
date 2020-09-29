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

const int MAX = 5 << 10;
vi G[MAX];
int color[MAX], n, m;
vi sub[2];
vector<pair<vi, vi>> subs;

void dfs(int u, int c){
	if(color[u] != -1){
		if(color[u] == c) return;
		puts("NO");
		exit(0);
	}
	color[u] = c;
	sub[c].pb(u);
	for(int v : G[u]) dfs(v, c^1);
}

vp V;

void floodfill(int u){
	loop(c, 2) sub[c].clear();
	dfs(u, 0);
	V.emplace_back(sz(sub[0]), sz(sub[1]));
	subs.emplace_back(sub[0], sub[1]);
}


int dp[MAX][MAX];
int C[MAX][MAX];

int solve(int i, int s){
	if(i == sz(V)) return s == 0;
	int & ret = dp[i][s];
	if(ret != -1) return ret;
	ret = 0;
	if(V[i].first <= s && solve(i+1, s - V[i].first)){
		ret = 1;
		C[i][s] = 0;
	}
	if(V[i].second <= s && solve(i+1, s - V[i].second)){
		ret = 1;
		C[i][s] = 1;
	}
	return ret;
}

string ans;

int n1, n2, n3;
void recon(){
	int i = 0, s = n2;
	ans = string(n, '0');
	while(i < sz(V)){
		int c = C[i][s];
		vi & A = (c == 0) ? subs[i].first : subs[i].second;
		vi & B = (c == 0) ? subs[i].second : subs[i].first;
		for(int x : A) ans[x-1] = '2';
		for(int x : B){
			if(n1) {
				ans[x-1] = '1';
				n1--;
			}
			else ans[x-1] = '3';
		}
		i++;
		s -= A.size();
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	scanf("%d %d %d", &n1, &n2, &n3);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	memset(color, -1, sizeof color);
	for(int i = 1; i <= n; i++) if(color[i] == -1) floodfill(i);
//	for(auto p : V) cerr << p;
//	cerr << endl;
	memset(dp, -1, sizeof dp);
	if(!solve(0, n2)) {
		puts("NO");
	}
	else {
		puts("YES");
		recon();
		cout << ans << endl;
	}
	return 0;
}
