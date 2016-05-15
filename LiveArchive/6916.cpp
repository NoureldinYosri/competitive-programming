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

point A[10];
ll F[1 << 20],R[1 << 20];
const int mod = 997;


ll EXP(ll b,int p){
	b %= mod;
	if(p == 0) return 1;
	if(p == 1) return b;
	return EXP(b*b,p >> 1) * EXP(b,p & 1) % mod;
}

ll nCr(int n,int k){
	if(F[0] == 0){
		F[0] = 1; R[0] = 1;
		loop(i,(1 << 20) - 1) F[i + 1] = F[i] * (i + 1) % mod,R[i + 1] = EXP(F[i + 1],mod - 2);
	}
	ll ans =  (((F[n] * R[k]) % mod) * R[n - k])%mod;
	cout << n << " " << k << " " << ans << endl;
	return ans;
}

void compress(vi & X,vi & nX,vi & W){
	sort(all(X));
	X.resize(unique(all(X)) - X.begin());
	int l = -1;
	for(int x : X){
		if(x == l + 1) nX.pb(x),W.pb(1);
		else {
			nX.pb(++l);
			W.pb(1);
			nX.pb(x);
			W.pb(x - l);
		}
	}
}

ll dp[1000][1000],G[1000][1000];

int main(){
	pre();
	int T,m,n,K;
	cin >> T;
	loop(t,T){
		cin >> m >> n >> K;
		vi X,Y;
		X.pb(0),X.pb(m - 1),Y.pb(0),Y.pb(n - 1);
		loop(i,K){
			cin >> A[i].first >> A[i].second;
			--A[i].first;
			--A[i].second;
			X.pb(max(A[i].first - 1,0));
			X.pb(A[i].first);
			X.pb(min(A[i].first + 1,m - 1));
			Y.pb(max(A[i].second - 1,0));
			Y.pb(A[i].second);
			Y.pb(min(A[i].second + 1,n - 1));
		}
		vi nX,nY,XW,YW;
		compress(X,nX,XW);
		compress(Y,nY,YW);
		fill(&G[0][0],&G[sz(nX)][0],0);
		loop(k,K){
			range(i,-1,1) range(j,-1,1) {
				int nx = A[k].first + i,ny = A[k].second + j;
				nx = lower_bound(all(nX),nx) - nX.begin();
				ny = lower_bound(all(nY),ny) - nY.begin();
				G[nx][ny] = 1;
			}
		}
		loop(i,sz(nX)) loop(j,sz(nY)){
			if(G[i][j]) dp[i][j] = 0;
			else if(i && j) {
				if(G[i - 1][j - 1]) dp[i][j] = (dp[i - 1][j] + dp[i][j - 1])%mod;
				else dp[i][j] = dp[i - 1][j - 1] * nCr(XW[i] + YW[j],XW[i] ) % mod;
			}
			else if(i) dp[i][j] = dp[i - 1][j];
			else if(j) dp[i][j] = dp[i][j - 1];
			else dp[i][j] = 1;
			
		}
		cout << dp[sz(nX) - 1][sz(nY) - 1] << endl;
	}
}

