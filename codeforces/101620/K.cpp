#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int MAX = 505;
char G[MAX][10];
int best[MAX], mx[MAX];
int n;

int get_shifts(const char *S, int q){
	static char buffer[10];
	string s = string(S);
	int msk = 1, m = sz(s);
	copy(S, S + m, buffer);
	for(int i = 1;i < m; i++){
		rotate(buffer, buffer + 1, buffer + m);
		string tmp(buffer);
		if(tmp > s) {
			s = tmp;
			msk = 0;
		}
		if(tmp == s) {
			msk |= 1 << i;
			mx[q] = i;
		}
	}
	return msk;
}


int dp[8][MAX][MAX];

int get_complete(int k){
	return (1 << k) - 1;
}

int solve(int h, int s, int e){
	if(s > e) return 0;
	int & ret = dp[h][s][e];
	if(ret != -1) return ret;
	ret = 1 << 29;
	
	int zeros = 0, done = 1;
	for(int k = s; k <= e; k++)
		zeros += mx[k] == h, done &= (best[k] >> h)&1;
	if(done) return ret = 0;


	int sum = 0, ctr = 0;
	
	for(int k = s;k <= e; k++) if(mx[k] > h) {
		int r = k;
		while(r <= e && mx[r] > h) r++;
		sum += solve(h+1, k, r-1);
		k = r-1;
		ctr++;
	}
	ret = sum;
	if(zeros) ret += ctr;
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) {
		scanf("%s", G[i]);
		best[i] = get_shifts(G[i], i);
	}
	//prArr(mx, n, int);
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0, n-1) << endl;
	return 0;
}
