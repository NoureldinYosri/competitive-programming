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

const int MAX = 1 << 20;
int T,n,m,k,SZ;
int A[MAX],B[MAX],BIT[MAX + 1];

void update(int p){
	for(;p <= SZ;p += LSOne(p)) BIT[p]++;
}

int BS(){
	int p = 1,q = SZ,t = k;
	while(q > 1){
		q >>= 1;
		if(BIT[p + q - 1] < t) {
			t -= BIT[p + q - 1];
			p += q;
		}
	}
	return p;
}

void solve(){
	int ctr = 0;
	loop(i,m){
		if(A[i] == 0){
			if(ctr < k) puts("-1");
			else printf("%d\n",B[BS() - 1]);
		}
		else{
			++ctr;
			int v = lower_bound(B,B + n,A[i]) - B + 1;
			update(v);
		}
	}
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&m,&k); n = 0;
		loop(i,m) {
			scanf("%d",A + i);
			if(A[i] != 0) B[n++] = A[i];
		}
		sort(B,B + n);
		n = unique(B,B + n) - B;
		SZ = 1;
		while(SZ < n) SZ <<= 1;
		fill(BIT,BIT + SZ + 1,0);
		solve();
	}
	return 0;
}
