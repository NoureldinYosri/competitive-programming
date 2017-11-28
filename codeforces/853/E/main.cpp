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

const ll oo = 1LL << 60;
int n;
int A[1 << 20];
ll sum[1 << 20];
ll dp[1 << 20];



int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n){
		scanf("%d",A + i);
		sum[i] = A[i] + sum[i - 1];
	}
	for(int i = 1;i <= n;i++) {
		dp[i] = oo;
		for(int j = max(i-20,0);j < i;j++){
			ll tobuy = sum[i-1] - sum[j];
			int tmp = min(tobuy/10,0LL + A[i]);
			cerr << "A[i] is " << A[i] << endl;
			cerr << i << "\t" << tobuy << " + " << A[i] - min(tobuy/10,A[i] + 0LL) << endl;
			dp[i] = min(dp[i],dp[j] + tobuy + A[i] - tmp);
		}
	}
	prArr(dp,n+1,ll);
	cout << dp[n] << endl;

	return 0;
}
