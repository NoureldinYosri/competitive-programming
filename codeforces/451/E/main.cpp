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

const int mod = 1000000007;
int n;
ll S;
ll f[20];
int inv[] = {0, 1, 500000004, 333333336, 250000002, 400000003, 166666668, 142857144, 125000001, 111111112, 700000005, 818181824, 83333334, 153846155, 71428572, 466666670, 562500004, 352941179, 55555556, 157894738, 850000006, 47619048};

int mul(int a,int b) {
	return (a*(ll)b)%mod;
}
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

int C(ll n,int k){
	if(k > n) return 0;
	int ret = 1;
	for(int i = 0;i < k;i++) {
		ret = mul(ret,(n - i)%mod);
		ret = mul(ret,inv[i+1]);
	}
	return ret;
}

int getNum(int msk) {
	ll s = S;
	int sgn = 1;
	for(int i = 0;i < n;i++)
		if((msk >> i) & 1){
			s -= f[i] + 1;
			sgn *= -1;
		}
	if(s < 0) return 0;
	return sgn*C(s + n - 1,n-1);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	cin >> n >> S;
	loop(i,n) cin >> f[i];
	int ans = 0;
	for(int msk = 0;msk < (1 << n);msk++)
		ans = add(ans,getNum(msk));
	cout << ans << endl;
	return 0;
}
