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


using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}


ll Raise(ll x, int k){
	ll ret = 1;
	loop(i, k) ret *= x;
	return ret;
}
ll getRoot(ll x, int k){
	ll r = pow(x, 1.0/k) + 2;
	while(Raise(r, k) > x) r--;
	return r;
}

ll f(ll x){
	for(int k = 1; ; k++){
		ll r = getRoot(x, k);
		if(r == 1) break;
		if(Raise(r, k) == x && MillerRabin(r)) return r;
	}
	return 0;
}


vi V;
vector<vector<ll>> vals;
int dp[1010][1010];
int choice[1010][1010];

int solve(int i, int k){
	if(k == 0) return true;
	if(i == sz(V)) return false;
	int & ret = dp[i][k];
	if(ret != -1) return ret;
	ret = 0;
	for(int c = 0; c <= k && c <= V[i]; c++){
		if(c == 1) continue;
		ret = solve(i + 1, k - c);
		if(ret){
			choice[i][k] = c;
			break;
		}
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n, k; scanf("%d %d", &n, &k);
	if(k == 1){
		puts("0");
		return 0;
	}
	map<ll, vector<ll>> M;
	int tot = 0;
	vector<ll> bad;
	loop(i, n){
		ll x; scanf("%lld", &x);
		ll y = f(x);
		if(y) M[y].push_back(x), tot++;
		else bad.push_back(x);
	}
	
	tot = 0;
	for(auto [p, r] : M){
		if(sz(r) > 1) tot += sz(r);
	}
	
	if(tot >= k){
		for(auto [p, r] : M) {
	//		cerr << p << ": " << r.size() << endl;
	//		print(r, ll);
			if(sz(r) <= 1) continue;
			V.push_back(r.size());
			vals.push_back(r);
		}
		memset(dp, -1, sizeof dp);
		if(solve(0, k)){
			for(int i = 0; i < sz(V) && k; i++) {
				int c = choice[i][k];
				loop(k, c) printf("%lld ", vals[i][k]);
				k -= c;
			}
			puts("");
		} else {
			puts("0");
		}		
	} else {
		vector<ll> R;
		for(auto [p, r] : M)
			for(auto x : r)
				R.push_back(x);
		for(auto x : bad){
			if(sz(R) == k) break;
			ll y = x;
			for(auto [p, _] : M)
				while(y%p == 0)
					y /= p;
			if(y == 1) R.push_back(x);
		}
		
		if(sz(R) == k){
			for(ll x : R) printf("%lld ", x);
			puts("");
		} else {
			puts("0");
		}
		
	}
	
	return 0;
}
