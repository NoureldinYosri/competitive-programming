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
int n,m,blkSize;
int A[MAX];
int blk[600][600];
int IDX[600];

void build(){
	blkSize = sqrt(n) + 5;
	int idx = 0;	
	for(int i = 1;i <= n;i++){
		A[i - 1] = i;
		blk[idx][IDX[idx]++] = i;
		if(IDX[idx] == blkSize) idx++;	
	}
}


inline int get_inv(int pos){
	int L = pos/blkSize,ret = 0;
	for(int i = 0;i < L;i++)
		ret += IDX[i] + blk[i] - upper_bound(blk[i],blk[i] + IDX[i],A[pos]);
	for(int i = L + 1,e = (n - 1)/blkSize;i <= e;i++)
		ret += upper_bound(blk[i],blk[i] + IDX[i],A[pos]) - blk[i];
	for(int i = L*blkSize,j = 0;i < n && j < blkSize;i++,j++){
		if(i < pos)	ret += A[i] > A[pos];
		else ret += A[i] < A[pos];
	}
	return ret;
}

inline void update(int x,int v){
	int u = x/blkSize,o = A[x],pos = -1;
	for(int i = 0,L = IDX[u];i < L;i++)
		if(blk[u][i] == o){
			blk[u][i] = v;
			pos = i;
			break;
		}
	A[x] = v;
	assert(pos != -1);
	while(pos > 0 && blk[u][pos - 1] > blk[u][pos]){
		swap(blk[u][pos - 1],blk[u][pos]);
		pos--;
	}
	while(pos < IDX[u] - 1 && blk[u][pos] > blk[u][pos + 1]){
		swap(blk[u][pos + 1],blk[u][pos]);
		pos++;
	}
}

int main(){
	scanf("%d %d",&n,&m);		
	build();
	ll inv = 0;
	while(m--){
		int x,y; scanf("%d %d",&x,&y); x--,y--;
		if(x != y){
			if(x > y) swap(x,y);
			inv -= get_inv(x) + get_inv(y) - (A[x] > A[y]);
			int ox = A[x],oy = A[y];			
			update(x,oy);
			update(y,ox);
			inv += get_inv(x) + get_inv(y) - (A[x] > A[y]);
		}
		printf("%lld\n",inv); 
	}
	return 0;
}
