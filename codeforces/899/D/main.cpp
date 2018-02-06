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

int digit[10];
int num;
ll dp[10][2][2][2][2];
bool debug;

ll solve(int dig,int isEq1,int isEq2,int areEq,int isZero) {
	if(dig == 10) return !isZero;
	ll & ret = dp[dig][isEq1][isEq2][areEq][isZero];
	if(ret != -1) return ret;
	ret = 0;
	int r = 10 - dig;
	if(debug) cerr << dig << " " << r << " " << num << " " << isEq1 << " " << isEq2 << endl;
	if(r > num) {
		loop(d1,10) {
			if(isEq1 && d1 > digit[dig]) continue;
			loop(d2,10) {
				if(isEq2 && d2 > digit[dig]) continue;
				if(areEq && d1 > d2) continue;
				if(debug) cerr << "at .. " << dig << " " << d1 << " " << d2 << " " << digit[dig] << endl;
				ret += solve(dig+1,isEq1 && d1==digit[dig],isEq2 && d2 == digit[dig],areEq && d1==d2,isZero && d1==0);
			}
		}
	}
	else {
		loop(d1,10){
			int d2 = 9 - d1;
			if(isEq1 && d1 > digit[dig]) continue;
			if(isEq2 && d2 > digit[dig]) continue;
			if(areEq && d1 > d2) continue;
			if(debug) cerr << "at " << dig << " " << d1 << " " << d2 << endl;
			ret += solve(dig+1,isEq1 && d1==digit[dig],isEq2 && d2 == digit[dig],areEq && d1==d2,isZero && d1==0);
		}
	}
	if(debug)
		cerr << dig << " " << isEq1 << " " << isEq2 << " " << areEq << " -> " << ret << endl;
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	string s; cin >> s;
	int n;
	sscanf(s.c_str(),"%d",&n);
	for(int i = 0;i < sz(s);i++)
		digit[sz(s)-1-i] = s[i] - '0';
	reverse(digit,digit + 10);
	ll ans = 0;
	for(num=10;num > 0 && !ans;num--){
//		debug = num == 1;
		memset(dp,-1,sizeof dp);
		ans = solve(0,1,1,1,1);
	}
	if(!ans) ans = n*(n-1LL)/2;
	cout << ans << endl;
	return 0;
}
