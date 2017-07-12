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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 100*1000 + 10;
const int MAXK = 325;

int A[MAX],n;
int dp[MAXK + 1][MAX];

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	range(k,1,MAXK){
		for(int i = n-1;i >= 0;i--){
			if(i + A[i] + k >= n) dp[k][i] = 1;
			else dp[k][i] = 1 + dp[k][i + A[i] + k];
		}
	}
	int m; scanf("%d",&m);
	while(m--){
		int p,k; scanf("%d %d",&p,&k); p--;
		if(k <= MAXK) printf("%d\n",dp[k][p]);
		else {
			int ans = 0;
			while(p < n){
				ans++;
				p += A[p] + k;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
