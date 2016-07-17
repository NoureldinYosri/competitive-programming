#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

const int mod = 1e9 + 7;

char line[1 << 20];
int L;

int dp[1 << 20][4][4];


inline bool isValidCorner(int a,int b){
	if(b == 3) return a != 0;
	if(b == 2) return 0;
	if(b == 1) return a == 3;
	if(b == 0) return a != 3;
}


inline bool is_valid(int p,int v){
	int k = isdigit(line[p]) ? (line[p] - '0') : ((line[p] == '?') ? 4 : 3);
	return (k == 4) || k == v;
}

int solve(int i,int p,int pp){
	if(i == L) return isValidCorner(pp,p);
	if(dp[i][p][pp] != -1) return dp[i][p][pp];
	dp[i][p][pp] = 0;
	int k = isdigit(line[i]) ? (line[i] - '0') : ((line[i] == '?') ? 4 : 3);
	loop(j,4) if(k == 4 || k == j) {
			bool c = 0;
			if(p == 3) c = pp != 0 && j != 0;
			else if(p == 2) c = pp == 3 && j == 3;
			else if(p == 1) c =  (pp == 3) + (j == 3) == 1;
			else c = pp != 3 && j != 3;
			if(c){
				if(pp == 3) c = p != 0;
				else if(pp == 2) c = p == 3;
				else if(pp == 1) c = 1;
				else c = p != 3;
				if(c){				
					if(j == 3) c = p != 0;
					else if(j == 2) c = p == 3;
					else if(j == 1) c = 1;
					else c = p != 3;
					if(c){
						dp[i][p][pp] += solve(i + 1,j,p);
						if(dp[i][p][pp] >= mod) dp[i][p][pp] -= mod;
					}
				}
			}
	} 
	return dp[i][p][pp];	
}

int main(){
	scanf("%s",line);
	L = strlen(line);
	if(L == 1) {
		if(line[0] == '?') puts("2");
		else if(line[0] == '*' || line[0] == '0') puts("1");
		else puts("0");
		return 0;
	}
	if(L == 2){
		if(line[0] == '?' && line[1] == '?')puts("3");
		else if(line[0] == '?' || line[1] == '?'){
			if(line[1] == '?') swap(line[0],line[1]);
			if(line[1] == '0' || line[1] == '1' || line[1] == '*') puts("1");
			else puts("0");
		}
		else {
			if(strcmp(line,"00") == 0 || strcmp(line,"*1") == 0 || strcmp(line,"1*") == 0) puts("1");
			else puts("0");
		}
		return 0;
	}
	fill(&dp[0][0][0],&dp[L][0][0],-1LL);
	ll ans = 0;
	
	loop(i,4) loop(j,4) if(isValidCorner(i,j) && is_valid(0,j) && is_valid(1,i)) {
		ans += solve(2,i,j);
		if(ans >= mod) ans -= mod;
	}
	cout << ans << endl;
	cerr << ans << endl;
	
	return 0;
}
