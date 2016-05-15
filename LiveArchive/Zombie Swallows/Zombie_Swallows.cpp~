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

ll L,R,A[200],suff[200]; int n;
char out[2][50] = {"Sallow swallow wallows in dust.","Sallow swallow swallows."};

bool bt(int i,ll l){
	if(L <= l && l <= R) return 1;
	if(l > R || l + suff[i] < L) return 0;
	if(i == n) return 0;
	return bt(i + 1,l + A[i]) || bt(i + 1,l);
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld %lld %d",&L,&R,&n);
		loop(i,n) scanf("%lld",&A[i]);
		sort(A,A + n);
		reverse(A,A + n);
		suff[n] = 0;
		for(int i = n - 1;i >= 0;i--){
			suff[i] = suff[i + 1] + A[i];
		}	
		printf("%s",out[bt(0,0)]);
		if(T) puts("");
	}
	return 0;
}
