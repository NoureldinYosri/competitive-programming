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

const int MAX = 1e5 + 1e3;
int n,m;
int A[MAX],B[MAX];
int ST[MAX << 2];

void build(int node,int s,int e){
	if(s == e) {
		ST[node] = B[s];
		return;
	}
	ST[node] = -1;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m + 1,e);
}

void push(int node,int s,int e){
	if(s == e || ST[node] == -1) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	ST[left] = ST[node];
	ST[right] = ST[node] + m - s + 1;
	if(s == m) ST[left] = A[ST[left]];
	if(m + 1 == e) ST[right] = A[ST[right]];
	ST[node] = -1;
}

void update(int node,int s,int e,int l,int r,int offset){
	if(l <= s && e <= r){
		ST[node] = offset;
		if(s == e) ST[node] = A[ST[node]];
		return;
	}	
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,offset);
	else if(m < l) update(right,m + 1,e,l,r,offset);
	else{
		update(left,s,m,l,m,offset);
		update(right,m + 1,e,m + 1,r,offset + m + 1 - l);
	}
}

int query(int node,int s,int e,int p){
	if(s == e) return ST[node];
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) return query(left,s,m,p);
	else return query(right,m + 1,e,p);
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	loop(i,n) scanf("%d",B + i);
	build(1,0,n - 1);
	while(m--){
		int t,x,y,k;
		scanf("%d %d",&t,&x); x--;
		if(t == 1){
			scanf("%d %d",&y,&k); y--;
			update(1,0,n - 1,y,y + k - 1,x);
		}
		else printf("%d\n",query(1,0,n - 1,x));
	}	
	return 0;
}
