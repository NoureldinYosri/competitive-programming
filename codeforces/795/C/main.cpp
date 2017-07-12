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

int cnt [] = {6,2,5,5,4,5,6,3,7,6};
map<int,int> to;

const int MAX = 100*1000 + 10;
int dp[MAX],vis[MAX];
int choice[MAX];

int solve(int n){
	if(n == 0) return 0;
	if(vis[n]) return dp[n];
	vis[n] = 1;
	dp[n] = -1000000;
	for(auto e : to)
		if(e.xx <= n){
			int tmp = solve(n - e.xx) + 1;
			if(tmp >= dp[n]){
				dp[n] = tmp;
				choice[n] = e.xx;
			}
		}
	return dp[n];
}

int main(){
	//freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	to[2] = 1;
	to[3] = 7;
	to[4] = 4;
	to[5] = 5;
	to[6] = 9;
	to[7] = 8;


	int n; cin >> n;

	int len = solve(n);
	assert(len > 0);
	string out;
	while(n > 0){
		out.pb(to[choice[n]] + '0');
		n -= choice[n];
	}
	assert(sz(out) == len);
	cout << out << endl;

	return 0;
}
