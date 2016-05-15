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

int A[1 << 20],CNT[1 << 20];
int bucket_size,n,m,k,L,R;
vector<pair<pi,int> > bucket[1 << 20];
ll Q[1 << 20];

int main(){
	scanf("%d %d %d",&n,&m,&k);
	loop(i,n){
		scanf("%d",&A[i + 1]);
		A[i + 1] ^= A[i];
	}
	bucket_size = sqrt(n) + 2;
	bucket_size = min(bucket_size,m);
	int num_buckets = 0;
	loop(i,m){
		scanf("%d %d",&L,&R);
		L--;
		int u = L/bucket_size;
		bucket[u].pb(mp(mp(R + 1,L),i));
		num_buckets = max(num_buckets,u + 1);
	}
	loop(i,num_buckets) sort(all(bucket[i]));
	ll ans = 0;		
	loop(i,num_buckets){
		int left = i*bucket_size,right = left;
		for(auto q : bucket[i]){
			int l = q.xx.yy,r = q.xx.xx;
			while(right < r){
				ans += CNT[k ^ A[right]];
				CNT[A[right]]++;
				right++;
			}
			while(left < l){
				CNT[A[left]]--;
				ans -= CNT[k ^ A[left]];
				left++;
			}
			while(left > l){
				left--;
				ans += CNT[k^A[left]];
				CNT[A[left]]++;				
			}
			Q[q.yy] = ans;
		}
		for(;left < right;left++){
			CNT[A[left]]--;
			ans -= CNT[k^A[left]];
		}
	}
	loop(i,m) printf("%lld\n",Q[i]);
	return 0;
}
