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

const int MAX = 100000 + 1e2;
int A[MAX],cnt[MAX],cnt2[MAX],n,m;
int blk[MAX],L[MAX],R[MAX],ord[MAX],ans[MAX];
int blkSize;

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	loop(i,m) scanf("%d %d",L + i,R + i),ord[i] = i;	
	
	blkSize = sqrt(n) + 5; blkSize = min(blkSize,n);
	loop(i,m) blk[i] = L[i]/blkSize;
	sort(ord,ord + m,[](const int & a,const int & b){
		return tie(blk[a],R[a]) < tie(blk[b],R[b]);
	});

	for(int blk = 0,i = 0;i < m;blk++){
		int l = 0,r = -1,mx = 0; cnt2[0] = n;
		for(;i < m && ::blk[ord[i]] < blk;i++){
			for(;r < R[ord[i]];r++) {
				cnt2[cnt[A[r+1]]]--;
				cnt[A[r+1]]++;
				cnt2[cnt[A[r+1]]]++;
				if(mx < cnt[A[r+1]]) mx++;
			}
			for(;l < L[ord[i]];l++){
				cnt2[cnt[A[l]]]--;
				cnt[A[l]]--;
				cnt2[cnt[A[l]]]++;
				if(!cnt2[mx]) mx--;
			}
			for(;l > L[ord[i]];l--){
				cnt2[cnt[A[l-1]]]--;
				cnt[A[l-1]]++;
				cnt2[cnt[A[l-1]]]++;
				if(mx < cnt[A[l-1]]) mx++;
			}
			ans[ord[i]] = mx;
		}
		for(;l <= r;l++){
			cnt2[cnt[A[l]]]--;
			cnt[A[l]]--;
			cnt2[cnt[A[l]]]++;	
		}
	}
	loop(i,m) printf("%d\n",ans[i]);
	return 0;
}
