#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
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

int n,k,q;
int A[5000];
ll x;
pl C[5000*21];


int main(){
	scanf("%d %d",&n,&k);
	int idx = 0;
	C[idx++] = mp(0LL,0LL);
	loop(i,n) {
		scanf("%d",A + i);
		range(j,1,k) C[idx++] = mp(A[i]*1LL*j,j);
	}
	sort(C,C + idx);
	int m = idx; idx = 0;	
	loop(i,m){
		int j = i;
		while(j < m && C[i].xx == C[j].xx) j++;
		C[idx++] = C[i];
	}
	m = idx;
	int q;
	scanf("%d",&q); ;
	while(q--){
		scanf("%I64d",&x);
		int ans = 50;
		loop(i,m){
				auto p = lower_bound(C,C + m,mp(x - C[i].xx,0LL)) - C;
				if(p == m) continue;
				if(C[p].xx + C[i].xx == x && C[p].yy + C[i].yy <= k) ans = min(ans + 0LL,C[p].yy + C[i].yy);	
		}
		printf("%d\n",(ans == 50) ? -1 : ans);
	}
	return 0;
}
