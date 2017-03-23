#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;


const int num_mod = 2,MAX = 200'000 + 10;

vi primes = {981957593, 972697049, 965796919, 980577181, 966964931, 974108659, 980075431, 981473159, 969821843, 979799729, 982032683, 982095251, 964378067, 973638899, 965132059, 976744303, 981593897, 963570227, 969475069, 976645057, 964657277, 978753037, 966019699, 971726099, 974616931, 980671249, 977753957, 971551267, 981123889, 963965129, 962673301, 963124867, 978915583, 970772783, 971674681, 962693027, 965244407, 974664781, 965126381, 978052087, 969542401, 966226777, 975986411, 978481381, 966835703, 981604849, 981496511, 967259537, 967010533, 979270169};


int val[num_mod];
int A[MAX],n,k;



ll add(ll a,ll b,ll mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

ll mul(ll a,ll b,ll mod){
	if(!a || !b) return 0;
	if(a < INT_MAX && b < INT_MAX) return (a*b)%mod;
	ll c = 0;
	if(a > b) swap(a,b);
	for(;a > 1;a >>= 1){
		if(a & 1) c = add(c,b,mod);
		b <<= 1;
		if(b >= mod) b -= mod;
	}
	return add(b,c,mod);
}


ll pow_mod(ll x,ll p,ll mod){
	if(!p) return 1;
	ll y = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) y = mul(x,y,mod);
		x = mul(x,x,mod);
	}
	return mul(x,y,mod);
}

int main(){
	srand(0);
	random_shuffle(all(primes));	
	int n,k; scanf("%d %d",&n,&k); n ++;
	loop(i,n) scanf("%d",A + i);
	reverse(A,A + n);

	for(int k = 0;k < num_mod;k++)
		for(int i = 0;i < n;i++)
			val[k] = add(mul(val[k],2,primes[k]),A[i],primes[k]);

	reverse(A,A + n);		
	ll common = 1;
	for(int k = 0;k < num_mod;k++) common *= primes[k];
	int p2 [num_mod],aux[num_mod],ans = 0;
	ll prd[num_mod];
	for(int j = 0;j < num_mod;j++){ 
		prd[j] = mul(common/primes[j],pow_mod(common/primes[j],primes[j] - 2,primes[j]),common);
		p2[j] = 1;
	}

	for(int i = 0;i < n;i++){
		ll x = 0;
		for(int j = 0;j < num_mod;j++){
			aux[j] = add(val[j],-mul(p2[j],A[i],primes[j]),primes[j]);
			aux[j] = mul(add(0,-aux[j],primes[j]),pow_mod(p2[j],primes[j]-2,primes[j]),primes[j]);
			x = add(x,mul(aux[j] ,prd[j],common),common);
		}

		for(int j = 0;j < num_mod;j++) assert(x%primes[j] == aux[j]);
	///	prArr(aux,num_mod,int);
	//	cerr << x << " " << common - x << endl;
		if (x == 0 && i == n-1) continue;
		if(x <= k || common - x <= k) 
			ans++;
		for(int j = 0;j < num_mod;j++) p2[j] = add(p2[j],p2[j],primes[j]);
	}	
	bool all_zero = 1;
	for(int j = 0;j < num_mod;j++) all_zero &= val[j] == 0;
	if(all_zero) ans -= n - 1;
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
