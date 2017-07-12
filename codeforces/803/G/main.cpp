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


const int MAX = 1024;
int dp[MAX][2*MAX + 10];
int nxt[MAX][2*MAX + 10];
char line[MAX];
int n,k;

int solve(int pos,int diff){
	if(abs(diff) > k) return 0;
	if(abs(diff) == k) return pos == n;
	if(pos == n) return 0;
	int & ret = dp[pos][diff + 1024];
	if(dp[pos][diff + 1024] != -1) return ret;
	ret = 0;
	int & ne = nxt[pos][diff + 1024];
	if(line[pos] == 'W') {
		ne = 1;
		return ret = solve(pos + 1,diff + 1);
	}
	else if(line[pos] == 'D') {
		ne = 0;
		return ret = solve(pos + 1,diff);
	}
	else if(line[pos] == 'L') {
		ne = -1;
		return ret = solve(pos + 1,diff - 1);
	}
	else{
		range(i,-1,1)
				if(solve(pos + 1,diff + i)){
					ne = i;
					return ret = 1;
				}
		return ret;
	}
}

char out [] = "LDW";

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	scanf("%d %d",&n,&k);
	scanf("%s",line);
	memset(dp,-1,sizeof dp);
	if(solve(0,0)){
		int pos = 0,diff = 0;
		for(;pos < n;pos++){
			int ne = nxt[pos][diff + 1024];
			diff += ne;
			putchar(out[ne + 1]);
		}
	}
	else puts("NO");

	return 0;
}
