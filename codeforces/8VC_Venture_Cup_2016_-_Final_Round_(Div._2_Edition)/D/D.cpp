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

int n;
ll ST[4 << 20][3];
int k,a,b,q;
	
void update(int node,int s,int e,int p,ll v){
	if(s == e){
		ST[node][0] += v;
		ST[node][1] = min(ST[node][0],a + 0LL);
		ST[node][2] = min(ST[node][0],b + 0LL);
		return ;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m + 1,e,p,v);
	loop(i,3) ST[node][i] = ST[left][i] + ST[right][i];
}

void query(int node,int s,int e,int l,int r,ll *ret){
	if(l <= s && e <= r) {
		copy(ST[node],ST[node] + 3,ret);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,ret);
	if(m < l) return query(right,m + 1,e,l,r,ret);
	ll A[3],B[3];
	query(left,s,m,l,m,A);
	query(right,m + 1,e,m + 1,r,B);
	loop(i,3) ret[i] = A[i] + B[i];
}


int main(){
	scanf("%d %d %d %d %d",&n,&k,&a,&b,&q);
	while(q--){
		int x,y,z;
		scanf("%d %d",&x,&y);
		if(x == 1){
			scanf("%d",&z);
			update(1,0,n,y,z);
		}
		else{
			ll ans = 0,ret[3];
			query(1,0,n,0,y - 1,ret);
			ans += ret[2];
			if(y + k <= n) {
				query(1,0,n,y + k,n,ret);
				ans += ret[1];
			}			
			printf("%I64d\n",ans);			
		}
	}
	return 0;
}
