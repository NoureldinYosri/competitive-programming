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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int oo = 1 << 29;
const int MAXN = 100*1000 + 10,MAXA = 100*1000 + 10;
int f[MAXA],A[MAXN],n;

int bin(int x,int *A) {
	int n = 0;
	while(x) {
		A[n++] = x&1;
		x >>= 1;
	}
	if(!n) A[n++] = 0;
	reverse(A,A + n);
	return n;
}

int getCost(int x,int v){
	static int A[50],B[50];
	int ret = 0;
	while(x > v) x >>= 1,ret++;

	int n = bin(x,A);
	int m = bin(v,B);
	assert(n <= m);
	ret += m - n;
	for(int i = n;i < m;i++) if(B[i]) return oo;
	int lst = n;
	for(int i = n-1;i >= 0;i--)
		if(A[i] != B[i]) {
			if(B[i]) return oo;
			lst = i;
		}
	ret += (n - lst)*2;
	return ret;
}

int getCost(int v) {
	int tmp = 0;
	loop(i,n){
		int x = A[i];
		int cost = getCost(x,v);
		tmp = min(tmp + cost,oo);
	}
//	cout << v << ": " << tmp << endl;
	return tmp;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	int g = *min_element(A,A + n);
	int big = *max_element(A,A + n);
	int ans = INT_MAX;
	for(int v = g;v;v >>= 1) {
		for(int t = v;t <= big;t <<= 1)
			ans = min(ans,getCost(t));
	}
	cout << ans << endl;
	return 0;
}
