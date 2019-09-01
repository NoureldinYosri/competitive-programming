#ifdef ACTIVE
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


const int MAXN = 2 << 10;
int n;
int A[MAXN];
int B[MAXN],m;
vi pos[MAXN];



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	copy(A,A + n,B);
	m = n;
	sort(B,B + m);
	m = unique(B,B + m) - B;
	loop(i,n) {
		A[i] = lower_bound(B,B + m,A[i]) - B;
		pos[A[i]].push_back(i);
	}

	int ans = n-1;
	for(int i = 0;i < n;i++) {
		int e = i;
		for(int v = 0;v < m;v++) {
			if(sz(pos[v]) <= 1) continue;
			int j = lower_bound(all(pos[v]),i) - pos[v].begin();
			if(j > 1) {
				e = i + 2*n;
				break;
			}
			int k = sz(pos[v]) - 2 + j;
			e = max(e,pos[v][k] + 1);
//			if(i == 1) cout << j << " " << k << " " << e << endl;
		}
		ans = min(ans,e - i);
	}
	cout << ans << endl;
	return 0;
}
#endif
