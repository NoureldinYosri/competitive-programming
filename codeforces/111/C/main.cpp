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


int n,m;

int dp[40][1 << 10][1 << 10];

bool check(int prv,int cur,int nxt){
	for(int c = 0;c < m;c++) {
		if(prv & (1 << c)) continue;
		if(cur & (1 << c)) continue;
		if(nxt & (1 << c)) continue;
		if(c && (cur & (1 << (c-1)))) continue;
		if(cur & (1 << (c + 1))) continue;
		return 0;
	}
	return 1;
}

int brute_force(int row,int prv,int cur) {
	if(row == n-1) return check(prv,cur,0) ? popcnt(cur) : (n*m);
	if(dp[row][prv][cur] != -1) return dp[row][prv][cur];
	int & ret = dp[row][prv][cur];
	ret = n*m;
	loop(nxt,1 << m) if(check(prv,cur,nxt))
		ret = min(ret,brute_force(row + 1,cur,nxt));
	ret += popcnt(cur);
	return ret;
}

int solve() {
	memset(dp,-1,sizeof dp);
	int ret = n*m;
	loop(msk,1 << m) ret = min(ret,brute_force(0,0,msk));
	ret = n*m - ret;
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	for(n = 1;n <= 20;n++){
	/*	cout << setfill(' ') << setw(2) ;
		cout << n << " : ";
		for(m = 1;m <= 8;m++){
			cout << setfill(' ') << setw(2) << solve() << " ";
			flush(cout);
		}
		cout << endl;
		*/
		m = n;
		cout << n << " : " << solve() << endl;
	}
	/*cin >> n >> m;
	if(m > 2 ) cout << n*(m - 1) << endl;
	else cout << solve() << endl;
	*/
	return 0;
}
