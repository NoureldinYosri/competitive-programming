#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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
const double PI = acos(-1);
using namespace std;

const int MAX = 100*1000 + 10;
const int mod = 1e9 + 7;
int A[MAX],n;
int prime[MAX],freq[MAX],cf[MAX];
vi divs[MAX];
vi aux;

void sieve(){
	divs[1].pb(1);
	for(int i = 2;i < MAX;i++){
		if(!prime[i]) {
			prime[i] = i;
			for(ll j = i*1LL*i;j < MAX;j += i)
				prime[j] = i;
		}
		int p = prime[i],n = i,q = 0;
		while(n%p == 0) n /= p,q++;
		divs[i] = divs[n];
		int s = 0,e = divs[i].size();
		while(q--){
			for(;s < e;s++) divs[i].pb(divs[i][s]*p);
			e += sz(divs[n]);
		}
		sort(all(divs[i]));
	}
}


int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
	return x;
}

int mul(int a,int b){
	return (a*1LL*b)%mod;
}

int powmod(int x,int p){
	if(!p) return 1;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i),freq[A[i]]++;
	for(int i = 1;i < MAX;i++)
		cf[i] = cf[i - 1] + freq[i - 1];
	sort(A,A + n);
	int ans = 0;
	for(int lcm = 1;lcm < MAX;lcm++) {
		int m = n - cf[lcm];
		int x = sz(divs[lcm]) - 1;
		int a = add(powmod(x + 1,m),-powmod(x,m)),b = 1;
		aux.clear();
		for(int d : divs[lcm]) aux.pb(lower_bound(A,A + n,lcm) - lower_bound(A,A + n,d));
		for(int i = 0;i + 1 < sz(aux);i++)
			aux[i] -= aux[i + 1];
		for(int i = 0;i < sz(aux);i++)
			b = mul(b,powmod(i+1,aux[i]));
		int tmp = mul(a,b);
//		if(lcm <= 6) cerr << lcm << " " << a << " " << b << endl;
		ans = add(ans,tmp);
	}
	cout << ans << endl;
	return 0;
}
