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

const int MAX = 50000,offset = MAX;
int cnt[MAX + 1],n,m,blkSize;
int A[MAX];
int L[MAX],R[MAX],ord[MAX],blk[MAX];
deque<int> fst[2*MAX + 1],lst[2*MAX + 1];

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) {
		scanf("%d",A + i);
		A[i] += i ? A[i - 1] : 0;
	}
	blkSize = sqrt(n);
	loop(i,m){
		scanf("%d %d",L + i,R + i);
		ord[i] = i;
		blk[i] = L/blkSize;
	}	
	sort(ord,ord + m,[](const int & a,const int & b){
		return tie(blk[a],R[a]) < tie(blk[b],R[b]);
	});
	for(int i = 0,blk = 0;i < m;blk++){
		int l = 0,r = -1,ans = 0;
		fst[offset].pb(l);
		for(;i < m && blk == ::blk[ord[i]];i++){
			for(;r < R[ord[i]];r++) {
				int sum = S[r + 1];
				if(!fst[sum + offset].empty()){
					int len = r + 1 - fst[sum + offset].front();
					cnt[len]++;
					if(ans > len) ans++;
				}
				lst[sum + offset].pb(r+1);
				if(r != -1) lst[S[r] + offset].pb(r+1);
			}
			for(;l < L[ord[i]];l++){
				
			}
		}
	}
	return 0;
}
