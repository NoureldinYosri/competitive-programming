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
ll BIT[MAX];
int n;
int A[MAX];

void add(int p, int v){
	for(;p < MAX; p += LSOne(p))
		BIT[p] += v;
}
ll get(int p){
	ll ret = 0;
	for(;p; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		int m; scanf("%d %d", &n, &m);
		while(m--){
			int t ,a , b; scanf("%d %d %d", &t, &a, &b);
			if(t == 1) {
				add(a, b - A[a]);
				A[a] = b;
			}
			else {
				printf("%lld\n", get(b) - get(a - 1));
			}
		}
//		fill(BIT, BIT + n + 1, 0);
//		fill(A, A + n + 1, 0);
	}
	return 0;
}
