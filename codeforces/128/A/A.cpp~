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

int n,d;
ll a,b;
pair<ll,int> A[1 << 20];

int main(){
	scanf("%d %d",&n,&d);
	scanf("%I64d %I64d",&a,&b);
	loop(i,n){
		ll c,d;
		scanf("%I64d %I64d",&c,&d);
		A[i] = mp(c*a + d*b,i + 1);
	}
	sort(A,A + n);
	deque<pair<ll,int> > B;
	ll sum = 0,ans = 0;
	int e = 0;
	loop(i,n){
		B.pb(A[i]); sum += A[i].xx;		
		while(sum > d){
			sum -= B.front().xx;
			B.pop_front();
		}
		if(sz(B) > ans){
			ans = sz(B);
			e = i;
		}
	}
	printf("%I64d\n",ans);
	while(ans--) printf("%d%s",A[e--].yy,ans ? " " : "\n");
	return 0;
}
