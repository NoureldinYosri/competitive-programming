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

int A[15];

int main(){
	pre();
	int T,K;
	cin >> T;
	loop(t,T){
		cin >> K;
		loop(i,15) cin >> A[i];
		int ans = 0;
		range(s,1,13)
			range(e,s,13){
				int l = A[s - 1],r = A[e + 1],c = 1;
				range(i,s,e) c &= (A[i] > l) && (A[i] > r);
				ans += c;
			}
		cout << K << " " << ans << endl;
	}
	return 0;
}
