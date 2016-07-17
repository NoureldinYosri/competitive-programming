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

const int mod = 1e9 + 7;
const int MAX = 200000;
int p2[MAX],F[2][MAX];

int main(){
	p2[0] = 1;
	loop(i,MAX - 1) {
		p2[i + 1] = p2[i] << 1;
		if(p2[i + 1] >= mod) p2[i + 1] -= mod;
	}
	int T,N,K;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&N,&K);
		cerr << N << " " << K << endl;
		if(N == 0) puts("1");
		else if(K == 0) puts("0");
		else if(K >= N) printf("%d\n",p2[N]);
		else {
			loop(i,K + 1){
				F[0][i] = p2[i];
				F[1][i] = F[0][i] + (i ? F[1][i - 1] : 0);
				if(F[1][i] >= mod) F[1][i] -= mod;
			}
			range(i,K,N - 1) {
				F[0][i + 1] = F[1][i] - F[1][i - K] + mod;
				while(F[0][i + 1] >= mod) F[0][i + 1] -= mod;
				F[1][i + 1] = F[0][i + 1] + F[1][i];
				if(F[1][i + 1] >= mod) F[1][i + 1] -= mod;
		//		cerr << F[0][i + 1] << endl;
			}
			printf("%d\n",F[0][N]);
		}
	}
	return 0;
}
