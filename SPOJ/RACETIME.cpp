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

int bucket_size;
vi bucket[1 << 20];
int A[1 << 20];

int main(){
	int N,Q,a,b,x,ctr = -1;
	scanf("%d %d",&N,&Q);
	bucket_size = sqrt(N) + 1;	
	bucket_size = min(bucket_size,N);
	loop(i,N){
		scanf("%d",&a);
		A[i] = a;
		if(i%bucket_size) bucket[ctr].pb(a);
		else bucket[++ctr].pb(a); 
	}
	char c[10];
	while(Q--){
		scanf("%s %d %d",&c,&a,&b);
		if(c[0] == 'M'){
			--a;
			int u = a / bucket_size;
			*lower_bound(all(bucket[u]),A[a]) = b;
			sort(all(bucket[u]));
			A[a] = b;
		}
		else{
			--a,--b;
			scanf("%d",&x);
			int u = a / bucket_size, v = b / bucket_size;
			int ans = 0;
			if(u == v) for(;a <= b;a++) ans += A[a] <= x;
			else{
				int ex = min((u + 1)*bucket_size - 1,N - 1),sy = v * bucket_size;
				for(;a <= ex;a++) ans += A[a] <= x;
				for(;b >= sy;b--) ans += A[b] <= x;
				for(++u;u < v;u++) ans += upper_bound(all(bucket[u]),x) - bucket[u].begin();
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
