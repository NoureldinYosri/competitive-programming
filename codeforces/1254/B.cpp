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


ll S;
int A[1 << 20],B[1 << 20];
int n;

vector<ll> primes;

void factor(ll v){	
	for(ll x = 2;x*x <= v;x++){
		if(v%x == 0){
			primes.push_back(x);
			while(v%x == 0) v /= x;
		}
	}
	if(v > 1) primes.push_back(v);
}


vector<ll> aux;
ll pref[1 << 20];

ll work(ll p){
	int m = sz(aux);
	loop(i,m) {
		pref[i] = i*aux[i];
		pref[i] += i ? pref[i-1] : 0;
	}
	assert(accumulate(all(aux),0LL) == p);
	
	ll ret = 1LL << 60;
	ll suff = 0,suffCnt = 0;
	for(int k = m-1;k >= 0;k--){
		ll prefCnt = p - suffCnt;
		ll tmp = prefCnt*k - pref[k];
		tmp += suff - suffCnt*k;
		ret = min(ret,tmp);
		
		suff += k*aux[k];
		suffCnt += aux[k];
	}
	return ret;
}

ll solve(ll p){
	if(accumulate(A,A + n,0LL)%p) return 1LL << 60;
	loop(i,n) B[i] = A[i]%p;
	
	ll ret = 0;
	for(int i = 0;i < n;) {
		if(B[i] == 0) i++;
		else{
			int j = i;
			ll s = 0;
			aux.clear();
			while(j < n && s < p){
				s += B[j];
				aux.push_back(B[j]);
				j++;
			}
			i = j-1;
			B[i] = s%p;
			aux.back() -= B[i];
			assert(aux.back() > 0);
			ret += work(p);
		}
	}

	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		S += A[i];
	}
	if(S <= 1){
		puts("-1");
		return 0;
	}
	factor(S);
	ll ans = LLONG_MAX;
	for(ll p : primes)
		ans = min(ans,solve(p));
	cout << ans << endl;
	return 0;
}

