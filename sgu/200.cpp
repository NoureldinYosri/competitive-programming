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
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); //cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

const int MAX = 1e3;

vi P;
int sm_pr[MAX];

ostream& operator<<(ostream &stream, pi &v){
	stream << "(" << v.first << " ," << v.second << ")";
	return stream;
}

void sieve(){
	for(int i = 2;i < MAX;i++)
		if(sm_pr[i] == 0){
			P.pb(i);
			sm_pr[i] = i;
			for(int j = i*i;j < MAX;j += i)
				sm_pr[j] = i;
		}
}

vector<pi> factor(int n){
	vi F;
	vector<pi> ret;
	while(n > 1){
		F.pb(sm_pr[n]);
		n /= sm_pr[n];
	}
	sort(all(F));
	loop(i,(int)sz(F)){
		int j = i;
		while(j < (int)sz(F) && F[i] == F[j]) j++;
		ret.pb(mp(F[i],j - i));
		i = j - 1;
	}
	return ret;
}

int A[100];

map<vi,ll> dp[101];

ll solve(vi state,int n){
	//cout << n << " " ;
	//print(state,int);
	if(n == -1) {
		int c = 0;
		for(int s : state) c += s;
	//	cout << "c = " << c << endl;
		return c == 0;
	}
	vi t = state;
	if(dp[n].find(state) != dp[n].end()) return dp[n][state];
	dp[n][state] = solve(state,n - 1);
	vector<pi> F = factor(A[n]);
	for(auto p : F)
		if(p.second & 1)
			state[lower_bound(all(P),p.first) - P.begin() + 1] ^= 1;
	dp[n][t] += solve(state,n - 1);
	//cout << n << " ";
	//print(t,int);
	//cout << " -> " << dp[n][t] << endl;
	return dp[n][t];
}

int main(){
	pre();
	sieve();
	int t,m,a;
	cin >> t >> m;
	ll ans = 1;
	loop(i,m) cin >> A[i];
	vi state(t + 1,0);
	cout << solve(state,m - 1) - 1 << endl;
	return 0;
}
