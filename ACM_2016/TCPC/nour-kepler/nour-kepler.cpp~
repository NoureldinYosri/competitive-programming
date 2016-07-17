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

char name[1 << 20][50];
vector<pair<pi,int> > V;

int main(){
	int T,n,m; scanf("%d",&T);
	while(T--){
		V.clear();		
		scanf("%d %d",&n,&m);
		loop(i,n){
			scanf("%s",name[i]);
			int mx = INT_MIN,mn = INT_MAX;
			loop(j,m) {
				int a; scanf("%d",&a);
				mx = max(mx,a);
			}
			loop(j,m) {
				int a; scanf("%d",&a);
				mn = min(mn,a);
			}
			V.pb(mp(mp(mx - mn,mx),n - i));
		}
		sort(all(V));
		puts(name[n - V.back().yy]);
	}
	return 0;
}
