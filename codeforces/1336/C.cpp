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

const int ans_mod = 998244353;
const int MAXN = 3000 + 10;
vi cand_base {26,29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139};
vi cand_mod {999999151,999999739,1000000321,1000000861,999999163,999999751,1000000349,1000000871,999999181,999999757,1000000363,1000000891,999999191,999999761,1000000403,1000000901,999999193,999999797,1000000409,1000000919,999999197,999999883,1000000411,1000000931,999999223,999999893,1000000427,1000000933,999999229,999999929,1000000433,1000000993,999999323,999999937,1000000439,1000001011,999999337,1000000007,1000000447,1000001021,999999353,1000000009,1000000453,1000001053,999999391,1000000021,1000000459,1000001087,999999433,1000000033,1000000483,1000001099,999999487,1000000087,1000000513,1000001137,999999491,1000000093,1000000531,1000001161,999999503,1000000097,1000000579,1000001203,999999527,1000000103,1000000607,1000001213,999999541,1000000123,1000000613,1000001237,999999587,1000000181,1000000637,1000001263,999999599,1000000207,1000000663,1000001269,999999607,1000000223,1000000711,1000001273,999999613,1000000241,1000000753,1000001279,999999667,1000000271,1000000787,1000001311,999999677,1000000289,1000000801,1000001329,999999733,1000000297,1000000829,1000001333};
int base[2], mod[2], base_power[2][MAXN];

inline int mul(int a,int b,int mod){
	return (a*1LL*b)%mod;
}
inline int add(int a,int b,int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

void init_hash(){
	srand(0);
	srand(time(0));
	random_shuffle(all(cand_base));
	random_shuffle(all(cand_mod));
	loop(i,2) base[i] = cand_base[i];
	loop(i,2) mod[i] = cand_mod[i];
	loop(i,2) base_power[i][0] = 1;
	for(int i= 0;i < 2;i++)
		for(int j = 0;j < MAXN-1;j++)
			base_power[i][j + 1] = mul(base_power[i][j],base[i],mod[i]);
}

string txt, patt;
short fail[MAXN], n, m;
short mem[MAXN][26];

int get_fail(int len, char c, short *fail, const string & txt, short dp[MAXN][26]){
	short & ret = dp[len][c - 'a'];
	if(ret != -1) return ret;
	while(len && txt[len] != c) len = fail[len-1];
	if(txt[len] == c) len++;
	return ret = len;
}

int get_pref_len(int len, char c){
	return get_fail(len, c, fail, patt, mem);
}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(const pi & p) const {
		uint64_t x = p.first;
		x = (x << 32) | p.second;
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
unordered_map<pi, short, custom_hash> table[MAXN];
pi H[MAXN][MAXN];
short match[MAXN][MAXN];
short match2[2][MAXN][MAXN];

void init(){
	memset(mem, -1, sizeof mem);
	reverse(all(patt));
	n = txt.size();
	m = patt.size();
	for(int i = 1, l = 0; i < m;i++){
		fail[i] = l = get_pref_len(l, patt[i]);
	}
	init_hash();
	
	for(int s = 0;s < m; s++){
		int h[2] = {0, 0};
		for(int e = s, l = 0; e < m; e++){
			int c = patt[e] - 'a' + 1;
			loop(i, 2) h[i] = add(mul(h[i], base[i], mod[i]), c, mod[i]);
			int len = e - s + 1;
			pi p(h[0], h[1]);
			table[len][p] = s;
			H[s][len] = p;
			l = get_pref_len(l, patt[e]);
			match[s][len] = l;
		}
		loop(st, 2){
			int l = st;
			for(int e = s; e < m; e++){
				l = get_pref_len(l, patt[e]);
				match2[st][s][e-s+1] = l;
			}			
		}
	}
	
}




int dp2[MAXN][MAXN];



int solve2(int len, int i){
	if(i == n) return len == m;
	int & ret = dp2[len][i];
	if(ret != -1) return ret;
	
	ret = len == m;
	int tmp = len;
	if(tmp == m) tmp = fail[m-1];
	tmp = get_pref_len(tmp, txt[i]);
	
	ret = add(ret, solve2(tmp, i+1), ans_mod);
	ret = add(ret, solve2(len, i+1), ans_mod);
	
	return ret;
}

int dp[MAXN][MAXN];

pi get_h(char c, pi h, int len){
	int v = c - 'a' + 1;
	int a = base_power[0][len];
	int b = base_power[1][len];
	h.first = add(h.first, mul(v, a, mod[0]), mod[0]);
	h.second = add(h.second, mul(v, b, mod[1]), mod[1]);
	return h;	
}

pi get_h(pi h, char c, int len){
	int v = c - 'a' + 1;
	h.first = add(mul(h.first, base[0], mod[0]), v, mod[0]);
	h.second = add(mul(h.second, base[1], mod[1]), v, mod[1]);
	return h;
}

int solve(int st, int len){
	if(len == m) return solve2(m, m);
	int & ret = dp[st][len];
	if(ret != -1) return ret;
	
	ret = 0;
	
	pi h0 = H[st][len];
	
	char c = txt[len];
	
	pi hA = get_h(c, h0, len);
	pi hB = get_h(h0, c, len);
	
	
	

	if(table[len+1].count(hA)) ret = add(ret, solve(table[len+1][hA], len+1), ans_mod);
	else {
		ret = add(ret, solve2(match2[c==patt[0]][st][len], len+1), ans_mod);
	}
	if(table[len+1].count(hB)) ret = add(ret, solve(table[len+1][hB], len+1), ans_mod);
	else {
		ret = add(ret, solve2(get_pref_len(match[st][len], c), len+1), ans_mod);
	}
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> txt >> patt;
	init();
	memset(dp, -1, sizeof dp);
	memset(dp2, -1, sizeof dp2);
	cout << solve(0, 0) << endl;
	return 0;
}
