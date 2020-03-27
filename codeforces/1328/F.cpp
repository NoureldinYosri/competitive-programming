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


const int MAX = 200*1000 + 50, oo = 1e9 + 50;
int n, K;

map<int, int> freq;

ll val[MAX], cnt[MAX];
int m = 0;

ll pref_cnt[MAX], suff_cnt[MAX];
ll pref_sum[MAX], suff_sum[MAX];


ll solve(){
//	prArr(val, m, ll);
//	prArr(cnt, m, ll);
	ll ret = 1LL << 60;
	
	loop(i, m){
		pref_cnt[i] = cnt[i] + (i ? pref_cnt[i-1] : 0);
		pref_sum[i] = val[i]*cnt[i] + (i ? pref_sum[i-1] : 0);
	}
	suff_cnt[m] = suff_sum[m] = 0;
	for(int i = m-1; i >= 0; i--){
		suff_cnt[i] = cnt[i] + suff_cnt[i+1];
		suff_sum[i] = val[i]*cnt[i] + suff_sum[i+1];
	}
	
	for(int i = 2; i < m-2; i++){
		ll tmp = 0;
		tmp = abs(pref_cnt[i-2]*val[i-1] - pref_sum[i-2]);
		int k = min(K - cnt[i], pref_cnt[i-1]);
		tmp += pref_cnt[i-1]*abs(val[i]-1 - val[i-1]);
		tmp += k;
		
		int r = K - cnt[i] - k;
		ll tmp2 = 0;
		
		if(r) {
			tmp2 = abs(suff_sum[i+2] - val[i+1]*suff_cnt[i+2]);
			assert(suff_cnt[i+1] >= r);
			tmp2 += suff_cnt[i+1]*abs(val[i+1]-1 - val[i]);
			tmp2 += r;
		}
		//cout << tmp << " " << tmp2 << endl;
		
		ret = min(ret, tmp + tmp2);
	}
	
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &K);
	loop(i, n) {
		int x; scanf("%d", &x);
		freq[x]++;
		if(freq[x] >= K){
			puts("0");
			return 0;
		}
	}
	freq[0] = 0;
	freq[-1] = 0;
	freq[oo] = 0;
	freq[oo+1] = 0;
	for(auto p : freq){
		val[m] = p.first;
		cnt[m] = p.second;
		m++;
	}
	
	
	ll ans = solve();
	reverse(val, val + m);
	reverse(cnt, cnt + m);
	loop(i, m) val[i] *= -1;
//	cerr << endl;
	ans = min(ans, solve());
	cout << ans << endl;
	return 0;
}
