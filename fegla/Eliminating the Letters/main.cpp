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

int dp[26][128][128][8];
char G[128][129];
int oo = 1 << 28;
int N;


void buildTable(int LG){
	loop(k,26) loop(i,N) loop(j,N) dp[k][i][j][0] = (G[i][j] - 'A') != k;
	for(int lg = 1,step = 1;lg <= LG;lg++,step <<= 1)
		loop(k,26) loop(i,N) loop(j,N) {
			dp[k][i][j][lg] = 0;
			loop(a,2) loop(b,2){
				int tmp = oo;
				loop(q,26) tmp = min(tmp,dp[q][i + a*step][j + b*step][lg - 1] + (q != k));
				dp[k][i][j][lg] += tmp;
			}
		}
}

void solve(){
	int lg = 0;
	while(N != (1 << lg)) lg++;
	buildTable(lg);
	int best = oo;
	char choice = 'A';
	loop(i,26) {
		int tmp = dp[i][0][0][lg];
		if(tmp < best) {
			best = tmp;
			choice = i + 'A';
		}
	}
	printf("%c %d\n",choice,best);
}

int main(){
	freopen("eliminating.in", "r", stdin);
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		loop(i,N) scanf("%s",G[i]);
		solve();
	}
	return 0;
}
