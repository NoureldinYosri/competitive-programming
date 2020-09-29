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

char txt[1 << 20];
int n;
int vis[1 << 20][4];
vector<string> ans;

bool dfs(int i, int len){
	if(i == n) return true;
	if(vis[i][len] != -1) return vis[i][len];
	string prv;
	loop(j, len) prv.pb(txt[i-1-j]);
	reverse(all(prv));
	string nxt;
	bool res = false;
	for(int j = i; j < n && sz(nxt) < 3; j++){
		nxt.pb(txt[j]);
		if(sz(nxt) == 1 || nxt == prv) continue;
		if(dfs(j + 1, sz(nxt))){
			ans.pb(nxt);
			res = true;
		}
	}
	return vis[i][len] = res;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%s", txt);
	n = strlen(txt);
	memset(vis, -1, sizeof vis);
	for(int i = 5; i < n; i++)
		dfs(i, 0);
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	printf("%d\n", sz(ans));
	for(string & s : ans) printf("%s\n", s.c_str());
	return 0;
}
