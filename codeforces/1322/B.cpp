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


const int MAXA = 10*1000*1000 + 10;
const int MAXN = 400*1000 + 10, MAXLG = 26;
int n;
int A[MAXN], B[MAXN];
int BIT[2][MAXA];

void add(int p, int v, int *T){
	for(++p; p < MAXA; p += LSOne(p))
		T[p] += v;
}
int get(int p, int *T){
	int ret = 0;
	for(p = min(p + 1, MAXA-1); p ; p ^= LSOne(p))
		ret += T[p];
	return ret;
}




vp hist;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	int ans = 0;
	int cnt[2];
	for(int b = 0;b <= MAXLG;b++){
		int parity = 0;
		cnt[0] = cnt[1] = 0;
		loop(i, n) {
			int x = A[i] & ((2 << b) - 1);
			int x0 = (A[i] >> b)&1;
			x ^= x0 << b;
			hist.emplace_back(x0, x);
			
			if(x0 == 0){
				parity ^= cnt[0] - get((1 << b) - x - 1, BIT[0]);
				parity ^= get((1 << b) - x - 1, BIT[1]);
			}
			else {
				parity ^= get((1 << b) - x - 1, BIT[0]);
				parity ^= cnt[1] - get((1 << b) - x - 1, BIT[1]);
			}
		
			cnt[x0]++;
			add(x, 1, BIT[x0]);
		}
		while(!hist.empty()){
			add(hist.back().second, -1, BIT[hist.back().first]);
			hist.pop_back();
		}		
		parity &= 1;
		ans |= parity << b;
	}
	cout << ans << endl;
	return 0;
}
