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
#define print(A,t) cout << #A << ": "; copy(all (A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define ll long long
#define vi vector<int>
#define pl pair<unsigned ,unsigned >
#define pre() fin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

vector<unsigned > A[10000];
unsigned  n,m,x,y;
	


int main(){
	unsigned x,y;
	fread(&m,sizeof(m),1,stdin);
	fread(&n,sizeof(n),1,stdin);
	loop(i,m) A[i].resize(n);
	loop(i,m) loop(j,n) fread(&A[i][j],sizeof(m),1,stdin);
	while(fread(&x,sizeof(m),1,stdin) && fread(&y,sizeof(m),1,stdin)){
	 	if(y < x) swap(x,y);
		ll ans = 0;
		loop(i,m) ans += upper_bound(all(A[i]),y) - lower_bound(all(A[i]),x); 		
		printf("%lld\n",ans);
	}
	return 0;
}
