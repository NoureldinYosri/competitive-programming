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

const int MAX = 1000000 + 10;
int P[MAX];
ll sig[MAX],ans[MAX];

void init(){
	for(int i = 2;i < MAX;i++)
		if(!P[i]) {
			P[i] = i;
			for(ll j = i*1LL*i;j < MAX;j += i)
				P[j] = i;
		}
	sig[1] = 1;
	for(int i = 2;i < MAX;i++) {
		ll n = i,p = P[i],q = 1;
		while(n%p == 0){
			n /= p;
			q *= p;
		}
		sig[i] = sig[n] * ((q*q*p + 1)/(p + 1));
	}
	for(int i = 1;i < MAX;i++){
		ans[i] = ((sig[i] + 1)*i)/2;
	}

}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	init();
	int T; scanf("%d",&T);
	while(T--){
		int n; scanf("%d",&n);
		printf("%lld\n",ans[n]);
	}
	return 0;
}
