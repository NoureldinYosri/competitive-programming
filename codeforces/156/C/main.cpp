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

const int MAX = 111,mod = 1000*1000*1000 + 7;
char input[MAX];
int dp [MAX][MAX*26],vis[MAX][MAX*26];
int visID = 1,len;

inline int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
	return x;
}

int solve(int pos,int palance){
	if(pos == len) return (palance == 0) ? 1 : 0;
	if(vis[pos][palance] == visID) return dp[pos][palance];
	vis[pos][palance] = visID;
	dp[pos][palance] = 0;
	for (int i = 0;i < 26 && i <= palance;i++)
		dp[pos][palance] = add(dp[pos][palance],solve(pos + 1,palance - i));
	return dp[pos][palance];
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	dp[0][0] = 1;
	for(int i = 1;i < MAX;i++)
		for(int j = 0;j < MAX*26;j++){
			for(int k = 0;k < 26 && k <= j;k++)
				dp[i][j] = add(dp[i][j],dp[i-1][j - k]);
		}
	int T ; scanf("%d",&T);
	while (T-- ) {
		scanf("%s",input);
		int tot = 0;
		len = strlen(input);
		loop(i,len) tot += input[i] - 'a';
		printf("%d\n",add(dp[len][tot],-1));
	}
	return 0;
}
