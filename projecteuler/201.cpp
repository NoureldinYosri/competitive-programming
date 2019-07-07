//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcountll(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//using namespace std;
//
//const int MAXN = 100,MAXW = MAXN*(MAXN + 1)*(2*MAXN + 1)/6;
//
//char dp[MAXN+1][MAXN/2+1][MAXW+1];
//
//char solve(int i,int c,int r) {
//	if(r == 0) return c == 0;
//	if(i == 0) return 0;
//	char & ret = dp[i][c][r];
//	if(ret != -1) return ret;
//	ret = solve(i-1,c,r);
//	if(i*i <= r) ret += solve(i-1,c-1,r-i*i);
//	if(ret > 2) ret = 2;
//	return ret;
//}
//
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	memset(dp,-1,sizeof dp);
//	long long ans = 0;
//	for(int i = 1;i <= MAXW;i++)
//		ans += (solve(100,50,i) == 1) *i;
//	cout << ans << endl;
//	return 0;
//}
