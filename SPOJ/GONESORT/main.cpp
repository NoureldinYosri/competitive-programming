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


const int MAX = 250 + 10;
int A[MAX],B[MAX],idx[MAX];
int dp[MAX];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		int n; scanf("%d",&n);
		loop(i,n) scanf("%d",A + i),B[i] = A[i];
		sort(B,B + n);
		int m = unique(B,B + n) - B;
		loop(i,n) {
			A[i] = lower_bound(B,B + m,A[i]) - B;
			idx[A[i]] = i;
		}
		idx[m] = -1;
		int ans = 0;
		for(int i = m-1;i >= 0;i--){
			if(idx[i + 1] > idx[i]) dp[i] = dp[i + 1] + 1;
			else dp[i] = 1;
			ans = max(ans,dp[i]);
		}

		printf("%d\n",n - ans);
	}
	return 0;
}
