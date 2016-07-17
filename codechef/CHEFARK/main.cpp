#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
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

ll mod = 1000000007;

#define mul(a,b) (((a%mod)*1LL*(b%mod))%mod)

int inv[1 << 20];

int main(){
	inv[1] = 1;
	for(int i = 2;i < (1 << 20);i++) {
		inv[i] = (mod - mul((mod/i),inv[mod%i])) % mod;
		inv[i] = (inv[i] + mod)%mod;
	}
	int T,n,k,a,zeros;
	scanf("%d",&T);
	while(T--){
		zeros = 0;
		scanf("%d %d",&n,&k);
		loop(i,n) scanf("%d",&a),zeros += a == 0;
		n -= zeros;
		int ans = 0,C = 1;
		for(int i = 0,L = min(n,k) + 1;i < L;i++){
			if(!((k - i) & 1) || zeros){ 
				ans += C;
				if(ans >= mod) ans -= mod;
			}
			C = mul(mul(n - i,C),inv[i + 1]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
