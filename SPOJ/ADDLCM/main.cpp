#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
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

const int MAX = 1000000 + 1,r2 = 500000004,mod = 1000000007;
int prime[MAX];
int divs[240],siz = 0;
int phi[MAX];
ll sig[MAX],tot[MAX];
map<pi,int> memo;
ll cnt[240];

inline int add(ll a,ll b){
	if(abs(a) >= mod) a %= mod;
	if(abs(b) >= mod) b %= mod;
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

inline int mul(ll a,ll b){
	if(abs(a) >= mod) a %= mod;
	if(abs(b) >= mod) b %= mod;
	return (a*1LL*b)%mod;
}

void sieve(){
	for(int i = 1;i < MAX;i++) phi[i] = i;
	for(int i = 2;i < MAX;i++)
		if(!prime[i]) {
			prime[i] = i;
			phi[i] = i - 1;
			for(int j = 2*i;j < MAX;j += i){
				prime[j] = i;
				phi[i] -= phi[i]/i;
			}
		}
	sig[1] = 1;
	for(int i = 2;i < MAX;i++) {
		ll n = i,p = prime[i],q = 1;
		while(n%p == 0){
			n /= p;
			q *= p;
		}

		sig[i] = mul(sig[n] , ((q*q*p + 1)/(p + 1)));
	}
	for(int i = 1;i < MAX;i++)
		tot[i] = mul(mul(sig[i] + 1,i),r2);
}


void get_divs(int n){
	if(n == 1) {
		divs[0] = 1;
		siz = 1;
		return;
	}
	int p = prime[n],ctr = 0;
	while(n%p == 0) {
		ctr++;
		n /= p;
	}
	get_divs(n);
	int start = 0,end = siz,cur = siz;
	loop(i,ctr) {
		for(;start < end;start++) divs[cur++] = divs[start]*p;
		end = cur;
	}
	siz = end;
}



int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	int T; scanf("%d",&T);
	while(T--) {
		int a,b; scanf("%d %d",&a,&b);
		pi mem = mp(a,b);
		if(memo.find(mem) != memo.end()) {
			printf("%d\n",memo[mem]);
			continue;
		}
		int ans = tot[b];
		a--;
		if(a){
			get_divs(b);
			sort(divs,divs + siz);
			reverse(divs,divs + siz);
			int tmp = 0;
			for(int i = 0;i < siz;i++) {
				int d = divs[i];
				// b*j/gcd(j,b)
				// gcd(i,b) = d
				cnt[i] = mul(mul(a/d , a/d + 1),r2);
				for(int j = 0;j < i;j++)
					if(divs[j]%divs[i] == 0)
						cnt[i] = add(cnt[i],-mul((divs[j]/divs[i]), cnt[j]));
				tmp = add(tmp,cnt[i]);
			}
//			cerr << a << " " << b << endl;
//			prArr(divs,siz,int);
//			prArr(cnt,siz,int);
			tmp = mul(tmp,b);
//			cerr << a << " " << b << " " << tmp << endl;
			ans = add(ans,-tmp);
		}
		printf("%d\n",ans);
		memo[mem] = ans;
	}
	return 0;
}
