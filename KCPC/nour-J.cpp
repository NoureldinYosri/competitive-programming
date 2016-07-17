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
	int T,n; ll ans,a;
	map<string,ll> M;
	scanf("%d",&T);
	while(T--){
		M.clear();
		scanf("%d",&n);
		while(n--){
			scanf("%lld",&a);
			string s = "";
			while(a){
				if(a%10) s += a%10 + '0';
				a /= 10;
			}
			sort(all(s));
			if(M.find(s) == M.end()) M[s] = 0;
			M[s]++;
		}
		ans = 0;
		for(auto p : M)
			ans += p.second * (p.second - 1);
		ans >>= 1;
		printf("%lld\n",ans);
	}
	return 0;
}
