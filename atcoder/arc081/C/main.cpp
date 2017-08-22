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

const int MAX = 200*1000 + 10;
string S,out;
int n;
vi IDX[128];
char choice[MAX];
int dp[MAX];

int solve(int pos){
	if(pos == n) {
		choice[pos] = 'a';
		return 1;
	}
	if(dp[pos] != -1) return dp[pos];
	dp[pos] = 1 << 28;
	for(char c = 'a';c <= 'z';c++) {
		auto p = lower_bound(all(IDX[(int)c]),pos);
		if(p == IDX[(int)c].end()) {
			choice[pos] = c;
			dp[pos] = 1;
			break;
		}
		int tmp = min(dp[pos],1 + solve(*p + 1));
		if(tmp < dp[pos]) {
			dp[pos] = tmp;
			choice[pos] = c;
		}
	}
	return dp[pos];
}

void recon(int pos){
	char c = choice[pos];
	putchar(c);
	if(pos == n) return;
	auto p = lower_bound(all(IDX[(int)c]),pos);
	if(p == IDX[(int)c].end()) return;
	recon(*p + 1);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> S;
	n = sz(S);
	loop(i,n) IDX[(int)S[i]].pb(i);
	memset(dp,-1,sizeof dp);
	solve(0);
	recon(0);

	return 0;
}
