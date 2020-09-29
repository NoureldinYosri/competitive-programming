#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const ll oo = 1LL << 60;
const int MAXN = 100*100 + 10;
int n, H;
ll A, B;
pi P[MAXN];
ll dp[MAXN];
int body[MAXN];

bool is_bad(int k, int j, int i){
	ll x = P[k].first - P[j].first, y = P[k].second;
	ll d = P[i].first - P[j].first;
	
	ll LHS = 4*x*d - 4*x*x;
	ll RHS = 2*y - 2*H + d;
	if(RHS < 0) return 0;
	RHS *= RHS;
	return LHS < RHS;
}

bool is_good(int i, int j){
	ll d = P[i].first - P[j].first;
	return 2*max(P[i].second, P[j].second) <= 2*H-d;	
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d %lld %lld", &n, &H, &A, &B);
	loop(i, n) {
		scanf("%d %d", &P[i].first, &P[i].second);
		if(P[i].second > H) {
			puts("impossible");
			return 0;
		}
	}
	
	dp[0] = A*(H - P[0].second);
	body[0] = 1;
	
	for(int i = 1; i < n;i ++){
		dp[i] = oo;
		loop(j, i) if(is_good(i, j)) {
			bool can = 1;
			
			int & k = body[j];
			
			for(k = max(j + 1, k-2); k < i; k++) {
				can = !is_bad(k, j, i);
				if(!can) break;
			}
			ll d = P[i].first - P[j].first;
			if(can) dp[i] = min(dp[i], dp[j] + A*(H - P[i].second) + B*d*d);
		}
		body[i] = i+1;
	}
	
	
	if(dp[n-1] >= oo) puts("impossible");
	else cout << dp[n-1] << endl;
	
	return 0;
}
