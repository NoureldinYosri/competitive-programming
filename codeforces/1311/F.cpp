#pragma GCC optimize ("O3")
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


const int MAX = 1 << 20;
using pl = pair<ll, ll>;
vi aux;
pi P[MAX];
int n;

pl R[MAX];
pl L[MAX];

pl operator + (const pl & A, const pl & B){
	return pl(A.first + B.first, A.second + B.second);
}
pl operator - (const pl & A, const pl & B){
	return pl(A.first - B.first, A.second - B.second);
}

void add(int p, pl v, pl *BIT){
	for(;p < MAX; p += LSOne(p))
		BIT[p] = BIT[p] + v;
}
pl get(int p, pl *BIT){
	pl ret (0, 0);
	for(;p; p ^= LSOne(p))
		ret = ret + BIT[p];
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", &P[i].first);
	loop(i, n) {
		scanf("%d", &P[i].second);
		aux.pb(abs(P[i].second));
	}
	sort(all(aux));
	aux.resize(unique(all(aux)) - aux.begin());
	sort(P, P + n);
	
	ll ans = 0;
	loop(i, n){
		int x = P[i].first, v = P[i].second;
		int dir = (v > 0) - (v < 0);
		v = abs(v);
		v = upper_bound(all(aux), v) - aux.begin();
		
		ll cur = 0;
		pl tmp(0, 0);
		if(dir >= 0){
			tmp = get(v, R) + get(MAX-1, L);
			cur = tmp.second * x - tmp.first;
			add(v, pl(x, 1), R);
		}
		else {
			tmp = get(MAX-1, L) - get(v-1, L); 
			cur = tmp.second * x - tmp.first;			
			add(v, pl(x, 1), L);
		}
		//cerr << P[i] << " " << cur << " " << tmp << endl;
		ans += cur;
	}
	cout << ans << endl;
	return 0;
}
