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

const int MAXQ = 500*1000 + 11;
int L[MAXQ],R[MAXQ],ans[MAXQ];
vi Q[MAXQ];
int A[MAXQ],n,m;
map<int,int> lst;
int ST[1 << 20];

void build(int cur,int s,int e) {
	ST[cur] = INT_MAX;
	if(s == e) return;
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
}

void update(int cur,int s,int e,int p,int v) {
	ST[cur] = min(ST[cur],v);
	if(s == e) return;
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
}

int query(int cur,int s,int e,int l,int r) {
	if(l <= s && e <= r)return ST[cur];
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return min(query(left,s,m,l,m),query(right,m+1,e,m+1,r));
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",A + i);
	loop(q,m) {
		scanf("%d %d",L + q,R + q);
		Q[R[q]].push_back(q);
	}
	build(0,1,n);
	for(int i = 1;i <= n;i++){
		int x = A[i];
		if(lst[x]) {
			int j = lst[x];
			int d = i - j;
//			cerr << j << " " << d << endl;
			update(0,1,n,j,d);
		}
		lst[x] = i;
		for(int q : Q[i]) {
			int & v = ans[q];
			v = query(0,1,n,L[q],R[q]);
//			cerr << L[q] << " " << R[q] << " -> " << v << endl;
			if(v == INT_MAX) v = -1;
		}
	}
	loop(q,m) printf("%d\n",ans[q]);
	return 0;
}
