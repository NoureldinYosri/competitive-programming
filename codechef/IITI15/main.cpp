#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
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

const int MAX = 200'000 + 10;
int BIT[MAX],n;
int A[MAX],B[MAX],m;
int L[MAX],R[MAX],blk[MAX],blkSize,ord[MAX];
ll ans[MAX];

void update(int p,int v){
	for(;p <= n;p += LSOne(p))
		BIT[p] += v;
}

int get(int p){
	int ret = 0;
	for(;p;p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i),B[i] = A[i];
	sort(B,B + n);
	m = unique(B,B + n) - B;
	loop(i,n) A[i] = upper_bound(B,B + m,A[i]) - B;
	scanf("%d",&m);
	blkSize = sqrt(n);
	loop(i,m) {
		scanf("%d %d",L + i,R + i);
		L[i]--,R[i] --;
		blk[i] = R[i]/blkSize;
		ord[i] = i;
	}
	sort(ord,ord + m,[](const int & a,const int & b){
		return tie(blk[a],R[a]) < tie(blk[b],R[b]);
	});

	for(int q = 0,blk = 0;q < m;blk++){
		int l = 0,r = -1,L,R;
		ll inv = 0;
		for(;q < m && ::blk[ord[q]] == blk;q++){
			L = ::L[ord[q]];
			R = ::R[ord[q]];
			for(;r < R;r++){
				inv += get(n) - get(A[r + 1]);

				update(A[r + 1],1);
 			}
			for(;l < L;l++){
				inv -= get(A[l] - 1);
				update(A[l],-1);
			}
			for(;l > L;l--){
				inv += get(A[l - 1] - 1);
				update(A[l - 1],1);
			}
			ans[ord[q]] = inv;
		}
		for(;l <= r;l++) update(A[l],-1);
	}
	loop(i,m) printf("%lld\n",ans[i]);
	return 0;
}
