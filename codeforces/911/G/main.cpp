#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
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
using namespace std;

const int MAXST = 2 << 18,MAXA = 100,MAXN = 200*1000;
int ST[MAXST][MAXA];
int A[MAXN],n;

void build(int cur,int s,int e) {
	loop(i,MAXA) ST[cur][i] = i;
	if(s == e) return;
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
}

void update(int *P,int x,int y) {
	loop(i,MAXA) if(P[i] == x) P[i] = y;
}


void push(int cur) {
	int left = 2*cur + 1,right = left + 1;
	loop(i,MAXA){
		ST[left][i] = ST[cur][ST[left][i]];
		ST[right][i] = ST[cur][ST[right][i]];
	}
	loop(i,MAXA) ST[cur][i] = i;
}

void update(int cur,int s,int e,int l,int r,int x,int y) {
	if(l <= s && e <= r) return update(ST[cur],x,y);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	push(cur);
	if(r <= m) update(left,s,m,l,r,x,y);
	else if(m < l) update(right,m+1,e,l,r,x,y);
	else{
		update(left,s,m,l,m,x,y);
		update(right,m+1,e,m+1,r,x,y);
	}
}

int query(int cur,int s,int e,int p) {
	if(s == e) return ST[cur][A[p]];
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	int x = -1;
	if(p <= m) x = query(left,s,m,p);
	else x = query(right,m+1,e,p);
	assert(x != -1);
	x = ST[cur][x];
	return x;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		A[i]--;
	}
	build(0,0,n-1);
	int m; scanf("%d",&m);
	while(m--) {
		int l,r,x,y;
		scanf("%d %d %d %d",&l,&r,&x,&y);
		l--,r--;
		x--,y--;
		update(0,0,n-1,l,r,x,y);
	}
	loop(i,n) printf("%d%c",query(0,0,n-1,i)+1," \n"[i==n-1]);
	return 0;
}
