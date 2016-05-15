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

int A[100];
int main(){
	int T,N,sum;
	cin >> T;
	while(T--){
		cin >> N;
		sum = 0;
		loop(i,N) cin >> A[i],sum += A[i];
		//sum = x * N + N * (N - 1)/2
		if((2*sum) % N == 0){
			int x = (2*sum) / N - N + 1;
			if(x & 1) cout << "-1\n";
			else{
				x >>= 1;
				if(x < 0) cout << "-1\n";
				else{
					int ans = 0;
					loop(i,N) ans += max(0,x + i - A[i]);
					cout << ans << "\n";
				}
			}
		}
		else cout << "-1\n";
	}
	return 0;
}
