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

const ll mod = 1e9 + 7;



void EXP(ll A[3][3],ll p){
	if(p == 0){
		loop(i,3) loop(j,3) A[i][j] = i == j;
		return;
	}
	ll B[3][3] = {{1,0,0},{0,1,0},{0,0,1}},D[3][3];
	int ctr = 0;
	while(p > 1){
		if(p & 1) {
			loop(i,3) loop(j,3){
				D[i][j] = 0;
				loop(k,3) D[i][j] += A[i][k] * B[k][j] % mod, D[i][j] -= (D[i][j] > mod) ? mod : 0;
			}
			loop(i,3) loop(j,3) B[i][j] = D[i][j];
		}
		loop(i,3) loop(j,3){
			D[i][j] = 0;
			loop(k,3) D[i][j] += A[i][k] * A[k][j] % mod, D[i][j] -= (D[i][j] > mod) ? mod : 0;
		}
		loop(i,3) loop(j,3) A[i][j] = D[i][j];
		p >>= 1;
	}
	loop(i,3) loop(j,3){
		D[i][j] = 0;
		loop(k,3) D[i][j] += A[i][k] * B[k][j]%mod, D[i][j] -= (D[i][j] > mod) ? mod : 0;
	}
	loop(i,3) loop(j,3) A[i][j] = D[i][j];
}

#define gc getchar_unlocked
inline void scan(ll & x){
	x = 0;
	char b[50],*p = b;
	fread(b,1,50,stdin);
	while(!('0' <= *p && *p <= '9')) p++;
	x = *p - '0';
	while('0' <= *p && *p <= '9') x = (x << 1) + (x << 3) + *p - '0',p++;
}

int main(){
	int t; ll n;
	scanf("%d",&t);
	ll B[3] = {0,0,1};
	while(t--){
		scanf("%lld",&n);
		ll A[3][3] = {{1,3,2},{0,5,3},{0,3,2}};
		EXP(A,n);
		ll G = 0;
		loop(i,3) G += A[0][i] * B[i]%mod,G -= (G > mod) ? mod : 0;
		printf("%lld\n",G);
	}
	return 0;
}


