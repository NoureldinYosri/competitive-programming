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


const int mod = 1e9 + 7;

int n;
string s;

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int mul(int a, int b){
	return (a*(ll)b)%mod;
}




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> s;
	n = sz(s);
	vi V;
	for(int i = 0; i < n; ){
		int j = i;
		while(j < n && s[i] == s[j]) j++;
		if(V.empty() && s[i] == '1') V.pb(0);
		V.pb(j - i);			
		i = j;
	}
	if(sz(V) == 1){
		cout << n << endl;
		return 0;
	}
	int m = sz(V);
	vi dp(m, 1);
	vi inv(n+1, 1);
	for(int i = 2; i <= n;i ++)
		inv[i] = mod - mul(mod/i, inv[mod%i]);
	int scale = V[0] + 1;
	if(m&1){
		scale = mul(scale, V.back() + 1);
		V.pop_back();
		m = sz(V);
	}

	vp ones;


	int sum_zero = 1;
	for(int i = 1; i < m; i++){
		if(i & 1){
/*			int tmp = 0;
			for(int j = 0; j < i; j += 2){
				tmp = add(tmp, mul(dp[j], V[i]));
			}
			dp[i] = tmp;
*/			dp[i] = mul(V[i], sum_zero);
			ones.emplace_back(dp[i], 0);
		} else {
			int tmp = 0, sum = 0;
			while(!ones.empty() && ones.back().second < V[i]){
				auto [v, h] = ones.back(); ones.pop_back();
				sum = add(sum, v);
				tmp = add(tmp, mul(v, V[i] - h));
			}
			ones.emplace_back(sum, V[i]);
			dp[i] = tmp;
			sum_zero = add(sum_zero, tmp);
		}
	}
	
//	print(dp, int);
	
	int ans = 0;
	for(int i = 1; i < m; i += 2) ans = add(ans, dp[i]);
	ans = mul(ans, scale);
	cout << ans << endl;
	return 0;
}
