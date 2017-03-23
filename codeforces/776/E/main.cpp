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

const int MAX = 1000'000,MAXP = 78498;
int P[MAXP],m;
int not_prime[MAX];

void sieve(){
	for(int i = 2;i < MAX;i++)
		if(!not_prime[i]){
			P[m++] = i;
			for(ll j = i*1LL*i;j < MAX;j += i)
				not_prime[j] = 1;
		}
}

ll phi(ll n){
	ll ret = n;
	loop(i,m){
		ll p = P[i];
		if(p*p > n) break;
		if(n%p == 0) {
			ret -= ret/p;
			while(n %p == 0) n /= p;
		}			
	}
	if(n != 1) ret -= ret/n;
	return ret;
}

int main(){
	sieve();
	ll n,k; cin >> n >> k;
	k = (k + 1) >> 1;
	while(k && n > 1){
		n = phi(n);
		k--;
	}
	int mod = 1000000007;
	n %= mod;
	cerr << n << endl;
	cout << n << endl;
	
	
	return 0;
}
