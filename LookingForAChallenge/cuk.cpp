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


const ll oo = 1LL << 60;
using pl = pair<ll, ll>;
using vpl = vector<pl>;
int A[24];
int n;

void generate(int offset, int len,vpl  & V){
	int p3 = 1;
	loop(i, len) p3 *= 3;
	for(int msk = 0;msk < p3; msk++){
		ll S[3] = {0};
		for(int s = msk, i = 0; i < len; i++) {
			int j = i + offset;
			S[s%3] += A[j];
			s /= 3;
		}
		V.emplace_back(S[1] - S[0], S[2] - S[1]);
	}
}

vpl L, R;

map<ll, ll> M;


inline void insert(ll x, ll y){
	static vector<ll> aux;
	auto ptr = M.lower_bound(x);
	if(ptr != M.end() && ptr->second <= y) return;
	
	aux.clear();
	M[x] = y;
	ptr = M.find(x);
	while(ptr != M.begin()){
		ptr--;
		if(ptr->second < y) break;
		aux.pb(ptr->first);
	}
	for(ll v : aux) M.erase(v);
		
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	int m = n/2;
	generate(0, m, L);
	generate(m, n-m, R);
	
	sort(all(L));
	sort(all(R));
	ll ans = LLONG_MAX;
	int j = sz(R)-1;
	for(auto p : L){
		while(j >= 0 && R[j].first >= -p.first){
			auto q = R[j--];
			insert(q.second, q.first + q.second);
		}
		auto ptr = M.lower_bound(-p.second);
		if(ptr == M.end()) continue;
		ans = min(ans, p.first + p.second + ptr->second);
	}
	cout << ans << endl;
	return 0;
}
