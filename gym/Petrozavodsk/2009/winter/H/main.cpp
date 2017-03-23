#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
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
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

ll A[1 << 18],B[1 << n];
int cntA[1 << 18][63],cntB[1 << 18][63],n;
map<int,map<int,map<int,int> > > dp[1 << 18],bit[1 << 18];

bool exist(int a,int b,int c,int d){
	if(dp[a].find(b) == dp[a].end()) return 0;
	if(dp[a][b].find(c) == dp[a][b].end()) return 0;
	return dp[a][b][c].find(d) != dp[a][b][c].end();
}

int get_cnt(int s,int e,int cnt [][63],int bit){
	return cnt[e][bit] - (s ? cnt[s - 1][bit] : 0);
}

int solve(int s1,int s2,int L,int bit){
	if(bit == 63) return 1;
	if(exist(s1,s2,L,bit)) return dp[s1][s2][L][bit];
	int ones_a = get_cnt(s1,s1 + L - 1,cnt_A,bit) ,ones_b = get_cnt(s2,s2 + L - 1,cnt_B,bit);
	int zeros_a = L - ones_a,zeros_b = L - ones_b;
	dp[s1][s2][L][bit] = 0;
	if(ones_a == ones_b && solve(s1,s2,L,bit + 1)) {
		::bit[s1][s2][L] = 0;
		return dp[s1][s2][L][bit] = 1;		
	}
	if((ones_a == zeros_b && zeros_b == ones_a) || (ones_a == ones_b)){
		//s1 ,s2 + cnt1,cnt0,biti+1
		//s1 + cnt0,s2,cnt1,biti+1
		if(solve(s1,s2 + ones_b,zeros_b,bit + 1) && solve(s1 + zeros_a,s2,ones_a,bit + 1)){
			::bit[s1][s2][L][bit] = 1;
			return dp[s1][s2][L][bit] = 1;		
		}
	}
	return dp[s1][s2][L][bit] = 0;
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%lld",A + i);
	loop(i,n) scanf("%lld",B + i);
	sort(A,A + n);
	sort(B,B + n);
	loop(i,n){
		loop(j,63) {
			cntA[i][j] = bool(A[i] & (1 << j)) + (i ? cntA[i - 1][j] : 0);
			cntB[i][j] = bool(B[i] & (1 << j)) + (i ? cntB[i - 1][j] : 0);
		}
	}
	if(solve(0,0,n,0)){
		int ans = 0;
		int s1 = 0,s2 = 0,L = n,bit = 0;
		while(s1 
	}
	else puts("-1");
		
	return 0;
}
