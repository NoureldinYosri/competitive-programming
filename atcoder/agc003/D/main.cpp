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


typedef pair<ll,ll> pl;
const int MAX = 100*1000;
vi P;
bool not_prime[MAX + 1];
map<ll,pair<vl,vl> > memo;

void init(){
	for(int i = 2;i <= MAX;i++)
		if(not_prime[i] == 0){
			P.pb(i);
			for(ll j = i*1LL*i; j <= MAX;j += i)
				not_prime[j] = 1;
		}
}


pair<vl,vl> canonize(ll x) {
	if(memo.find(x) != memo.end()) return memo[x];
	vl self,anti;
	ll y = x;
	for(int p : P){
		if(p*1LL*p > x) break;
		if(x%p == 0) {
			int e = 0;
			while(x%p == 0) x /= p,e++;
			e %= 3;
			if(e == 0) continue;
			self.pb(p);
			anti.pb(p);
			if(e == 2) self.pb(p);
			else anti.pb(p);
		}
	}
	if(x > 1) {
		self.pb(x);
		anti.pb(x);
		anti.pb(x);
	}
	return memo[y] = mp(self,anti);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	init();
	map<vl,vl> toAnti;
	map<vl,int> cnt;
	int n; scanf("%d",&n);
	int cubes = 0;
	loop(i,n) {
		ll x; scanf("%lld",&x);
		pair<vl,vl> tmp = canonize(x);
		vl self = tmp.xx, anti = tmp.yy;
		if(self.empty()) {
			cubes++;
			continue;
		}
		cnt[self]++;
		toAnti[self] = anti;
	}

	int ans = cubes > 0;
	while(!cnt.empty()) {
		vl self = cnt.begin()->xx;
		assert(toAnti.find(self) != toAnti.end());
		vl anti = toAnti[self];
		ans += max(cnt[self],cnt[anti]);
		cnt.erase(self);
		cnt.erase(anti);
	}
	cout << ans << endl;
	return 0;
}
