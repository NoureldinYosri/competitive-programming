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

const int mod = 998244353, MAX = 3e5 + 10 ;
int fact[MAX], invFact[MAX], invInt[MAX];
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

void init(){
	invInt[1] = 1;
	for(int i = 2; i < MAX; i++)
		invInt[i] = mod - mul(mod/i, invInt[mod%i]);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < MAX; i++){
		fact[i] = mul(fact[i - 1], i);
		invFact[i] = mul(invFact[i - 1], invInt[i]);
	}
}

int C(int n, int k){
	if(k > n) return 0;
	return mul(fact[n], mul(invFact[k], invFact[n - k]));
}

int n, m;
vp events;




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	scanf("%d %d", &n, &m);
	loop(i, n){
		int s, e; scanf("%d %d", &s, &e);
		events.emplace_back(s, -1);
		events.emplace_back(e, 1);
	}
	sort(all(events));
	int ans = 0, ctr = 0;
	for(auto [_, s] : events){
		if(s == -1){
			ans = add(ans, C(ctr, m - 1));
			ctr++;
		} else {
			ctr--;
		}
	}
	cout << ans << endl;
	return 0;
}
