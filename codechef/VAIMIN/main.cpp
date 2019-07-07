#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

const int MAXA = 4 << 20;
const int MAXN = 5 << 10,mod = 1e9 + 7;
set<pi> forbidden;
int p,q,c,M;
int X[MAXN],Y[MAXN];
int fact[MAXA],invi[MAXA],invf[MAXA];

int brute_force_dp[MAXN][MAXN];
int brute_force_solve(int g,int b) {
	if(p >= MAXN || q >= MAXN) return -1;
	if(forbidden.count(mp(g,b))) return 0;
	if(p == g && q == b) return 1;
	int & ret = brute_force_dp[g][b];
	if(ret != -1) return ret;
	ret = 0;
	if(g+1 <= p) ret = brute_force_solve(g+1,b);
	if(b+1 <= q && g-b > c) ret += brute_force_solve(g,b+1);
	if(ret >= mod) ret -= mod;
	return ret;
}
int brute_force() {
	memset(brute_force_dp,-1,sizeof brute_force_dp);
	return brute_force_solve(0,0);
}

int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a,int b) {
	return (a*1LL*b)%mod;
}

void init(){
	fact[0] = 1;
	for(int i = 1;i < MAXA;i++)
		fact[i] = mul(fact[i-1],i);

	invi[1] = 1;
	for(int i = 2;i < MAXA;i++){
		invi[i] = mul(mod-mod/i,invi[mod%i]);
		assert(mul(invi[i],i) == 1);
	}

	invf[0] = 1;
	for(int i = 1;i < MAXA;i++)
		invf[i] = mul(invf[i-1],invi[i]);
}
int C(int n,int k) {
	if(k > n || k < 0) return 0;
	int ret = fact[n];
	ret = mul(ret,invf[k]);
	ret = mul(ret,invf[n-k]);
	return ret;
}

int formula(int g,int b,int c){
	if(g-c < b) return 0;
	if(g < 0 || b < 0) return 0;
	g -= c;
	int r = C(g+b,g);
	r = mul(r,g-b+1);
	r = mul(r,invi[g+1]);
	return r;
}

int get_cnt(int f,int t) {
	int g = X[t] - X[f],b = Y[t] - Y[f];
	int nc = c - X[f] + Y[f];
	if(nc >= 0) return formula(g,b,nc);
	else {
		int m = -nc + 1,ret ;
		if(b > g + m - 1) ret = 0;
		else {
			ret = C(g + b,g);
			if(m <= b)
				ret = add(ret,-C(g+b,b-m));
		}
		return ret;
	}
}

int paths[MAXN][MAXN];

bool inrange (int x,int l,int r) {
	return l <= x && x <= r;
}

bool inpath(int f,int k,int t) {
	return inrange(X[k],X[f],X[t]) && inrange(Y[k],Y[f],Y[t]);
}

int get_paths(int f,int t) {
	if(f == t) return 1;
	if(f > t) return 0;
	int & ret = paths[f][t];
	if(ret != -1) return ret;

	ret = get_cnt(f,t);
	for(int k = f+1;k < t;k++) if(inpath(f,k,t)){
//		if(f == 0 && t == 3){
//			cerr << f << " < " << k << " < " << t << "\t" ;
//			cerr << get_paths(f,k) << "*" << get_cnt(k,t) << endl;
//			cerr << "was " << ret << endl;
//		}
		ret = add(ret,-mul(get_paths(f,k),get_cnt(k,t)));
	}
	return ret;
}


int solve(){
	if(q && c > p) return 0;
	if(c > p) return q == 0;
	memset(paths,-1,sizeof paths);
	int m = 0;
	for(auto p : forbidden){
		if(p.xx-c >= p.yy){
			++m;
			X[m] = p.xx;
			Y[m] = p.yy;
		}
		if(p.yy == 0 && p.xx <= c) return 0;
	}
	X[0] = c,Y[0] = 0;
	X[m+1] = p,Y[m+1] = q;
//	prArr(X,m+2,int);
//	prArr(Y,m+2,int);
//	get_paths(0,m+1);
//	for(int i = 0;i < m+1;i++){
//		prArr(paths[i],m+2,int);
//	}
	return get_paths(0,m+1);
}


void create_case(){
	p = rand()%5;
	q = rand()%5;
	c = rand()%5;
	M = rand()%5 + 1;
	forbidden.clear();
	loop(i,M)
		forbidden.insert(mp(rand()%5,rand()%5));
	M = sz(forbidden);
}

void test(){
	for(int t = 0;t < 100;t++) {
		create_case();
		int correct = brute_force();
		int s = solve();
		if(correct != s) {
			cerr << "failed on " << endl;
			cerr << p << " " << q << " " << c << " " << M << endl;
			for(auto po : forbidden)
				cerr << po.xx << " " << po.yy << endl;
			cerr << "expected " << correct << " found " << s << endl;
			return;
		}
	}
	cerr << "passed :)" << endl;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	init();
	scanf("%d %d %d",&p,&q,&c);
	scanf("%d",&M);
	loop(i,M){
		int a,b; scanf("%d %d",&a,&b);
		forbidden.insert(mp(a,b));
	}
//	printf("%d\n",brute_force());
	cout << solve() << endl;

//	if(q && p < c) cerr << 0 << endl;
//	else{
//		X[0] = 0,Y[0] = 0;
//		X[1] = p,Y[1] = q;
//		cout << get_cnt(0,1) << endl;
//	}
//	for(c = 0; c != -4;c--){
//		cerr << c << endl;
//		for(p = 0;p <= 10;p++,cerr << endl)
//			for(q = 0;q <= 10;q++){
//				X[0] = 0,Y[0] = 0;
//				X[1] = p,Y[1] = q;
//				cerr << "(" << brute_force() << ", " << get_cnt(0,1) << ")" << " ";
//			}
//	}

//	test();

	return 0;
}
