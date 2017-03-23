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

const int MAX = 5000 * 100;
vi divisors[MAX + 1];
int prime_div[MAX + 1],num[MAX + 1];
int A[MAX + 1],cnt[MAX + 1],in[MAX + 1],f[MAX + 1],n,m,x;
int mx;

void sieve(){
	divisors[1].pb(1);
	for(int i = 2;i <= mx;i++)
		if(!prime_div[i]){
			num[i] = 1;
			prime_div[i] = i;
			divisors[i].pb(1); 
			divisors[i].pb(i);
			for(ll j = i*1LL*i;j <= MAX;j += i)
				prime_div[j] = i;
		}
		else {
			num[i] = num[i / prime_div[i]] + 1;
			divisors[i] = divisors[i / prime_div[i]];
			for(int j = 0,L = sz(divisors[i]);j < L;j++)
				if(divisors[i][j]%prime_div[i])
					divisors[i].pb(divisors[i][j] * prime_div[i]);
			sort(all(divisors[i]));
			divisors[i].resize(unique(all(divisors[i])) - divisors[i].begin());
			sort(all(divisors[i]),[](const int & a,const int & b){
				return num[a] < num[b];
			});
		}
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i + 1),mx = max(mx,A[i + 1]);
	sieve();
	ll ans = 0; int ctr = 0;
	loop(i,m){
		int x; scanf("%d",&x);
		ll tmp = 0; int lst = 1,sgn = 1;
		for(int d : divisors[A[x]]) if(d != 1) {
			sgn ^= num[d] != lst;
			tmp += (2*sgn - 1) * cnt[d];
		//	tmp += f[d];
			lst = num[d];
		}
		//cerr << A[x] << " " << tmp << " " << ans << " " << ctr << endl;	
		//print(divisors[A[x]],int);	
		tmp = ctr - tmp - in[x] * (A[x] == 1);
		//cerr << "tmp = " << tmp << "\n========================" << endl;		
		if(in[x]) ans -= tmp;
		else ans += tmp;
		for(int d : divisors[A[x]]) if(d != 1) cnt[d] -= 2*in[x] - 1;
		if(sz(divisors[A[x]])%2 == 1) f[A[x]] -= 2*in[x] - 1;
		ctr -= 2*in[x] - 1;
		in[x] ^= 1;
		printf("%lld\n",ans);	
	}
	return 0;
}
