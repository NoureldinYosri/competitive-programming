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

const int MAX = 1e5 + 10;
int n,m,blkSize;
int A[MAX];
int L[MAX],R[MAX],ord[MAX],blk[MAX];


void insert(int v){
	auto p = val.lower_bound(v),q;
	if(p != val.end()){
		q = p; 
		if(q != val.begin()){
			q--;
			diff.erase(abs(*p - *q));
			diff.insert(v - *q);
		}
		diff.insert(*p - v);
	}
	else if(!val.empt()){
		--p;
		diff.insert(v - *p);
	}
	ele.insert(v);
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	blkSize = sqrt(n);
	scanf("%d",&m);
	loop(i,m){
		scanf("%d %d",L + i,R + i);
		L[i]--,R[i]--;
		blk[i] = L[i]/blkSize;
		ord[i] = i;
	}
	sort(ord,ord + m,[](const int & a,const int & b){\
		return tie(blk[a],R[a]) < tie(blk[b],R[b]);	
	});
	for(int i = 0,blk = 0;i < m;blk++){
		int l = 0,r = -1;
		multiset<int> val,diff;
		
		for(;i < m && ::blk[ord[i]] == blk;i++){
			for(;r < R[ord[i]];r++) {
				int v = A[r + 1];
				insert(v);
			}			
		}
	}	
	return 0;
}
