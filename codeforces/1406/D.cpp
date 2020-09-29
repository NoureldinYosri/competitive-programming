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


int A[1 << 20], n;
ll T[2][1 << 20];
ll diff[1 << 20];

void update(int p, ll v, ll *BIT){
	for(; p <= n; p += LSOne(p)) BIT[p] += v;
}

ll get(int p, ll *BIT){
	ll ret = 0;
	for(; p; p ^= LSOne(p)) ret += BIT[p];
	return ret;
}

ll compute(){
	ll B = get(n, T[0]);
	ll C = get(1, T[1]);
	ll v = (B - C) >> 1;
	return max(B-v, C + v);
}

void logic(int i, int sgn){
	ll v = diff[i];
	update(i, sgn*max(v, 0LL), T[0]);
	update(i, sgn*min(v, 0LL), T[1]); 
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", A + i);
		diff[i] = A[i] - A[i-1];
		logic(i, 1);
	}
	printf("%lld\n", compute());
	int m; scanf("%d", &m);
	while(m--){
		int l, r, dx; scanf("%d %d %d", &l, &r, &dx);
		
		logic(l, -1);
		diff[l] += dx;
		logic(l, 1);
		
		if(r < n){
			logic(r+1, -1);
			diff[r+1] -= dx;
			logic(r+1, 1);
		}
		printf("%lld\n", compute());
	}
 	return 0;
}
