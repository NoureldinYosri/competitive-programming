#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
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
const double PI = acos(-1);
using namespace std;

const ll oo = 1LL << 60;
int n,k,p;
int A[1024],B[2 << 10];
ll dp[1 << 10][2 << 10];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&k,&p);
	range(i,1,n) scanf("%d",A + i);
	range(i,1,k) scanf("%d",B + i);
	sort(A+1,A + n + 1);
	sort(B+1,B + k + 1);
	range(i,0,n) dp[i][0] = oo;
	range(i,0,k) dp[0][i] = 0;
	range(i,1,n)
		range(j,1,k) {
			dp[i][j] = min(dp[i][j - 1],max(dp[i - 1][j - 1] , abs(A[i] - B[j] + 0LL) + abs(B[j] - p + 0LL)));
		}
	cout << dp[n][k] << endl;
	return 0;
}
