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

int n;
int A[1 << 20];
int B[1 << 20];
int val[1 << 20], ord[1 << 20];
int BIT[1 << 20];
vi aux;
	
void add(int p, int v){
	for(++p; p <= sz(aux); p += LSOne(p))
		BIT[p] += v;
}

int get(int p){
	int ret = 0;
	for(++p; p; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	loop(i, n) scanf("%d", B + i);
	loop(i, n) aux.pb(A[i] - B[i]), aux.pb(B[i] - A[i]);
	sort(all(aux));
	aux.resize(unique(all(aux)) - aux.begin());
	
	ll ans = 0;
	loop(i, n){
		int v = B[i] - A[i];
		v = lower_bound(all(aux), v) - aux.begin();
		ans += i - get(v);
		
		v = A[i] - B[i];
		v = lower_bound(all(aux), v) - aux.begin();
		add(v, 1);
	}
	
	cout << ans << endl;
	
	return 0;
}
