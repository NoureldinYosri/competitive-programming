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

const int MAX = 300000;
int N,C,M;
pi ST[MAX << 2];
int A[MAX];
vi pos[MAX];

pi merge(pi a,pi b){
	if(a.xx == b.xx) return mp(a.xx,a.yy + b.yy);
	if(a.yy > b.yy) return mp(a.xx,a.yy - b.yy);
	else return mp(b.xx,b.yy - a.yy);
}

void build(int node,int s,int e){
	if(s == e){
		ST[node] = mp(A[s],1);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m + 1,e);
	ST[node] = merge(ST[left],ST[right]);
}

pi query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	else if(m < l) return query(right,m + 1,e,l,r);
	else return merge(query(left,s,m,l,m),query(right,m + 1,e,m + 1,r));
}

int main(){
	scanf("%d %d",&N,&C);
	loop(i,N) {
		scanf("%d",A + i);
		pos[A[i]].pb(i);
	}
	build(1,0,N - 1);
	scanf("%d",&M);
	loop(i,M){
		int l,r; scanf("%d %d",&l,&r); l--,r--;
		int color = query(1,0,N - 1,l,r).xx;
		int ctr = upper_bound(all(pos[color]),r) - lower_bound(all(pos[color]),l);
		int t = (r - l + 1)/2;		
		if(ctr > t) printf("yes %d\n",color);
		else puts("no");
	}				
	return 0;
}
