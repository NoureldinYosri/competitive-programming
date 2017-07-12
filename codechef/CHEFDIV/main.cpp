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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 1 << 20;
int notP[MAX];
vi P;
vi Ps[MAX];

void sieve(){
	P.reserve(78498);
	for (int i = 2;i < MAX;i++)
		if(notP[i] == 0){
			P.pb(i);
			for(ll j = i*1LL*i;j < MAX;j += i)
				notP[j] = 1;
		}
}


int main(){
	//freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	sieve();
	ll a,b; cin >> a >> b;
	vi Q;
	ll ans = 0;
	for(int p : P) {
		if(a%p == 0) Ps[0].pb(p);
		else Ps[p - a%p].pb(p);
	}
	for(ll N = a,i = 0;N <= b;N++,i++){
		ll n = N,seg = 1;
		for(int p : Ps[i]){
			assert(n%p == 0);
			int ctr = 0;
			while(n%p == 0){
				n /= p;
				ctr++;
			}
			seg *= ctr + 1;
			Q.pb(ctr);
			if(i + p < MAX) Ps[i + p].pb(p);
		}
		if(n != 1){
			bool c = 1;
			for(int q = 2;q*q <= n && c;q++)
				c = n%q != 0;
			seg *= 2;
			Q.pb(1);
		}
		sort(all(Q));
		while(!Q.empty()){
			ans += seg;
			seg = (seg*Q.back())/(Q.back() + 1);
			Q.back()--;
			if(!Q.back()) Q.pop_back();
			else {
				int j = sz(Q) - 1;
				while(j && Q[j - 1] > Q[j]){
					swap(Q[j],Q[j - 1]);
					j--;
				}
			}
		}
	}
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}

