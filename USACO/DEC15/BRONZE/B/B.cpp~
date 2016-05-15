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

int A[110][2];

int main(){
	freopen("speeding.in","r",stdin);
	freopen("speeding.out","w",stdout);
	int M,N,x0 = 1,d,speed;
	cin >> M >> N;
	loop(i,M) {
		loop(j,2) cin >> A[i][j];
		A[i][0] += i ? A[i - 1][0] : 0;
	}
	int i = 0,ans = 0;	
	loop(j,N){
		cin >> d >> speed;
		while(d){
			//cerr << x0 << " " << speed << " " << A[i][1] << " " << ans << endl;
			d--;
			x0++;
			ans = max(ans,speed - A[i][1]);
			if(x0 == A[i][0] + 1)i++;			
		}
	}
	cout << ans << endl;
	return 0;
}
