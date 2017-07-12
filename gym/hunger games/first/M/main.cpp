#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 200*1000 + 10;
int A[MAX],B[MAX],ST[2][MAX << 2];

void build(int node,int s,int e){
	if(s == e){
		ST[0][node] = A[s];
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[0][node] = max(ST[0][left],ST[0][right]);
}

void update(int node,int s,int e,int p,int v){
	if(s == e){
		ST[1][node] = v;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
	ST[1][node] = max(ST[1][left],ST[1][right]);
}

int query(int node,int s,int e,int l,int r,int *ST){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,ST);
	if(m < l) return query(right,m+1,e,l,r,ST);
	return max(query(left,s,m,l,m,ST),query(right,m+1,e,m+1,r,ST));
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	int n,m; scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d ",A + i);
	build(1,0,n-1);
	loop(i,m){
		int t,l,r; scanf("%d %d %d",&t,&l,&r);
		l--,r--;
		t = (t == 1) ? 0 : 1;
		int L = t ? m : n;
		int g = query(1,0,L - 1,l,r,ST[t]);
		update(1,0,m-1,i,g);
		printf("%d\n",g);
	}
	return 0;
}
