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


const int oo = 1 << 29;
int n;
int A[300][300];
int dp[300][300][2*300+10];

int solve(int low,int high,int steps){
	int c1 = steps - low,c2 = steps - high;
	if(c1 == n || c2 == n) return -oo;
	if(low == n || high == n) return -oo;
	if(low == n-1 && c1 == n-1 && high == n-1 && c2 == n-1) return A[n-1][n-1];
	if(high > low) return -oo;
	if(c2 < c1) return -oo;
	int & ret = dp[low][high][steps];
	if(ret != INT_MIN) return ret;
	ret = -oo;
	loop(i,2) loop(j,2) ret = max(ret,solve(low+i,high+j,steps + 1));
	ret += A[low][c1];
	if(mp(low,c1) != mp(high,c2)) ret += A[high][c2];
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) loop(j,n) scanf("%d",&A[i][j]);
        fill(&dp[0][0][0],&dp[300][0][0],INT_MIN);
	if(n == 1) printf("%d\n",A[0][0]);
	else cout << solve(0,0,0) << endl;
	return 0;
}
