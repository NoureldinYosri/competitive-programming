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

const int MAXN = 200*1000 + 10;
int n,m,blk_siz;
int A[MAXN],B[MAXN],C[MAXN],R[MAXN];

inline void fix(int u,int p) {
	int s = u*blk_siz,e = min(s + blk_siz,n);
//	while(p > s && B[p-1] > B[p]) swap(B[p],B[p-1]),p--;
//	while(p+1 < e && B[p+1] < B[p]) swap(B[p],B[p+1]),p++;
	sort(B + s,B + e);
	for(int i = s;i < e;i++)
		R[B[i]] = i;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&m);
	loop(i,n) {
		scanf("%d",A + i);
		A[i]--;
		R[A[i]] = i;
	}
	loop(i,n) {
		scanf("%d",B + i);
		B[i]--;
		B[i] = R[B[i]];
	}
	copy(B,B + n,C);

	blk_siz = sqrt(n) + 0.5;
	for(int s = 0;s < n;) {
		int e = min(s + blk_siz,n);
		sort(B + s,B + e);
		s = e;
	}
	loop(i,n) R[B[i]] = i;

	for(;m > 0;m--){
		int t; scanf("%d",&t);
		if(t == 1) {
			int la,ra,lb,rb;
			scanf("%d %d %d %d",&la,&ra,&lb,&rb);
			la--,ra--,lb--,rb--;
			int ans = 0;
			int u = lb/blk_siz,v = rb/blk_siz;
			if(u == v) {
				for(int i = lb;i <= rb;i++)
					ans += la <= C[i] && C[i] <= ra;
			}
			else {
				for(int i = lb,e = u*blk_siz+blk_siz;i < e;i++)
					ans += la <= C[i] && C[i] <= ra;
				for(int i = v*blk_siz;i <= rb;i++)
					ans += la <= C[i] && C[i] <= ra;
				for(++u;u < v;u++){
					int s = u*blk_siz,e = s + blk_siz;
					ans += upper_bound(B+s,B+e,ra)
							- lower_bound(B+s,B+e,la);
				}
			}
			printf("%d\n",ans);
		}
		else {
			int x,y; scanf("%d %d",&x,&y);
			x--,y--;

			int cx = C[x],cy = C[y];
			int sx = R[cx],sy = R[cy];

			swap(C[x],C[y]);
			swap(B[sx],B[sy]);

			if(sx > sy) swap(sx,sy);
			fix(sx/blk_siz,sx);
			fix(sy/blk_siz,sy);
		}
	}
	return 0;
}
