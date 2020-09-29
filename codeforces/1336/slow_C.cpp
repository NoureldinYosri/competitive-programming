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

const int mod = 998244353;
const int MAXN = 3 << 10;
string txt, patt[2];
int fail[2][MAXN], n, m;
int mem[2][MAXN][26];

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

int get_fail(int len, char c, int *fail, const string & txt, int dp[MAXN][26]){
	int & ret = dp[len][c - 'a'];
	if(ret != -1) return ret;
	while(len && txt[len] != c) len = fail[len-1];
	if(txt[len] == c) len++;
	return ret = len;
}


void init(){
	memset(mem, -1, sizeof mem);
	patt[1] = string(patt[0]);
	reverse(all(patt[1]));
	n = txt.size();
	m = patt[0].size();
	loop(c, 2){
		for(int i = 1, l = 0; i < m;i++){
			fail[c][i] = l = get_fail(l, patt[c][i], fail[c], patt[c], mem[c]);
		}
	}
}




int dp2[MAXN][MAXN];


int get_pref_len(int len, char c){
	return get_fail(len, c, fail[1], patt[1], mem[1]);
}

int solve2(int len, int i){
	if(i == n) return len == m;
	int & ret = dp2[len][i];
	
	ret = len == m;
	int tmp = len;
	if(tmp == m) tmp = fail[1][m-1];
	tmp = get_pref_len(tmp, txt[i]);
	
	ret = add(ret, solve2(tmp, i+1));
	ret = add(ret, solve2(len, i+1));
	
	return ret;
}

int dp[MAXN][MAXN];

int get_len(string A){
	int l = 0;
	for(char c : A) l = get_pref_len(l, c);
	return l;
}

bool find(string s, int & x){
	int L = sz(s);
	loop(i, m-L+1){
		if(s == patt[1].substr(i, L)){
			x = i;
			return 1;
		}
	}
	return 0;
}

int solve(int st, int len){
	if(len == m) return solve2(m, m);
	int & ret = dp[st][len];
	if(ret != -1) return ret;
	
	ret = 0;
	
	string s = patt[1].substr(st, len);
	

	int i = len;
	string A = s + txt[i];
	string B = txt[i] + s;
	
	int x;
	if(find(A, x)) ret = add(ret, solve(x, len+1));
	else ret = add(ret, solve2(get_len(A), len+1));
	
	if(find(B, x)) ret = add(ret, solve(x, len+1));
	else ret = add(ret, solve2(get_len(B), len+1));
	
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> txt >> patt[0];
	init();
	memset(dp, -1, sizeof dp);
	memset(dp2, -1, sizeof dp2);
	cout << solve(0, 0) << endl;
	return 0;
}
