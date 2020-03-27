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

const int MAX = 100*1000 + 10, MAXP = 7;
int A[MAX];
int S[MAX][MAXP];
int n, p, k;
int ord[MAX];

ll dp[2][1 << MAXP];
int cnt[1 << MAXP];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &p, &k);
	loop(i, n) scanf("%d", A + i), ord[i] = i;
	loop(i, n) loop(j, p) scanf("%d", &S[i][j]);
	
	sort(ord, ord + n, [](const int & a, const int & b){
		return A[a] > A[b];
	});
	
	loop(msk, (1 << p)) cnt[msk] = msk ? popcnt(msk) : 0;
	loop(msk, (1 << p)) dp[0][msk] = - cnt[msk] * (1LL << 60);
	
	
	int cur = 0, other = 1;
	loop(t, n){
		swap(cur, other);
		int w = ord[t];
		loop(msk, (1 << p)) dp[cur][msk] = -(1LL << 60);
		for(int msk = 0;msk < (1 << p); msk++){
			int h = t - cnt[msk];
			if(h < 0) continue;
			dp[cur][msk] = dp[other][msk] + (h < k) * A[w];
		}
		for(int msk = 0;msk < (1 << p); msk++){
			int h = t - cnt[msk];
			if(h < 0) continue;
			loop(i, p) if(!((msk >> i) & 1)) {
				int tmsk = msk | (1 << i);
				dp[cur][tmsk] = max(dp[cur][tmsk], dp[other][msk] + S[w][i]);
			}
		}		
	}
	
	printf("%lld\n", dp[cur][(1 << p) - 1]);
	
	
	return 0;
}
