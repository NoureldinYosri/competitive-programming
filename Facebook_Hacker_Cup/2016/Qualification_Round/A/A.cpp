#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int n;
ll P[2000][2];
ll D[2000];

int main(){
	int T; ll ans;
	scanf("%d",&T);
	loop(t,T){
		ans = 0;
		scanf("%d",&n);
		loop(i,n) loop(j,2) scanf("%lld",&P[i][j]);
		loop(i,n){
			loop(j,n) {
				D[j] = 0;
				loop(k,2) D[j] += (P[i][k] - P[j][k])*(P[i][k] - P[j][k]);
			}
			sort(D,D + n);
			loop(j,n){
				int k = j;
				while(k < n && D[j] == D[k]) k++;
				ll L = k - j;
				ans += L*(L - 1)/2;
				j = k - 1;
			}
		}
		printf("Case #%d: %lld\n",t + 1,ans);
	}	
	return 0;
}
