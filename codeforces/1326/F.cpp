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

const int MAXN = 15;

ll dp[MAXN][1 << MAXN];
int visID[MAXN][1 << MAXN], visNum;
char G[MAXN+1][MAXN+1];
vi target;
int s, e, N;

ll get_count(int prv, int msk){
	//cout << prv << " " << msk << endl;
	if(!msk) return 1;
	ll & ret = dp[prv][msk];
	if(visID[prv][msk] == visNum) return ret;
	visID[prv][msk] = visNum;
	ret = 0;
	int rem = popcnt(msk);
//	cout << sz(target) << " " << msk << " " << rem << endl;
	int tb = target[sz(target) - rem];
	for(int i = s; i < e; i++){
		int b = (msk >> i) & 1;
		if(!b) continue;
		if(G[prv][i]-'0' != tb)
			ret += get_count(i, msk ^ (1 << i));
	}
	return ret;
}

void i2v(int msk, int len){
	target.clear();
	while(msk){
		target.pb(msk & 1);
		msk >>= 1;
	}
	while(sz(target) < len) target.pb(0);
}

ll cnt[MAXN][1 << MAXN];

void work(int offset, int len){
	s = offset;
	e = s + len;
	for(int msk = 0; msk < (1 << (len-1)); msk++){
		i2v(msk, len-1);
		visNum++;
		int tot = (1 << N) - 1;
		tot &= ((1 << e) - 1) ^ ((1 << s) - 1);
		for(int i = s; i < e; i++)
			cnt[i][msk] = get_count(i, tot^(1 << i));
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &N);
	loop(i, N) scanf("%s", G[i]);
	work(0, N);
	
	for(int msk = 0; msk < (1 << (N-1)); msk++){
		ll ans = 0;
		loop(i, N) ans += cnt[i][msk];
		printf("%lld ", ans);
	}
	puts("");

	return 0;
}
