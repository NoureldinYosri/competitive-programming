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
using namespace std;

void prBI(string t){
	reverse(all(t));
	cout << t;
}





string dp[1001][5001];
int N,M;

string add(string a,string b){
	string c = "";
	int L = max(len(a),len(b)),r = 0;
	loop(i,L){
		r += ((i < (int)len(a)) ? (a[i]-'0') : 0) + ((i < (int)len(b)) ? (b[i]-'0') : 0);
		if(r <= 9) c += (char)(r + '0'),r = 0;
		else c += (char)(r%10 + '0'),r /= 10; 
	}
	if(r) c += (char)(r + '0');
	return c;
}

string solve(int n,int k){
	if(k == 0) return (n == 0) ? "1" : "0";
	if(!dp[n][k].empty()) return dp[n][k];
	string & ans = dp[n][k];
	ans = "0";
	if(n == 0) loop(i,N) ans = add(ans,solve(i + 1,k - 1));
	else {	
		ans = solve(0,k - 1);
		if(n > 1) ans = add(ans,solve(n - 1,k - 1));
		else ans = add(ans,solve(N,k - 1));
		
		if(n < N) ans = add(ans,solve(n + 1,k - 1));
		else ans = add(ans,solve(1,k - 1)); 				
	}
	return ans;
}

int main(){
	pre();
	cin >> N >> M;	
	if(M == 0) cout << 0;
	else prBI(solve(0,M));
	cout << endl;
	return 0;
}
