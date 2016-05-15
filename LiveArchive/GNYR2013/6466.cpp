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

int main(){
	pre();
	int N,T;
	double D,A,B,F,ans,t;
	cin >> T;
	while(T--){
		ans = 0;
		int i = 0;
		cin >> N >> D >> A >> B >> F;
		while(D > 1e-4){
			if (i) t = D/(F + B);
			else t = D/(F + A);
			ans += t * F;
			D = D - (A + B) * t;
			i = !i;
		}
		printf("%d %.2lf\n",N,ans);
	}
	return 0;
}
