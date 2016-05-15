#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

char s[1 << 20];
int dp[2],dp2[2];
int n;


int main(){
	scanf("%d %s",&n,s);
	loop(i,n){
		if(s[i] == '0') dp[0] = max(dp[0],1 + dp[1]),dp2[1] = max(dp2[1],1 + dp2[0]);
		else dp[1] = max(dp[1],1 + dp[0]),dp2[1] = max(dp2[0],1 + dp2[1]);
	}
	int z = max(dp[0],dp[1]),ans = z;
	loop(i,n){
		int j = i;
		while(j < n && s[i] == s[j])j++;
		if(j - i == 1) continue;
		else if(j - i == 2) {
			if(i == 0 || j == n) ans = max(ans,z + 1);
		}
		else ans = max(ans,2 + z);
		i = j - 1;
	}
	cout << ans << endl;
	return 0;
}
