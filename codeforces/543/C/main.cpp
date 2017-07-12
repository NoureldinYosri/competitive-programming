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

const int MAX = 20;
ll dp[MAX+1][1 << MAX];
char str[MAX][26];
int cost[MAX][MAX],who[MAX][26];
ll sum[MAX][26];
int n,m;
const ll oo = 1LL << 60;
int lookup[1 << 20];

ll solve(){
    for(int msk = 0;msk < (1 << n);msk++) dp[m][msk] = oo;
	dp[m][(1 << n)-1] = 0L;
	for(int pos = m-1;pos >= 0;pos--)
		for (int msk = (1 << n)-1;msk >= 0;msk--){
			dp[pos][msk] = dp[pos + 1][msk];
			ll ret = dp[pos][msk];
			for(int omsk = ((1 << n) - 1) ^ msk,cur;omsk;omsk ^= LSOne(omsk)) {
				cur = lookup[LSOne(omsk)];
				ret = min(ret,dp[pos][msk | (1 << cur)] + cost[cur][pos]);
				int c = str[cur][pos] - 'a';
				ret = min(ret,dp[pos][msk | who[pos][c]] + sum[pos][c] - cost[cur][pos]);
			}
			dp[pos][msk] = ret;
		}
	return dp[0][0];
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	loop(i,MAX) lookup[1 << i] = i;
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%s",str[i]);
	loop(i,n) loop(j,m) scanf("%d",&cost[i][j]);
    for(int pos = 0;pos < m;pos++)
		for(int i = 0;i < n;i++) {
			int c = str[i][pos] - (int)'a';
			sum[pos][c] += cost[i][pos];
			who[pos][c] |= 1 << i;
		}
    cout << solve() << endl;
	return 0;
}
