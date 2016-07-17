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

int A[1 << 20],n,T;
ll  S[1 << 20];
int mn[1<< 20];
int mx[1<< 20];

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		loop(i,n){
			scanf("%d",A + i + 1);
			S[i + 1] = S[i] + A[i + 1];
		}
		deque<int> MQ(1,0);
		range(i,1,n){
			mn[i] = MQ.front();
			while(!MQ.empty() && S[MQ.back()] >= S[i]) MQ.pop_back();
			MQ.pb(i);
		}
		MQ.clear();
		rran(i,1,n){
			while(!MQ.empty() && S[MQ.back()] <= S[i]) MQ.pop_back();
			MQ.pb(i);
			mx[i] = MQ.front();
		}
		ll ans = LLONG_MIN;
		range(i,1,n){
			ll tmp = S[mx[i]] - S[mn[i]];
			ans = max(ans,tmp);
			if(A[i] < 0 && i != mx[i]) {
				tmp -= A[i];
				ans = max(ans,tmp);
			}
		}
		printf("%lld\n",ans);
	}	
	return 0;
}
