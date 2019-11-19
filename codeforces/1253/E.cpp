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


const int MAXN = 88,MAXM = 100*1000 + 10;
ll dp[MAXM];
int X[MAXN],R[MAXN];

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int n,m; 
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d %d",X + i,R + i);
	
	dp[m+1] = 0;
	for(int p = m;p > 0;p--){
		dp[p] = m - p + 1;
		for(int i = 0;i < n;i++){
			int d = abs(p - X[i]);
			d = max(d,R[i]);
			if(d == R[i]){
				dp[p] = dp[p+1];
				break;
			}
			if(p < X[i]){
				int c = d - R[i];
				int e = min(X[i] + d,m);
				dp[p] = min(dp[p],c + dp[e+1]);				
			}
		}
	}
	cout << dp[1] << endl;
	return 0;
}

