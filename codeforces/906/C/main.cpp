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

const int MAX = 22;
vi G[MAX];
int Conv[MAX],n;
int dp[1 << MAX],who[1 << MAX];

int solve(int msk) {
	if(dp[msk] != -1) return dp[msk];
	int & ret = dp[msk];
	ret = 100000;
	for(int i = 0;i < n;i++) {
		bool y = 0;
		int tmsk = msk | Conv[i];
		if(msk & (1 << i)) y = 1;
		if(msk == 0) {
			y = 1;
			tmsk |= 1 << i;
		}
		if(tmsk == msk) y = 0;
		if(y) {
			int tmp = 1 + solve(tmsk);
			if(tmp < ret) {
				ret = tmp;
				who[msk] = i;
			}
		}
	}
	return ret;
}




int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int m; scanf("%d %d",&n,&m);
	loop(i,m) {
		int a,b; scanf("%d %d",&a,&b);
		--a,--b;
		Conv[a] |= 1 << b;
		Conv[b] |= 1 << a;
	}
	if(m == n*(n-1)/2) {
		puts("0");
		return 0;
	}

	memset(dp,-1,sizeof dp);
	dp[(1 << n) - 1] = 0;
	int ans = solve(0) ;
	printf("%d\n",ans);
	for(int i = 0,msk = 0;i < ans;i++) {
		int j = who[msk];
		printf("%d%c",j+1," \n"[i==ans-1]);
		if(!msk) msk |= 1 << j;
		msk |= Conv[j];
	}

//	int msk = tot;
//	vi V{1, 10, 12, 17, 18, 20, 9, 16, 13, 5, 11, 14, 8, 7, 21, 22};
//	for(int x : V) msk ^= 1 << (x - 1);
//	vi C;
//	cerr << getCard(msk,C) << endl;
	return 0;
}
