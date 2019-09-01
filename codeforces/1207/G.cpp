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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

struct Handler{
	vi who,len,prv;
};

const int MAX = 400*1000 + 10;
vi cand_base {26,29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139};
vi cand_mod {999999151,999999739,1000000321,1000000861,999999163,999999751,1000000349,1000000871,999999181,999999757,1000000363,1000000891,999999191,999999761,1000000403,1000000901,999999193,999999797,1000000409,1000000919,999999197,999999883,1000000411,1000000931,999999223,999999893,1000000427,1000000933,999999229,999999929,1000000433,1000000993,999999323,999999937,1000000439,1000001011,999999337,1000000007,1000000447,1000001021,999999353,1000000009,1000000453,1000001053,999999391,1000000021,1000000459,1000001087,999999433,1000000033,1000000483,1000001099,999999487,1000000087,1000000513,1000001137,999999491,1000000093,1000000531,1000001161,999999503,1000000097,1000000579,1000001203,999999527,1000000103,1000000607,1000001213,999999541,1000000123,1000000613,1000001237,999999587,1000000181,1000000637,1000001263,999999599,1000000207,1000000663,1000001269,999999607,1000000223,1000000711,1000001273,999999613,1000000241,1000000753,1000001279,999999667,1000000271,1000000787,1000001311,999999677,1000000289,1000000801,1000001329,999999733,1000000297,1000000829,1000001333};
int base[2],mod[2],base_power[2][MAX];

inline int mul(int a,int b,int mod){
	return (a*1LL*b)%mod;
}
inline int add(int a,int b,int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

void init(){
	srand(0);
//	srand(time(0));
	random_shuffle(all(cand_base));
	random_shuffle(all(cand_mod));
	loop(i,2) base[i] = cand_base[i];
	loop(i,2) mod[i] = cand_mod[i];
	loop(i,2) base_power[i][0] = 1;
	for(int i= 0;i < 2;i++)
		for(int j = 0;j < MAX-1;j++)
			base_power[i][j + 1] = mul(base_power[i][j],base[i],mod[i]);
}


const int MAX = 400*1000 + 10,MAXLEN = 650;
int trie[MAX][26],ts = 1;
int mapTo[MAX],n;
int dfs_in[MAX],dfs_out[MAX],dfs_time;

void readTrie(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		int t; scanf("%d",&t);
		int x,tc;
		if(t == 1) {
			char c; scanf(" %c",&c);
			int tc = c-'a';
			x = 0;
		}
		else {
			int x,tc; char c; scanf("%d %c",&x,&c);
			tc = c - 'a';
			x = mapTo[x];
		}
		if(trie[x][tc]) mapTo[i] = trie[x][tc];
		else mapTo[i] = trie[x][tc] = ts++;
	}
}


void dfs(int u) {
	dfs_in[u] = dfs_time++;
	for(int c = 0;c < 26;c++)
		if(trie[u][c])
			dfs(trie[u][c]);
	dfs_out[u] = dfs_time;
}

struct hasher{
public:
	ll operator () (const pi & p) const {
		return ((p.first+0LL) << 32) + p.second;
	}
};

unordered_map<pi,Handler,hasher> M;
vi seq;

inline void append(int h[2],int v) {
	for(int i = 0;i < 2;i++) {
		h[i] = mul(h[i],base[i],mod[i]);
		h[i] = add(h[i],v,mod[i]);
	}
}
inline void pop(int h[2],int v,int len) {
	for(int i = 0;i < 2;i++)
		h[i] = add(h[i],-mul(v,base_power[i][len],mod[i]),mod[i]);
}

void update(Handler & h,int u) {
	int iv = sz(h.who) - 1;
	while(iv != -1 && dfs_out[h.who[iv]] <= dfs_in[u])
		iv = h.prv[iv];
	h.who.push_back(u);
	h.prv.push_back(iv);
	h.len.push_back((iv == -1) ? 1 : (1 + h.len[iv]));
}

void dfs(int u,int h[2],int len) {
	pi ph (h[0],h[1]);
	update(M[ph],u);

	for(int c = 0;c < 26;c++) if(trie[u][c]){
		seq.push_back(c);
		int hp [2] = {h[0],h[1]};
		append(hp,c+1);
		if(sz(seq) > len) pop(hp,seq[sz(seq)-len-1]+1,len);
		dfs(trie[u][c],hp,len);
		seq.pop_back();
	}
}

void preprocess(){
	init();
	dfs(0);
	for(int len = 1;len < MAXLEN;len++) {
		int h[2] = {0,0};
		seq.clear();
		dfs(0,h,len);
	}
}
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	readTrie();
	preprocess();

	return 0;
}
