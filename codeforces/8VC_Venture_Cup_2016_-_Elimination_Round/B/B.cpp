#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int dp[201][201][201];

int solve(int a,int b,int c){
	if(a == 0 && b == 0 && c > 0) return 4;
	if(a == 0 && b > 0 && c == 0) return 2;
	if(a > 0 && b == 0 && c == 0) return 1; 
	if(a < 0 || b < 0 || c < 0) return 0;
	if(dp[a][b][c] != -1) return dp[a][b][c];
	dp[a][b][c] = 0;
	if(c >= 2) dp[a][b][c] = dp[a][b][c] | solve(a,b,c - 1);
	if(b >= 2) dp[a][b][c] = dp[a][b][c] | solve(a,b - 1,c);
	if(a >= 2) dp[a][b][c] = dp[a][b][c] | solve(a - 1,b,c);
	if(a && b) dp[a][b][c] = dp[a][b][c] | solve(a - 1,b - 1,c + 1);
	if(b && c) dp[a][b][c] = dp[a][b][c] | solve(a + 1,b - 1,c - 1);
	if(a && c) dp[a][b][c] = dp[a][b][c] | solve(a - 1,b + 1,c - 1);
	return dp[a][b][c];
}

char line[300];

int main(){
	int r = 0,b = 0,g = 0,n;	
	scanf("%d %s",&n,line);
	loop(i,n) {
		r += line[i] == 'R';
		g += line[i] == 'G';
		b += line[i] == 'B';
	}	
	loop(i,201) loop(j,201) loop(k,201) dp[i][j][k] = -1;
	int mask = solve(r,g,b);
	string out = "";
	if(mask & 1) out += "R";
	if(mask & 2) out += "G";
	if(mask & 4) out += "B";
	sort(all(out));
	cout << out << endl;
	return 0;
}
