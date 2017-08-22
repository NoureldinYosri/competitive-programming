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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 1 << 20,MAXLG = 20;
int sparse[2][MAX][MAXLG],lg[MAX];

int A[1 << 20],n;
int couple[MAX];

void build(int sparse[MAX][MAXLG],int t){
	lg[0] = -1;
	loop(i,MAX-1) lg[i + 1] = lg[i] + ((i + 1) == LSOne(i+1));
	loop(i,n) sparse[i][0] = (i%2 == t) ? A[i] : INT_MAX;
	loop(k,MAXLG-1) loop(i,n){
		int j = i + (1 << k);
		if(j >= n) j = i;
		sparse[i][k + 1] = min(sparse[i][k],sparse[j][k]);
	}
}

int RMQ(int a,int b,int sparse[MAX][MAXLG]){
	int l = lg[b - a + 1];
	return min(sparse[a][l],sparse[b - (1 << l) + 1][l]);
}


int get_cutpoint(int l,int r){
	if(l+1==r) return l+1;
	if(A[l + 1] < RMQ(l+3,r,sparse[1 - l%2])) return l+1;
	int s = 0,e = (r - l + 1)/2 - 1;
	int parity = 1 - l%2;
	while(s < e) {
		int m = s + (e - s + 1)/2;
		int pos = l + m*2 + 1;
		if(RMQ(l,r,sparse[parity]) == RMQ(pos,r,sparse[parity])) s = m;
		else e = m - 1;
	}
	return l + s*2 + 1;
}

int get_pivot(int l,int r){
	int s = 0,e = (r - l + 1)/2 - 1;
	while(s < e){
		int m = s + (e - s + 1)/2;
		if(RMQ(l,r,sparse[l%2]) == RMQ(l + 2*m,r,sparse[l%2])) s = m;
		else e = m-1;
	}
	return l + 2*s;
}

struct cmp{
public:
	bool operator () (const pi & a,const pi & b){
		return RMQ(a.xx,a.yy,sparse[a.xx&1]) > RMQ(b.xx,b.yy,sparse[b.xx&1]);
	}
};

deque<int> dq;
PQ<pi,vector<pi>,cmp> pq;

void solve(int s,int e){
//	cerr << s << " " << e << endl;
	int l = e - s + 1;
	assert(l%2 == 0);
	if(l == 0) return ;
	if(l == 2) {
		dq.push_back(A[s]);
		dq.push_back(A[e]);
	}
	else{
		int pivot = get_pivot (s,e);
		int cutpoint = get_cutpoint(pivot,e);
	//	cerr << s << " " << e << " -> " << pivot << " " << cutpoint << endl;
		dq.push_back(A[pivot]);
		dq.push_back(A[cutpoint]);
		if(s != pivot) pq.push(mp(s,pivot-1));
		if(pivot+1 != cutpoint) pq.push(mp(pivot+1,cutpoint-1));
		if(cutpoint != e) pq.push(mp(cutpoint+1,e));
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	build(sparse[1],1);
	build(sparse[0],0);

	pq.push(mp(0,n-1));
	while(!pq.empty()) {
		auto p = pq.top(); pq.pop();
		solve(p.xx,p.yy);
	}
	//print(dq,int);
	loop(i,n) printf("%d%c",dq[i]," \n"[i==n-1]);
	return 0;
}
